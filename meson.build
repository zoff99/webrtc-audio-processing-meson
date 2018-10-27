project('webrtc-audio-processing-example', ['c', 'cpp'])

inc_common = include_directories(
    'webrtc',
    'abseil-cpp',
    'chromium')

add_project_arguments(
    '-DWEBRTC_POSIX',
    '-DWEBRTC_LINUX',
    '-DWEBRTC_APM_DEBUG_DUMP=0',
    '-DWEBRTC_NS_FLOAT',
    
    '-DWEBRTC_USE_BUILTIN_ISAC_FLOAT',
    
    language: ['cpp', 'c']
)

libaudio_processing_files = files(
    'webrtc/modules/audio_processing/audio_processing_impl.cc',
    'webrtc/modules/audio_processing/audio_processing_impl.h',
    
    'webrtc/modules/audio_processing/aec/aec_resampler.cc',
    'webrtc/modules/audio_processing/aec/aec_resampler.h',
    'webrtc/modules/audio_processing/aec/echo_cancellation.cc',
    'webrtc/modules/audio_processing/aec/echo_cancellation.h',
    'webrtc/modules/audio_processing/agc/agc.cc',
    'webrtc/modules/audio_processing/agc/agc.h',
    'webrtc/modules/audio_processing/agc/agc_manager_direct.cc',
    'webrtc/modules/audio_processing/agc/agc_manager_direct.h',
    'webrtc/modules/audio_processing/agc/gain_map_internal.h',
    'webrtc/modules/audio_processing/agc/loudness_histogram.cc',
    'webrtc/modules/audio_processing/agc/loudness_histogram.h',
    'webrtc/modules/audio_processing/agc/utility.cc',
    'webrtc/modules/audio_processing/agc/utility.h',
    'webrtc/modules/audio_processing/audio_buffer.cc',
    'webrtc/modules/audio_processing/audio_buffer.h',
    'webrtc/modules/audio_processing/audio_processing_impl.cc',
    'webrtc/modules/audio_processing/audio_processing_impl.h',
    'webrtc/modules/audio_processing/common.h',
    'webrtc/modules/audio_processing/echo_cancellation_impl.cc',
    'webrtc/modules/audio_processing/echo_cancellation_impl.h',
    'webrtc/modules/audio_processing/echo_control_mobile_impl.cc',
    'webrtc/modules/audio_processing/echo_control_mobile_impl.h',
    'webrtc/modules/audio_processing/echo_detector/circular_buffer.cc',
    'webrtc/modules/audio_processing/echo_detector/circular_buffer.h',
    'webrtc/modules/audio_processing/echo_detector/mean_variance_estimator.cc',
    'webrtc/modules/audio_processing/echo_detector/mean_variance_estimator.h',
    'webrtc/modules/audio_processing/echo_detector/moving_max.cc',
    'webrtc/modules/audio_processing/echo_detector/moving_max.h',
    'webrtc/modules/audio_processing/echo_detector/normalized_covariance_estimator.cc',
    'webrtc/modules/audio_processing/echo_detector/normalized_covariance_estimator.h',
    'webrtc/modules/audio_processing/gain_control_for_experimental_agc.cc',
    'webrtc/modules/audio_processing/gain_control_for_experimental_agc.h',
    'webrtc/modules/audio_processing/gain_control_impl.cc',
    'webrtc/modules/audio_processing/gain_control_impl.h',
    'webrtc/modules/audio_processing/gain_controller2.cc',
    'webrtc/modules/audio_processing/gain_controller2.h',
    'webrtc/modules/audio_processing/include/audio_processing.cc',
    'webrtc/modules/audio_processing/include/audio_processing.h',
    'webrtc/modules/audio_processing/include/config.cc',
    'webrtc/modules/audio_processing/include/config.h',
    'webrtc/modules/audio_processing/level_estimator_impl.cc',
    'webrtc/modules/audio_processing/level_estimator_impl.h',
    'webrtc/modules/audio_processing/low_cut_filter.cc',
    'webrtc/modules/audio_processing/low_cut_filter.h',
    'webrtc/modules/audio_processing/noise_suppression_impl.cc',
    'webrtc/modules/audio_processing/noise_suppression_impl.h',
    'webrtc/modules/audio_processing/render_queue_item_verifier.h',
    'webrtc/modules/audio_processing/residual_echo_detector.cc',
    'webrtc/modules/audio_processing/residual_echo_detector.h',
    'webrtc/modules/audio_processing/rms_level.cc',
    'webrtc/modules/audio_processing/rms_level.h',
    'webrtc/modules/audio_processing/splitting_filter.cc',
    'webrtc/modules/audio_processing/splitting_filter.h',
    'webrtc/modules/audio_processing/three_band_filter_bank.cc',
    'webrtc/modules/audio_processing/three_band_filter_bank.h',
    'webrtc/modules/audio_processing/transient/common.h',
    'webrtc/modules/audio_processing/transient/daubechies_8_wavelet_coeffs.h',
    'webrtc/modules/audio_processing/transient/dyadic_decimator.h',
    'webrtc/modules/audio_processing/transient/moving_moments.cc',
    'webrtc/modules/audio_processing/transient/moving_moments.h',
    'webrtc/modules/audio_processing/transient/transient_detector.cc',
    'webrtc/modules/audio_processing/transient/transient_detector.h',
    'webrtc/modules/audio_processing/transient/transient_suppressor.cc',
    'webrtc/modules/audio_processing/transient/transient_suppressor.h',
    'webrtc/modules/audio_processing/transient/wpd_node.cc',
    'webrtc/modules/audio_processing/transient/wpd_node.h',
    'webrtc/modules/audio_processing/transient/wpd_tree.cc',
    'webrtc/modules/audio_processing/transient/wpd_tree.h',
    'webrtc/modules/audio_processing/typing_detection.cc',
    'webrtc/modules/audio_processing/typing_detection.h',
    'webrtc/modules/audio_processing/voice_detection_impl.cc',
    'webrtc/modules/audio_processing/voice_detection_impl.h',
)

