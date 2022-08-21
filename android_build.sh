if [ -f ./.config ];then
    echo "Loading config source file"
    source ./.config
fi
$ANDROID_NDK_HOME/ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk NDK_APPLICATION_MK=Application.mk
