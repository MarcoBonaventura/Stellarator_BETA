#ifndef __CAPPSTATEMANAGER_H__
    #define __CAPPSTATEMANAGER_H__

#include "CAppState.h"

enum {
        APPSTATE_NONE,
        APPSTATE_INTRO,
        APPSTATE_GAME,
        APPSTATE_PAUSE,
        //APPSTATE_GAMEOVER,
        APPSTATE_GAMEWIN,
        //APPSTATE_GAMELOSE,
        APPSTATE_CREDITS,
		APPSTATE_LOADING
     };

class CAppStateManager {

		
    public:

        static CAppState *ActiveAppState;

    public:

        static void OnEvent(SDL_Event *Event);

        static void OnActivate();

        static void OnDeactivate();

        static void OnLoop();

        static void OnRender();

    public:

        static void SetActiveAppState(int AppStateID);

        static CAppState *GetActiveAppState();

		

};

#endif