# C files
libaudio_processing_files += files(
    'webrtc/modules/audio_processing/agc/legacy/analog_agc.c',
    'webrtc/modules/audio_processing/agc/legacy/analog_agc.h',
    'webrtc/modules/audio_processing/agc/legacy/digital_agc.c',
    'webrtc/modules/audio_processing/agc/legacy/digital_agc.h',
    'webrtc/modules/audio_processing/agc/legacy/gain_control.h',
    'webrtc/modules/audio_processing/ns/defines.h',
    'webrtc/modules/audio_processing/ns/noise_suppression.c',
    'webrtc/modules/audio_processing/ns/noise_suppression.h',
    'webrtc/modules/audio_processing/ns/ns_core.c',
    'webrtc/modules/audio_processing/ns/ns_core.h',
    'webrtc/modules/audio_processing/ns/windows_private.h',
)

libaudio_processing_files += files(
    'webrtc/modules/audio_processing/logging/apm_data_dumper.cc',
    'webrtc/modules/audio_processing/logging/apm_data_dumper.h',

    # aec_core
    'webrtc/modules/audio_processing/aec/aec_common.h',
    'webrtc/modules/audio_processing/aec/aec_core.cc',
    'webrtc/modules/audio_processing/aec/aec_core.h',
    'webrtc/modules/audio_processing/aec/aec_core_optimized_methods.h',
    'webrtc/modules/audio_processing/aecm/aecm_core.cc',
    'webrtc/modules/audio_processing/aecm/aecm_core.h',
    'webrtc/modules/audio_processing/aecm/aecm_defines.h',
    'webrtc/modules/audio_processing/aecm/echo_control_mobile.cc',
    'webrtc/modules/audio_processing/aecm/echo_control_mobile.h',
    'webrtc/modules/audio_processing/utility/block_mean_calculator.cc',
    'webrtc/modules/audio_processing/utility/block_mean_calculator.h',
    'webrtc/modules/audio_processing/utility/delay_estimator.cc',
    'webrtc/modules/audio_processing/utility/delay_estimator.h',
    'webrtc/modules/audio_processing/utility/delay_estimator_internal.h',
    'webrtc/modules/audio_processing/utility/delay_estimator_wrapper.cc',
    'webrtc/modules/audio_processing/utility/delay_estimator_wrapper.h',
    'webrtc/modules/audio_processing/utility/ooura_fft.cc',
    'webrtc/modules/audio_processing/utility/ooura_fft.h',
    'webrtc/modules/audio_processing/utility/ooura_fft_tables_common.h',

    # aec_dump
    'webrtc/modules/audio_processing/include/aec_dump.cc',
    'webrtc/modules/audio_processing/include/aec_dump.h',

    # audio_processing_statistics
    'webrtc/modules/audio_processing/include/audio_processing_statistics.cc',
    'webrtc/modules/audio_processing/include/audio_processing_statistics.h',
)

