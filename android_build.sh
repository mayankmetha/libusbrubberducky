rm -rf out/android/ tmp/android/
if [ -f ./.config ];then
    echo "Loading config source file"
    source ./.config
fi
mkdir out out/android
$ANDROID_NDK_HOME/ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk NDK_APPLICATION_MK=Application.mk NDK_LIBS_OUT=out/android NDK_OUT=tmp/android
rm -rf tmp
