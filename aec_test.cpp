#include <cassert>

#include "webrtc/modules/audio_processing/audio_processing_impl.h"


using webrtc::AudioFrame;

using webrtc::AudioProcessing;
using webrtc::AudioProcessingBuilder;
using webrtc::ProcessingConfig;

std::unique_ptr<AudioProcessing> CreateApm(bool mobile_aec) {
    using webrtc::Config;

  Config old_config;
  std::unique_ptr<AudioProcessing> apm(
      AudioProcessingBuilder().Create(old_config));
  if (!apm) {
    return apm;
  }

  ProcessingConfig processing_config = {
      {{32000, 1}, {32000, 1}, {32000, 1}, {32000, 1}}};

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


// mock googletest ;DDD
#define EXPECT_EQ(a, b) assert((a) == (b));
#define EXPECT_GE(a, b) assert((a) >= (b));
#define EXPECT_LE(a, b) assert((a) <= (b));
#define EXPECT_NE(a, b) assert((a) != (b));

#define ASSERT_TRUE assert
#define ASSERT_GE(a, b) assert((a) >= (b));
#define ASSERT_LE(a, b) assert((a) <= (b));

int main() {
    using webrtc::AudioFrame;
    using webrtc::AudioProcessingStats;


    // Set up APM with AEC3 and process some audio.
    std::unique_ptr<AudioProcessing> apm = CreateApm(false);
    assert(apm);
    AudioProcessing::Config apm_config;
    apm_config.echo_canceller.enabled = true;
    apm->ApplyConfig(apm_config);

    // Set up an audioframe.
    AudioFrame frame;
    frame.num_channels_ = 1;
    SetFrameSampleRate(&frame, AudioProcessing::NativeRate::kSampleRate32kHz);

    // Fill the audio frame with a sawtooth pattern.
    int16_t* ptr = frame.mutable_data();
    for (size_t i = 0; i < frame.kMaxDataSizeSamples; i++) {
        ptr[i] = 10000 * ((i % 3) - 1);
    }

    // Do some processing.
    for (int i = 0; i < 200; i++) {
        EXPECT_EQ(apm->ProcessReverseStream(&frame), 0);
        EXPECT_EQ(apm->set_stream_delay_ms(0), 0);
        EXPECT_EQ(apm->ProcessStream(&frame), 0);
    }

    // Test statistics interface.
    AudioProcessingStats stats = apm->GetStatistics();
    // We expect all statistics to be set and have a sensible value.
    ASSERT_TRUE(stats.residual_echo_likelihood);
    EXPECT_GE(*stats.residual_echo_likelihood, 0.0);
    EXPECT_LE(*stats.residual_echo_likelihood, 1.0);
    ASSERT_TRUE(stats.residual_echo_likelihood_recent_max);
    EXPECT_GE(*stats.residual_echo_likelihood_recent_max, 0.0);
    EXPECT_LE(*stats.residual_echo_likelihood_recent_max, 1.0);
    ASSERT_TRUE(stats.echo_return_loss);
    EXPECT_NE(*stats.echo_return_loss, -100.0);
    ASSERT_TRUE(stats.echo_return_loss_enhancement);
    EXPECT_NE(*stats.echo_return_loss_enhancement, -100.0);
}