# stuff in webrtc/modules/audio_processing/agc2 (originally has own build file)
libaudio_processing_files += files(
    'webrtc/modules/audio_processing/agc2/agc2_common.cc',
    'webrtc/modules/audio_processing/agc2/agc2_common.h',
    'webrtc/modules/audio_processing/agc2/adaptive_mode_level_estimator_agc.cc',
    'webrtc/modules/audio_processing/agc2/adaptive_mode_level_estimator_agc.h',
    'webrtc/modules/audio_processing/agc2/vad_with_level.cc',
    'webrtc/modules/audio_processing/agc2/vad_with_level.h',
    'webrtc/modules/audio_processing/agc2/fixed_digital_level_estimator.cc',
    'webrtc/modules/audio_processing/agc2/fixed_digital_level_estimator.h',
    'webrtc/modules/audio_processing/agc2/fixed_gain_controller.cc',
    'webrtc/modules/audio_processing/agc2/fixed_gain_controller.h',
    'webrtc/modules/audio_processing/agc2/gain_curve_applier.cc',
    'webrtc/modules/audio_processing/agc2/gain_curve_applier.h',
    'webrtc/modules/audio_processing/agc2/interpolated_gain_curve.cc',
    'webrtc/modules/audio_processing/agc2/interpolated_gain_curve.h',
    'webrtc/modules/audio_processing/agc2/gain_applier.cc',
    'webrtc/modules/audio_processing/agc2/gain_applier.h',

    #webrtc/modules/audio_processing/agc2/rnn_vad/',
    'webrtc/modules/audio_processing/agc2/rnn_vad/rnn.cc',
    'webrtc/modules/audio_processing/agc2/rnn_vad/rnn.h',
    'webrtc/modules/audio_processing/agc2/rnn_vad/spectral_features.cc',
    'webrtc/modules/audio_processing/agc2/rnn_vad/spectral_features.h',
    'webrtc/modules/audio_processing/agc2/rnn_vad/features_extraction.cc',
    'webrtc/modules/audio_processing/agc2/rnn_vad/features_extraction.h',
    'webrtc/modules/audio_processing/agc2/rnn_vad/spectral_features_internal.cc',
    'webrtc/modules/audio_processing/agc2/rnn_vad/spectral_features_internal.h',
    'webrtc/modules/audio_processing/agc2/rnn_vad/fft_util.cc',
    'webrtc/modules/audio_processing/agc2/rnn_vad/fft_util.h',
    'webrtc/modules/audio_processing/agc2/rnn_vad/pitch_search.cc',
    'webrtc/modules/audio_processing/agc2/rnn_vad/pitch_search.h',
    'webrtc/modules/audio_processing/agc2/rnn_vad/pitch_search_internal.cc',
    'webrtc/modules/audio_processing/agc2/rnn_vad/pitch_search_internal.h',
    'webrtc/modules/audio_processing/agc2/rnn_vad/lp_residual.cc',
    'webrtc/modules/audio_processing/agc2/rnn_vad/lp_residual.h',
    

    # adaptive_digital
    'webrtc/modules/audio_processing/agc2/adaptive_agc.cc',
    'webrtc/modules/audio_processing/agc2/adaptive_agc.h',
    'webrtc/modules/audio_processing/agc2/adaptive_digital_gain_applier.cc',
    'webrtc/modules/audio_processing/agc2/adaptive_digital_gain_applier.h',
    'webrtc/modules/audio_processing/agc2/adaptive_mode_level_estimator.cc',
    'webrtc/modules/audio_processing/agc2/adaptive_mode_level_estimator.h',
    'webrtc/modules/audio_processing/agc2/saturation_protector.cc',
    'webrtc/modules/audio_processing/agc2/saturation_protector.h',

    # noise_level_estimator
    'webrtc/modules/audio_processing/agc2/biquad_filter.cc',
    'webrtc/modules/audio_processing/agc2/biquad_filter.h',
    'webrtc/modules/audio_processing/agc2/down_sampler.cc',
    'webrtc/modules/audio_processing/agc2/down_sampler.h',
    'webrtc/modules/audio_processing/agc2/noise_level_estimator.cc',
    'webrtc/modules/audio_processing/agc2/noise_level_estimator.h',
    'webrtc/modules/audio_processing/agc2/noise_spectrum_estimator.cc',
    'webrtc/modules/audio_processing/agc2/noise_spectrum_estimator.h',
    'webrtc/modules/audio_processing/agc2/signal_classifier.cc',
    'webrtc/modules/audio_processing/agc2/signal_classifier.h',
)

