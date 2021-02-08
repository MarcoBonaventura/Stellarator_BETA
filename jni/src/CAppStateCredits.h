#ifndef __CAPPSTATECREDITS_H__
    #define __CAPPSTATECREDITS_H__

#include "CAppState.h"
#include "Texture.h"
#include "CPlayerStat.h"

class CAppStateCredits : public CAppState {

    private:

        static CAppStateCredits Instance;

        int StartTime;

        int X, scroll;

        std::string     TextureName;
        SDL_Renderer*   Renderer;
        SDL_Window*     Window;
        SDL_Surface*    PrimarySurface;

    private:

        CAppStateCredits();

    public:

        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender();

    public:

        static CAppStateCredits* GetInstance();

        SDL_Renderer* GetRenderer();

        SDL_Window* GetWindow();


};

#endif
