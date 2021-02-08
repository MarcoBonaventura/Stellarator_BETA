#ifndef __CAPPSTATEGAMEWIN_H_
    #define __CAPPSTATEGAMEWIN_H_

#include "Texture.h"
#include "CPlayerStat.h"

class CAppStateGameWin : public CAppState {

    private:

        static CAppStateGameWin Instance;

		int StartTime, LastTime, interval, DELAY;

        int X, Y, Width, Height;
		int score0, score1, score2, score3, score4;

        std::string     TextureName, textureScoreBase;
		std::string		textureGrade0, textureGrade1, textureGrade2, textureGrade3, textureGrade4;
		SDL_Renderer*   Renderer;
        SDL_Window*     Window;
        SDL_Surface*    PrimarySurface;
		SDL_Surface*	ScoreSurface;

    private:

        CAppStateGameWin();

    public:

		void OnKeyDown(SDL_Keysym sym);

		void OnKeyUp(SDL_Keysym sym);

        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender();

    public:

        static CAppStateGameWin* GetInstance();

        SDL_Renderer* GetRenderer();

        SDL_Window* GetWindow();

};

#endif