# stuff in webrtc/modules/audio_processing/vad
libaudio_processing_files += files(
    'webrtc/modules/audio_processing/vad/common.h',
    'webrtc/modules/audio_processing/vad/gmm.cc',
    'webrtc/modules/audio_processing/vad/gmm.h',
    'webrtc/modules/audio_processing/vad/noise_gmm_tables.h',
    'webrtc/modules/audio_processing/vad/pitch_based_vad.cc',
    'webrtc/modules/audio_processing/vad/pitch_based_vad.h',
    'webrtc/modules/audio_processing/vad/pitch_internal.cc',
    'webrtc/modules/audio_processing/vad/pitch_internal.h',
    'webrtc/modules/audio_processing/vad/pole_zero_filter.cc',
    'webrtc/modules/audio_processing/vad/pole_zero_filter.h',
    'webrtc/modules/audio_processing/vad/standalone_vad.cc',
    'webrtc/modules/audio_processing/vad/standalone_vad.h',
    'webrtc/modules/audio_processing/vad/vad_audio_proc.cc',
    'webrtc/modules/audio_processing/vad/vad_audio_proc.h',
    'webrtc/modules/audio_processing/vad/vad_audio_proc_internal.h',
    'webrtc/modules/audio_processing/vad/vad_circular_buffer.cc',
    'webrtc/modules/audio_processing/vad/vad_circular_buffer.h',
    'webrtc/modules/audio_processing/vad/voice_activity_detector.cc',
    'webrtc/modules/audio_processing/vad/voice_activity_detector.h',
    'webrtc/modules/audio_processing/vad/voice_gmm_tables.h',
)

