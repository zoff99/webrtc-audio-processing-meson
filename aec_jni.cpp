
#include <jni.h>
#include <string>
#include <stdint.h>
#include <sys/types.h>

#include <android/log.h>

#include "webrtc/modules/audio_processing/audio_processing_impl.h"


const char *LOGTAG = "trifa.aec";

struct webrtc_aec *aec_context;

uint8_t *audio_buffer[1];
long audio_buffer_size[1];
int audio_buffer_offset[1];
uint8_t *audio_rec_buffer[1];
long audio_rec_buffer_size[1];
int audio_rec_buffer_offset[1];
int audio_delay_in_ms = 0;


// -----------------------------------
// -----------------------------------

using namespace webrtc;

struct webrtc_aec {
  AudioProcessing* proc{};
};

using AudioProcessingContext = webrtc_aec; // More C++-like name

namespace {

auto CreateApm(bool mobile_aec, int channels, int samplingfreq, int channels_rec, int samplingfreq_rec) -> AudioProcessing* {

    Config old_config;

    auto apm = AudioProcessingBuilder().Create(old_config);
    if (!apm) {
        return apm;
    }

/*
 const ProcessingConfig processing_config = {
      {{input_sample_rate_hz,
        ChannelsFromLayout(input_layout),
       {output_sample_rate_hz,
        ChannelsFromLayout(output_layout),
       {reverse_sample_rate_hz,
        ChannelsFromLayout(reverse_layout),
       {reverse_sample_rate_hz,
        ChannelsFromLayout(reverse_layout),
        }}};
*/

    ProcessingConfig processing_config = {
        {{samplingfreq_rec, static_cast<size_t>(channels_rec)},
         {samplingfreq_rec, static_cast<size_t>(channels_rec)},
         {samplingfreq, static_cast<size_t>(channels)},
         {samplingfreq, static_cast<size_t>(channels)}}};

    if (apm->Initialize(processing_config) != 0) {
        return nullptr;
    }

    // Disable all components except for an AEC and the residual echo detector.
    AudioProcessing::Config apm_config;
    apm_config.residual_echo_detector.enabled = true;
    apm_config.high_pass_filter.enabled = false;
    apm_config.gain_controller1.enabled = false;
    apm_config.gain_controller2.enabled = false;
    apm_config.echo_canceller.enabled = true;
    apm_config.echo_canceller.mobile_mode = mobile_aec;
    apm_config.noise_suppression.enabled = false;
    apm_config.level_estimation.enabled = false;
    apm_config.voice_detection.enabled = false;
    apm->ApplyConfig(apm_config);

    return apm;
}



void SetFrameSampleRate(AudioFrame* frame, int sample_rate_hz) {
  frame->sample_rate_hz_ = sample_rate_hz;
  frame->samples_per_channel_ =
      AudioProcessing::kChunkSizeMs * sample_rate_hz / 1000;
}


void AudioPlay(AudioProcessing* apm) {
    using webrtc::AudioFrame;
    using webrtc::AudioProcessingStats;

    // Set up audioframe
    AudioFrame frame;
    frame.num_channels_ = 1;
    SetFrameSampleRate(&frame, AudioProcessing::NativeRate::kSampleRate16kHz);

    int16_t* ptr = frame.mutable_data();
    for (size_t i = 0; i < frame.kMaxDataSizeSamples; i++) {
        ptr[i] = audio_buffer[0][i];
#if 0
        if (i < 8)
        {
            __android_log_print(ANDROID_LOG_INFO, LOGTAG, "c_play: i=%d b=%d", static_cast<int>(i), static_cast<int>(audio_buffer[0][i]));
        }
#endif
    }

    apm->ProcessReverseStream(&frame);
}

void AudioRecord(AudioProcessing* apm) {
    using webrtc::AudioFrame;
    using webrtc::AudioProcessingStats;

    // Set up audioframe
    AudioFrame frame;
    frame.num_channels_ = 1;
    SetFrameSampleRate(&frame, AudioProcessing::NativeRate::kSampleRate16kHz);

    int16_t* ptr = frame.mutable_data();
    for (size_t i = 0; i < frame.kMaxDataSizeSamples; i++) {
        ptr[i] = audio_rec_buffer[0][i];
#if 0
        if (i < 8)
        {
            __android_log_print(ANDROID_LOG_INFO, LOGTAG, "c_rec: i=%d b=%d", static_cast<int>(i), static_cast<int>(audio_rec_buffer[0][i]));
        }
#endif
    }

    apm->set_stream_delay_ms(audio_delay_in_ms);
    apm->ProcessStream(&frame);
}

} // end namespace

