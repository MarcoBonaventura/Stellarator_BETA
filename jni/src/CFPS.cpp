#include "CFPS.h"
#include "CAppStateGame.h"

CFPS CFPS::FPSControl;

CFPS::CFPS() {

    OldTime     = 0;
    LastTime    = 0.0f;

    SpeedFactor = 0;

    Frames      = 0;
    NumFrames   = 0;
	FPS			= 60.0f;

}

void CFPS::OnLoop() {

    if(!CAppStateGame::GetInstance()->onPause)
    {

        //SDL_Log("CFPS:OnLoop()");

        if (OldTime + 1000 < SDL_GetTicks()) {
            OldTime = SDL_GetTicks();

            NumFrames = Frames;

            Frames = 0;

        }


        SpeedFactor = ((SDL_GetTicks() - LastTime) / 1000.0f) * FPS;

        LastTime = SDL_GetTicks();

        Frames++;

    }

}

int CFPS::GetFPS() {

    return NumFrames;

}

float CFPS::GetSpeedFactor() {

    return SpeedFactor;

}


