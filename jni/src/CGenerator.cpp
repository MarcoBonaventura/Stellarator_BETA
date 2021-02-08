//=============================================================================
#define _CRT_SECURE_NO_DEPRECATE

#include "CGenerator.h"
#include "CPlayer.h"
#include "CPlayerStat.h"
#include "Stringify.h"

#include <random>
#include <iostream>
#include <cfloat> // DBL_MAX
#include <cmath> // std::nextafter

#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

CGenerator CGenerator::EnemyMaker;

Uint32 CGenerator::BossEventType = 10;
Uint32 CGenerator::Medal_1_EventType = 1;
Uint32 CGenerator::Medal_2_EventType = 2;
Uint32 CGenerator::Medal_3_EventType = 3;
Uint32 CGenerator::Medal_4_EventType = 4;
Uint32 CGenerator::Medal_5_EventType = 5;
Uint32 CGenerator::Medal_6_EventType = 6;

//int x30;
int StepA1 = CAppStateGame::StepA1;
int StepA2 = CAppStateGame::StepA2;
int StepB1 = CAppStateGame::StepB1;
int StepB2 = CAppStateGame::StepB2;
int StepC1 = CAppStateGame::StepC1;
int StepC2 = CAppStateGame::StepC2;

int	CGenerator::xc      = 0;
int CGenerator::EE      = 0;

int entityID = 0;

int		CGenerator::countEnemyMM2 = 0;
int		CGenerator::countEnemyMM2_overall = 0;

bool	CGenerator::BonusMM2 = false;

SHud CGenerator::BOSSHUD = {};
SBarStamina CGenerator::BOSSBAR = {};


CGenerator::CGenerator() {

    DeadTime = 0;

	EE = 0;
	

	

};

void CGenerator::OnGenerator(long counter, long gameplay) {

    TimeLeft = SDL_GetTicks();
    shot = true;

	//SDL_Log("OnGenerator(....) : %d", EE);


	//SDL_Log("CGenerator scene: %d", EE);
	//SDL_Log("CAppStateGame scene: %d", CAppStateGame::scene);

    //if (SDL_GetTicks() %100 == 0) SDL_Log("run scene %d", EE);

	int r = 0;
    if (EE < CAppStateGame::scene + 1)
	{
		if (!CEnemyQueue::EnemyList[EE].empty())
		{

			//while(!CEnemyQueue::EnemyList[EE].empty())
			//{
			//LOGD("CGenerator EnemyList size: %d", CEnemyQueue::EnemyList[EE].size());
			//CApp::Logger.OnLog(__FILE__, __LINE__, "EE", Stringify::Int(EE));
			//CApp::Logger.OnLog(__FILE__, __LINE__, "r", Stringify::Int(r));
			//CApp::Logger.OnLog(__FILE__, __LINE__, "EnemyListPolls", Stringify::Int(CEnemyQueue::EnemyList[EE][r].EnemySize));
			//CApp::Logger.OnLog(__FILE__, __LINE__, "EnemyListPolls", Stringify::Int(CEnemyQueue::EnemyList[EE][r].EnemyTimer));
			switch (CEnemyQueue::EnemyList[EE][r].EnemySize)
			{
				case 0:
					if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
						//SDL_Log("CGenerator  case3 EE: %d", EE);
						MakeSmall0();
					}
					break;
				case 1:
					if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
						//SDL_Log("CGenerator case4 EE: %d", EE);
						MakeSmall1();
					}
					break;
                case 2:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case4 EE: %d", EE);
                        MakeSmall2();
                    }
                    break;
                case 3:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case4 EE: %d", EE);
                        MakeSmall3();
                    }
                    break;
                case 4:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case4 EE: %d", EE);
                        MakeSmall4();
                    }
                    break;
				case 5:
					if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
						//SDL_Log("CGenerator case5 EE: %d", EE);
						MakeSmall5();
					}
					break;
				case 6:
					if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
						//SDL_Log("CGenerator case5 EE: %d", EE);
						MakeSmall6();
					}
					break;
				case 7:
					if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
						//SDL_Log("CGenerator case8 EE: %d", EE);
						//SDL_Log("CGenerator EnemyList size: %d", CEnemyQueue::EnemyList[EE].size());
						MakeSmall7();
					}
					break;
                case 8:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case8 EE: %d", EE);
                        //SDL_Log("CGenerator EnemyList size: %d", CEnemyQueue::EnemyList[EE].size());
                        MakeSmall8();
                    }
                    break;
				case 9:
					if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
						//SDL_Log("CGenerator case8 EE: %d", EE);
						//SDL_Log("CGenerator EnemyList size: %d", CEnemyQueue::EnemyList[EE].size());
						MakeSmall9();
					}
					break;
                case 10:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case8 EE: %d", EE);
                        //SDL_Log("CGenerator EnemyList size: %d", CEnemyQueue::EnemyList[EE].size());
                        MakeMedium0();
                    }
                    break;
			    case 11:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case8 EE: %d", EE);
                        //SDL_Log("CGenerator EnemyList size: %d", CEnemyQueue::EnemyList[EE].size());
                        MakeMedium1();
                    }
                    break;
                case 12:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case8 EE: %d", EE);
                        //SDL_Log("CGenerator EnemyList size: %d", CEnemyQueue::EnemyList[EE].size());
                        MakeMedium2();
                    }
                    break;
                case 13:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case8 EE: %d", EE);
                        //SDL_Log("CGenerator EnemyList size: %d", CEnemyQueue::EnemyList[EE].size());
                        MakeMedium3();
                    }
                    break;
                case 14:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case8 EE: %d", EE);
                        //SDL_Log("CGenerator EnemyList size: %d", CEnemyQueue::EnemyList[EE].size());
                        MakeMedium4();
                    }
                    break;
			    case 15:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case8 EE: %d", EE);
                        //SDL_Log("CGenerator EnemyList size: %d", CEnemyQueue::EnemyList[EE].size());
                        MakeMedium5();
                    }
                    break;
                case 16:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case8 EE: %d", EE);
                        //SDL_Log("CGenerator EnemyList size: %d", CEnemyQueue::EnemyList[EE].size());
                        MakeMedium6();
                    }
                    break;
				case 101:
					if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
						//SDL_Log("CGenerator case10 EE: %d", EE);
						MakeBoss1();
					}
					break;
                case 102:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case10 EE: %d", EE);
                        MakeBoss2();
                    }
                    break;
                case 103:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case10 EE: %d", EE);
                        MakeBoss3();
                    }
                    break;
                case 104:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case10 EE: %d", EE);
                        MakeBoss4();
                    }
                    break;
                case 105:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case10 EE: %d", EE);
                        MakeBoss5();
                    }
                    break;
                case 106:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case10 EE: %d", EE);
                        MakeBoss6();
                    }
                    break;
                case 107:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case10 EE: %d", EE);
                        MakeBoss7();
                    }
                    break;
                case 108:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case10 EE: %d", EE);
                        MakeBoss8();
                    }
                    break;
                case 109:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case10 EE: %d", EE);
                        MakeBoss9();
                    }
                    break;
                case 110:
                    if (counter % CEnemyQueue::EnemyList[EE][0].EnemyTimer == 0) {
                        //SDL_Log("CGenerator case10 EE: %d", EE);
                        MakeBossX();
                    }
                    break;

			}

			//break;
			//}

			enemyPause = SDL_GetTicks();
		}
		else
		{
		    //SDL_Log("enemy list empty");
			gamePlay = SDL_GetTicks();
			if (gamePlay > enemyPause + 3000)
			{
				if (CAppStateGame::CountEnemy() == 0) {
                    SDL_Log("EnemyListSize = %d then next scene!", CAppStateGame::CountEnemy());
                    if (EE != CAppStateGame::scene) LotteryEvents();
                    EE++;
				}
			}
		}
	}
	else if (EE == CAppStateGame::scene)
	{
	    //SDL_Log("Boss scene %d", CAppStateGame::scene);
		if (!Boss1) Mix_FadeOutChannel(-1, 3000);
	}



	//SDL_Log("CGenerator() invocated");

}



/// ****** SMALL ENEMY *****

