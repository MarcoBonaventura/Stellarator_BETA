//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "CApp.h"
//#include "CEntity.h
#include "Stringify.h"
#include "CAppStateGame.h"

bool CApp::LogFile = false;

//==============================================================================
void CApp::OnLoop() {
	



    CAppStateManager::OnLoop();



        CFPS::FPSControl.OnLoop();




    char Buffer[255];
    int a, b; 
    bool c;

	/*
    a = CFPS::FPSControl.GetFPS();
    b = CEntity::EntityList.size();
    c = CApp::LogFile;
	sprintf(Buffer, "FPS: %d - entity: %d - degub mode: %d", a, b, c);
	CApp::Logger.OnLog(__FILE__, __LINE__, "Frame in MAIN LOOP", Stringify::Int(a));
	*/

    //SDL_WM_SetCaption(Buffer, Buffer);

}

