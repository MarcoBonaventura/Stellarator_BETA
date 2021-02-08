#ifndef _CPOPUP_H_
    #define _CPOPUP_H_

#include "CParticles.h"


class CPopup : public CParticles{

		CPopup();
		
    public:

		static CPopup Instance;

		SDL_Window		*Window;
		SDL_Renderer	*popupRenderer;

		//CPopup(int x, int y);
        ~CPopup();

        int timeToLive;
		int Xp, Yp;

		static bool show;

		bool OnLoad();

        void OnLoop();

        void OnMove();

        void OnRender();

        void OnCleanup();

        void EntityDEL();

		int setX(int x) { Xp = x; return Xp; }
		int setY(int y) { Yp = y; return Yp; }

		static CPopup *GetInstance() { return &Instance; };

};


#endif // CPOPUP_H_INCLUDED
