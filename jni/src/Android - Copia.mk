LOCAL_PATH := $(call my-dir)
STL:=$(firstword $(subst _, ,$(APP_STL)))

include $(CLEAR_VARS)
LOCAL_MODULE := libSDL2
LOCAL_SRC_FILES := C:/ANDROID/AndroidProject/SDL/app/src/main/libs/$(TARGET_ARCH_ABI)/libSDL2.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libmpg123
LOCAL_SRC_FILES := C:/ANDROID/AndroidProject/SDL/app/src/main/libs/$(TARGET_ARCH_ABI)/libmpg123.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libhidapi
LOCAL_SRC_FILES := C:/ANDROID/AndroidProject/SDL/app/src/main/libs/$(TARGET_ARCH_ABI)/libhidapi.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libSDL2_image
LOCAL_SRC_FILES := C:/ANDROID/AndroidProject/SDL/app/src/main/libs/$(TARGET_ARCH_ABI)/libSDL2_image.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libSDL2_mixer
LOCAL_SRC_FILES := C:/ANDROID/AndroidProject/SDL/app/src/main/libs/$(TARGET_ARCH_ABI)/libSDL2_mixer.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libSDL2_ttf
LOCAL_SRC_FILES := C:/ANDROID/AndroidProject/SDL/app/src/main/libs/$(TARGET_ARCH_ABI)/libSDL2_ttf.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libfirebase_app
LOCAL_SRC_FILES := C:/ANDROID/firebase_cpp_sdk/libs/android/$(TARGET_ARCH_ABI)/$(STL)/libfirebase_app.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../../../../../firebase_cpp_sdk/include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libfirebase_admob
LOCAL_SRC_FILES := C:/ANDROID/firebase_cpp_sdk/libs/android/$(TARGET_ARCH_ABI)/$(STL)/libfirebase_admob.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../../../../../firebase_cpp_sdk/include
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := main
SDL_PATH := ../SDL2

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
                    $(LOCAL_PATH)/../SDL2_image/ \
                    $(LOCAL_PATH)/../SDL2_mixer/ \
                    $(LOCAL_PATH)/../SDL2_ttf \
                    $(LOCAL_PATH)/../SDL2_ttf \
                    $(LOCAL_PATH)/../../../../../../../firebase_cpp_sdk/include \
                    $(NDK_ROOT)/sources/android/native_app_glue

# Add your application source files here...
LOCAL_SRC_FILES := CAppStateGameWin.h \
	CAppStateIntro.h \
	CAppStateManager.h \
	CAppStateNone.h \
	CArea.h \
	CAsteroid.h \
	CBlast.h \
	CBomb.h \
	CGammaRay.h \
	CGammaRayEnemy.h \
	CBullet.h \
	CBulletBOSS1.h \
	CBulletEnemy.h \
	CBulletEnemy_S.h \
	CBulletSmart.h \
	CCamera.h \
	CCannon.h \
	CEnemyBOSS1.h \
	CEnemyMM.h \
	CEnemyMM_2.h \
	CEnemyMM_3.h \
	CEnemySX.h \
	CEnemySX_move.h \
	CEntity.h \
	CEvent.h \
	CFPS.h \
	CGalaxy.h \
	CGenerator.h \
	CMap.h \
	CMedal.h \
	CMenu.h \
	CParticle_BossXPL.h \
	CParticle_PlayerXPL.h \
	CParticle_Smoke.h \
	CParticle_XPL.h \
	CParticles.h \
	CPlayer.h \
	CPlayerStat.h \
	CPopup.h \
	CShield.h \
	CSoundBank.h \
	CTile.h \
	Define.h \
	FileManager.h \
	Log.h \
	Stringify.h \
	Texture.h \
	TextureBank.h \
	CAnimation.cpp \
	CApp.cpp \
	CApp_OnCleanup.cpp \
	CApp_OnEvent.cpp \
	CApp_OnInit.cpp \
	CApp_OnLog.cpp \
	CApp_OnLoop.cpp \
	CApp_OnRender.cpp \
	CAppState.cpp \
	CAppStateCredits.cpp \
	CAppStateGame.cpp \
	CAppStateGameLose.cpp \
	CAppStateGameOver.cpp \
	CAppStateGamePause.cpp \
	CAppStateGameWin.cpp \
	CAppStateIntro.cpp \
	CAppStateManager.cpp \
	CAppStateNone.cpp \
	CArea.cpp \
	CAsteroid.cpp \
	CBlast.cpp \
	CBomb.cpp \
	CGammaRay.cpp \
	CGammaRayEnemy.cpp \
	CBullet.cpp \
	CBulletBOSS1.cpp \
	CBulletEnemy.cpp \
	CBulletEnemy_S.cpp \
	CBulletSmart.cpp \
	CCamera.cpp \
	CCannon.cpp \
	CEnemyBOSS1.cpp \
	CEnemyMM.cpp \
	CEnemyMM_2.cpp \
	CEnemyMM_3.cpp \
	CEnemySX.cpp \
	CEnemySX_move.cpp \
	CEntity.cpp \
	CEntityCol.cpp \
	CEvent.cpp \
	CFPS.cpp \
	CGalaxy.cpp \
	CGenerator.cpp \
	CMap.cpp \
	CMedal.cpp \
	CMenu.cpp \
	CParticle_BossXPL.cpp \
	CParticle_PlayerXPL.cpp \
	CParticle_Smoke.cpp \
	CParticle_XPL.cpp \
	CParticles.cpp \
	CPlayer.cpp \
	CPlayerStat.cpp \
	CPopup.cpp \
	CShield.cpp \
	CSoundBank.cpp \
	CTile.cpp \
	FileManager.cpp \
	Stringify.cpp \
	Texture.cpp \
	TextureBank.cpp \
	CAnimation.h \
	CApp.h \
	CAppState.h \
	CAppStateCredits.h \
	CAppStateGame.h \
	CAppStateGameLose.h \
	CAppStateGameOver.h \
	CAppStateGamePause.h \
	Define.cpp \
	CEenemyQueue.h \
	CEnemyQueue.cpp \
	AndroidAssetManager.h \
	AndroidAssetManager.cpp \


LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL2_ttf libhidapi libmpg123

#LOCAL_WHOLE_STATIC_LIBRARIES := libandroid_native_app_glue

LOCAL_STATIC_LIBRARIES := libfirebase_admob libfirebase_app
#LOCAL_STATIC_LIBRARIES := android_native_app_glue

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -lstdc++ -landroid

LOCAL_CPPFLAGS  += -std=c++11

LOCAL_ARM_MODE:=arm

LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

include $(BUILD_SHARED_LIBRARY)