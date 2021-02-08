#ifndef _DEFINE_H_
    #define _DEFINE_H_

#include "jni.h"

#define MAP_WIDTH	4
#define MAP_HEIGHT	3
#define GAL_WIDTH   4
#define GAL_HEIGHT  3

#define TILE_SIZE	    256
#define TILEGAL_WSIZE   256
#define TILEGAL_HSIZE   256



//#define WWIDTH		1024
//#define	WHEIGHT		768

#define FRAME_X_SEC 120

extern int MapWidth;
extern int MapHeight;

extern int WWIDTH;
extern int WHEIGHT;

extern float SCREEN_W_RATIO;
extern float SCREEN_H_RATIO;

extern float OVERALL_RATIO;
extern float OVERALL_ENEMY_RATIO;
extern float OVERALL_SPEED_RATIO;
extern float OVERALL_BULLET_RATIO;

extern int x30;
extern int entityID;

extern int pointX;
extern int pointY;

extern int W_rect;
extern int H_rect;

extern JNIEnv* env;
extern jobject activity;

void testScreen();
JNIEnv* GetEnv();
jobject GetActivity();


#endif
