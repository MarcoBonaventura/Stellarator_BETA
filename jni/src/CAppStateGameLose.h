#ifndef __CAPPSTATEGAMELOSE_H_
    #define __CAPPSTATEGAMELOSE_H_

#include "Texture.h"
#include "CPlayerStat.h"

class CAppStateGameLose : public CAppState {

    private:

        static CAppStateGameLose Instance;

        int StartTime;

    private:

        CAppStateGameLose();

        std::string     TextureName;
        SDL_Renderer*   Renderer;
        SDL_Window*     Window;
        SDL_Surface*    PrimarySurface;

        int X, Y;

    public:

        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender();

    public:

        static CAppStateGameLose* GetInstance();

        SDL_Renderer* GetRenderer();

        SDL_Window* GetWindow();


};

#endif
