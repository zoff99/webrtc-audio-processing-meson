#include "webrtc/modules/audio_processing/audio_processing_impl.h"

int main() {
    webrtc::Config config;
    auto aec_processor = webrtc::AudioProcessingBuilder().Create();
}
