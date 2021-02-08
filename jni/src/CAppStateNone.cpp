#include "CAppStateNone.h"
#include "CAppStateManager.h"
#include "CAppStateIntro.h"

#include "CApp.h"


CAppStateNone CAppStateNone::Instance;

CAppStateNone::CAppStateNone() {

    SDL_Log("CAppStateNone()");

}

void CAppStateNone::OnActivate() {

    CApp::Logger.OnLog( __FILE__, __LINE__, "CAppStateNone", "");

}

void CAppStateNone::OnDeactivate() {



}

void CAppStateNone::OnLoop() {



}

void CAppStateNone::OnRender() {



}

CAppStateNone* CAppStateNone::GetInstance() {

    return &Instance;

}


