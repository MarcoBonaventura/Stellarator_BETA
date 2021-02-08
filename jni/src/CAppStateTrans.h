#ifndef __CAPPSTATETRANS_H__
    #define __CAPPSTATETRANS_H__

#include "CAppState.h"
#include "Texture.h"
#include "CMenu.h"
#include <vector>

class CAppStateTrans : public CAppState {
		
		CMenu* Menu = NULL;
		CMenu* Play = NULL;
		CMenu* Exit = NULL;
		CMenu* Option = NULL;
		CMenu* Video = NULL;
		CMenu* Sound = NULL;
		CMenu* Return = NULL;

		CMenu* ButtonVolSX = NULL;
		CMenu* ButtonVolDX = NULL;
		CMenu* SoundBar = NULL;
		//CMenu* TEST = NULL;

		CMenu*	Panel = NULL;

        static CAppStateTrans Instance;

		

        int StartTime, LastTime, interval, DELAY;
        int alpha, alpha_transparent;

        int X, Y, Width, Height;

        std::string     TextureName1, TextureName2;
		SDL_Renderer*   Renderer;
        SDL_Window*     Window;
        SDL_Surface*    PrimarySurface;
		
    private:

        CAppStateTrans();

    public:

		static std::vector<CMenu*>vectorMenu;

		void OnKeyDown(SDL_Keysym sym);

        void OnKeyUp(SDL_Keysym sym);
		
		void OnTouchedDown(float tX, float tY);

		void OnTouchedUp(float tX, float tY);

		void OnTouchedMove(float tX, float tY);
		
		void OnActivate();

        void OnDeactivate();

        void OnLoop();

		void OnRender();

		void freeMenu();

		void createMainP();
		void removeMainP();

		void createOptP();
		void removeOptP();

		void createSoundP();
		void removeSoundP();

    public:

        static CAppStateTrans* GetInstance();

		static bool onPause;
		static bool mainP;
		static bool videoP;
		static bool soundP;
		static bool back;
		static bool menuTrans;

		static bool isRunning;

		enum stateMenu
		{
			MAIN	= 0,
			NEWGAME = 1,
			PLAY	= 2,
			OPTION	= 3,
			VIDEO	= 4,
			SOUND	= 5,
			BACK	= 6,
			EXIT	= 7
		};
		
		//int menuQueue[4];  
		static int newMenu;
		static int queueID;

		static void setActiveMenu(stateMenu e);
		

};

#endif
