#! /bin/bash


_HOME2_=$(dirname $0)
export _HOME2_
_HOME_=$(cd $_HOME2_;pwd)
export _HOME_

cd "$_HOME_"
mkdir -p ./data/

echo '
id -a

cp -av android_stuff.sh /data/android_stuff.sh

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
automake \
wget \
curl \
python \
python3 \
meson \
unzip \
ninja-build

mkdir -p /data/

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

cd /data/
_HOME2_=$(dirname $0)
export _HOME2_
_HOME_=$(cd $_HOME2_;pwd)
export _HOME_

# ----- android --------------------------------------------------------------------
. /data/android_stuff.sh
# ----- android --------------------------------------------------------------------


cd /data/work/

# --------------- CODE -------------------------------------------------------------
# git clone https://github.com/strfry/webrtc-audio-processing-meson

git clone https://github.com/zoff99/webrtc-audio-processing-meson
cd webrtc-audio-processing-meson/
git checkout zoff99/android_002
# --------------- CODE -------------------------------------------------------------


git submodule update --init --depth=1
./gen-webrtc-build-meson.sh > webrtc/meson.build
meson . build
ninja -C build
' > ./data/runme.sh

cp -av android_stuff.sh ./data/android_stuff.sh


if [ "$1""x" == "githubworkflowx" ]; then
    cd ./data/
    sudo /bin/bash ./runme.sh
else

    system_to_build_for="ubuntu:18.04"


    cd $_HOME_/
    docker run -ti --rm \
      -v "$_HOME_"/data:/data \
      --net=host \
      "$system_to_build_for" \
      /bin/bash # /data/runme.sh

fi