# stuff in webrtc/modules/audio_processing/aec3 . TODO: Think about separate build file?
libaudio_processing_files += files(
    'webrtc/modules/audio_processing/aec3/adaptive_fir_filter.cc',
    'webrtc/modules/audio_processing/aec3/adaptive_fir_filter.h',
    'webrtc/modules/audio_processing/aec3/aec3_common.cc',
    'webrtc/modules/audio_processing/aec3/aec3_common.h',
    'webrtc/modules/audio_processing/aec3/aec3_fft.cc',
    'webrtc/modules/audio_processing/aec3/aec3_fft.h',
    'webrtc/modules/audio_processing/aec3/aec_state.cc',
    'webrtc/modules/audio_processing/aec3/aec_state.h',
    'webrtc/modules/audio_processing/aec3/block_framer.cc',
    'webrtc/modules/audio_processing/aec3/block_framer.h',
    'webrtc/modules/audio_processing/aec3/block_processor.cc',
    'webrtc/modules/audio_processing/aec3/block_processor.h',
    'webrtc/modules/audio_processing/aec3/block_processor_metrics.cc',
    'webrtc/modules/audio_processing/aec3/block_processor_metrics.h',
    'webrtc/modules/audio_processing/aec3/cascaded_biquad_filter.cc',
    'webrtc/modules/audio_processing/aec3/cascaded_biquad_filter.h',
    'webrtc/modules/audio_processing/aec3/comfort_noise_generator.cc',
    'webrtc/modules/audio_processing/aec3/comfort_noise_generator.h',
    'webrtc/modules/audio_processing/aec3/decimator.cc',
    'webrtc/modules/audio_processing/aec3/decimator.h',
    'webrtc/modules/audio_processing/aec3/delay_estimate.h',
    'webrtc/modules/audio_processing/aec3/downsampled_render_buffer.cc',
    'webrtc/modules/audio_processing/aec3/downsampled_render_buffer.h',
    'webrtc/modules/audio_processing/aec3/echo_canceller3.cc',
    'webrtc/modules/audio_processing/aec3/echo_canceller3.h',
    'webrtc/modules/audio_processing/aec3/echo_path_delay_estimator.cc',
    'webrtc/modules/audio_processing/aec3/echo_path_delay_estimator.h',
    'webrtc/modules/audio_processing/aec3/echo_path_variability.cc',
    'webrtc/modules/audio_processing/aec3/echo_path_variability.h',
    'webrtc/modules/audio_processing/aec3/echo_remover.cc',
    'webrtc/modules/audio_processing/aec3/echo_remover.h',
    'webrtc/modules/audio_processing/aec3/echo_remover_metrics.cc',
    'webrtc/modules/audio_processing/aec3/echo_remover_metrics.h',
    'webrtc/modules/audio_processing/aec3/erl_estimator.cc',
    'webrtc/modules/audio_processing/aec3/erl_estimator.h',
    'webrtc/modules/audio_processing/aec3/erle_estimator.cc',
    'webrtc/modules/audio_processing/aec3/erle_estimator.h',
    'webrtc/modules/audio_processing/aec3/fft_buffer.cc',
    'webrtc/modules/audio_processing/aec3/fft_buffer.h',
    'webrtc/modules/audio_processing/aec3/fft_data.h',
    'webrtc/modules/audio_processing/aec3/filter_analyzer.cc',
    'webrtc/modules/audio_processing/aec3/filter_analyzer.h',
    'webrtc/modules/audio_processing/aec3/frame_blocker.cc',
    'webrtc/modules/audio_processing/aec3/frame_blocker.h',
    'webrtc/modules/audio_processing/aec3/main_filter_update_gain.cc',
    'webrtc/modules/audio_processing/aec3/main_filter_update_gain.h',
    'webrtc/modules/audio_processing/aec3/matched_filter.cc',
    'webrtc/modules/audio_processing/aec3/matched_filter.h',
    'webrtc/modules/audio_processing/aec3/matched_filter_lag_aggregator.cc',
    'webrtc/modules/audio_processing/aec3/matched_filter_lag_aggregator.h',
    'webrtc/modules/audio_processing/aec3/matrix_buffer.cc',
    'webrtc/modules/audio_processing/aec3/matrix_buffer.h',
    'webrtc/modules/audio_processing/aec3/render_buffer.cc',
    'webrtc/modules/audio_processing/aec3/render_buffer.h',
    'webrtc/modules/audio_processing/aec3/render_delay_buffer.cc',
    'webrtc/modules/audio_processing/aec3/render_delay_buffer.h',
    'webrtc/modules/audio_processing/aec3/render_delay_controller.cc',
    'webrtc/modules/audio_processing/aec3/render_delay_controller.h',
    'webrtc/modules/audio_processing/aec3/render_delay_controller_metrics.cc',
    'webrtc/modules/audio_processing/aec3/render_delay_controller_metrics.h',
    'webrtc/modules/audio_processing/aec3/render_signal_analyzer.cc',
    'webrtc/modules/audio_processing/aec3/render_signal_analyzer.h',
    'webrtc/modules/audio_processing/aec3/residual_echo_estimator.cc',
    'webrtc/modules/audio_processing/aec3/residual_echo_estimator.h',
    'webrtc/modules/audio_processing/aec3/shadow_filter_update_gain.cc',
    'webrtc/modules/audio_processing/aec3/shadow_filter_update_gain.h',
    'webrtc/modules/audio_processing/aec3/skew_estimator.cc',
    'webrtc/modules/audio_processing/aec3/skew_estimator.h',
    'webrtc/modules/audio_processing/aec3/subtractor.cc',
    'webrtc/modules/audio_processing/aec3/subtractor.h',
    'webrtc/modules/audio_processing/aec3/subtractor_output.h',
    'webrtc/modules/audio_processing/aec3/suppression_filter.cc',
    'webrtc/modules/audio_processing/aec3/suppression_filter.h',
    'webrtc/modules/audio_processing/aec3/suppression_gain.cc',
    'webrtc/modules/audio_processing/aec3/suppression_gain.h',
    'webrtc/modules/audio_processing/aec3/suppression_gain_limiter.cc',
    'webrtc/modules/audio_processing/aec3/suppression_gain_limiter.h',
    'webrtc/modules/audio_processing/aec3/vector_buffer.cc',
    'webrtc/modules/audio_processing/aec3/vector_buffer.h',
    'webrtc/modules/audio_processing/aec3/vector_math.h',
)


