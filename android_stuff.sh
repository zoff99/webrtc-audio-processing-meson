
set -x

echo $_HOME_

export _SRC_=$_HOME_/build/
export _INST_=$_HOME_/inst/

echo $_SRC_
echo $_INST_

rm -Rf $_SRC_
rm -Rf $_INST_

mkdir -p $_SRC_
mkdir -p $_INST_

export ORIG_PATH_=$PATH

full=1
download_full=1
build_yasm=1

export _SDK_="$_INST_/sdk"
export _NDK_="$_INST_/ndk/"
export _BLD_="$_SRC_/build/"
export _CPUS_=$numcpus_

export _toolchain_="$_INST_/toolchains/"
export _s_="$_SRC_/"
export CF2=" "
export CF3=" "
# ---- arm -----
export AND_TOOLCHAIN_ARCH="arm"
export AND_TOOLCHAIN_ARCH2="arm-linux-androideabi"
export AND_PATH="$_toolchain_/arm-linux-androideabi/bin:$ORIG_PATH_"
export AND_PKG_CONFIG_PATH="$_toolchain_/arm-linux-androideabi/sysroot/usr/lib/pkgconfig"
export AND_CC="$_toolchain_/arm-linux-androideabi/bin/arm-linux-androideabi-clang"
export AND_GCC="$_toolchain_/arm-linux-androideabi/bin/arm-linux-androideabi-gcc"
export AND_CXX="$_toolchain_/arm-linux-androideabi/bin/arm-linux-androideabi-clang++"
export AND_READELF="$_toolchain_/arm-linux-androideabi/bin/arm-linux-androideabi-readelf"
export AND_STRIP="$_toolchain_/arm-linux-androideabi/bin/arm-linux-androideabi-strip"
export AND_ARTEFACT_DIR="arm"

export PATH="$_SDK_"/tools/bin:$ORIG_PATH_

export ANDROID_NDK_HOME="$_NDK_"
export ANDROID_HOME="$_SDK_"
export WRKSPACEDIR="$_HOME_""/workspace/"


mkdir -p $_toolchain_
mkdir -p $AND_PKG_CONFIG_PATH
mkdir -p $WRKSPACEDIR