/// standard
void CGenerator::MakeSmall0() {

    //-----GENERATE ENEMY SIZE SX---------------------------------------------


	int x = 0;
	x += (rand() % (WWIDTH - 200) + 64);
	int y = -300;

	SDL_Log("generate SX Enemy");

	ENEMY_SX = new CEnemySX(x, y);

	switch (CAppStateGame::currentMission)
    {
		case 1: // MISSION GREY ENEMY
        {

            //SDL_Log("MISSION GREY ENEMY");
            switch (rand() % 3)
            {

                case 0:
                    ENEMY_SX->selected = 0;
                    ENEMY_SX->entityTexture = "EnemySX_grey1_anim";
                    break;

                case 1:
                    ENEMY_SX->selected = 1;
                    ENEMY_SX->entityTexture = "EnemySX_grey2_anim";
                    break;

                case 2:
                    ENEMY_SX->selected = 2;
                    ENEMY_SX->entityTexture = "EnemySX_grey3_anim";
                    break;

                case 3:
                    ENEMY_SX->selected = 3;
                    ENEMY_SX->entityTexture = "EnemySX_grey4_anim";
                    break;

                case 4:
                    ENEMY_SX->selected = 4;
                    ENEMY_SX->entityTexture = "EnemySX_grey5_anim";
                    break;

                default:
                    ENEMY_SX->selected = 0;
                    ENEMY_SX->entityTexture = "EnemySX_grey1_anim";
                    break;
            }
            break;
        }// END MISSION GREY ENEMY

        case 2: // MISSION DARK ENEMY

            break;
        // END MISSION DARK ENEMY

        case 3: // MISSION YELLOW ENEMY

            break;
        // END MISSION YELLOW ENEMY

        case 4: // MISSION GREEN ENEMY

            break;
        // END MISSION GREEN ENEMY

        case 5: // FINAL MISSION - BIG_BOSS
            break;

	}

	ENEMY_SX->W2 = 150;
	ENEMY_SX->H2 = 150;
    ENEMY_SX->Width = ENEMY_SX->W2 * OVERALL_ENEMY_RATIO;
    ENEMY_SX->Height = ENEMY_SX->H2 * OVERALL_ENEMY_RATIO;
	ENEMY_SX->Dead = false;
	ENEMY_SX->Size = ENTITY_SIZE_SX;
	ENEMY_SX->Flags = ENTITY_FLAG_ENEMY_S;
	ENEMY_SX->OnInit();

	CEntity::EntityList.push_back(ENEMY_SX);
    CEntity::EntityMap[ENEMY_SX->ID]=ENEMY_SX;
    CEntity::TargetEnemyMap[ENEMY_SX->ID] = ENEMY_SX;
	SDL_Log("Enemy instance ID: %d", ENEMY_SX->ID);


	char TempC[255];
	int Temp = CEntity::EntityList.size();
	int n = sprintf(TempC, "%d", Temp);
	CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

	//if(!CPlayer::PlayerStat.GetDisabledFire()) CPlayer::PlayerStat.switchPlayerFire();


}




/// move dx
void CGenerator::MakeSmall1() {

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY
        {

            for (int i = 0; i < 20; i++)
            {

                int x = (-250 * (i + 1)) * OVERALL_ENEMY_RATIO;
                int y = 100;

                ENEMY_SX_MOVE = new CEnemySX_move(x, y, MOVE_DX);

                ENEMY_SX_MOVE->selected = 3;
                ENEMY_SX_MOVE->entityTexture = "EnemySX_grey4_anim";
                ENEMY_SX_MOVE->W2 = 150;
                ENEMY_SX_MOVE->H2 = 150;
                ENEMY_SX_MOVE->Width = ENEMY_SX_MOVE->W2 * OVERALL_ENEMY_RATIO;
                ENEMY_SX_MOVE->Height = ENEMY_SX_MOVE->H2 * OVERALL_ENEMY_RATIO;
                ENEMY_SX_MOVE->Dead = false;
                ENEMY_SX_MOVE->Size = ENTITY_SIZE_SSX;
                ENEMY_SX_MOVE->Flags = ENTITY_FLAG_ENEMY_S;
                ENEMY_SX_MOVE->OnInit();

                CEntity::EntityList.push_back(ENEMY_SX_MOVE);
                CEntity::EntityMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                CEntity::TargetEnemyMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE->ID);

                /*
                char TempC[255];
                int Temp = CEntity::EntityList.size();
                int n = sprintf(TempC, "%d", Temp);
                */
            }
        }
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        }

    //if(!CPlayer::PlayerStat.GetDisabledFire()) CPlayer::PlayerStat.switchPlayerFire();
    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}

/// move sx
void CGenerator::MakeSmall2() {

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY
        {

            for (int i = 0; i < 20; i++) {

                int x = (WWIDTH + 250 * (i + 1)) * OVERALL_ENEMY_RATIO;
                int y = 300 * OVERALL_ENEMY_RATIO;

                ENEMY_SX_MOVE = new CEnemySX_move(x, y, MOVE_SX);

                ENEMY_SX_MOVE->selected = 3;
                ENEMY_SX_MOVE->entityTexture = "EnemySX_grey4_anim";
                ENEMY_SX_MOVE->W2 = 150;
                ENEMY_SX_MOVE->H2 = 150;
                ENEMY_SX_MOVE->Width = ENEMY_SX_MOVE->W2 * OVERALL_ENEMY_RATIO;
                ENEMY_SX_MOVE->Height = ENEMY_SX_MOVE->H2 * OVERALL_ENEMY_RATIO;
                ENEMY_SX_MOVE->Dead = false;
                ENEMY_SX_MOVE->Size = ENTITY_SIZE_SSX;
                ENEMY_SX_MOVE->Flags = ENTITY_FLAG_ENEMY_S;
                ENEMY_SX_MOVE->OnInit();

                CEntity::EntityList.push_back(ENEMY_SX_MOVE);
                CEntity::EntityMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                CEntity::TargetEnemyMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                SDL_Log("Enemy SX move sx instance ID: %d", ENEMY_SX_MOVE->ID);

                /*
                char TempC[255];
                int Temp = CEntity::EntityList.size();
                int n = sprintf(TempC, "%d", Temp);
                */
            }
        }
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;
    }

    //if(!CPlayer::PlayerStat.GetDisabledFire()) CPlayer::PlayerStat.switchPlayerFire();
    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}

/// escape dx
void CGenerator::MakeSmall3() {

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY
        {

            for (int i = 0; i < 20; i++)
            {

                int x = (-250 * (i + 1)) * OVERALL_ENEMY_RATIO;
                int y = WHEIGHT * 0.5;

                ENEMY_SX_MOVE = new CEnemySX_move(x, y, ESCAPE_DX);

                ENEMY_SX_MOVE->selected = 3;
                ENEMY_SX_MOVE->entityTexture = "EnemySX_grey4_anim";
                ENEMY_SX_MOVE->W2 = 150;
                ENEMY_SX_MOVE->H2 = 150;
                ENEMY_SX_MOVE->Width = ENEMY_SX_MOVE->W2 * OVERALL_ENEMY_RATIO;
                ENEMY_SX_MOVE->Height = ENEMY_SX_MOVE->H2 * OVERALL_ENEMY_RATIO;
                ENEMY_SX_MOVE->Dead = false;
                ENEMY_SX_MOVE->Size = ENTITY_SIZE_SSX;
                ENEMY_SX_MOVE->Flags = ENTITY_FLAG_ENEMY_S;
                ENEMY_SX_MOVE->OnInit();

                CEntity::EntityList.push_back(ENEMY_SX_MOVE);
                CEntity::EntityMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                CEntity::TargetEnemyMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                SDL_Log("Enemy SX escape dx instance ID: %d", ENEMY_SX_MOVE->ID);

                /*
                char TempC[255];
                int Temp = CEntity::EntityList.size();
                int n = sprintf(TempC, "%d", Temp);
                */

            }
        }
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;
    }

    if(!CPlayer::PlayerStat.GetDisabledFire()) CPlayer::PlayerStat.switchPlayerFire();
    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}