# webrtc/modules/audio_processing/aec_dump
libaudio_processing_files += files(
    'webrtc/modules/audio_processing/aec_dump/null_aec_dump_factory.cc',
)

# x86 specific stuff
libaudio_processing_files += files(
    'webrtc/modules/audio_processing/aec/aec_core_sse2.cc',
    'webrtc/modules/audio_processing/utility/ooura_fft_sse2.cc',
    'webrtc/modules/audio_processing/utility/ooura_fft_tables_neon_sse2.h',
)

# for MIPS there is an optimized alternative
libaudio_processing_files += files(
    'webrtc/modules/audio_processing/aecm/aecm_core_c.cc'
)


# Selected pics from other modules
libaudio_processing_files += files(
    'webrtc/modules/audio_coding/codecs/isac/main/source/pitch_estimator.c',
    'webrtc/modules/audio_coding/codecs/isac/main/source/pitch_filter.c',
    'webrtc/modules/audio_coding/codecs/isac/main/source/filter_functions.c',
    'webrtc/modules/audio_coding/codecs/isac/main/source/isac_vad.c',

    'webrtc/rtc_base/memory/aligned_malloc.cc',
    'webrtc/rtc_base/checks.cc',
    'webrtc/rtc_base/event.cc',
    'webrtc/rtc_base/logging.cc',
    'webrtc/rtc_base/timeutils.cc',
    'webrtc/rtc_base/criticalsection.cc',
    'webrtc/rtc_base/platform_thread_types.cc',
    'webrtc/rtc_base/stringencode.cc',
    'webrtc/rtc_base/strings/string_builder.cc',
    'webrtc/rtc_base/stringutils.cc',
    'webrtc/rtc_base/event_tracer.cc',
    'webrtc/rtc_base/thread.cc',
    'webrtc/rtc_base/platform_thread.cc',
    'webrtc/rtc_base/thread_checker_impl.cc',

    'webrtc/system_wrappers/source/metrics.cc',
    'webrtc/system_wrappers/source/field_trial.cc', # TODO: investigate this field trial stuff
    'webrtc/system_wrappers/source/cpu_features.cc',
)


