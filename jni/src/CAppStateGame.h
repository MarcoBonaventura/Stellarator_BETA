#ifndef __CAPPSTATEGAME_H__
    #define __CAPPSTATEGAME_H__

#include "SDL_thread.h"
#include "Define.h"

#include "CAppState.h"

#include "CArea.h"
#include "CCamera.h"
#include "CGalaxy.h"
#include "CEntity.h"
#include "Texture.h"

#include "CPlayer.h"
#include "CShield.h"
#include "CPlayerStat.h"
#include "CAsteroid.h"

#include "CMedal.h"

#include "CBulletBOSS1.h"
#include "CGenerator.h"

#include "CEnemyQueue.h"

#include "CAppStateGamePause.h"
#include "CMenu.h"



#include "jni.h"


static struct android_app* g_app_state = nullptr;



class CAppStateGame : public CAppState {

    private:

        static CAppStateGame	Instance;
		static int				lastLevel;
		
		static bool				DisplayTouch;
        static int              EnemyAlive;



		CPlayer*        Player;

		CMedal          *MedalHonor;
        
        CAsteroid*      asteroid;

        std::string     TextureName;
        SDL_Renderer*   Renderer;
        SDL_Window*     Window;
        SDL_Surface*    PrimarySurface;

        SDL_Surface*    Surf_Display;

        float   interval, DELAY, DELAY_BOMB, DELAY_ROCKET, bombCounter, attack, enemy_Timer, enemy_Fire, BOSS_interval, BOSScounter;
        float   dXw, dYh, speed_inc;

		int     TimeOut, gamePlay, gamePlay2, levelStarted;
        int     x, y, a, b, c, fps;
        int		AreaSize;


        char	*game_ini;
		char	*fileLevel;
        char	*tempSoundLevel;
		char	TileMapFile[255];
		char	TileAreaFile[255];
		char	tempc[512];
		char	*t_e;

		char  	*new_line;
		
        Uint32  color;

		static bool MedalEvent;
		static bool MedalEventBoss;

		//CAppStateGamePause*	OptionButton;

        static SHud PLYHUD;
        static SBarStamina PLYBAR;





        //static void WaitForFutureCompletion(firebase::FutureBase future);
		

    private:

        CAppStateGame();

        //void MakeSmall_move();













    public:

        void OnKeyDown(SDL_Keysym sym);

        void OnKeyUp(SDL_Keysym sym);

		void OnTouchedDown(float tX, float tY);

		void OnTouchedUp(float tX, float tY);

		void OnTouchedMove(float tX, float tY, float dX, float dY);

		void OnMinimize();
		void OnRestore();

    
        void OnActivate();
		void OnDeactivate();

        void OnLoop();

        void OnLoad(char* File);

        void OnRender();

        void OnGenerator();

        void PlayerStat();

		void SwitchPlayerFiremode(int fm);

		void showADS();

		static Uint32   interstitial_event;


		static bool g_destroy_requested;
		static bool g_started;
		static bool g_restarted;
		static pthread_mutex_t g_started_mutex;

		

    public:

        static CAppStateGame *GetInstance();

		//std::vector<CEnemyQueue>	EnemyList;

        SDL_Renderer* GetRenderer();

        SDL_Window* GetWindow();

		static int		GetGameLoopTime() { return TimeLeft; };
		static int		GetGameCountLoop() { return countLoop; };

        static bool		levelCompleted;
		static bool		appMinimized;
		static bool     interstitialEvent;
		static bool		nextState;
		static bool		onPause;
        static bool     onReset;

        static int		count_M1;
        static int		count_M2;
		static int		count_M3;
		static int		count_M4;
		static int		count_M5;
		static int 		count_M6;

		static int		TimeLeft, DeadTime;
		static int		BossTimeDeath;

		static int		scene;
		
		static char		tempSoundBoss[255];
        static int      lastPause;
		static int		BG_volume;
		static int		volumeTuning;
		static void		setVolume(int vt);

		static int		StepA1;
		static int		StepA2;
		static int		StepB1;
		static int		StepB2;
		static int		StepC1;
		static int		StepC2;

		static  long    countLoop;

		static void		ResetLastLevel();

		static void		IncLastLevel() { lastLevel++; };

		static int		GetLastLevel() { return lastLevel; };
		static int		currentMission, currentLevel;
		static int      E, nEnemy;

        static int      CountEnemy();

		static bool 	ProcessEvents(int msec);

		static void		CheckJNIException();

		void            Call_Interstitial();

		void LotteryEvents(CEntity* Entity);

		//static bool		SetOnPause(bool pause);

		//static bool		GetOnPause();

		/*
		static int	Sound_PlayerXPL, Sound_explSX1, Sound_explSX2, Sound_explSX3, Sound_PlayerFire, Sound_Main_BG,
					Sound_BOSSlaser, Sound_Boss, Sound_Medal, Sound_MedalBoss, Sound_BossExpl;
		*/

		std::string Sound_Main_BG, Sound_Boss;
};

#endif
