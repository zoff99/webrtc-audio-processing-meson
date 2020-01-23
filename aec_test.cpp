
#include <jni.h>
#include <string>

#include "webrtc/modules/audio_processing/audio_processing_impl.h"


extern "C" {

JNIEXPORT void JNICALL Java_com_example_hellojni_HelloJni_stringFromJNI( JNIEnv * env, jobject obj )
{
    webrtc::Config config;
    auto aec_processor = webrtc::AudioProcessingBuilder().Create();
}

}