libcommon_audio_files = files(
    'webrtc/common_audio/audio_converter.cc',
    'webrtc/common_audio/audio_converter.h',
    'webrtc/common_audio/audio_util.cc',
    'webrtc/common_audio/channel_buffer.cc',
    'webrtc/common_audio/channel_buffer.h',
    'webrtc/common_audio/include/audio_util.h',
    'webrtc/common_audio/real_fourier.cc',
    'webrtc/common_audio/real_fourier.h',
    'webrtc/common_audio/real_fourier_ooura.cc',
    'webrtc/common_audio/real_fourier_ooura.h',
    'webrtc/common_audio/resampler/include/push_resampler.h',
    'webrtc/common_audio/resampler/include/resampler.h',
    'webrtc/common_audio/resampler/push_resampler.cc',
    'webrtc/common_audio/resampler/push_sinc_resampler.cc',
    'webrtc/common_audio/resampler/push_sinc_resampler.h',
    'webrtc/common_audio/resampler/resampler.cc',
    'webrtc/common_audio/resampler/sinc_resampler.cc',
    'webrtc/common_audio/smoothing_filter.cc',
    'webrtc/common_audio/smoothing_filter.h',
    'webrtc/common_audio/sparse_fir_filter.cc',
    'webrtc/common_audio/sparse_fir_filter.h',
    'webrtc/common_audio/vad/include/vad.h',
    'webrtc/common_audio/vad/vad.cc',
    'webrtc/common_audio/wav_file.cc',
    'webrtc/common_audio/wav_file.h',
    'webrtc/common_audio/wav_header.cc',
    'webrtc/common_audio/wav_header.h',
    'webrtc/common_audio/window_generator.cc',
    'webrtc/common_audio/window_generator.h',
)

# C files
libcommon_audio_files += files(
    'webrtc/common_audio/ring_buffer.c',
    'webrtc/common_audio/ring_buffer.h',
    'webrtc/common_audio/signal_processing/auto_corr_to_refl_coef.c',
    'webrtc/common_audio/signal_processing/auto_correlation.c',
    'webrtc/common_audio/signal_processing/complex_fft_tables.h',
    'webrtc/common_audio/signal_processing/copy_set_operations.c',
    'webrtc/common_audio/signal_processing/cross_correlation.c',
    'webrtc/common_audio/signal_processing/division_operations.c',
    'webrtc/common_audio/signal_processing/downsample_fast.c',
    'webrtc/common_audio/signal_processing/energy.c',
    'webrtc/common_audio/signal_processing/filter_ar.c',
    'webrtc/common_audio/signal_processing/filter_ma_fast_q12.c',
    'webrtc/common_audio/signal_processing/get_hanning_window.c',
    'webrtc/common_audio/signal_processing/get_scaling_square.c',
    'webrtc/common_audio/signal_processing/ilbc_specific_functions.c',
    'webrtc/common_audio/signal_processing/include/real_fft.h',
    'webrtc/common_audio/signal_processing/include/signal_processing_library.h',
    'webrtc/common_audio/signal_processing/include/spl_inl.h',
    'webrtc/common_audio/signal_processing/include/spl_inl_armv7.h',
    'webrtc/common_audio/signal_processing/levinson_durbin.c',
    'webrtc/common_audio/signal_processing/lpc_to_refl_coef.c',
    'webrtc/common_audio/signal_processing/min_max_operations.c',
    'webrtc/common_audio/signal_processing/randomization_functions.c',
    'webrtc/common_audio/signal_processing/real_fft.c',
    'webrtc/common_audio/signal_processing/refl_coef_to_lpc.c',
    'webrtc/common_audio/signal_processing/resample.c',
    'webrtc/common_audio/signal_processing/resample_48khz.c',
    'webrtc/common_audio/signal_processing/resample_by_2.c',
    'webrtc/common_audio/signal_processing/resample_by_2_internal.c',
    'webrtc/common_audio/signal_processing/resample_by_2_internal.h',
    'webrtc/common_audio/signal_processing/resample_fractional.c',
    'webrtc/common_audio/signal_processing/spl_init.c',
    'webrtc/common_audio/signal_processing/spl_inl.c',
    'webrtc/common_audio/signal_processing/spl_sqrt.c',
    'webrtc/common_audio/signal_processing/splitting_filter.c',
    'webrtc/common_audio/signal_processing/sqrt_of_one_minus_x_squared.c',
    'webrtc/common_audio/signal_processing/vector_scaling_operations.c',
    'webrtc/common_audio/vad/include/webrtc_vad.h',
    'webrtc/common_audio/vad/vad_core.c',
    'webrtc/common_audio/vad/vad_core.h',
    'webrtc/common_audio/vad/vad_filterbank.c',
    'webrtc/common_audio/vad/vad_filterbank.h',
    'webrtc/common_audio/vad/vad_gmm.c',
    'webrtc/common_audio/vad/vad_gmm.h',
    'webrtc/common_audio/vad/vad_sp.c',
    'webrtc/common_audio/vad/vad_sp.h',
    'webrtc/common_audio/vad/webrtc_vad.c',

    'webrtc/common_audio/third_party/spl_sqrt_floor/spl_sqrt_floor.c',
    'webrtc/common_audio/third_party/fft4g/fft4g.c',
)

