#!/bin/sh

## ./gen-webrtc-build-meson.sh > webrtc/meson.build

echo "webrtc_files = files("

#find webrtc/modules/audio_processing/ -type f | awk '{ print "'"\t\'"'" $0 "'"\'"'," }' \

cd webrtc
    (find modules/audio_processing/ -name "*.cc"
     find modules/audio_processing/ -name "*.c"
     find modules/audio_processing/ -name "*.h"
     find common_audio -name "*.cc"
     find common_audio -name "*.c"
     find common_audio -name "*.h"
     find api/audio -name "*.cc"
#     find modules/audio_coding/ -name "*.cc"
#     find modules/audio_coding/ -name "*.c"
#     find modules/audio_coding/ -name "*.h"
 ) \
    | awk '{ print "'"\t'"'" $0 "'"'"'," }' \
    | grep -v test \
    | grep -v /aec_dump/ \
    | grep -v /mock_ \
    | grep -v _neon.c \
    | grep -v _mips.c \
    | grep -v fixed_gain_controller.cc \
    | grep -v _json.cc

#    | grep -v neteq/tools \
#    | grep -v codecs/opus



echo ")"
