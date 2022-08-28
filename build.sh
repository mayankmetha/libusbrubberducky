case $(uname | tr '[:upper:]' '[:lower:]') in
  linux*)
    export LIB_OS_NAME=linux
    ;;
  darwin*)
    export LIB_OS_NAME=macos
    ;;
  msys*)
    export LIB_OS_NAME=windows
    ;;
  *)
    export LIB_OS_NAME=notset
    ;;
esac
rm -rf out/"$LIB_OS_NAME"
mkdir out out/"$LIB_OS_NAME"
if [ $LIB_OS_NAME == "macos" ]; then
  mkdir out/"$LIB_OS_NAME"/x86_64 out/"$LIB_OS_NAME"/arm64 out/"$LIB_OS_NAME"/universal
  clang++ -target x86_64-apple-macos10.12 -std=c++17 -o out/"$LIB_OS_NAME"/x86_64/usbrubberducky src/*.cpp
  chmod +x out/"$LIB_OS_NAME"/x86_64/usbrubberducky
  clang++ -target arm64-apple-macos11 -std=c++17 -o out/"$LIB_OS_NAME"/arm64/usbrubberducky src/*.cpp
  chmod +x out/"$LIB_OS_NAME"/arm64/usbrubberducky
  lipo -create -output out/"$LIB_OS_NAME"/universal/usbrubberducky out/"$LIB_OS_NAME"/x86_64/usbrubberducky out/"$LIB_OS_NAME"/arm64/usbrubberducky
else
  clang++ -o out/"$LIB_OS_NAME"/usbrubberducky -std=c++17 src/*.cpp
  chmod +x out/"$LIB_OS_NAME"/usbrubberducky
fi