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
rm -rf out/"$LIB_OS_NAME" tmp/"$LIB_OS_NAME"
mkdir out out/"$LIB_OS_NAME" tmp tmp/"$LIB_OS_NAME"
g++ -MMD -MP -std=c++17 -c src/*.cpp 
mv *.o tmp/"$LIB_OS_NAME"/
mv *.d tmp/"$LIB_OS_NAME"/
g++ -o out/"$LIB_OS_NAME"/usbrubberducky tmp/"$LIB_OS_NAME"/*.o