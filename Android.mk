LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libusbrubberducky
LOCAL_CLANG := false
LOCAL_SRC_FILES := src/keyboard.cpp main.cpp

LOCAL_CFLAGS := -std=c++17

include $(BUILD_EXECUTABLE)