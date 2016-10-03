LOCAL_PATH := $(call my-dir)

# include $(CLEAR_VARS)
LOCAL_C_INCLUDES := ${shell find -L $(LOCAL_PATH)/include -type d}
$(info $(LOCAL_C_INCLUDES))

LOCAL_MODULE := mythril
TARGET_PLATFORM := android-24
LOCAL_SRC_FILES :=
include $(LOCAL_PATH)/MythrilAndroid.mk
LOCAL_LDLIBS := -lGLESv2

include $(BUILD_SHARED_LIBRARY)
