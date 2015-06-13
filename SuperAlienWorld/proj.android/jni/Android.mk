LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
					../../Classes/AppDelegate.cpp \
					../../Classes/BackGround3Parts.cpp \
					../../Classes/BaseLevel.cpp \
					../../Classes/BaseMenuLayer.cpp \
					../../Classes/Enemy.cpp \
					../../Classes/EnemyFactory.cpp \
					../../Classes/EnemyFrog.cpp \
					../../Classes/EnemyLadybug.cpp \
					../../Classes/EnemyMouse.cpp \
					../../Classes/EnemySlimeBlue.cpp \
					../../Classes/EnemySlimeGreen.cpp \
					../../Classes/EnemySlimePurple.cpp \
					../../Classes/EnemySnail.cpp \
					../../Classes/EnemyWormGreen.cpp \
					../../Classes/GameManager.cpp \
					../../Classes/Level2.cpp \
					../../Classes/Level3.cpp \
					../../Classes/MainMenuLayer.cpp \
					../../Classes/Player.cpp \
					../../Classes/SelectMenuLayer.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