libcommon_audio_files += files(
    'webrtc/common_audio/fir_filter_c.cc',
    'webrtc/common_audio/fir_filter_c.h',
    'webrtc/common_audio/fir_filter_factory.cc',
    'webrtc/common_audio/fir_filter_factory.h',
    'webrtc/common_audio/signal_processing/dot_product_with_scale.cc',
    'webrtc/common_audio/signal_processing/dot_product_with_scale.h',
)


# TODO: Use the assembler versions on MIPS and ARM
libcommon_audio_files += files(
    'webrtc/common_audio/signal_processing/complex_bit_reverse.c',
    'webrtc/common_audio/signal_processing/filter_ar_fast_q12.c',

    'webrtc/common_audio/signal_processing/complex_fft.c',

    'webrtc/common_audio/fir_filter_sse.cc',
    'webrtc/common_audio/fir_filter_sse.h',
    'webrtc/common_audio/resampler/sinc_resampler_sse.cc',
)

# misc stuff
libcommon_audio_files += files(
    'webrtc/api/audio/audio_frame.cc'
)


libcommon_audio = static_library(
  'common_audio',
  libcommon_audio_files,
  include_directories : [inc_common],
)

librnnoise_files = files(
    'chromium/third_party/rnnoise/src/rnn_vad_weights.cc',
    'chromium/third_party/rnnoise/src/rnn_vad_weights.h',
    'chromium/third_party/rnnoise/src/kiss_fft.cc',
    'chromium/third_party/rnnoise/src/kiss_fft.h',
)

librnnoise = static_library(
    'rnnoise',
    librnnoise_files,
    include_directories : [inc_common],
)


libaudio_processing = static_library(
  'audio_processing',
  libaudio_processing_files,
  include_directories : [inc_common],
  #cpp_args: internal_args,
)


executable('aec_test', ['aec_test.cpp'],
    link_with: [libaudio_processing, libcommon_audio, librnnoise],
    include_directories: inc_common,
    cpp_args: '-DQT_NO_KEYWORDS',
    link_args: '-lGL' # Hack, should use Qt's OpenGL wrapper
)

#all_libraries += libaudio_processing

