# How to build

    git submodule update --init --depth=1
    ./gen-webrtc-build-meson.sh > webrtc/meson.build
    meson . build
    ninja -C build

## Notes for myself

- 
