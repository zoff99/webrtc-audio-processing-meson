
#include <jni.h>
#include <string>
#include <sys/types.h>

#include <android/log.h>

#include "webrtc/modules/audio_processing/audio_processing_impl.h"


#ifdef __cplusplus
extern "C" {
#endif

const char *LOGTAG = "trifa.aec";

uint8_t *audio_buffer[1];
long audio_buffer_size[1];
uint8_t *audio_rec_buffer[1];
long audio_rec_buffer_size[1];


// ----- function defs ------


void
Java_com_zoffcc_applications_nativeaudio_NativeAudio_set_1JNI_1audio_1rec_1buffer(JNIEnv *env,
                                                                                  jobject obj,
                                                                                  jobject buffer,
                                                                                  jlong buffer_size_in_bytes,
                                                                                  jint num)
{
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "set_audio_rec_buffer");

    audio_rec_buffer[num] = (uint8_t *) (*env).GetDirectBufferAddress(buffer);
    jlong capacity = buffer_size_in_bytes;
    audio_rec_buffer_size[num] = (long) capacity;
}

void Java_com_zoffcc_applications_nativeaudio_AudioProcessing_set_1JNI_1audio_1buffer(JNIEnv *env,
                                                                                  jobject obj,
                                                                                  jobject buffer,
                                                                                  jlong buffer_size_in_bytes,
                                                                                  jint num)
{
    audio_buffer[num] = (uint8_t *) (*env).GetDirectBufferAddress(buffer);
    jlong capacity = buffer_size_in_bytes;
    audio_buffer_size[num] = (long) capacity;
}

void Java_com_zoffcc_applications_nativeaudio_AudioProcessing_init(JNIEnv * env, jobject obj)
{
    __android_log_print(ANDROID_LOG_INFO, LOGTAG, "init");

    webrtc::Config config;
    auto aec_processor = webrtc::AudioProcessingBuilder().Create();
}



#ifdef __cplusplus
}
#endif

