#! /bin/bash


_HOME2_=$(dirname $0)
export _HOME2_
_HOME_=$(cd $_HOME2_;pwd)
export _HOME_

cd "$_HOME_"
mkdir -p ./data/

echo '
id -a

export DEBIAN_FRONTEND=noninteractive
export DEBIAN_PRIORITY=critical

apt-get update
# apt-get upgrade
apt-get -y --force-yes --no-install-recommends install \
build-essential \
ca-certificates \
git \
flex \
bison \
autotools-dev \
autoconf \
wget \
meson \
unzip \
ninja-build

cd /data/ && mkdir -p work/
cd work && rm -Rf *

# ----- meson ----------------------------------------------------------------------
cd /data/work/
mkdir meson_
cd meson_/
wget https://github.com/mesonbuild/meson/releases/download/0.53.0/meson-0.53.0.tar.gz
tar -xzf meson-0.53.0.tar.gz
rm /usr/bin/meson
ln -s /data/work/meson_/meson-0.53.0/meson.py /usr/bin/meson
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

cd /data/work/

# --------------- CODE -------------------------------------------------------------
# git clone https://github.com/strfry/webrtc-audio-processing-meson

git clone https://github.com/zoff99/webrtc-audio-processing-meson
cd webrtc-audio-processing-meson/
git checkout zoff99/android
# --------------- CODE -------------------------------------------------------------


git submodule update --init --depth=1
./gen-webrtc-build-meson.sh > webrtc/meson.build
meson . build
ninja -C build
' > ./data/runme.sh

if [ "$1""x" == "githubworkflowx" ]; then
    cd ./data/
    /bin/bash ./runme.sh
else

    system_to_build_for="ubuntu:18.04"


    cd $_HOME_/
    docker run -ti --rm \
      -v "$_HOME_"/data:/data \
      --net=host \
      "$system_to_build_for" \
      /bin/bash /data/runme.sh

fi