// -----------------------------------
// -----------------------------------


#ifdef __cplusplus
extern "C" {
#endif


// ----- function defs ------


void
Java_com_zoffcc_applications_nativeaudio_AudioProcessing_set_1JNI_1audio_1rec_1buffer(JNIEnv *env,
                                                                                  jobject obj,
                                                                                  jobject buffer,
                                                                                  jlong buffer_size_in_bytes,
                                                                                  jint num,
                                                                                  jint buffer_offset)
{
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "set_audio_rec_buffer");

    audio_rec_buffer[num] = (uint8_t *) (*env).GetDirectBufferAddress(buffer);
    jlong capacity = buffer_size_in_bytes;
    audio_rec_buffer_size[num] = (long) capacity;
    audio_rec_buffer_offset[num] = buffer_offset;
}

void Java_com_zoffcc_applications_nativeaudio_AudioProcessing_set_1JNI_1audio_1buffer(JNIEnv *env,
                                                                                  jobject obj,
                                                                                  jobject buffer,
                                                                                  jlong buffer_size_in_bytes,
                                                                                  jint num,
                                                                                  jint buffer_offset)
{
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "set_audio_buffer");

    audio_buffer[num] = (uint8_t *) (*env).GetDirectBufferAddress(buffer);
    jlong capacity = buffer_size_in_bytes;
    audio_buffer_size[num] = (long) capacity;
    audio_buffer_offset[num] = buffer_offset;
}

void Java_com_zoffcc_applications_nativeaudio_AudioProcessing_init(JNIEnv * env, jobject obj,
                                                                   jint channels, jint samplingfreq,
                                                                   jint channels_rec, jint samplingfreq_rec)
{
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "init:%d %d %d %d", channels, samplingfreq, channels_rec, samplingfreq_rec);

	const bool use_mobile_aec = false;

	auto context = new AudioProcessingContext;
	aec_context = context;

	context->proc = ::CreateApm(use_mobile_aec, channels, samplingfreq, channels_rec, samplingfreq_rec);

    if (context->proc == nullptr)
    {
        __android_log_print(ANDROID_LOG_INFO, LOGTAG, "init:CreateApm:ERROR:NULL");
    }
    else
    {
        __android_log_print(ANDROID_LOG_INFO, LOGTAG, "init:CreateApm:%p", context->proc);
    }

}

void Java_com_zoffcc_applications_nativeaudio_AudioProcessing_set_1audio_1delay(JNIEnv * env, jobject obj,
                                                                   jint delay_ms)
{
    audio_delay_in_ms = delay_ms;
}

void Java_com_zoffcc_applications_nativeaudio_AudioProcessing_play(JNIEnv * env, jobject obj)
{
    auto context = static_cast<AudioProcessingContext*>(aec_context);
    ::AudioPlay(context->proc);
}

void Java_com_zoffcc_applications_nativeaudio_AudioProcessing_record(JNIEnv * env, jobject obj)
{
    auto context = static_cast<AudioProcessingContext*>(aec_context);
    ::AudioRecord(context->proc);
}

void Java_com_zoffcc_applications_nativeaudio_AudioProcessing_destroy(JNIEnv * env, jobject obj)
{
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "destroy");

    auto context = static_cast<AudioProcessingContext*>(aec_context);
    context->proc->Release();
    delete context;
}


#ifdef __cplusplus
}
#endif

