LOCAL_PATH := $(call my-dir) 
 
include $(CLEAR_VARS) 
 
LOCAL_MODULE    := clock
LOCAL_SRC_FILES := /tmp/clock/jni/main.c
 
include $(BUILD_EXECUTABLE) 
