LOCAL_PATH := $(call my-dir)

#find all the file recursively under jni/
SRCFILES = $(call walk, $(LOCAL_PATH)/../)
FILE_LIST := $(filter %.cpp, $(SRCFILES))


include $(CLEAR_VARS)
LOCAL_MODULE := mythril
TARGET_PLATFORM := android-24
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_LDLIBS := -lGLESv2
include $(BUILD_SHARED_LIBRARY)