/// escape sx
void CGenerator::MakeSmall4() {

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY
        {

            for (int i = 0; i < 20; i++)
            {

                int x = (WWIDTH + 250 * (i + 1)) * OVERALL_ENEMY_RATIO;
                int y = WHEIGHT * 0.5;

                ENEMY_SX_MOVE = new CEnemySX_move(x, y, ESCAPE_SX);

                ENEMY_SX_MOVE->selected = 3;
                ENEMY_SX_MOVE->entityTexture = "EnemySX_grey4_anim";
                ENEMY_SX_MOVE->W2 = 150;
                ENEMY_SX_MOVE->H2 = 150;
                ENEMY_SX_MOVE->Width = ENEMY_SX_MOVE->W2 * OVERALL_ENEMY_RATIO;
                ENEMY_SX_MOVE->Height = ENEMY_SX_MOVE->H2 * OVERALL_ENEMY_RATIO;
                ENEMY_SX_MOVE->Dead = false;
                ENEMY_SX_MOVE->Size = ENTITY_SIZE_SSX;
                ENEMY_SX_MOVE->Flags = ENTITY_FLAG_ENEMY_S;
                ENEMY_SX_MOVE->OnInit();

                CEntity::EntityList.push_back(ENEMY_SX_MOVE);
                CEntity::EntityMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                CEntity::TargetEnemyMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                SDL_Log("Enemy Sx scape sx instance ID: %d", ENEMY_SX_MOVE->ID);

                /*
                char TempC[255];
                int Temp = CEntity::EntityList.size();
                int n = sprintf(TempC, "%d", Temp);
                */
            }
        }
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;
    }

    if(!CPlayer::PlayerStat.GetDisabledFire()) CPlayer::PlayerStat.switchPlayerFire();
    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}

/// pyramid
void CGenerator::MakeSmall5() {

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY
        {

            for (int i = 0; i < 5; i++)
            {
                if (i == 0) {
                    int x = ((WWIDTH / 2) - 75 * OVERALL_ENEMY_RATIO);
                    int y = -250 * OVERALL_ENEMY_RATIO;

                    ENEMY_SX_MOVE = new CEnemySX_move(x, y, PYRAMID);

                    ENEMY_SX_MOVE->selected = 3;
                    ENEMY_SX_MOVE->triggerFIRE = 50;
                    ENEMY_SX_MOVE->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE->W2 = 150;
                    ENEMY_SX_MOVE->H2 = 150;
                    ENEMY_SX_MOVE->Width = ENEMY_SX_MOVE->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE->Height = ENEMY_SX_MOVE->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE->Dead = false;
                    ENEMY_SX_MOVE->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE);
                    CEntity::EntityMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE->ID);

                } else if (i == 1) {
                    /// enemy sx
                    int x = ((WWIDTH / 2) - 225 * OVERALL_ENEMY_RATIO);
                    int y = -400 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE1 = new CEnemySX_move(x, y, PYRAMID);

                    ENEMY_SX_MOVE1->selected = 3;
                    ENEMY_SX_MOVE1->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE1->triggerFIRE = 80;
                    ENEMY_SX_MOVE1->W2 = 150;
                    ENEMY_SX_MOVE1->H2 = 150;
                    ENEMY_SX_MOVE1->Width = ENEMY_SX_MOVE1->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE1->Height = ENEMY_SX_MOVE1->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE1->Dead = false;
                    ENEMY_SX_MOVE1->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE1->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE1->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE1);
                    CEntity::EntityMap[ENEMY_SX_MOVE1->ID] = ENEMY_SX_MOVE1;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE1->ID] = ENEMY_SX_MOVE1;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE1->ID);

                    /// enemy dx
                    x = ((WWIDTH / 2) + 75 * OVERALL_ENEMY_RATIO);

                    CEnemySX_move *ENEMY_SX_MOVE2 = new CEnemySX_move(x, y, PYRAMID);

                    ENEMY_SX_MOVE2->selected = 3;
                    ENEMY_SX_MOVE2->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE2->triggerFIRE = 90;
                    ENEMY_SX_MOVE2->W2 = 150;
                    ENEMY_SX_MOVE2->H2 = 150;
                    ENEMY_SX_MOVE2->Width = ENEMY_SX_MOVE2->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE2->Height = ENEMY_SX_MOVE2->H2 * OVERALL_ENEMY_RATIO;;
                    ENEMY_SX_MOVE2->Dead = false;
                    ENEMY_SX_MOVE2->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE2->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE2->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE2);
                    CEntity::EntityMap[ENEMY_SX_MOVE2->ID] = ENEMY_SX_MOVE2;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE2->ID] = ENEMY_SX_MOVE2;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE2->ID);
                } else if (i == 2) {
                    /// enemy sx
                    int x = ((WWIDTH / 2) - 375 * OVERALL_ENEMY_RATIO);
                    int y = -550 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE1 = new CEnemySX_move(x, y, PYRAMID);

                    ENEMY_SX_MOVE1->selected = 3;
                    ENEMY_SX_MOVE1->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE1->triggerFIRE = 80;
                    ENEMY_SX_MOVE1->W2 = 150;
                    ENEMY_SX_MOVE1->H2 = 150;
                    ENEMY_SX_MOVE1->Width = ENEMY_SX_MOVE1->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE1->Height = ENEMY_SX_MOVE1->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE1->Dead = false;
                    ENEMY_SX_MOVE1->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE1->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE1->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE1);
                    CEntity::EntityMap[ENEMY_SX_MOVE1->ID] = ENEMY_SX_MOVE1;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE1->ID] = ENEMY_SX_MOVE1;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE1->ID);

                    /// enemy middle
                    x = ((WWIDTH / 2) - 75 * OVERALL_ENEMY_RATIO);

                    CEnemySX_move *ENEMY_SX_MOVE2 = new CEnemySX_move(x, y, PYRAMID);

                    ENEMY_SX_MOVE2->selected = 3;
                    ENEMY_SX_MOVE2->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE2->triggerFIRE = 90;
                    ENEMY_SX_MOVE2->W2 = 150;
                    ENEMY_SX_MOVE2->H2 = 150;
                    ENEMY_SX_MOVE2->Width = ENEMY_SX_MOVE2->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE2->Height = ENEMY_SX_MOVE2->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE2->Dead = false;
                    ENEMY_SX_MOVE2->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE2->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE2->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE2);
                    CEntity::EntityMap[ENEMY_SX_MOVE2->ID] = ENEMY_SX_MOVE2;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE2->ID] = ENEMY_SX_MOVE2;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE2->ID);

                    /// enemy dx
                    x = ((WWIDTH / 2) + 225 * OVERALL_ENEMY_RATIO);

                    CEnemySX_move *ENEMY_SX_MOVE3 = new CEnemySX_move(x, y, PYRAMID);

                    ENEMY_SX_MOVE3->selected = 3;
                    ENEMY_SX_MOVE3->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE3->triggerFIRE = 60;
                    ENEMY_SX_MOVE3->W2 = 150;
                    ENEMY_SX_MOVE3->H2 = 150;
                    ENEMY_SX_MOVE3->Width = ENEMY_SX_MOVE3->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE3->Height = ENEMY_SX_MOVE3->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE3->Dead = false;
                    ENEMY_SX_MOVE3->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE3->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE3->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE3);
                    CEntity::EntityMap[ENEMY_SX_MOVE3->ID] = ENEMY_SX_MOVE3;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE3->ID] = ENEMY_SX_MOVE3;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE3->ID);
                } else if (i == 3) {
                    /// enemy 1 sx
                    int x = ((WWIDTH / 2) - 525 * OVERALL_ENEMY_RATIO);
                    int y = -700 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE1 = new CEnemySX_move(x, y, PYRAMID);

                    ENEMY_SX_MOVE1->selected = 3;
                    ENEMY_SX_MOVE1->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE1->triggerFIRE = 80;
                    ENEMY_SX_MOVE1->W2 = 150;
                    ENEMY_SX_MOVE1->H2 = 150;
                    ENEMY_SX_MOVE1->Width = ENEMY_SX_MOVE1->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE1->Height = ENEMY_SX_MOVE1->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE1->Dead = false;
                    ENEMY_SX_MOVE1->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE1->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE1->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE1);
                    CEntity::EntityMap[ENEMY_SX_MOVE1->ID] = ENEMY_SX_MOVE1;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE1->ID] = ENEMY_SX_MOVE1;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE1->ID);

                    /// enemy middle sx
                    x = ((WWIDTH / 2) - 225 * OVERALL_ENEMY_RATIO);

                    CEnemySX_move *ENEMY_SX_MOVE2 = new CEnemySX_move(x, y, PYRAMID);

                    ENEMY_SX_MOVE2->selected = 3;
                    ENEMY_SX_MOVE2->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE2->triggerFIRE = 90;
                    ENEMY_SX_MOVE2->W2 = 150;
                    ENEMY_SX_MOVE2->H2 = 150;
                    ENEMY_SX_MOVE2->Width = ENEMY_SX_MOVE2->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE2->Height = ENEMY_SX_MOVE2->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE2->Dead = false;
                    ENEMY_SX_MOVE2->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE2->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE2->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE2);
                    CEntity::EntityMap[ENEMY_SX_MOVE2->ID] = ENEMY_SX_MOVE2;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE2->ID] = ENEMY_SX_MOVE2;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE2->ID);

                    /// enemy middle dx
                    x = ((WWIDTH / 2) + 75 * OVERALL_ENEMY_RATIO);

                    CEnemySX_move *ENEMY_SX_MOVE3 = new CEnemySX_move(x, y, PYRAMID);

                    ENEMY_SX_MOVE3->selected = 3;
                    ENEMY_SX_MOVE3->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE3->triggerFIRE = 60;
                    ENEMY_SX_MOVE3->W2 = 150;
                    ENEMY_SX_MOVE3->H2 = 150;
                    ENEMY_SX_MOVE3->Width = ENEMY_SX_MOVE3->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE3->Height = ENEMY_SX_MOVE3->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE3->Dead = false;
                    ENEMY_SX_MOVE3->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE3->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE3->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE3);
                    CEntity::EntityMap[ENEMY_SX_MOVE3->ID] = ENEMY_SX_MOVE3;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE3->ID] = ENEMY_SX_MOVE3;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE3->ID);

                    /// enemy sx
                    x = ((WWIDTH / 2) + 375 * OVERALL_ENEMY_RATIO);

                    CEnemySX_move *ENEMY_SX_MOVE4 = new CEnemySX_move(x, y, PYRAMID);

                    ENEMY_SX_MOVE4->selected = 3;
                    ENEMY_SX_MOVE4->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE4->triggerFIRE = 100;
                    ENEMY_SX_MOVE4->W2 = 150;
                    ENEMY_SX_MOVE4->H2 = 150;
                    ENEMY_SX_MOVE4->Width = ENEMY_SX_MOVE4->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE4->Height = ENEMY_SX_MOVE4->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE4->Dead = false;
                    ENEMY_SX_MOVE4->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE4->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE4->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE4);
                    CEntity::EntityMap[ENEMY_SX_MOVE4->ID] = ENEMY_SX_MOVE4;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE4->ID] = ENEMY_SX_MOVE4;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE4->ID);
                }
            }
        }
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

    }

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());


}

