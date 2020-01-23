project('webrtc-audio-processing-example', ['c', 'cpp'])

inc_common = include_directories(
    'webrtc',
    'abseil-cpp',
)

add_project_arguments(
    '-DWEBRTC_POSIX',
    '-DWEBRTC_LINUX',
    '-DWEBRTC_APM_DEBUG_DUMP=0',
    '-DWEBRTC_NS_FLOAT',
    
    '-DWEBRTC_USE_BUILTIN_ISAC_FLOAT',
    
    language: ['cpp', 'c']
)

subdir('webrtc')

webrtc_files += files(
    'webrtc/rtc_base/checks.cc',
    'webrtc/rtc_base/checks.h',
    'webrtc/rtc_base/memory/aligned_malloc.cc',

    'webrtc/modules/audio_coding/codecs/isac/main/source/pitch_estimator.c',
    'webrtc/modules/audio_coding/codecs/isac/main/source/pitch_filter.c',
    'webrtc/modules/audio_coding/codecs/isac/main/source/filter_functions.c',
    'webrtc/modules/audio_coding/codecs/isac/main/source/isac_vad.c',

    'webrtc/rtc_base/checks.cc',
    'webrtc/rtc_base/event.cc',
    'webrtc/rtc_base/logging.cc',
    'webrtc/rtc_base/time_utils.cc',
    'webrtc/rtc_base/critical_section.cc',
    'webrtc/rtc_base/platform_thread_types.cc',
    'webrtc/rtc_base/string_encode.cc',
    'webrtc/rtc_base/strings/string_builder.cc',
    'webrtc/rtc_base/string_utils.cc',
    'webrtc/rtc_base/event_tracer.cc',
    'webrtc/rtc_base/thread.cc',
    'webrtc/rtc_base/platform_thread.cc',
    'webrtc/rtc_base/race_checker.cc',
    'webrtc/rtc_base/synchronization/sequence_checker.cc',
    'webrtc/rtc_base/synchronization/yield_policy.cc',

#    'webrtc/rtc_base/task_queue.cc',
    'webrtc/api/task_queue/task_queue_base.cc',

    'webrtc/system_wrappers/source/metrics.cc',
    'webrtc/system_wrappers/source/field_trial.cc', # TODO: investigate this field trial stuff
    'webrtc/system_wrappers/source/cpu_features.cc',

)


webrtc_files += files(
    'abseil-cpp/absl/types/bad_optional_access.cc',
    'abseil-cpp/absl/base/internal/throw_delegate.cc',
    'abseil-cpp/absl/strings/string_view.cc',
    'abseil-cpp/absl/strings/internal/memutil.cc',
    'abseil-cpp/absl/strings/ascii.cc',
)

webrtc_files += files(
    'third_party/rnnoise/src/rnn_vad_weights.cc',
    'third_party/rnnoise/src/rnn_vad_weights.h',
)

webrtc_files += files(
    'third_party/pffft/src/fftpack.c',
    'third_party/pffft/src/fftpack.h',
    'third_party/pffft/src/pffft.c',
    'third_party/pffft/src/pffft.h'
)

libwebrtc_audio_processing = static_library(
  'webrtc_audio_processing',
  webrtc_files,
  include_directories : [inc_common],
  # link_args: '-lpthread'
  #cpp_args: internal_args,
)

libaec = shared_library(
  'aec',
  ['aec_test.cpp'],
  include_directories : [inc_common],
  link_with: [libwebrtc_audio_processing],
  cpp_args: '-DQT_NO_KEYWORDS',
  link_args: '-Wl,-soname,libaec.so'
)



#executable('aec_test', ['aec_test.cpp'],
#    link_with: [libwebrtc_audio_processing],
#    include_directories: inc_common,
#    cpp_args: '-DQT_NO_KEYWORDS',
#    # link_args: '-lpthread' # Hack, should be exported by libwebrtc
#)

#all_libraries += libaudio_processing

