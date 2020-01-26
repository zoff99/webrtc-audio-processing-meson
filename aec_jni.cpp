
#include <jni.h>
#include <string>
#include <stdint.h>
#include <sys/types.h>

#include <android/log.h>

#include "webrtc/modules/audio_processing/audio_processing_impl.h"


const char *LOGTAG = "trifa.aec";

struct webrtc_aec *aec_context;

int16_t *audio_buffer[1];
long audio_buffer_size[1];
int audio_buffer_offset[1];
int16_t *audio_rec_buffer[1];
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
        __android_log_print(ANDROID_LOG_INFO, LOGTAG, "CreateApm:Create:error");
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
        __android_log_print(ANDROID_LOG_INFO, LOGTAG, "CreateApm:Initialize:error");
        return nullptr;
    }

    // Disable all components except for an AEC and the residual echo detector.
    AudioProcessing::Config apm_config;
    apm_config.residual_echo_detector.enabled = true;
    apm_config.high_pass_filter.enabled = true;
    apm_config.gain_controller1.enabled = true;
    apm_config.gain_controller2.enabled = true;
    apm_config.echo_canceller.enabled = true;
    apm_config.echo_canceller.mobile_mode = mobile_aec;
    apm_config.noise_suppression.enabled = true;
    apm_config.level_estimation.enabled = true;
    apm_config.voice_detection.enabled = true;
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

    int apm_return_code = 0;

    // Set up audioframe
    AudioFrame frame;
    frame.num_channels_ = 1;
    SetFrameSampleRate(&frame, AudioProcessing::NativeRate::kSampleRate16kHz);

    int16_t* ptr = frame.mutable_data();
    for (size_t i = 0; i < 160; i++) {
        ptr[i] = audio_buffer[0][i];
    }

    apm_return_code = apm->ProcessReverseStream(&frame);
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioPlay:res=%d", apm_return_code);
}

void AudioRecord(AudioProcessing* apm) {
    using webrtc::AudioFrame;
    using webrtc::AudioProcessingStats;

    int apm_return_code = 0;

    // Set up audioframe
    AudioFrame frame;
    frame.num_channels_ = 1;
    SetFrameSampleRate(&frame, AudioProcessing::NativeRate::kSampleRate16kHz);

    int16_t* ptr = frame.mutable_data();
    for (size_t i = 0; i < 160; i++) {
        ptr[i] = audio_rec_buffer[0][i];
    }

    apm_return_code = apm->set_stream_delay_ms(audio_delay_in_ms);
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:set_stream_delay_ms:res=%d", apm_return_code);
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:set_stream_delay_ms:value=%d", audio_delay_in_ms);

    apm_return_code = apm->ProcessStream(&frame);
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:res=%d", apm_return_code);

    int num_changed = 0;

    for (size_t i = 0; i < 160; i++) {
        if (audio_rec_buffer[0][i] != ptr[i])
        {
            num_changed++;
        }
        audio_rec_buffer[0][i] = ptr[i];
    }
    
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:num_changed=%d", num_changed);

    AudioProcessingStats stats = apm->GetStatistics();
    if (stats.delay_median_ms.has_value())
    {
        int32_t median = *stats.delay_median_ms;
        __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:stats.delay_median_ms=%d", median);
    }

    if (stats.delay_standard_deviation_ms.has_value())
    {
        int32_t delay_standard_deviation_ms = *stats.delay_standard_deviation_ms;
        __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:stats.delay_standard_deviation_ms=%d", delay_standard_deviation_ms);
    }

    if (stats.delay_ms.has_value())
    {
        int32_t delay_ms = *stats.delay_ms;
        __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:stats.delay_ms=%d", delay_ms);
    }

    if (stats.output_rms_dbfs.has_value())
    {
        int output_rms_dbfs = *stats.output_rms_dbfs;
        __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:stats.output_rms_dbfs=%d", output_rms_dbfs);
    }

    const float echo_return_loss = stats.echo_return_loss.value_or(-1.0f);
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:stats.echo_return_loss=%f", echo_return_loss);
    const float echo_return_loss_enhancement =
        stats.echo_return_loss_enhancement.value_or(-1.0f);
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:stats.echo_return_loss_enhancement=%f", echo_return_loss_enhancement);
    const float divergent_filter_fraction =
        stats.divergent_filter_fraction.value_or(-1.0f);
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:stats.divergent_filter_fraction=%f", divergent_filter_fraction);
    const float residual_echo_likelihood =
        stats.residual_echo_likelihood.value_or(-1.0f);
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:stats.residual_echo_likelihood=%f", residual_echo_likelihood);
    const float residual_echo_likelihood_recent_max =
        stats.residual_echo_likelihood_recent_max.value_or(-1.0f);
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "AudioRecord:stats.residual_echo_likelihood_recent_max=%f", residual_echo_likelihood_recent_max);
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

    audio_rec_buffer[num] = (int16_t *) (*env).GetDirectBufferAddress(buffer);
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

    audio_buffer[num] = (int16_t *) (*env).GetDirectBufferAddress(buffer);
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