/// diamond
void CGenerator::MakeSmall6() {

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY
        {

            for (int i = 0; i < 5; i++)
            {
                if (i == 0) {
                    int x = ((WWIDTH / 2) - 75 * OVERALL_ENEMY_RATIO);
                    int y = -150 * OVERALL_ENEMY_RATIO;

                    ENEMY_SX_MOVE = new CEnemySX_move(x, y, DIAMOND);

                    ENEMY_SX_MOVE->selected = 3;
                    ENEMY_SX_MOVE->triggerFIRE = 60;
                    ENEMY_SX_MOVE->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE->W2 = 150;
                    ENEMY_SX_MOVE->H2 = 150;
                    ENEMY_SX_MOVE->Width = ENEMY_SX_MOVE->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE->Height = ENEMY_SX_MOVE->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE->Dead = false;
                    ENEMY_SX_MOVE->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE);
                    CEntity::EntityMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE->ID);

                } else if (i == 1) {
                    /// enemy sx
                    int x = ((WWIDTH / 2) - 225 * OVERALL_ENEMY_RATIO);
                    int y = -300 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE1 = new CEnemySX_move(x, y, DIAMOND);

                    ENEMY_SX_MOVE1->selected = 3;
                    ENEMY_SX_MOVE1->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE1->triggerFIRE = 80;
                    ENEMY_SX_MOVE1->W2 = 150;
                    ENEMY_SX_MOVE1->H2 = 150;
                    ENEMY_SX_MOVE1->Width = ENEMY_SX_MOVE1->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE1->Height = ENEMY_SX_MOVE1->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE1->Dead = false;
                    ENEMY_SX_MOVE1->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE1->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE1->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE1);
                    CEntity::EntityMap[ENEMY_SX_MOVE1->ID] = ENEMY_SX_MOVE1;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE1->ID] = ENEMY_SX_MOVE1;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE1->ID);

                    /// enemy dx
                    x = ((WWIDTH / 2) + 75 * OVERALL_ENEMY_RATIO);
                    y = -300 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE2 = new CEnemySX_move(x, y, DIAMOND);

                    ENEMY_SX_MOVE2->selected = 3;
                    ENEMY_SX_MOVE2->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE2->triggerFIRE = 90;
                    ENEMY_SX_MOVE2->W2 = 150;
                    ENEMY_SX_MOVE2->H2 = 150;
                    ENEMY_SX_MOVE2->Width = ENEMY_SX_MOVE2->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE2->Height = ENEMY_SX_MOVE2->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE2->Dead = false;
                    ENEMY_SX_MOVE2->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE2->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE2->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE2);
                    CEntity::EntityMap[ENEMY_SX_MOVE2->ID] = ENEMY_SX_MOVE2;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE2->ID] = ENEMY_SX_MOVE2;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE2->ID);
                } else if (i == 2) {
                    /// enemy sx
                    int x = ((WWIDTH / 2) - 375 * OVERALL_ENEMY_RATIO);
                    int y = -450 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE3 = new CEnemySX_move(x, y, DIAMOND);

                    ENEMY_SX_MOVE3->selected = 3;
                    ENEMY_SX_MOVE3->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE3->triggerFIRE = 60;
                    ENEMY_SX_MOVE3->W2 = 150;
                    ENEMY_SX_MOVE3->H2 = 150;
                    ENEMY_SX_MOVE3->Width = ENEMY_SX_MOVE3->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE3->Height = ENEMY_SX_MOVE3->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE3->Dead = false;
                    ENEMY_SX_MOVE3->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE3->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE3->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE3);
                    CEntity::EntityMap[ENEMY_SX_MOVE3->ID] = ENEMY_SX_MOVE3;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE3->ID] = ENEMY_SX_MOVE3;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE3->ID);

                    /// enemy middle
                    x = ((WWIDTH / 2) - 75 * OVERALL_ENEMY_RATIO);
                    y = -450 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE4 = new CEnemySX_move(x, y, DIAMOND);

                    ENEMY_SX_MOVE4->selected = 3;
                    ENEMY_SX_MOVE4->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE4->triggerFIRE = 100;
                    ENEMY_SX_MOVE4->W2 = 150;
                    ENEMY_SX_MOVE4->H2 = 150;
                    ENEMY_SX_MOVE4->Width = ENEMY_SX_MOVE4->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE4->Height = ENEMY_SX_MOVE4->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE4->Dead = false;
                    ENEMY_SX_MOVE4->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE4->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE4->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE4);
                    CEntity::EntityMap[ENEMY_SX_MOVE4->ID] = ENEMY_SX_MOVE4;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE4->ID] = ENEMY_SX_MOVE4;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE4->ID);

                    /// enemy dx
                    x = ((WWIDTH / 2) + 225 * OVERALL_ENEMY_RATIO);
                    y = -450 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE5 = new CEnemySX_move(x, y, DIAMOND);

                    ENEMY_SX_MOVE5->selected = 3;
                    ENEMY_SX_MOVE5->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE5->triggerFIRE = 80;
                    ENEMY_SX_MOVE5->W2 = 150;
                    ENEMY_SX_MOVE5->H2 = 150;
                    ENEMY_SX_MOVE5->Width = ENEMY_SX_MOVE5->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE5->Height = ENEMY_SX_MOVE5->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE5->Dead = false;
                    ENEMY_SX_MOVE5->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE5->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE5->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE5);
                    CEntity::EntityMap[ENEMY_SX_MOVE5->ID] = ENEMY_SX_MOVE5;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE5->ID] = ENEMY_SX_MOVE5;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE5->ID);
                } else if (i == 3) {
                    /// enemy 1 sx
                    int x = ((WWIDTH / 2) - 525 * OVERALL_ENEMY_RATIO);
                    int y = -600 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE7 = new CEnemySX_move(x, y, DIAMOND);

                    ENEMY_SX_MOVE7->selected = 3;
                    ENEMY_SX_MOVE7->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE7->triggerFIRE = 100;
                    ENEMY_SX_MOVE7->W2 = 150;
                    ENEMY_SX_MOVE7->H2 = 150;
                    ENEMY_SX_MOVE7->Width = ENEMY_SX_MOVE7->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE7->Height = ENEMY_SX_MOVE7->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE7->Dead = false;
                    ENEMY_SX_MOVE7->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE7->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE7->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE7);
                    CEntity::EntityMap[ENEMY_SX_MOVE7->ID] = ENEMY_SX_MOVE7;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE7->ID] = ENEMY_SX_MOVE7;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE7->ID);

                    /// enemy middle sx
                    x = ((WWIDTH / 2) - 225 * OVERALL_ENEMY_RATIO);
                    y = -600 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE8 = new CEnemySX_move(x, y, DIAMOND);

                    ENEMY_SX_MOVE8->selected = 3;
                    ENEMY_SX_MOVE8->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE8->triggerFIRE = 120;
                    ENEMY_SX_MOVE8->W2 = 150;
                    ENEMY_SX_MOVE8->H2 = 150;
                    ENEMY_SX_MOVE8->Width = ENEMY_SX_MOVE8->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE8->Height = ENEMY_SX_MOVE8->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE8->Dead = false;
                    ENEMY_SX_MOVE8->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE8->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE8->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE8);
                    CEntity::EntityMap[ENEMY_SX_MOVE8->ID] = ENEMY_SX_MOVE8;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE8->ID] = ENEMY_SX_MOVE8;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE8->ID);

                    /// enemy middle dx
                    x = ((WWIDTH / 2) + 75 * OVERALL_ENEMY_RATIO);
                    y = -600 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE9 = new CEnemySX_move(x, y, DIAMOND);

                    ENEMY_SX_MOVE9->selected = 3;
                    ENEMY_SX_MOVE9->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE9->triggerFIRE = 110;
                    ENEMY_SX_MOVE9->W2 = 150;
                    ENEMY_SX_MOVE9->H2 = 150;
                    ENEMY_SX_MOVE9->Width = ENEMY_SX_MOVE9->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE9->Height = ENEMY_SX_MOVE9->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE9->Dead = false;
                    ENEMY_SX_MOVE9->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE9->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE9->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE9);
                    CEntity::EntityMap[ENEMY_SX_MOVE9->ID] = ENEMY_SX_MOVE9;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE9->ID] = ENEMY_SX_MOVE9;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE9->ID);

                    /// enemy dx
                    x = ((WWIDTH / 2) + 375 * OVERALL_ENEMY_RATIO);
                    y = -600 * OVERALL_ENEMY_RATIO;

                    CEnemySX_move *ENEMY_SX_MOVE10 = new CEnemySX_move(x, y, DIAMOND);

                    ENEMY_SX_MOVE10->selected = 3;
                    ENEMY_SX_MOVE10->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE10->triggerFIRE = 100;
                    ENEMY_SX_MOVE10->W2 = 150;
                    ENEMY_SX_MOVE10->H2 = 150;
                    ENEMY_SX_MOVE10->Width = ENEMY_SX_MOVE10->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE10->Height = ENEMY_SX_MOVE10->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE10->Dead = false;
                    ENEMY_SX_MOVE10->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE10->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE10->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE10);
                    CEntity::EntityMap[ENEMY_SX_MOVE10->ID] = ENEMY_SX_MOVE10;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE10->ID] = ENEMY_SX_MOVE10;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE10->ID);
                }
            }
        }
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;
    }

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}


