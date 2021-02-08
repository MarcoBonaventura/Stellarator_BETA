#include "CAppStateCredits.h"
#include "CAppStateManager.h"
#include "CAppStateIntro.h"

#include "CPlayerStat.h"

#include "CApp.h"


CAppStateCredits CAppStateCredits::Instance;

CAppStateCredits::CAppStateCredits() {

    SDL_Log("CAppStateCredits()");
    scroll = 400;

}

void CAppStateCredits::OnActivate() {

    StartTime = SDL_GetTicks();

    CApp::Logger.OnLog( __FILE__, __LINE__, "CAppStateGameCredits", "");
	SDL_Log("CAppStateGameCredits activated");

    Window   = CAppStateIntro::GetInstance()->GetWindow();

    Renderer = CAppStateIntro::GetInstance()->GetRenderer();

    SDL_SetRenderDrawColor(Renderer, 0xff, 0xff, 0xff, 0xff);

    TextureName = "Splash_CreditsRolls";

    X = (WWIDTH /2) -400;

}

void CAppStateCredits::OnDeactivate() {

    CApp::Logger.OnLog( __FILE__, __LINE__, "CAppStateGameCredits DEactivated", "");

	SDL_Log("CAppStateGameOver DEactivated");

	//SDL_Quit();

    // REMOVE PlayerStat SDL_Surface and SDL_Texture
    //CApp::Logger.OnLog( __FILE__, __LINE__, "Cleaning player stats", "");
    SDL_Log("PlayerStat.OnCleanup()");
    CPlayerStat::PlayerStat.OnCleaunp();


}

void CAppStateCredits::OnLoop() {

    if(StartTime + 18000 < SDL_GetTicks())
    {
        //CAppStateManager::SetActiveAppState(APPSTATE_NONE);
        CApp::Running = false;
    }

    scroll += -1;

}

void CAppStateCredits::OnRender() {

    if (Renderer) SDL_RenderClear(Renderer);

    if (Renderer)
    {
        TextureBank::Get(TextureName)->Render(X, scroll, 800, 1536, 255);
    }
    else
    {
		CApp::Logger.OnLog( __FILE__, __LINE__, "bad Renderer", "");
		SDL_Log("CAppStateGameCredits bad Renderer");
	}

    if (Renderer) SDL_RenderPresent(Renderer);

}

CAppStateCredits* CAppStateCredits::GetInstance() {

    return &Instance;

}

//-----------------------------------------------------------------------------
SDL_Renderer* CAppStateCredits::GetRenderer() {

    return Renderer;

}

//-----------------------------------------------------------------------------
SDL_Window* CAppStateCredits::GetWindow() {

    return Window;

}

