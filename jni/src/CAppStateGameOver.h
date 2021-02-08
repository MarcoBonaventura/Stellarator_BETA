#ifndef __CAPPSTATEGAMEOVER_H__
    #define __CAPPSTATEGAMEOVER_H__

#include "CAppState.h"
#include "Texture.h"
#include "CPlayerStat.h"

class CAppStateGameOver : public CAppState {

    private:

        static CAppStateGameOver Instance;

        int StartTime;

        int X, Y, Width, Height, scroll;

        std::string     TextureName;
        SDL_Renderer*   Renderer;
        SDL_Window*     Window;
        SDL_Surface*    PrimarySurface;

    private:

        CAppStateGameOver();

    public:

        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender();

    public:

        static CAppStateGameOver* GetInstance();

        SDL_Renderer* GetRenderer();

        SDL_Window* GetWindow();



};

#endif