/// grid
void CGenerator::MakeSmall7() {

    int x = ((WWIDTH / 2) - 525 * OVERALL_ENEMY_RATIO);
    int y = -150 * OVERALL_ENEMY_RATIO;

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY
        {
            for (int i = 0; i < 4; i++)
            {
                for (int z = 0; z < 4; z++) {
                    ENEMY_SX_MOVE = new CEnemySX_move(x, y, GRID);

                    ENEMY_SX_MOVE->selected = 3;
                    ENEMY_SX_MOVE->triggerFIRE = 60;
                    ENEMY_SX_MOVE->entityTexture = "EnemySX_grey4_anim";
                    ENEMY_SX_MOVE->EnemyFireMode = SNIPER;
                    ENEMY_SX_MOVE->W2 = 150;
                    ENEMY_SX_MOVE->H2 = 150;
                    ENEMY_SX_MOVE->Width = ENEMY_SX_MOVE->W2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE->Height = ENEMY_SX_MOVE->H2 * OVERALL_ENEMY_RATIO;
                    ENEMY_SX_MOVE->Dead = false;
                    ENEMY_SX_MOVE->Size = ENTITY_SIZE_SSX;
                    ENEMY_SX_MOVE->Flags = ENTITY_FLAG_ENEMY_S;
                    ENEMY_SX_MOVE->OnInit();

                    CEntity::EntityList.push_back(ENEMY_SX_MOVE);
                    CEntity::EntityMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                    CEntity::TargetEnemyMap[ENEMY_SX_MOVE->ID] = ENEMY_SX_MOVE;
                    SDL_Log("Enemy instance ID: %d", ENEMY_SX_MOVE->ID);
                    x += 300 * OVERALL_ENEMY_RATIO;
                }
                x = ((WWIDTH / 2) - 525 * OVERALL_ENEMY_RATIO);
                y -= 150 * OVERALL_ENEMY_RATIO;

            }
        }
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;
    }


    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());


}
void CGenerator::MakeSmall8() {}
void CGenerator::MakeSmall9() {}





/// ***** MEDIUM ENEMY *****

void CGenerator::MakeMedium0() {

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            {
                //int x = (rand() % (WWIDTH - 400) + 20);
                int x = (WWIDTH / 2) - ((300 * OVERALL_ENEMY_RATIO) / 2);
                int y = -350;

                EnemyMM = new CEnemyMM(x, y, NONE);

                EnemyMM->selected = 0;
                EnemyMM->Flags = ENTITY_FLAG_ENEMY_M;
                EnemyMM->Dead = false;
                EnemyMM->W2 = 300;
                EnemyMM->H2 = 300;
                EnemyMM->Width = EnemyMM->W2 * OVERALL_ENEMY_RATIO;
                EnemyMM->Height = EnemyMM->H2 * OVERALL_ENEMY_RATIO;
                EnemyMM->OnInit();

                EnemyMM->entityTexture = "EnemyMM_grey4_anim";

            }
            break;

        case 2: // MISSION DARK ENEMY
            break;

        case 3:	// MISSION YELLOW ENEMY
            break;

        case 4:	// MISSION GREEN ENEMY
            break;

        default:
            break;
    }


    CEntity::EntityList.push_back(EnemyMM);
    CEntity::EntityMap[EnemyMM->ID] = EnemyMM;
    CEntity::TargetEnemyMap[EnemyMM->ID] = EnemyMM;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}

