#include "CAppStateGameWin.h"
#include "CAppStateManager.h"
#include "CAppStateIntro.h"
#include "CAppStateGame.h"

#include "CPlayer.h"
#include "CPlayerStat.h"

#include "CSoundBank.h"
#include "CApp.h"


CAppStateGameWin CAppStateGameWin::Instance;

CAppStateGameWin::CAppStateGameWin() {

	SDL_Log("CAppStateWin()");

}

void CAppStateGameWin::OnActivate() {

	DELAY = 50;
	interval = 0;

    StartTime = SDL_GetTicks();

    Window   = CAppStateIntro::GetInstance()->GetWindow();

    Renderer = CAppStateIntro::GetInstance()->GetRenderer();

    SDL_SetRenderDrawColor(Renderer, 0xff, 0x00, 0x00, 0xFF);

	ScoreSurface = NULL;

    Width  = 1024;
    Height = 768;

    X = Y = 0;

    TextureName = "Splash_Victory_1024";
	textureScoreBase = "ScoreSurfaceBase2";
	textureGrade0 = "grade0";
	textureGrade1 = "grade1";
	textureGrade2 = "grade2";
	textureGrade3 = "grade3";
	textureGrade4 = "MedalBoss1";

	score0 = score1 = score2 = score3 = score4 = 0;

	// begin slot-machine sound-like
	//CSoundBank::SoundControl.Play(2, "coin_01", -1);

}

void CAppStateGameWin::OnDeactivate() {

	CSoundBank::SoundControl.Halt(2);


}

void CAppStateGameWin::OnLoop() {

    if(StartTime + 10000 < SDL_GetTicks())
    {
        //OnDeactivate();
        //CAppStateManager::SetActiveAppState(APPSTATE_CREDITS);

    }

	if (score0 >= CPlayer::PlayerStat.starSX) CSoundBank::SoundControl.Pause("coin_01");

	LastTime = SDL_GetTicks();



}

void CAppStateGameWin::OnRender() {

    if(Renderer) SDL_RenderClear(Renderer);

    if (Renderer)
    {
        TextureBank::Get(TextureName)->Render(X, Y, WWIDTH, WHEIGHT, 255);
	}
    else
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "bad Renderer", "");
    }

	int kX = 300;
	int kY = 85;
	for (int i = 0; i < 5; i++)
	{
		TextureBank::Get(textureScoreBase)->Render(kX, kY, 300, 70, 255);
		kY += 100;
	}

	TextureBank::Get(textureGrade0)->Render(320, 105, 30, 28, 255);
	TextureBank::Get(textureGrade1)->Render(320, 200, 30, 35, 255);
	TextureBank::Get(textureGrade3)->Render(320, 300, 35, 40, 255);
	TextureBank::Get(textureGrade4)->Render(320, 395, 30, 55, 255);

	if (score0 < CPlayer::PlayerStat.starSX) score0++;
	CPlayerStat::PlayerStat.OnRender(520, 90, 50, 60, score0, ScoreSurface);
	if (score1 < CPlayer::PlayerStat.starMM) score1++;
	CPlayerStat::PlayerStat.OnRender(520, 190, 50, 60, score1, ScoreSurface);
	if (score3 < CPlayer::PlayerStat.starM1) score3++;
	CPlayerStat::PlayerStat.OnRender(520, 290, 50, 60, score3, ScoreSurface);
	if (score4 < CPlayer::PlayerStat.starBB) score4++;
	CPlayerStat::PlayerStat.OnRender(520, 390, 50, 60, score0, ScoreSurface);
	
	SDL_Delay(30);
	
    
	if (Renderer) SDL_RenderPresent(Renderer);

}

void CAppStateGameWin::OnKeyDown(SDL_Keysym sym) {

	switch (sym.sym)
	{
	case SDLK_p: {
		if (interval > DELAY)
		{
			LastTime = LastTime - StartTime;
			std::cout << "OnPausa before lastPause: " << CAppStateGame::lastPause << std::endl;
			CAppStateGame::lastPause += LastTime;
			std::cout << "OnPausa LastTime: " << LastTime << " - lastPause: " << CAppStateGame::lastPause << std::endl;
			CAppStateManager::SetActiveAppState(APPSTATE_GAME);
			interval = 0;
		}
		break;
	}

	case SDLK_ESCAPE: {
		CAppStateManager::SetActiveAppState(APPSTATE_GAME);
		break;
	}

	default: {}
	}
}


//-----------------------------------------------------------------------------
void CAppStateGameWin::OnKeyUp(SDL_Keysym sym) {

	switch (sym.sym) {



	default: {
	}
	}


}


CAppStateGameWin* CAppStateGameWin::GetInstance() {

    return &Instance;

}

//-----------------------------------------------------------------------------
SDL_Renderer* CAppStateGameWin::GetRenderer() {

    return Renderer;

}

//-----------------------------------------------------------------------------
SDL_Window* CAppStateGameWin::GetWindow() {

    return Window;

}

