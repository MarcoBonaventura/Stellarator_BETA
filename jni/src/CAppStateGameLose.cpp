#include "CAppStateGameLose.h"
#include "CAppStateManager.h"
#include "CAppStateIntro.h"

#include "CApp.h"


CAppStateGameLose CAppStateGameLose::Instance;

CAppStateGameLose::CAppStateGameLose() {

    SDL_Log("CAppStateGameLose()");

}

void CAppStateGameLose::OnActivate() {

    StartTime = SDL_GetTicks();

    Window   = CAppStateIntro::GetInstance()->GetWindow();

    Renderer = CAppStateIntro::GetInstance()->GetRenderer();

    TextureName = "Splash_Lose2_1024";

    X = Y = 0;

}

void CAppStateGameLose::OnDeactivate() {



}

void CAppStateGameLose::OnLoop() {

    if(StartTime + 8000 < SDL_GetTicks())
    {
        //CAppStateManager::SetActiveAppState(APPSTATE_GAMEOVER);
    }



}

void CAppStateGameLose::OnRender() {


    if (Renderer)
    {
		SDL_RenderClear(Renderer);
        TextureBank::Get(TextureName)->Render(0, 0, WWIDTH, WHEIGHT, 255);
		SDL_RenderPresent(Renderer);
	}
    else
    {
		SDL_Log("CAppStateGameLose bad Renderer\n");
        //CApp::Logger.OnLog( __FILE__, __LINE__, "bad Renderer", "");
    }

   

}

CAppStateGameLose* CAppStateGameLose::GetInstance() {

    return &Instance;

}