void CGenerator::MakeMedium1() {


    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            int x, y;

            if (CAppStateGame::count_M1 < 2)
            {
                if (CAppStateGame::count_M1 < 1)
                {
                    x = 100 * OVERALL_ENEMY_RATIO;
                } else {
                    x = (WWIDTH - 400 * OVERALL_ENEMY_RATIO) - (100 * OVERALL_ENEMY_RATIO);
                }
                //int x = (rand() % (WWIDTH - 400) + 20);

                y = -350;

                EnemyMM = new CEnemyMM(x, y, ROTATE);

                EnemyMM->selected = 1;
                EnemyMM->Flags = ENTITY_FLAG_ENEMY_M;
                EnemyMM->Dead = false;
                EnemyMM->W2 = 400;
                EnemyMM->H2 = 250;
                EnemyMM->Width = EnemyMM->W2 * OVERALL_ENEMY_RATIO;
                EnemyMM->Height = EnemyMM->H2 * OVERALL_ENEMY_RATIO;
                EnemyMM->MoveDown = true;
                EnemyMM->OnInit();

                EnemyMM->entityTexture = "EnemyMM_grey1_anim";

            }
            break;

        case 2: // MISSION DARK ENEMY
            break;

        case 3:	// MISSION YELLOW ENEMY
            break;

        case 4:	// MISSION GREEN ENEMY
            break;

        default:
            break;
    }


    CEntity::EntityList.push_back(EnemyMM);
    CEntity::EntityMap[EnemyMM->ID] = EnemyMM;
    CEntity::TargetEnemyMap[EnemyMM->ID] = EnemyMM;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}




void CGenerator::MakeMedium2() {

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            if (CAppStateGame::count_M2 < 2)
            {
                if (CAppStateGame::count_M2 < 1) {
                    x = 100 * OVERALL_ENEMY_RATIO;
                } else {
                    x = (WWIDTH - 450 * OVERALL_ENEMY_RATIO) - (100 * OVERALL_ENEMY_RATIO);
                }

                int y = -350 * OVERALL_ENEMY_RATIO;

                EnemyMM2 = new CEnemyMM_2(x, y);
                EnemyMM2->id_MM2 = countEnemyMM2_overall;

                EnemyMM2->selected = 2;
                EnemyMM2->entityTexture = "EnemyMM_grey2_anim";
                EnemyMM2->W2 = 450;
                EnemyMM2->H2 = 350;
                EnemyMM2->Width = EnemyMM2->W2 * OVERALL_ENEMY_RATIO;
                EnemyMM2->Height = EnemyMM2->H2 * OVERALL_ENEMY_RATIO;
                EnemyMM2->offsetY = 0;
                EnemyMM2->Dead = false;
                EnemyMM2->Flags = ENTITY_FLAG_ENEMY_F;
                EnemyMM2->OnInit();

                CEntity::EntityList.push_back(EnemyMM2);
                CEntity::EntityMap[EnemyMM2->ID]=EnemyMM2;
                CEntity::TargetEnemyMap[EnemyMM2->ID] = EnemyMM2;
            }

            break;

        case 2: // MISSION DARK ENEMY
            break;

        case 3:	// MISSION YELLOW ENEMY
            break;

        case 4:	// MISSION GREEN ENEMY
            break;

        default:
            break;
    }


    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());


}



void CGenerator::MakeMedium3() {

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            x = WWIDTH / 2;
            y = -410 * OVERALL_ENEMY_RATIO;

            EnemyMM3 = new CEnemyMM_3(x, y);

            EnemyMM3->selected = 3;
            EnemyMM3->entityTexture = "EnemyMM_grey3_anim";
            EnemyMM3->W2 = 400;
            EnemyMM3->H2 = 400;
            EnemyMM3->Width = EnemyMM3->W2 * OVERALL_ENEMY_RATIO;
            EnemyMM3->Height = EnemyMM3->H2 * OVERALL_ENEMY_RATIO;
            EnemyMM3->offsetY = 0;
            EnemyMM3->Dead = false;
            EnemyMM3->Flags = ENTITY_FLAG_ENEMY_F;
            EnemyMM3->OnInit();



            break;

        case 2: // MISSION DARK ENEMY
            break;

        case 3:	// MISSION YELLOW ENEMY
            break;

        case 4:	// MISSION GREEN ENEMY
            break;

        default:
            break;

    }


    CEntity::EntityList.push_back(EnemyMM3);
    CEntity::EntityMap[EnemyMM3->ID]=CEntity::EntityList.back();
    CEntity::TargetEnemyMap[EnemyMM3->ID] = EnemyMM3;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());


}

void CGenerator::MakeMedium4() {

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            {
                //int x = (rand() % (WWIDTH - 400) + 20);
                int x = (WWIDTH / 2) - ((300 * OVERALL_ENEMY_RATIO) / 2);
                int y = -350;

                EnemyMM = new CEnemyMM(x, y, NONE);

                EnemyMM->selected = 4;
                EnemyMM->Flags = ENTITY_FLAG_ENEMY_M;
                EnemyMM->Dead = false;
                EnemyMM->W2 = 300;
                EnemyMM->H2 = 300;
                EnemyMM->Width = EnemyMM->W2 * OVERALL_ENEMY_RATIO;
                EnemyMM->Height = EnemyMM->H2 * OVERALL_ENEMY_RATIO;
                EnemyMM->OnInit();

                EnemyMM->entityTexture = "EnemyMM_grey4_anim";

                CEntity::EntityList.push_back(EnemyMM);
                CEntity::EntityMap[EnemyMM->ID] = EnemyMM;
                CEntity::TargetEnemyMap[EnemyMM->ID] = EnemyMM;

            }
            break;

        case 2: // MISSION DARK ENEMY
            break;

        case 3:	// MISSION YELLOW ENEMY
            break;

        case 4:	// MISSION GREEN ENEMY
            break;

        default:
            break;
    }

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}

void CGenerator::MakeMedium5() {

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            int x, y;

            if (CAppStateGame::count_M5 < 2) {
                if (CAppStateGame::count_M5 < 1) {
                    x = 100 * OVERALL_ENEMY_RATIO;
                }
                else {
                    x = (WWIDTH - 400 * OVERALL_ENEMY_RATIO) - (100 * OVERALL_ENEMY_RATIO);
                }
                y = -350;

                EnemyMM = new CEnemyMM(x, y, NONE);

                EnemyMM->selected = 5;
                EnemyMM->Flags = ENTITY_FLAG_ENEMY_M;
                EnemyMM->Dead = false;
                EnemyMM->W2 = 400;
                EnemyMM->H2 = 250;
                EnemyMM->Width = EnemyMM->W2 * OVERALL_ENEMY_RATIO;
                EnemyMM->Height = EnemyMM->H2 * OVERALL_ENEMY_RATIO;
                EnemyMM->OnInit();

                EnemyMM->entityTexture = "EnemyMM_grey1_anim";

                CEntity::EntityList.push_back(EnemyMM);
                CEntity::EntityMap[EnemyMM->ID] = EnemyMM;
                CEntity::TargetEnemyMap[EnemyMM->ID] = EnemyMM;

                SDL_Log("MM5 count: %d", CAppStateGame::count_M5);
            }

            break;

        case 2: // MISSION DARK ENEMY
            break;

        case 3:	// MISSION YELLOW ENEMY
            break;

        case 4:	// MISSION GREEN ENEMY
            break;

        default:
            break;
    }

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}


void CGenerator::MakeMedium6() {


    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            int x, y;

            if (CAppStateGame::count_M6 < 2)
            {
                if (CAppStateGame::count_M6 < 1)
                {
                    x = -400;
                } else {
                    x = WWIDTH;
                }
                //int x = (rand() % (WWIDTH - 400) + 20);

                y = 350;

                EnemyMM = new CEnemyMM(x, y, ROTATE);

                EnemyMM->selected = 2;
                EnemyMM->Flags = ENTITY_FLAG_ENEMY_M;
                EnemyMM->Dead = false;
                EnemyMM->W2 = 400;
                EnemyMM->H2 = 250;
                EnemyMM->Width = EnemyMM->W2 * OVERALL_ENEMY_RATIO;
                EnemyMM->Height = EnemyMM->H2 * OVERALL_ENEMY_RATIO;
                EnemyMM->OnInit();

                EnemyMM->entityTexture = "EnemyMM_grey1_anim";

            }
            break;

        case 2: // MISSION DARK ENEMY
            break;

        case 3:	// MISSION YELLOW ENEMY
            break;

        case 4:	// MISSION GREEN ENEMY
            break;

        default:
            break;
    }


    CEntity::EntityList.push_back(EnemyMM);
    CEntity::EntityMap[EnemyMM->ID] = EnemyMM;
    CEntity::TargetEnemyMap[EnemyMM->ID] = EnemyMM;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}








