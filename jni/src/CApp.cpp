//==============================================================================
#include "CApp.h"
#include "CAppStateGame.h"
#include "CPlayer.h"
#include "Define.h"
#include <SDL.h>

#include <android/log.h>


#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)



bool CApp::Running = true;
bool CApp::game_OVER = false;


int	 CAppStateGame::currentMission = 0;
int	 CAppStateGame::currentLevel = 0;
bool CAppStateGame::onPause = false;
//bool CAppStateGame::levelCompleted = false;

bool CPlayer::GodMODE = false;
int	 CPlayer::PlayerHonor = 0;


const int   TICKS_PER_SECOND = 60;
const int   SKIP_TICKS = 1000 /TICKS_PER_SECOND;
const int   MAX_FRAMESKIP = 1;

long next_game_tick = SDL_GetTicks();
int loops;
bool success = false;

CApp CApp::Instance;


//==============================================================================
CApp::CApp() {

    Running = true;

}

CApp::~CApp() {

	SDL_Log("close app");

}


//-----------------------------------------------------------------------------
CApp* CApp::GetInstance() {

    return &CApp::Instance;

}


//------------------------------------------------------------------------------
int CApp::OnExecute() {

	if (!OnInit()) { return -1; }


    next_game_tick = SDL_GetTicks();

    SDL_Event Event;
    bool CAppPause = false;

    while(Running)
    {
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
            if(Event.type == SDL_QUIT) Running = false;

            if (Event.window.event == SDL_WINDOWEVENT_MINIMIZED || Event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
            {
                SDL_Log("FOCUS LOST/MINIMIZED");
            }
            else if(Event.window.event ==SDL_WINDOWEVENT_FOCUS_GAINED || Event.window.event == SDL_WINDOWEVENT_RESTORED)
            {
                //next_game_tick = SDL_GetTicks();
                SDL_Log("FOCUS GAINED/RESTORED");
                //CAppStateGame::GetInstance()->onPause = false;
            }
            //if (Event.type == CAppStateGame::GetInstance()->interstitial_event) CAppStateGame::GetInstance()->Call_Interstitial();

        }

        loops = 0;
        //SDL_Log("while-loop pre-step");
        while (SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP)
        {
            //SDL_Log("while-loop inside-step");
            OnLoop();

            //OnRender();

            next_game_tick += SKIP_TICKS;
            loops++;
            //SDL_Log("loops: %d - next_tick: %d - SDL_Ticks: %d", loops, next_game_tick, SDL_GetTicks());}

        }
        //SDL_Log("while-loop post-step");


        //interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_game_tick) /float(SKIP_TICKS);

        //OnLoop();
        OnRender();

    }

    OnCleanup();

	SDL_Quit();

#ifdef ANDROID
	exit(0);
#else
	return 0;
#endif


}



//==============================================================================
int main(int argc, char* argv[]) {

	CApp theApp;

    return theApp.OnExecute();
}
//==============================================================================
