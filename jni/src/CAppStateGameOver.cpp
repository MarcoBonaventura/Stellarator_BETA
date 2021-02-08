#include "CAppStateGameOver.h"
#include "CAppStateManager.h"
#include "CAppStateIntro.h"

#include "CApp.h"

#include <android/log.h>


CAppStateGameOver CAppStateGameOver::Instance;

CAppStateGameOver::CAppStateGameOver() {

	SDL_Log("!!CAppStateGameOver!!");
	StartTime = SDL_GetTicks();

}

void CAppStateGameOver::OnActivate() {


    StartTime = SDL_GetTicks();

    Window = CAppStateIntro::GetInstance()->GetWindow();

	Renderer = CAppStateIntro::GetInstance()->GetRenderer();

	SDL_SetRenderDrawColor(Renderer, 0xff, 0xff, 0xff, 0xff);
    
    X = Y = 0;

    TextureName = "Splash_Lose2_1024";

}

void CAppStateGameOver::OnDeactivate() {
	
    CApp::Logger.OnLog( __FILE__, __LINE__, "CAppStateGameOver deactivated", "");
	SDL_Log("CAppStateGameOver deactivated");

}

void CAppStateGameOver::OnLoop() {

	if(SDL_GetTicks() > StartTime + 5000)
    {
		SDL_Log("set APPSTATE_CREDITS");
		CAppStateManager::SetActiveAppState(APPSTATE_CREDITS);
    }

    
}

void CAppStateGameOver::OnRender() {

	if (Renderer)
	{
		SDL_RenderClear(Renderer);

		TextureBank::Get(TextureName)->Render(X, Y, WWIDTH, WHEIGHT, 255);
	
		SDL_RenderPresent(Renderer);
	}
	else
	{
		SDL_Log("CAppStateGameOver bad Renderer");
	}



}

CAppStateGameOver* CAppStateGameOver::GetInstance() {

    return &Instance;

}


//-----------------------------------------------------------------------------
SDL_Renderer* CAppStateGameOver::GetRenderer() {

    return Renderer;

}

//-----------------------------------------------------------------------------
SDL_Window* CAppStateGameOver::GetWindow() {

    return Window;

}