void CGenerator::MakeBoss1() {

    BossHUD();

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

                Boss1 = new CEnemyBOSS1(((WWIDTH / 2) - 250), -700, BOSS_SEEK);

                Boss1->damage = 100;
                Boss1->entityTexture = "EnemyBOSS_grey1_anim";
                Boss1->W2 = 500;
                Boss1->H2 = 500;
                Boss1->Width = Boss1->W2 * OVERALL_ENEMY_RATIO;
                Boss1->Height = Boss1->H2 * OVERALL_ENEMY_RATIO;
                Boss1->selected = 1;
                Boss1->OnInit();

                // create cannon sx
                /*
                CannonSX = new CCannon(CEnemyBOSS1::getXen() + 36, CEnemyBOSS1::getYen()+ 74, 0);
                CannonSX->entityTexture = "cannon";
                CannonSX->Width = 50;
                CannonSX->Height = 63;
                CannonSX->Type = ENTITY_TYPE_GENERIC;
                CannonSX->Size = ENTITY_SIZE_SX;
                CannonSX->Flags = ENTITY_FLAG_ENEMY_S;
                CannonSX->Dead = false;
                CannonSX->OnInit();

                SDL_Log("push_back() CannonSX");
                CEntity::EntityList.push_back(CannonSX);
                */

                //create cannon dx
                /*
                CannonDX = new CCannon(CEnemyBOSS1::getXen() + 175, CEnemyBOSS1::getYen() + 92, 1);
                CannonDX->entityTexture = "cannon";
                CannonDX->Width = 30;
                CannonDX->Height = 38;
                CannonDX->Type = ENTITY_TYPE_GENERIC;
                CannonDX->Size = ENTITY_SIZE_SX;
                CannonDX->Flags = ENTITY_FLAG_ENEMY_S;
                CannonDX->Dead = false;
                CannonDX->OnInit();
                */

                //CEntity::EntityList.push_back(CannonDX);

                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;


    }






    BossSoundStage();

    CreateBossEvent();

    SDL_Log("push_back() BOSS1");
    CEntity::EntityList.push_back(Boss1);
    CEntity::EntityMap[Boss1->ID] = Boss1;
    CEntity::TargetEnemyMap[Boss1->ID] = Boss1;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}


void CGenerator::MakeBoss2() {

    BossHUD();

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            Boss1 = new CEnemyBOSS1((WWIDTH / 2 - ((470 * OVERALL_ENEMY_RATIO) / 2)), -400, BOSS_ABC);

            Boss1->damage = 100;
            Boss1->entityTexture = "EnemyBOSS_grey2_anim";
            Boss1->W2 = 470;
            Boss1->H2 = 371;
            Boss1->Width = Boss1->W2 * OVERALL_ENEMY_RATIO;
            Boss1->Height = Boss1->H2 * OVERALL_ENEMY_RATIO;
            Boss1->selected = 2;
            Boss1->OnInit();

            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

    }


    BossSoundStage();

    CreateBossEvent();

    SDL_Log("push_back() BOSS2");
    CEntity::EntityList.push_back(Boss1);
    CEntity::EntityMap[Boss1->ID] = Boss1;
    CEntity::TargetEnemyMap[Boss1->ID] = Boss1;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());

}


void CGenerator::MakeBoss3() {

    BossHUD();

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            Boss1 = new CEnemyBOSS1((WWIDTH / 2 - ((525 * OVERALL_ENEMY_RATIO) / 2)), -700, BOSS_ABC);

            Boss1->damage = 100;
            Boss1->entityTexture = "EnemyBOSS_grey3_anim";
            Boss1->W2 = 525;
            Boss1->H2 = 400;
            Boss1->Width = Boss1->W2 * OVERALL_ENEMY_RATIO;
            Boss1->Height = Boss1->H2 * OVERALL_ENEMY_RATIO;
            Boss1->MoveRight = true;
            Boss1->pos_C = true;
            Boss1->selected = 3;
            Boss1->OnInit();

            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

    }


    BossSoundStage();

    CreateBossEvent();

    SDL_Log("push_back() BOSS3");
    CEntity::EntityList.push_back(Boss1);
    CEntity::EntityMap[Boss1->ID] = Boss1;
    CEntity::TargetEnemyMap[Boss1->ID] = Boss1;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());


}


void CGenerator::MakeBoss4() {

    BossHUD();

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            Boss1 = new CEnemyBOSS1(WWIDTH + 100, 10, BOSS_VANISH);

            Boss1->damage = 100;
            Boss1->entityTexture = "EnemyBOSS_grey4_anim";
            Boss1->W2 = 400;
            Boss1->H2 = 400;
            Boss1->Width = Boss1->W2 * OVERALL_ENEMY_RATIO;
            Boss1->Height = Boss1->H2 * OVERALL_ENEMY_RATIO;
            Boss1->selected = 4;
            Boss1->OnInit();

            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

    }


    BossSoundStage();

    CreateBossEvent();

    SDL_Log("push_back() BOSS4");
    CEntity::EntityList.push_back(Boss1);
    CEntity::EntityMap[Boss1->ID] = Boss1;
    CEntity::TargetEnemyMap[Boss1->ID] = Boss1;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());


}


void CGenerator::MakeBoss5() {

    BossHUD();

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            Boss1 = new CEnemyBOSS1(WWIDTH + 200, 10, BOSS_VANISH);

            Boss1->damage = 100;
            Boss1->entityTexture = "EnemyBOSS_grey5_anim";
            Boss1->W2 = 500;
            Boss1->H2 = 500;
            Boss1->Width = Boss1->W2 * OVERALL_ENEMY_RATIO;
            Boss1->Height = Boss1->H2 * OVERALL_ENEMY_RATIO;
            Boss1->selected = 5;
            Boss1->OnInit();

            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

    }


    BossSoundStage();

    CreateBossEvent();

    SDL_Log("push_back() BOSS5");
    CEntity::EntityList.push_back(Boss1);
    CEntity::EntityMap[Boss1->ID] = Boss1;
    CEntity::TargetEnemyMap[Boss1->ID] = Boss1;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());


}


void CGenerator::MakeBoss6() {

    BossHUD();

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            Boss1 = new CEnemyBOSS1(300, -900, BOSS_LF_RX);

            Boss1->damage = 100;
            Boss1->entityTexture = "EnemyBOSS_grey6_anim";
            Boss1->W2 = 470;
            Boss1->H2 = 371;
            Boss1->Width = Boss1->W2 * OVERALL_ENEMY_RATIO;
            Boss1->Height = Boss1->H2 * OVERALL_ENEMY_RATIO;
            Boss1->selected = 1;
            Boss1->OnInit();

            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

    }


    BossSoundStage();

    CreateBossEvent();

    SDL_Log("push_back() BOSS6");
    CEntity::EntityList.push_back(Boss1);
    CEntity::EntityMap[Boss1->ID] = Boss1;
    CEntity::TargetEnemyMap[Boss1->ID] = Boss1;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());


}


void CGenerator::MakeBoss7() {

    BossHUD();

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            Boss1 = new CEnemyBOSS1(300, -900, BOSS_LF_RX);

            Boss1->damage = 100;
            Boss1->entityTexture = "EnemyBOSS_grey7_anim";
            Boss1->W2 = 470;
            Boss1->H2 = 371;
            Boss1->Width = Boss1->W2 * OVERALL_ENEMY_RATIO;
            Boss1->Height = Boss1->H2 * OVERALL_ENEMY_RATIO;
            Boss1->selected = 1;
            Boss1->OnInit();

            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

    }


    BossSoundStage();

    CreateBossEvent();

    SDL_Log("push_back() BOSS7");
    CEntity::EntityList.push_back(Boss1);
    CEntity::EntityMap[Boss1->ID] = Boss1;
    CEntity::TargetEnemyMap[Boss1->ID] = Boss1;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());


}


void CGenerator::MakeBoss8() {

    BossHUD();

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            Boss1 = new CEnemyBOSS1(300, -900, BOSS_LF_RX);

            Boss1->damage = 100;
            Boss1->entityTexture = "EnemyBOSS_grey8_anim";
            Boss1->W2 = 470;
            Boss1->H2 = 371;
            Boss1->Width = Boss1->W2 * OVERALL_ENEMY_RATIO;
            Boss1->Height = Boss1->H2 * OVERALL_ENEMY_RATIO;
            Boss1->selected = 1;
            Boss1->OnInit();

            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

    }


    BossSoundStage();

    CreateBossEvent();

    SDL_Log("push_back() BOSS8");
    CEntity::EntityList.push_back(Boss1);
    CEntity::EntityMap[Boss1->ID] = Boss1;
    CEntity::TargetEnemyMap[Boss1->ID] = Boss1;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());



}


