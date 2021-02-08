#include "Define.h"
#include "Stringify.h"
#include "CApp.h"

#include <SDL.h>
#include <SDL_ttf.h>
//#include <SDL_opengl.h>

float OVERALL_RATIO;
float OVERALL_ENEMY_RATIO;
float OVERALL_SPEED_RATIO;
float OVERALL_BULLET_RATIO;


void testScreen()
{
	SDL_DisplayMode current;
	int i;

	for (i = 0; i < SDL_GetNumVideoDisplays(); ++i)
	{
		if ((SDL_GetCurrentDisplayMode(i, &current)) != 0)
		{
			SDL_Log("unable to retrieve display mode\n");
		}
		else
		{
			WWIDTH = current.w;
			WHEIGHT = current.h;
		}
	}

	SCREEN_W_RATIO = (float)(WWIDTH) / 835;
	SCREEN_H_RATIO = (float)(WHEIGHT) / 1600;

	if (WHEIGHT < 1300) {
		OVERALL_RATIO = 0.25;
		OVERALL_BULLET_RATIO = 0.40;
		OVERALL_ENEMY_RATIO = 0.60;
		OVERALL_SPEED_RATIO = 0.70;
	}
	else if (WHEIGHT >= 1300 && WHEIGHT <= 2000) {
		OVERALL_RATIO = 0.45;
		OVERALL_BULLET_RATIO = 0.70;
		OVERALL_ENEMY_RATIO = 1.00;
		OVERALL_SPEED_RATIO = 1.00;
	}
	else if (WHEIGHT > 2000) {
		OVERALL_RATIO = 0.60;
		OVERALL_BULLET_RATIO = 1.00;
	    OVERALL_ENEMY_RATIO = 1.25;
	    OVERALL_SPEED_RATIO = 1.25;
	}

	MapWidth = WWIDTH / TILEGAL_WSIZE + 1;
    MapHeight = WHEIGHT / TILEGAL_HSIZE;
	MapHeight = WHEIGHT / TILEGAL_HSIZE;
    int temp_DELTA_H = MapHeight * TILEGAL_HSIZE;
    if (temp_DELTA_H < WHEIGHT) MapHeight++;

	SDL_Log("WWIDTH %d", WWIDTH);
	SDL_Log("WHEIGHT %d", WHEIGHT);
	SDL_Log("Mapwidth %d", MapWidth);
	SDL_Log("MapHeight %d", MapHeight);
	SDL_Log("OVERALL_RATIO %1.3f", OVERALL_RATIO);
	SDL_Log("OVERALL_ENEMY_RATIO %1.3f", OVERALL_ENEMY_RATIO);
	SDL_Log("OVERALL_SPEED_RATIO %1.3f", OVERALL_SPEED_RATIO);

	x30 = WWIDTH * 0.30;

	pointX = (WWIDTH / 100) * 10;
	pointY = (WHEIGHT / 100) * 50;
	W_rect = (WWIDTH / 100) * 90;
	H_rect = 100;

}

JNIEnv* GetEnv() {

	// retrieve the JNI environment.
	JNIEnv* env = static_cast<JNIEnv*>(SDL_AndroidGetJNIEnv());

	assert(env);

	return env;

}

jobject GetActivity() {

	// retrieve the Java instance of the SDLActivity
	jobject activity = static_cast<jobject>(SDL_AndroidGetActivity());

	return activity;



}