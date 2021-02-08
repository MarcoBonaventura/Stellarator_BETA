//==============================================================================
#include "CApp.h"
#include "TextureBank.h"
#include "CSoundBank.h"
#include "Define.h"
#include "Stringify.h"
#include "CCamera.h"

#include <iostream>

#include <android/log.h>

#include "jni.h"

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

SDL_Joystick* gGameController = NULL;
SDL_Haptic* gControllerHaptic = NULL;
SDL_Haptic* mouseHaptic = NULL;



//==============================================================================
bool CApp::OnInit() {


	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_TIMER | SDL_VIDEO_DRIVER_ANDROID) < 0)
	{
		SDL_Log("SDL_Init() error");
		return -1;
	}
	// get monitor resolution and refresh rate info
	SDL_Log("run testScreen()");
	testScreen();


	//check for mouse
	//Check for joysticks
	//Get controller haptic device

	mouseHaptic = SDL_HapticOpen(0);
	if (mouseHaptic == NULL)
	{
		SDL_Log("Warning: Mouse does not support haptics! SDL Error: %s", SDL_GetError());
	}
	else
	{
		//Get initialize rumble
		if (SDL_HapticRumbleInit(mouseHaptic) < 0)
		{
			SDL_Log("Warning: Unable to initialize Mouse rumble! SDL Error: %s", SDL_GetError());
		}
	}

	


	//Check for joysticks
	if (SDL_NumJoysticks() < 1)
	{
		SDL_Log("Warning: No joysticks connected!");
	}
	else
	{
		//Load joystick
		gGameController = SDL_JoystickOpen(0);
		if (gGameController == NULL)
		{
			SDL_Log("Warning: Unable to open game controller! SDL Error: %s", SDL_GetError());
		}
		else
		{
			//Get controller haptic device
			gControllerHaptic = SDL_HapticOpenFromJoystick(gGameController);
			if (gControllerHaptic == NULL)
			{
				SDL_Log("Warning: Controller does not support haptics! SDL Error: %s", SDL_GetError());
			}
			else
			{
				//Get initialize rumble
				if (SDL_HapticRumbleInit(gControllerHaptic) < 0)
				{
					SDL_Log("Warning: Unable to initialize rumble! SDL Error: %s", SDL_GetError());
				}
			}
		}
	}




    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
		SDL_Log("unable to initialize hinting");
        return false;
    }


    int code = Mix_Init(MIX_INIT_MP3);
    if (code & MIX_INIT_MP3) {
        SDL_Log("MP3 libraries loaded fine: %d", code);
    }


    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) { return false; }

    if( TTF_Init() == -1 ) { return false; }

	

    //-----INIT VIDEO MODE----------------------------------------------------
    /*
    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    */




    CAppStateManager::SetActiveAppState(APPSTATE_INTRO);

    return true;
}




//==============================================================================
