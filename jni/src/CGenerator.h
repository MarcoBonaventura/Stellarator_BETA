#ifndef _CGENERATOR_H_
    #define _CGENERATOR_H_

#include "CEnemySX.h"
#include "CEnemySX_move.h"
#include "CEnemyMM.h"
#include "CEnemyMM_2.h"
#include "CEnemyMM_3.h"
#include "CEnemyBOSS1.h"
#include "CAppStateGame.h"
#include "CMedal.h"
#include "CCannon.h"
#include "CPlayerStat.h"

enum bonusEvent
{
	EVENT_TRIPLE_FIRE 	= 1,
	EVENT_PENTA_FIRE 	= 2,
	EVENT_ROCKET_SMART 	= 3,
	EVENT_GAMMARAY		= 4,
	EVENT_TOTAL_FIRE	= 5,
	EVENT_BONUS_POINT	= 6,
	EVENT_BOSS			= 7
};



class CGenerator {

        float a, b, c;
        int x, y;
		static int EE;
        int temp_EE;
		int M2_x1, M2_x2;

        int gamePlay;
        int DeadTime;
		int enemyPause;

		bool shot;


		//int StepA1, StepA2, StepB1, StepB2;

		CEnemySX		*ENEMY_SX 		= NULL;
		CEnemySX_move   *ENEMY_SX_MOVE 	= NULL;
		CEnemyMM    	*EnemyMM 		= NULL;
		CEnemyMM_2  	*EnemyMM2 		= NULL;
		CEnemyMM_3		*EnemyMM3 		= NULL;
		CEnemyBOSS1 	*Boss1 			= NULL;


		CCannon*	CannonSX			= NULL;
		CCannon*	CannonDX	 		= NULL;


    public:

		enum Medals{
			FIRE_TRIPLE 	= 1,
			FIRE_PENTA 		= 2,
			FIRE_ROCKET 	= 3,
			FIRE_GAMMARAY 	= 4,
			FIRE_TOTAL 		= 5,
			BONUS_POINT		= 6,
			BOSS			= 10
		};
        //CEnemySX *EnemyZ;
        //CEnemyMM *EnemyMM = NULL;
        //CEnemyBOSS1     *EnemyBOSS1;

		static CGenerator   EnemyMaker;

		static SHud BOSSHUD;
		static SBarStamina BOSSBAR;

		static Uint32		BossEventType;
		static Uint32		Medal_1_EventType;
		static Uint32		Medal_2_EventType;
		static Uint32		Medal_3_EventType;
		static Uint32		Medal_4_EventType;
		static Uint32		Medal_5_EventType;
		static Uint32		Medal_6_EventType;

		static int      countEnemyMM2;
		static bool		BonusMM2;
		static int      countEnemyMM2_overall;
		static int     	xc;


        CGenerator();

        void OnGenerator(long counter, long gameplay);

        int TimeLeft;

        void MakeSmall0();
        void MakeSmall1();
		void MakeSmall2();
		void MakeSmall3();
		void MakeSmall4();
		void MakeSmall5();
		void MakeSmall6();
		void MakeSmall7();
		void MakeSmall8();
		void MakeSmall9();

		void MakeMedium0();
		void MakeMedium1();
		void MakeMedium2();
		void MakeMedium3();
		void MakeMedium4();
		void MakeMedium5();
		void MakeMedium6();

        void MakeBoss1();
		void MakeBoss2();
		void MakeBoss3();
		void MakeBoss4();
		void MakeBoss5();
		void MakeBoss6();
		void MakeBoss7();
		void MakeBoss8();
		void MakeBoss9();
		void MakeBossX();

		void BossHUD();
		void BossSoundStage();

        //bool LevelCompleted();

        int getDeadTime();

		static void setEE(int e) { EE = e; };
		static int getEE() { return EE; };

		void LotteryEvents();
		void CreateBossEvent();
		void CreateMedal_1_Event();
		void CreateMedal_2_Event();
		void CreateMedal_3_Event();
		void CreateMedal_4_Event();
		void CreateMedal_5_Event();
		void CreateMedal_6_Event();

		static int setXC(int temp_x) { xc = temp_x; }


};


#endif
