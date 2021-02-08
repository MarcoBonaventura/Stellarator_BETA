#ifndef __CAPPSTATEGAMEPAUSE_H__
    #define __CAPPSTATEGAMEPAUSE_H__

#include "CAppState.h"
#include "Texture.h"
#include "CMenu.h"
#include <vector>

class CAppStateGamePause : public CAppState {
		
		CMenu* BACKGROUND = NULL;
        CMenu* BACKGROUND2 = NULL;
		CMenu* HANGAR = NULL;
		CMenu* Menu = NULL;
		CMenu* Explorer = NULL;

		CMenu* Play = NULL;
		CMenu* Next = NULL;
		CMenu* Resume = NULL;
		CMenu* Exit = NULL;
		CMenu* Return = NULL;
		CMenu* Option = NULL;
		CMenu* Video = NULL;
		CMenu* Sound = NULL;

		CMenu* MotherShip = NULL;
		CMenu* Debrief = NULL;

		CMenu* Mission0 = NULL;
		CMenu* Mission1 = NULL;
		CMenu* Mission2 = NULL;
		CMenu* Mission3 = NULL;
		CMenu* Mission4 = NULL;
        CMenu* Mission5 = NULL;
        CMenu* Mission6 = NULL;
        CMenu* Mission7 = NULL;
        CMenu* Mission8 = NULL;
        CMenu* Mission9 = NULL;

		CMenu* Level0 = NULL;
		CMenu* Level1 = NULL;
		CMenu* Level2 = NULL;
		CMenu* Level3 = NULL;
		CMenu* Level4 = NULL;
		CMenu* LevelX = NULL;

		CMenu* ShipA = NULL;
		CMenu* ShipB = NULL;
		CMenu* ShipC = NULL;
		CMenu* ShipX = NULL;

		CMenu* ButtonVolSX = NULL;
		CMenu* ButtonVolDX = NULL;
		CMenu* SoundBar = NULL;
		//CMenu* TEST = NULL;

		CMenu*	Panel = NULL;

		static CAppStateGamePause Instance;

		static bool explorer;

        int StartTime, LastTime, interval, DELAY;
        int alpha, alpha_transparent;

        int X, Y, Width, Height;

        std::string     TextureName1, TextureName2;
		SDL_Renderer*   Renderer;
        SDL_Window*     Window;
        SDL_Surface*    PrimarySurface;
		
   

        CAppStateGamePause();

    public:

		static std::vector<CMenu*>vectorMenu;

		void OnKeyDown(SDL_Keysym sym);

        void OnKeyUp(SDL_Keysym sym);
		
		void OnTouchedDown(float tX, float tY);

		void OnTouchedUp(float tX, float tY);

		void OnTouchedMove(float tX, float tY, float dX, float dY);

		void OnMinimize();
		void OnRestore();

		void OnReset();

		void OnActivate();

        void OnDeactivate();

        void OnLoop();

		void OnRender();

		void freeMenu();

		void createMainP();
		void removeMainP();

		void createNextP();
		void removeNextP();

		void createResumeP();
		void removeResumeP();

		void createLevelCompleted();
		void removeLevelCompleted();

		void createLevelGameOver();
		void removeLevelGameOver();

		void createOptP();
		void removeOptP();

		void createPauseP();
		void removePauseP();

		void createSoundP();
		void removeSoundP();

		void createBACKGROUND();
		void removeBACKGROUND();

		void createHANGAR();
		void removeHANGAR();

		void createEXPLORER();
		void removeEXPLORER();

		void createMissionP();
		void removeMissionP();

    public:

        static CAppStateGamePause* GetInstance();

		static bool onPause;
		static bool mainP;
		static bool videoP;
		static bool soundP;
		static bool back;
		static bool menuTrans;

		static bool isRunning;

		enum stateMenu
		{
			MAIN = 0,
			NEWGAME = 1,
			PLAY = 2,
			SHIP = 3,
			OPTION = 4,
			VIDEO = 5,
			SOUND = 6,
			BACK = 7,
			RESUME = 8,
			NEXT = 9,
			MISSION = 10,
			COMPLETED = 11,
			GAME_OVER = 12,
			EXIT = 13
		};
		
		
		//int menuQueue[4];  
		static int newMenu;
		static int queueID;

		static void setActiveMenu(stateMenu e);
		
		
};

#endif
