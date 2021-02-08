//==============================================================================
#include "CCamera.h"
#include "CFPS.h"
#include "CApp.h"
#include "Stringify.h"
#include "CAppStateGame.h";

#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

//==============================================================================
CCamera CCamera::CameraControl;

CFPS cameraFPS;

//==============================================================================
CCamera::CCamera() {

	X = 0;
	//Y = -(MapHeight * TILE_SIZE) *2; // MapHeight * TILE_SIZE * 60 >>>> see "1.area" file in "map" folder
	//Y = -1024;
	
	//Yg = ((MapHeight * TILE_SIZE) + (MapHeight * TILE_SIZE - WHEIGHT)); // same here but in "1.galaxy" file
	//Yg = -((MapHeight * TILEGAL_HSIZE));
	

	TargetX = NULL;
	TargetY = NULL;

	TargetMode = TARGET_MODE_NORMAL;

	

}

//==============================================================================
void CCamera::OnInit() {

	Yg = -((MapHeight * TILEGAL_HSIZE) * 2) + WHEIGHT;
	//Yg = -2176;
	Y = Yg;
	LOGD("CAMERA Yg: %f - Y: %f", Yg, Y);

	
}

//==============================================================================
void CCamera::OnMove(float MoveX, float MoveY) {

	X += MoveX;
	Y += MoveY;

}

//==============================================================================
float CCamera::GetX() {

	if(TargetX != NULL) 
	{
		if(TargetMode == TARGET_MODE_CENTER) 
		{
			return *TargetX - (WWIDTH / 2);
		}
		return *TargetX;
	}

	return X;

}

//------------------------------------------------------------------------------
float CCamera::GetY() {

	if(TargetMode == TARGET_MODE_EXPLORER) 
	{
		return Y;
	}
	else if (TargetMode == TARGET_MODE_NORMAL)
	{
		/** scroll background px/sec */
		Y += 1.50 * OVERALL_SPEED_RATIO;
        //SDL_Log("camera-Y %1.3f", Y);
		return Y;
	}
	
	//SDL_Log("TARGET_MODE undefined %d", TargetMode);

	//return Y;

}


//-----------------------------------------------------------------------------
float CCamera::ResetY() {

    //SDL_Log("reset camera-Y %1.3f", Y);
	return Y = -((MapHeight * TILE_SIZE) + (MapHeight * TILE_SIZE - WHEIGHT));

}

//-----------------------------------------------------------------------------
float CCamera::ResetYg() {

    SDL_Log("reset camera-Yg %f", Yg);
	return Yg = -((MapHeight * TILE_SIZE) + (MapHeight * TILE_SIZE - WHEIGHT));

}

//-----------------------------------------------------------------------------
float CCamera::GetYgal() {

    if(TargetY != NULL) 
	{
		if(TargetMode == TARGET_MODE_CENTER) 
		{
			//return *TargetY - (WHEIGHT / 2);
			return *TargetY - (WHEIGHT);
		}
		return *TargetY;
	}

    /** scroll background px/sec */
    Yg += 1.30 * OVERALL_SPEED_RATIO;
    //Y += 3 * CFPS::FPSControl.GetSpeedFactor();

	// SDL_Log("Camera-Yg %f", Yg);
	return Yg;

}


//=============================================================================
float CCamera::GetYint() {

	float IntY = (float)floor(CCamera::CameraControl.Y + 0.5);
	float anotherIntY = (float)(CCamera::CameraControl.Y + 0.5);
	float YetAnotherIntY = 0;

    if (CCamera::CameraControl.Y >= 0)
    {
		YetAnotherIntY = (float)(CCamera::CameraControl.Y + 0.5);
    }
    else
    {
		YetAnotherIntY = (float)(CCamera::CameraControl.Y - 0.5);
    }

    return YetAnotherIntY;

}


//==============================================================================
void CCamera::SetPos(float X, float Y) {

	this->X = X;
	this->Y = Y;

}

//------------------------------------------------------------------------------
void CCamera::SetTarget(float* X, float* Y) {

	TargetX = X;
	TargetY = Y;

}


