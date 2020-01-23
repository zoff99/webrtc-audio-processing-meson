#! /bin/bash


_HOME2_=$(dirname $0)
export _HOME2_
_HOME_=$(cd $_HOME2_;pwd)
export _HOME_

cd "$_HOME_"
mkdir -p ./data/
mkdir -p ./repo/

echo '

id -a
pwd
ls -al ./

mkdir -p /data/
mkdir -p /repo/

cp -av android_stuff.sh /data/android_stuff.sh 2>/dev/null # only valid for CI
cp -a abseil-cpp ./repo/ 2>/dev/null # only valid for CI
cp -a *.sh /repo/ 2>/dev/null # only valid for CI
cp -a *.cpp /repo/ 2>/dev/null # only valid for CI
cp -a ./.git /repo/ 2>/dev/null # only valid for CI
cp -a ./.gitmodules /repo/ 2>/dev/null # only valid for CI
cp -a cross /repo/ 2>/dev/null # only valid for CI
cp -a meson.build /repo/ 2>/dev/null # only valid for CI
cp -a third_party /repo/ 2>/dev/null # only valid for CI
cp -a webrtc /repo/ 2>/dev/null # only valid for CI

export DEBIAN_FRONTEND=noninteractive
export DEBIAN_PRIORITY=critical

apt-get update
apt-get -y --force-yes --no-install-recommends install \
build-essential \
ca-certificates \
git \
nano \
vim \
flex \
bison \
autotools-dev \
autoconf \
automake \
wget \
curl \
rsync \
python \
python3 \
meson \
unzip \
ninja-build

apt-get -y --force-yes remove meson
apt-get -y --force-yes remove ninja-build

mkdir -p /data/

cd /data/ && mkdir -p work/
cd work && rm -Rf *

# ----- meson ----------------------------------------------------------------------
cd /data/work/
mkdir meson_
cd meson_/
meson_version="0.49.2"
wget https://github.com/mesonbuild/meson/releases/download/"$meson_version"/meson-"$meson_version".tar.gz
tar -xzf meson-"$meson_version".tar.gz
rm /usr/bin/meson
ln -s /data/work/meson_/meson-"$meson_version"/meson.py /usr/bin/meson
# ----- meson ----------------------------------------------------------------------


# ----- ninja ----------------------------------------------------------------------
cd /data/work/
mkdir ninja_
cd ninja_/
wget https://github.com/ninja-build/ninja/releases/download/v1.9.0/ninja-linux.zip
unzip ninja-linux.zip
rm /usr/bin/ninja
ln -s /data/work/ninja_/ninja /usr/bin/ninja
# ----- ninja ----------------------------------------------------------------------

cd /data/
_HOME2_=$(dirname $0)
export _HOME2_
_HOME_=$(cd $_HOME2_;pwd)
export _HOME_

# ----- android --------------------------------------------------------------------
. /data/android_stuff.sh
# ----- android --------------------------------------------------------------------

# ----- remove linux C compilers ---------------------------------------------------
rm -f /usr/bin/gcc
rm -f /usr/bin/g++
rm -f /usr/bin/cc
rm -f /usr/bin/cc++
# ----- remove linux C compilers ---------------------------------------------------


cd /data/work/

# --------------- CODE -------------------------------------------------------------
mkdir -p webrtc-audio-processing-meson/
rsync -a /repo/ webrtc-audio-processing-meson/
cd webrtc-audio-processing-meson
# --------------- CODE -------------------------------------------------------------


# ------- patch meson --------------------------------------------------------------
sed -i -e '"'"'s#self.is_cross =.*$#self.is_cross = True#'"'"' /data/work/meson_/meson-"$meson_version"/mesonbuild/compilers/c.py
cat /data/work/meson_/meson-"$meson_version"/mesonbuild/compilers/c.py | grep -A10 -B10 "self.is_cross ="
# ------- patch meson --------------------------------------------------------------

git submodule update --init --depth=50
./gen-webrtc-build-meson.sh > webrtc/meson.build


ARCH="arm"
ABI="armeabi-v7a"


rm -Rf armv7a-build
mkdir armv7a-build

# meson . build
meson setup --errorlogs --cross-file cross/android-armhf.ini \
  --prefix=/data/inst/toolchains/arm-linux-androideabi \
  --includedir=/data/inst/toolchains/arm-linux-androideabi/sysroot/usr/include \
  --libdir=/data/inst/toolchains/arm-linux-androideabi/sysroot/usr/lib \
  armv7a-build .

ninja -C armv7a-build

ls -hal /data/work/webrtc-audio-processing-meson/armv7a-build/libwebrtc_audio_processing.a || exit 1
cp -av /data/work/webrtc-audio-processing-meson/armv7a-build/libwebrtc_audio_processing.a /data/
chmod a+rwx /data/libwebrtc_audio_processing.a

ls -al /data/work/webrtc-audio-processing-meson/armv7a-build/libaec.so || exit 1
cp -av /data/work/webrtc-audio-processing-meson/armv7a-build/libaec.so /data/
chmod a+rwx /data/libaec.so

#export V=1

#arm-linux-androideabi-clang++ -O3 -g -shared -Wall -Wextra \
#    -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function \
#    -Wno-pointer-sign -Wno-unused-but-set-variable \
#    -funwind-tables -Wl,--no-merge-exidx-entries -Wl,-soname,libaec.so \
#    aec_test.cpp -o libaec.so \
#    -std=gnu99 -I/data/inst/toolchains/arm-linux-androideabi/sysroot/usr/include \
#    /data/work/webrtc-audio-processing-meson/armv7a-build/libwebrtc_audio_processing.a \
#    -lm

#/data/inst/toolchains//arm-linux-androideabi/bin/arm-linux-androideabi-clang++ \
#  -O3 -g -shared -Wall -Wextra     \
#  -DWEBRTC_APM_DEBUG_DUMP=0 \
#  -DQT_NO_KEYWORDS \
#  -funwind-tables -Wl,--no-merge-exidx-entries -Wl,-soname,libaec.so \
#  aec_test.cpp -o libaec.so   \
#  -std=c++17 -I/data/inst/toolchains/arm-linux-androideabi/sysroot/usr/include \
#  /data/work/webrtc-audio-processing-meson/armv7a-build/libwebrtc_audio_processing.a  \
#  -lm -I./webrtc/ -I./abseil-cpp/

' > ./data/runme.sh

cp -av android_stuff.sh ./data/android_stuff.sh
cp -a ./abseil-cpp ./repo/
cp -a ./*.sh ./repo/
cp -a ./*.cpp ./repo/
cp -a ./.git ./repo/
cp -a ./.gitmodules ./repo/
cp -a ./cross ./repo/
cp -a ./meson.build ./repo/
cp -a ./third_party ./repo/
cp -a ./webrtc ./repo/


if [ "$1""x" == "githubworkflowx" ]; then
    cd ./data/
    sudo /bin/bash ./runme.sh
else

    system_to_build_for="ubuntu:18.04"


    cd $_HOME_/
    docker run -ti --rm \
      -v "$_HOME_"/data:/data \
      -v "$_HOME_"/repo:/repo \
      --net=host \
      "$system_to_build_for" \
      /bin/bash # /data/runme.sh

fi