void CGenerator::MakeBoss9() {

    BossHUD();

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            Boss1 = new CEnemyBOSS1(300, -900, BOSS_LF_RX);

            Boss1->damage = 100;
            Boss1->entityTexture = "EnemyBOSS_grey9_anim";
            Boss1->W2 = 470;
            Boss1->H2 = 371;
            Boss1->Width = Boss1->W2 * OVERALL_ENEMY_RATIO;
            Boss1->Height = Boss1->H2 * OVERALL_ENEMY_RATIO;
            Boss1->selected = 1;
            Boss1->OnInit();

            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

    }


    BossSoundStage();

    CreateBossEvent();

    SDL_Log("push_back() BOSS1");
    CEntity::EntityList.push_back(Boss1);
    CEntity::EntityMap[Boss1->ID] = Boss1;
    CEntity::TargetEnemyMap[Boss1->ID] = Boss1;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());



}


void CGenerator::MakeBossX() {

    BossHUD();

    switch (CAppStateGame::currentMission)
    {
        case 1: // MISSION GREY ENEMY

            Boss1 = new CEnemyBOSS1(300, -900, BOSS_LF_RX);

            Boss1->damage = 100;
            Boss1->entityTexture = "EnemyBOSS_greyX_anim";
            Boss1->W2 = 503;
            Boss1->H2 = 400;
            Boss1->Width = Boss1->W2 * OVERALL_ENEMY_RATIO;
            Boss1->Height = Boss1->H2 * OVERALL_ENEMY_RATIO;
            Boss1->selected = 1;
            Boss1->OnInit();

            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

    }


    BossSoundStage();

    CreateBossEvent();

    SDL_Log("push_back() BOSSX");
    CEntity::EntityList.push_back(Boss1);
    CEntity::EntityMap[Boss1->ID] = Boss1;
    CEntity::TargetEnemyMap[Boss1->ID] = Boss1;

    CEnemyQueue::EnemyList[EE].erase(CEnemyQueue::EnemyList[EE].begin());



}






//=============================================================================
int CGenerator::getDeadTime() {

    return DeadTime;

}










/***	EVENT's FUNC	***/

void CGenerator::LotteryEvents() {

    const double start = 1;
    const double stop = 100;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(start, std::nextafter(stop, DBL_MAX));

    int winnerNumber = (int)dist(mt);
    int tempMedal = 0;
    SDL_Log("Medal Event %d", winnerNumber);

    if (winnerNumber >= 1 && winnerNumber <= 60) tempMedal = 1;
    else if (winnerNumber >= 41 && winnerNumber <= 49) tempMedal = 2;
    else if (winnerNumber >= 50 && winnerNumber <= 80) tempMedal = 3;
    else if (winnerNumber >= 81 && winnerNumber <= 93) tempMedal = 4;
    else if (winnerNumber >= 94 && winnerNumber <= 100) tempMedal = 5;


    switch(tempMedal)
    {
        case EVENT_TRIPLE_FIRE:
            CreateMedal_1_Event();
            break;

        case EVENT_PENTA_FIRE:
            CreateMedal_2_Event();
            break;

        case EVENT_ROCKET_SMART:
            CreateMedal_3_Event();
            break;

        case EVENT_GAMMARAY:
            CreateMedal_4_Event();
            break;

        case EVENT_TOTAL_FIRE:
            CreateMedal_5_Event();
            break;

        default:
            CreateMedal_1_Event();
    }

}



void CGenerator::CreateMedal_1_Event()
{
    SDL_Log("Medal_1 Event invocated");

    Medal_1_EventType = SDL_RegisterEvents(1);
    if (Medal_1_EventType != ((Uint32)-1))
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event));
        event.type = FIRE_TRIPLE;
        event.user.code = 0;
        event.user.data1 = 0;
        event.user.data2 = 0;
        SDL_PushEvent(&event);
    }
}

void CGenerator::CreateMedal_2_Event()
{
    SDL_Log("Medal_2 Event invocated");

    Medal_2_EventType = SDL_RegisterEvents(1);
    if (Medal_2_EventType != ((Uint32)-1))
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event));
        event.type = FIRE_PENTA;
        event.user.code = 0;
        event.user.data1 = 0;
        event.user.data2 = 0;
        SDL_PushEvent(&event);
    }
}

void CGenerator::CreateMedal_3_Event()
{
    SDL_Log("Medal_3 Event invocated");

    Medal_3_EventType = SDL_RegisterEvents(1);
    if (Medal_3_EventType != ((Uint32)-1))
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event));
        event.type = FIRE_ROCKET;
        event.user.code = 0;
        event.user.data1 = 0;
        event.user.data2 = 0;
        SDL_PushEvent(&event);
    }
}

void CGenerator::CreateMedal_4_Event()
{
    SDL_Log("Medal_4 Event invocated");

    Medal_4_EventType = SDL_RegisterEvents(1);
    if (Medal_4_EventType != ((Uint32)-1))
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event));
        event.type = FIRE_GAMMARAY;
        event.user.code = 0;
        event.user.data1 = 0;
        event.user.data2 = 0;
        SDL_PushEvent(&event);
    }
}

void CGenerator::CreateMedal_5_Event()
{
    SDL_Log("Medal_5 Event invocated");

    Medal_5_EventType = SDL_RegisterEvents(1);
    if (Medal_5_EventType != ((Uint32)-1))
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event));
        event.type = FIRE_TOTAL;
        event.user.code = 0;
        event.user.data1 = 0;
        event.user.data2 = 0;
        SDL_PushEvent(&event);
    }
}

void  CGenerator::CreateMedal_6_Event()
{
    SDL_Log("Medal_6 Event invocated");

    Medal_6_EventType = SDL_RegisterEvents(1);
    if (Medal_6_EventType != ((Uint32)-1))
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event));
        event.type = BONUS_POINT;
        event.user.code = 0;
        event.user.data1 = 0;
        event.user.data2 = 0;
        SDL_PushEvent(&event);
    }

}

void CGenerator::CreateBossEvent()
{

    BossEventType = SDL_RegisterEvents(1);
    if (EVENT_BOSS != ((Uint32)-1))
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event));
        event.type = EVENT_BOSS;
        event.user.code = 0;
        event.user.data1 = 0;
        event.user.data2 = 0;
        SDL_PushEvent(&event);
    }

}

void CGenerator::BossHUD() {

    CPlayer::PlayerStat.setFireMode(CPlayer::FIRE_NONE);

    BOSSHUD.w = 338 * OVERALL_ENEMY_RATIO;
    BOSSHUD.h = 85 * OVERALL_ENEMY_RATIO;
    BOSSHUD.x = WWIDTH - BOSSHUD.w - 10;
    BOSSHUD.y = 10;
    BOSSHUD.x2 = 0;
    BOSSHUD.y2 = 0;
    BOSSHUD.w2 = 675;
    BOSSHUD.h2 = 170;
    BOSSHUD.alpha = 255;


    BOSSBAR.w = 230 * OVERALL_ENEMY_RATIO;
    BOSSBAR.h = 30 * OVERALL_ENEMY_RATIO;
    BOSSBAR.x = BOSSHUD.x + 0.76 * BOSSHUD.w;
    BOSSBAR.y = BOSSHUD.y + 0.33 * BOSSHUD.h;
    BOSSBAR.x2 = 0;
    BOSSBAR.y2 = 0;
    BOSSBAR.w2 = 459;
    BOSSBAR.h2 = 60;
    BOSSBAR.perc = 0;


}

void CGenerator::BossSoundStage() {

    CAppStateGame::BG_volume = MIX_MAX_VOLUME / 6;
    Mix_Volume(-1, CAppStateGame::BG_volume);
    CSoundBank::SoundControl.Play2(CAppStateGame::tempSoundBoss);

}