if [ "$full""x" == "1x" ]; then

    if [ "$download_full""x" == "1x" ]; then
        cd $WRKSPACEDIR
        curl https://dl.google.com/android/repository/sdk-tools-linux-4333796.zip -o sdk.zip

        cd $WRKSPACEDIR
        curl https://dl.google.com/android/repository/android-ndk-r17c-linux-x86_64.zip -o android-ndk-r13b-linux-x86_64.zip
    fi

    cd $WRKSPACEDIR
    # --- verfiy SDK package ---
    echo '92ffee5a1d98d856634e8b71132e8a95d96c83a63fde1099be3d86df3106def9  sdk.zip' \
        > sdk.zip.sha256
    sha256sum -c sdk.zip.sha256 || exit 1
    # --- verfiy SDK package ---
    unzip sdk.zip
    mkdir -p "$_SDK_"
    mv -v tools "$_SDK_"/
    yes | "$_SDK_"/tools/bin/sdkmanager --licenses > /dev/null 2>&1

    # Install Android Build Tool and Libraries ------------------------------
    # Install Android Build Tool and Libraries ------------------------------
    # Install Android Build Tool and Libraries ------------------------------
    $ANDROID_HOME/tools/bin/sdkmanager --update
    ANDROID_VERSION=26
    ANDROID_BUILD_TOOLS_VERSION=26.0.2
    $ANDROID_HOME/tools/bin/sdkmanager "build-tools;${ANDROID_BUILD_TOOLS_VERSION}" \
        "platforms;android-${ANDROID_VERSION}" \
        "platform-tools"
    ANDROID_VERSION=25
    $ANDROID_HOME/tools/bin/sdkmanager "platforms;android-${ANDROID_VERSION}"
    ANDROID_BUILD_TOOLS_VERSION=25.0.0
    $ANDROID_HOME/tools/bin/sdkmanager "build-tools;${ANDROID_BUILD_TOOLS_VERSION}"

    echo y | $ANDROID_HOME/tools/bin/sdkmanager "extras;m2repository;com;android;support;constraint;constraint-layout;1.0.2"
    echo y | $ANDROID_HOME/tools/bin/sdkmanager "extras;m2repository;com;android;support;constraint;constraint-layout-solver;1.0.2"
    echo y | $ANDROID_HOME/tools/bin/sdkmanager "build-tools;27.0.3"
    echo y | $ANDROID_HOME/tools/bin/sdkmanager "platforms;android-27"
    # -- why is this not just called "cmake" ? --
    # cmake_pkg_name=$($ANDROID_HOME/tools/bin/sdkmanager --list --verbose|grep -i cmake| tail -n 1 | cut -d \| -f 1 |tr -d " ");
    echo y | $ANDROID_HOME/tools/bin/sdkmanager "cmake;3.6.4111459"
    # -- why is this not just called "cmake" ? --
    # Install Android Build Tool and Libraries ------------------------------
    # Install Android Build Tool and Libraries ------------------------------
    # Install Android Build Tool and Libraries



    cd $WRKSPACEDIR
    # --- verfiy NDK package ---
    #echo '3524d7f8fca6dc0d8e7073a7ab7f76888780a22841a6641927123146c3ffd29c  android-ndk-r13b-linux-x86_64.zip' \
    #    > android-ndk-r13b-linux-x86_64.zip.sha256
    #sha256sum -c android-ndk-r13b-linux-x86_64.zip.sha256 || exit 1
    # --- verfiy NDK package ---
    unzip android-ndk-r13b-linux-x86_64.zip
    rm -Rf "$_NDK_"
    mv -v android-ndk-r??? "$_NDK_"



    echo 'export ARTEFACT_DIR="$AND_ARTEFACT_DIR";export PATH="$AND_PATH";export PKG_CONFIG_PATH="$AND_PKG_CONFIG_PATH";export READELF="$AND_READELF";export STRIP="$AND_STRIP";export GCC="$AND_GCC";export CC="$AND_CC";export CXX="$AND_CXX";export CPPFLAGS="";export LDFLAGS="";export TOOLCHAIN_ARCH="$AND_TOOLCHAIN_ARCH";export TOOLCHAIN_ARCH2="$AND_TOOLCHAIN_ARCH2"' > $_HOME_/pp
    chmod u+x $_HOME_/pp
    rm -Rf "$_s_"
    mkdir -p "$_s_"


    ## ------- init vars ------- ##
    ## ------- init vars ------- ##
    ## ------- init vars ------- ##
    . $_HOME_/pp
    ## ------- init vars ------- ##
    ## ------- init vars ------- ##
    ## ------- init vars ------- ##


    mkdir -p "$PKG_CONFIG_PATH"
    $_NDK_/build/tools/make_standalone_toolchain.py --arch "$TOOLCHAIN_ARCH" \
        --install-dir "$_toolchain_"/arm-linux-androideabi --api 21 --force   





    if [ "$build_yasm""x" == "1x" ]; then
    # --- YASM ---
    cd $_s_
    rm -Rf yasm
    git clone --depth=1 --branch=v1.3.0 https://github.com/yasm/yasm.git
    cd $_s_/yasm/;autoreconf -fi
    rm -Rf "$_BLD_"
    mkdir -p "$_BLD_"
    cd "$_BLD_";$_s_/yasm/configure --prefix="$_toolchain_"/arm-linux-androideabi/sysroot/usr \
        --disable-shared --disable-soname-versions --host=arm-linux-androideabi \
        --with-sysroot="$_toolchain_"/arm-linux-androideabi/sysroot
    cd "$_BLD_"
    make -j $_CPUS_
    ret_=$?
    if [ $ret -ne 0 ]; then
        sleep 10
        make clean
        make -j $_CPUS_ || exit 1
    fi
    cd "$_BLD_";make install
    # --- YASM ---
    fi

fi

