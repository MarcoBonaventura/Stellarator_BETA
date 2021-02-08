#include "CAppStateManager.h"

// Refer to your Other App States Here
#include "CAppStateIntro.h"
#include "CAppStateGame.h"
//#include "CAppStateGameOver.h"
#include "CAppStateGamePause.h"
#include "CAppStateGameWin.h"
#include "CAppStateCredits.h"
#include "CAppStateGameLose.h"
#include "CAppStateTrans.h"


CAppState*  CAppStateManager::ActiveAppState = 0;

//-----------------------------------------------------------------------------
void CAppStateManager::OnEvent(SDL_Event *EventHolder) {

    if(ActiveAppState) ActiveAppState->OnEvent(EventHolder);

}


//-----------------------------------------------------------------------------
void CAppStateManager::OnActivate() {

}


//-----------------------------------------------------------------------------
void CAppStateManager::OnDeactivate() {
	
}


//-----------------------------------------------------------------------------
void CAppStateManager::OnLoop() {

    if(ActiveAppState) ActiveAppState->OnLoop();
	
}


//-----------------------------------------------------------------------------
void CAppStateManager::OnRender() {

    if(ActiveAppState) ActiveAppState->OnRender();

}


//-----------------------------------------------------------------------------
void CAppStateManager::SetActiveAppState(int AppStateID) {

    if(ActiveAppState) ActiveAppState->OnDeactivate();

    if(AppStateID == APPSTATE_NONE)
    {
        ActiveAppState = 0;
        //SDL_QUIT;
    }
    if(AppStateID == APPSTATE_INTRO)    ActiveAppState = CAppStateIntro::GetInstance();
    if(AppStateID == APPSTATE_GAME)     ActiveAppState = CAppStateGame::GetInstance();
    if(AppStateID == APPSTATE_PAUSE)    ActiveAppState = CAppStateGamePause::GetInstance();
    //if(AppStateID == APPSTATE_GAMEOVER) ActiveAppState = CAppStateGameOver::GetInstance();
    if(AppStateID == APPSTATE_GAMEWIN)  ActiveAppState = CAppStateGameWin::GetInstance();
    //if(AppStateID == APPSTATE_GAMELOSE) ActiveAppState = CAppStateGameLose::GetInstance();
    if(AppStateID == APPSTATE_CREDITS)  ActiveAppState = CAppStateCredits::GetInstance();
	
    ActiveAppState->OnActivate();
	
}


//-----------------------------------------------------------------------------
CAppState* CAppStateManager::GetActiveAppState() {

    return ActiveAppState;

}







