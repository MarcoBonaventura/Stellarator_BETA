//==============================================================================
#ifndef _CCAMERA_H_
    #define _CCAMERA_H_

#include <SDL.h>
#include <math.h>

#include "Define.h"

//==============================================================================

enum {
	TARGET_MODE_NORMAL		= 0,
	TARGET_MODE_CENTER		= 1,
	TARGET_MODE_EXPLORER	= 2
};

//==============================================================================
class CCamera {

	public:

		static CCamera CameraControl;

		float X;
		float Y, Yg;

		float* TargetX;
		float* TargetY;

	public:

		int TargetMode;

	public:

		CCamera();
		void OnInit();

	public:

		void OnMove(float MoveX, float MoveY);

		float GetX();
		float GetY();
		float GetYgal();

		float ResetY();
		float ResetYg();

		float GetYint();

	public:

		void SetPos(float X, float Y);

		void SetTarget(float* X, float* Y);
};

//==============================================================================

#endif
