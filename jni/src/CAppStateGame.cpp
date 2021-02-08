#define _CRT_SECURE_NO_DEPRECATE

#include "CAppStateGame.h"
#include "CAppStateIntro.h"


#include "CSoundBank.h"
#include "CMedal.h"
#include "TextureBank.h"
#include "Stringify.h"
#include "CPopup.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <random>

#include <android/log.h>
#include <android_native_app_glue.h>

#include "firebase/admob.h"
#include "firebase/admob/types.h"
#include "firebase/admob/interstitial_ad.h"
#include "firebase/admob/types.h"
#include "firebase/app.h"
#include "firebase/future.h"
#include "firebase/admob/banner_view.h"

JNIEnv* env;
jobject activity;


bool CAppStateGame::g_destroy_requested = false;
bool CAppStateGame::g_started = false;
bool CAppStateGame::g_restarted = false;


#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)




CAppStateGame CAppStateGame::Instance;

int		x30;
long	CAppStateGame::countLoop				= 0;
int		CAppStateGame::lastPause				= 0;
int		CAppStateGame::TimeLeft					= 0;
int		CAppStateGame::DeadTime					= 0;
int		CAppStateGame::BossTimeDeath			= 0;
int		CAppStateGame::BG_volume				= 0;
int		CAppStateGame::volumeTuning				= 7;

int		CAppStateGame::StepA1					= 0;
int		CAppStateGame::StepA2					= 0;
int		CAppStateGame::StepB1					= 0;
int		CAppStateGame::StepB2					= 0;
int		CAppStateGame::StepC1					= 0;
int		CAppStateGame::StepC2					= 0;

int     CAppStateGame::count_M1                 = 0;
int     CAppStateGame::count_M2                 = 0;
int     CAppStateGame::count_M3                 = 0;
int     CAppStateGame::count_M4                 = 0;
int     CAppStateGame::count_M5                 = 0;
int     CAppStateGame::count_M6                 = 0;

int		CAppStateGame::scene					= 0;
char	CAppStateGame::tempSoundBoss[255]		= {};
int		CAppStateGame::lastLevel				= 0;
int     CAppStateGame::E                        = 0;
int     CAppStateGame::nEnemy                   = 0;

int     CAppStateGame::EnemyAlive               = 0;


bool	CAppStateGame::appMinimized				= false;
bool	CAppStateGame::DisplayTouch				= false;
bool	CAppStateGame::nextState				= false;
bool    CAppStateGame::onReset                  = false;
bool    CAppStateGame::interstitialEvent        = false;

bool	CAppStateGame::MedalEvent				= true;
bool	CAppStateGame::MedalEventBoss			= true;

Uint32  CAppStateGame::interstitial_event       = 2;

SHud            CAppStateGame::PLYHUD = {};
SBarStamina     CAppStateGame::PLYBAR = {};



//bool CAppStateGame::g_destroy_requested         = false;
//bool CAppStateGame::g_started                   = false;
//bool CAppStateGame::g_restarted                 = false;


//int CAppStateGame::Sound_Main_BG = 0;
//int CAppStateGame::Sound_Boss = 0;




CAppStateGame::CAppStateGame() {

    SDL_Log("CAppStateGame()");

}


//-----------------------------------------------------------------------------

void CAppStateGame::OnKeyDown(SDL_Keysym sym) {

    switch(sym.sym)
	{

	    case SDLK_LEFT: {
            Player->MoveLeft = true;
            break;
        }

        case SDLK_RIGHT: {
            Player->MoveRight = true;
            break;
        }

        case SDLK_UP: {
            Player->MoveUp = true;
            break;
        }

        case SDLK_DOWN: {
            Player->MoveDown = true;
            break;
        }

        case SDLK_SPACE: {
            if (Player->fireMODE == CPlayer::FIRE_ROCKET)
            {
                if (interval > DELAY_ROCKET)
                {
                    Player->Fire();
                    interval = 0;
                }
            }
            else
            {
                if (interval > DELAY)
                {
                    Player->Fire();
                    interval = 0;
                }
            }
            break;
        }

        case SDLK_LCTRL: {
            if (bombCounter > 0)
            {
                if (interval > DELAY_BOMB)
                {
                    Player->DropBomb();
                    interval = 0;
                    bombCounter--;
                }
            }
            break;
        }

        case SDLK_p: {
            if (interval > DELAY)
            {
                lastPause = SDL_GetTicks();
                onPause = true;
                CAppStateManager::SetActiveAppState(APPSTATE_PAUSE);
                interval = 0;
            }
            break;
        }

		case SDLK_w: {
			 CEnemyBOSS1::damage = 0;
		}
		break;

        case SDLK_s: {

            }
            break;

        case SDLK_ESCAPE: {
			if (interval > DELAY)
			{
				lastPause = SDL_GetTicks();
				onPause = true;
				CAppStateManager::SetActiveAppState(APPSTATE_GAMEWIN);
				interval = 0;
			}
            break;
        }

		default: {}
	}
}


//-----------------------------------------------------------------------------
void CAppStateGame::OnKeyUp(SDL_Keysym sym) {

    switch(sym.sym) {
        case SDLK_LEFT: {
            Player->MoveLeft = false;
            break;
        }

        case SDLK_RIGHT: {
            Player->MoveRight = false;
            break;
        }

        case SDLK_UP: {
            Player->MoveUp = false;
            break;
        }

        case SDLK_DOWN: {
            Player->MoveDown = false;
            break;
        }

        case SDLK_SPACE: {
            Player->canFire = false;
            break;
        }

        default: {
        }
    }


}





/***** IN GAME TOUCH EVENTS *****/

void CAppStateGame::OnTouchedDown(float tX, float tY)
{
	//SDL_Log("StateGame::OnTouchedDown\n");

	SDL_Event e;
	SDL_PollEvent(&e);

    if (DisplayTouch)
    {

        e.type = SDL_FINGERDOWN;
        e.tfinger.x = tX;
        e.tfinger.y = tY;

        int tXw = tX * WWIDTH;
        int tYh = tY * WHEIGHT;



		if (tXw >= 0 && tXw <= WWIDTH && tYh >= 0 && tYh <= 250)
		{
			lastPause = SDL_GetTicks();
			//appMinimized = true;
			SDL_Log("AppStateGame onPause touched");
			onPause = true;
			interval = 0;
			CAppStateManager::SetActiveAppState(APPSTATE_PAUSE);
		}

		//LOGD("OnTouchedDown tfinger: (%1.4f, %1.4f)", tX, tY);
		//SDL_Log("OnTouchedDown tfinger : %1.4f, %1.4f", tX, tY);
		//SDL_Log("OnTouchedDown X - Y: %d - %d", tXw, tYh);
		//LOGD("OnTouchedUp WWIDTH&WHEIGHT: %d x %d", WWIDTH, WHEIGHT);

		/*
		if (Player->GetX() > tXw)
		{
		if (tXw <= Player->GetX() + 128 && tXw >= Player->GetX() - 128)
		{
		LOGD("StopMoveX() invocated");
		Player->StopMoveX();
		//Player->MoveRight = false;
		//Player->MoveLeft = false;
		}
		else
		{
		LOGD("moving left");
		Player->MoveRight = false;
		Player->MoveLeft = true;
		}
		}
		else if (Player->GetX() < tXw)
		{
		if (tXw <= Player->GetX() + 128 && tXw >= Player->GetX() - 128)
		{
		LOGD("StopMoveX() invocated");
		Player->StopMoveX();
		//Player->MoveRight = false;
		//Player->MoveLeft = false;
		}
		else
		{
		LOGD("moving right");
		Player->MoveLeft = false;
		Player->MoveRight = true;
		}
		}



		if (Player->GetY() > tYh)
		{
		if (tYh <= Player->GetY() + 128 && tYh >= Player->GetY() - 128)
		{
		LOGD("StopMoveY() invocated");
		Player->StopMoveY();
		//Player->MoveDown = false;
		//Player->MoveUp = false;
		}
		else
		{
		LOGD("moving up");
		Player->MoveUp = true;
		Player->MoveDown = false;
		}
		}
		else if (Player->GetY() < tYh)
		{
		if (tYh <= Player->GetY() + 128 && tYh >= Player->GetY() - 128)
		{
		LOGD("StopMoveY() invocated");
		Player->StopMoveY();
		//Player->MoveDown = false;
		//Player->MoveUp = false;
		}
		else
		{
		LOGD("moving down");
		Player->MoveDown = true;
		Player->MoveUp = false;
		}
		}

		*/

	}

}



void CAppStateGame::OnTouchedUp(float tX, float tY)
{
	//SDL_Log("StateGame::OnTouchedUp\n");

	SDL_Event e;
	SDL_PollEvent(&e);

    if (DisplayTouch)
    {

        e.type = SDL_FINGERUP;
        e.tfinger.x = tX;
        e.tfinger.y = tY;

        int tXw = tX * WWIDTH;
        int tYh = tY * WHEIGHT;
        //LOGD("OnTouchedUp X - Y: %d - %d", tXw, tYh);

		Player->MoveDown = false;
		Player->MoveUp = false;
		Player->MoveRight = false;
		Player->MoveLeft = false;
	}

	
	

}



void CAppStateGame::OnTouchedMove(float tX, float tY, float dX, float dY)
{
	//SDL_Log("StateGame::OnTouchedMove\n");

	SDL_Event e;
	SDL_PollEvent(&e);

    if (DisplayTouch)
    {

        e.type = SDL_FINGERMOTION;
        e.tfinger.x = tX;
        e.tfinger.y = tY;
        e.tfinger.dx = dX;
        e.tfinger.dy = dY;

        //float tXw = tX * WWIDTH;
        //float tYh = tY * WHEIGHT;
        dXw = dX * WWIDTH;
        dYh = dY * WHEIGHT;

        //SDL_Log("e.tfinger.dx: %1.4f e.tfinger.dy: %1.4f", e.tfinger.dx, e.tfinger.dy);
        //SDL_Log("dXw: %1.4f dYh: %1.4f", dXw, dYh);
        //SDL_Log("Player->X %1.4f Player->Y %1.4f", Player->PlayerGetX(), Player->PlayerGetY());



	    if(!CPlayer::PlayerStat.Dead && !nextState) Player->OnMove(dXw, dYh);
	}






	/***** ANALOGIC PILOT MODE *****

	if (Player->GetX() > tXw)
	{
		if (tXw >= Player->GetX() && tXw <= Player->GetX() + 128)
		{
			//LOGD("StopMoveX() invocated");
			Player->StopMoveX();
			//Player->MoveRight = false;
			//Player->MoveLeft = false;
		}
		else
		{
			//LOGD("moving left");
			Player->MoveRight = false;
			Player->MoveLeft = true;
		}
	}
	else if (Player->GetX() < tXw)
	{
		if (tXw >= Player->GetX() && tXw <= Player->GetX() + 128)
		{
			//LOGD("StopMoveX() invocated");
			Player->StopMoveX();
			//Player->MoveRight = false;
			//Player->MoveLeft = false;
		}
		else
		{
			//LOGD("moving right");
			Player->MoveLeft = false;
			Player->MoveRight = true;
		}
	}



	if (Player->GetY() > tYh)
	{
		if (tYh >= Player->GetY() && tYh <= Player->GetY() + 128)
		{
			//LOGD("StopMoveY() invocated");
			Player->StopMoveY();
			//Player->MoveDown = false;
			//Player->MoveUp = false;
		}
		else
		{
			//LOGD("moving up");
			Player->MoveUp = true;
			Player->MoveDown = false;
		}
	}
	else if (Player->GetY() < tYh)
	{
		if (tYh >= Player->GetY() && tYh <= Player->GetY() + 128)
		{
			//LOGD("StopMoveY() invocated");
			Player->StopMoveY();
			//Player->MoveDown = false;
			//Player->MoveUp = false;
		}
		else
		{
			//LOGD("moving down");
			Player->MoveDown = true;
			Player->MoveUp = false;
		}
	}

	*/
	

}

/*****************************************************************************/




//-----------------------------------------------------------------------------
void CAppStateGame::OnLoad(char* File) {

    CEnemyQueue::EnemyList.clear();

    SDL_Log("reading Level.x data");
    std::string levelData[10];
    const int TOTAL_DATA = 10;
    char buffer[512] = {"\0"};
    int blocks;

    SDL_RWops* io = SDL_RWFromFile(File, "rb");
    SDL_RWread(io, buffer, sizeof(buffer), 3);
    SDL_RWclose(io);



    char *line2 = strtok(strdup(buffer), "\n");

    SDL_Log("buffer: %s", line2);





#ifdef _WIN32
    char *line = strtok(_strdup(buffer), "\r\n");
#else
    char *line = strtok(strdup(buffer), ";");
#endif

    /***** Read File Level *****/
    //std::istringstream(Stringify::Char(line)) >> currentLevel;
    int temp_string;
    //currentLevel = atoi(line);
    temp_string = atoi(line);
    //CApp::Logger.OnLog(__FILE__, __LINE__, "file RW_ops currentLevel: ", Stringify::Int(currentLevel));
    line = strtok(NULL, ";");

    /***** Read Level Sound Track *****/
    //std::istringstream(Stringify::Char(line)) >> tempSoundLevel;
    //strcpy(tempSoundLevel, line);
    tempSoundLevel = line;
    //CApp::Logger.OnLog(__FILE__, __LINE__, "file RW_ops level soundtrack: ", Stringify::Char(tempSoundLevel));
    SDL_Log("file RW_ops level soundtrack: %s", tempSoundLevel);
    SDL_Log("read filelevel tempSoundLevel lenght: %d", strlen(tempSoundLevel));
    line = strtok(NULL, ";");

    /***** Read Boss Sound Track *****/
    //std::istringstream(Stringify::Char(line)) >> tempSoundBoss;
    strcpy(tempSoundBoss, line);
    //CApp::Logger.OnLog(__FILE__, __LINE__, "file RW_ops BOSS soundtrack: ", Stringify::Char(tempSoundBoss));
    LOGD("file RW_ops Boss soundtrack: %s", tempSoundBoss);
    line = strtok(NULL, ";");

    /***** Get File Map *****/
    //std::istringstream(Stringify::Char(line)) >> TileMapFile;
    strcpy(TileMapFile, line);
    //CApp::Logger.OnLog(__FILE__, __LINE__, "file RW_ops Tile Map File: ", Stringify::Char(TileMapFile));
    LOGD("file RW_ops Tile Map file: -%s-", TileMapFile);
    line = strtok(NULL, ";");

    /***** Get File Area *****/
    //std::istringstream(Stringify::Char(line)) >> TileAreaFile;
    strcpy(TileAreaFile, line);
    //CApp::Logger.OnLog(__FILE__, __LINE__, "file RW_ops Tile Area File: ", Stringify::Char(TileAreaFile));
    LOGD("file RW_ops Tile Area file: -%s-", TileAreaFile);
    line = strtok(NULL, "\n");

    /***** Read Area Size *****/
    //std::istringstream(Stringify::Char(line)) >> AreaSize;
    AreaSize = atoi(line);
    //CApp::Logger.OnLog(__FILE__, __LINE__, "file RW_ops AreaSize: ", Stringify::Int(AreaSize));
    LOGD("file RW_ops AreaSize: %d", AreaSize);

    //line = strtok(NULL, " ");
    //line = strtok(NULL, "\n");





    /***** !! IMPORT ENEMY PATTERN !! *****/




    /*
    SDL_Log("scene 2nd reading: %d", scene);
    if ((fileLevel == "levelX.level"))
    {
        scene = 3;
        SDL_Log("scene 3rd reading: %d", scene);
    }

    for (int E = 0; E < 4; E++)
    {

        //LOGD("loop E: %d", E);
        CApp::Logger.OnLog(__FILE__, __LINE__, "import enemy map", "step1");
        //SDL_Log("import enemy map step1\n");

        if (E == 0 || E == 1) { nEnemy = 7; }
        else if (E == 2) { nEnemy = 3; }
        else if (E == 3) { nEnemy = 1; }

        std::vector<CEnemyQueue> rowEnemy;
        //LOGD("file RW_ops enemy line STEP1: %s", line);

        for (int i = 0; i < nEnemy; i++)
        {

            //LOGD("loop i: %d", i);
            //std::istringstream(Stringify::Char(line)) >> tempc;
            strcpy(tempc, line);
            line = strtok(NULL, " ");
            //LOGD("file RW_ops enemy tempc STEP2: %s", tempc);

            std::string s = Stringify::Char(tempc);
            std::string token;
            size_t pos = 0;

            CEnemyQueue tempEnemy;

            while ((pos = s.find(delimiter)) != std::string::npos)
            {
                token = s.substr(0, pos);
                s.erase(0, pos + delimiter.length());
            }

            std::istringstream(token.c_str()) >> tempEnemy.EnemySize;
            std::istringstream(s.c_str()) >> tempEnemy.EnemyTimer;
            rowEnemy.push_back(tempEnemy);
            //LOGD("file RW_ops token: %s", token.c_str());
            //LOGD("file RW_ops erased: %s", s.c_str());
            //LOGD("file RW_ops enemyTimer: %d", tempEnemy.EnemyTimer);

        }
        CEnemyQueue::EnemyList.push_back(rowEnemy);
    }
    */




    E = 0;
    nEnemy = 0;
    std::string delimiter = ":";

    std::string check = Stringify::Char(line);

    SDL_Log("reading block: %s", line);

    while(line != NULL)
    {

        SDL_Log("new rowEnemy");
        std::vector<CEnemyQueue> rowEnemy;

        line = strtok(NULL, " ");
        //SDL_Log("line: -%s-", line);
        check = Stringify::Char(line);

        while (check != "#")
        {
            //SDL_Log("working line: -%s-", line);

            if (check == "EOF") break;
            strcpy(tempc, line);
            line = strtok(NULL, " ");

            //temp_line = strtok(NULL, " ");

            std::string s = Stringify::Char(tempc);
            std::string token;
            size_t pos = 0;

            CEnemyQueue tempEnemy;

            while ((pos = s.find(delimiter)) != std::string::npos)
            {
                token = s.substr(0, pos);
                s.erase(0, pos + delimiter.length());
            }

            std::istringstream(token.c_str()) >> tempEnemy.EnemySize;
            std::istringstream(s.c_str()) >> tempEnemy.EnemyTimer;
            rowEnemy.push_back(tempEnemy);
            LOGD("file RW_ops token: -%s-", token.c_str());
            //LOGD("file RW_ops erased: %s", s.c_str());
            LOGD("file RW_ops enemyTimer: -%d-", tempEnemy.EnemyTimer);

            nEnemy++;
            SDL_Log("nEnemy %d", nEnemy);
            check = Stringify::Char(line);
            //SDL_Log("next line: -%s- check: -%s-", line, check.c_str());
        }

        CEnemyQueue::EnemyList.push_back(rowEnemy);

        if (check == "EOF") break;
        nEnemy = 0;
        E++;
        SDL_Log("E loop: %d", E);
        //line = strtok(NULL, "\0");

    }

    SDL_Log("E tot: %d", E);
    scene = E;

    for (int  i=0; i < CEnemyQueue::EnemyList.size(); i++)
    {
        SDL_Log("i: %d", i);
        for (int y=0; y < CEnemyQueue::EnemyList[i].size(); y++)
        {
            SDL_Log("y: %d", y);
            SDL_Log("enemylist.size: %d", CEnemyQueue::EnemyList[i][y].EnemySize);
            SDL_Log("enemylist.timer: %d", CEnemyQueue::EnemyList[i][y].EnemyTimer);
        }
    }


    /***** Set Enviroments*****/
    SDL_Log("set Enviroments");
    CGalaxy::GalaxyControl.setEnviroments(Stringify::Char(TileMapFile), AreaSize);
    CArea::AreaControl.setEnviroments(Stringify::Char(TileAreaFile), AreaSize);
    CCamera::CameraControl.OnInit();

    //FILE* tempData = buffer;



}

void CAppStateGame::setVolume(int vt)
{
    BG_volume = MIX_MAX_VOLUME / vt;
    //Mix_Volume(-1, BG_volume);
    Mix_Volume(-1, volumeTuning);
}

//-----------------------------------------------------------------------------
void CAppStateGame::OnActivate() {

    //showADS();

    interstitialEvent = false;

    /*
    SDL_Event e;
    SDL_PollEvent(&e);
    e.type == CApp::interstitial_event;

    */

    interstitial_event = SDL_RegisterEvents(1);
    if (interstitial_event != ((Uint32)-1))
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event));
        event.type = interstitial_event;
        event.user.code = 0;
        event.user.data1 = 0;
        event.user.data2 = 0;
        SDL_PushEvent(&event);
    }

    //SDL_Delay(3000);

    //onPause = !onPause;

    //SDL_Delay(1000);
	SDL_Log("CAppStaGame activate, currentLevel: %d", currentLevel);


	CCamera::CameraControl.TargetMode = TARGET_MODE_NORMAL;

	MedalEvent = true;
    MedalEventBoss = true;

    if(!onPause)
    {
        SDL_Log("APPSTAGAME PAUSE = FALSE");

            //***** SDL2 Windows Initialize *****

            Window = CAppStateIntro::GetInstance()->GetWindow();
            PrimarySurface = SDL_GetWindowSurface(Window);
            Renderer = CAppStateIntro::GetInstance()->GetRenderer();


            if (CPlayerStat::PlayerStat.OnLoad() == false) {
                SDL_Log("Font Player stats loading error");
            } else {
                SDL_Log("Font Player loaded");
            }

            scene = 0;

            SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);


            SDL_Log("CAppStaGame reading level file");
            SDL_Log("last level loaded: %d", GetLastLevel());
            SDL_Log("OnActivate >> current level >> %d", currentLevel);


            /*** CHECK WHATEVER LEVEL PLAY ***/
            if (!CAppStateIntro::GetInstance()->GetMothershipComplete()) {
                SDL_Log("Mothership mission");
                fileLevel = "level0.level";
                //CAppStateIntro::GetInstance()->SetMothershipComplete(true);
            } else {
                SDL_Log("Get Mission Level");
                switch (currentMission) {
                    case 0:
                        switch (currentLevel) {
                            case 0:
                                fileLevel = "level11.level";
                                break;
                            case 1:
                                fileLevel = "level12.level";
                                break;
                            case 2:
                                fileLevel = "level13.level";
                                break;
                            case 3:
                                fileLevel = "level14.level";
                                break;
                            case 4:
                                fileLevel = "level15.level";
                                break;
                            case 5:
                                fileLevel = "level16.level";
                                break;
                            case 6:
                                fileLevel = "level17.level";
                                break;
                            case 7:
                                fileLevel = "level18.level";
                                break;
                            case 8:
                                fileLevel = "level19.level";
                                break;
                            case 9:
                                fileLevel = "level1x.level";
                                break;
                        }
                        break;

                    case 1:
                        switch (currentLevel) {
                            case 0:
                                fileLevel = "level21.level";
                                break;
                            case 1:
                                fileLevel = "level22.level";
                                break;
                            case 2:
                                fileLevel = "level23.level";
                                break;
                            case 3:
                                fileLevel = "level24.level";
                                break;
                            case 4:
                                fileLevel = "level25.level";
                                break;
                            case 5:
                                fileLevel = "level26.level";
                                break;
                            case 6:
                                fileLevel = "level27.level";
                                break;
                            case 7:
                                fileLevel = "level28.level";
                                break;
                            case 8:
                                fileLevel = "level29.level";
                                break;
                            case 9:
                                fileLevel = "level2x.level";
                                break;
                        }
                        break;

                    case 2:
                        switch (currentLevel) {
                            case 0:
                                fileLevel = "level31.level";
                                break;
                            case 1:
                                fileLevel = "level32.level";
                                break;
                            case 2:
                                fileLevel = "level33.level";
                                break;
                            case 3:
                                fileLevel = "level34.level";
                                break;
                            case 4:
                                fileLevel = "level35.level";
                                break;
                            case 5:
                                fileLevel = "level36.level";
                                break;
                            case 6:
                                fileLevel = "level37.level";
                                break;
                            case 7:
                                fileLevel = "level37.level";
                                break;
                            case 8:
                                fileLevel = "level37.level";
                                break;
                            case 9:
                                fileLevel = "level3x.level";
                                break;
                        }
                        break;

                    case 3:
                        switch (currentLevel) {
                            case 0:
                                fileLevel = "level41.level";
                                break;
                            case 1:
                                fileLevel = "level42.level";
                                break;
                            case 2:
                                fileLevel = "level43.level";
                                break;
                            case 3:
                                fileLevel = "level44.level";
                                break;
                            case 4:
                                fileLevel = "level45.level";
                                break;
                            case 5:
                                fileLevel = "level46.level";
                                break;
                            case 6:
                                fileLevel = "level47.level";
                                break;
                            case 7:
                                fileLevel = "level48.level";
                                break;
                            case 8:
                                fileLevel = "level49.level";
                                break;
                            case 9:
                                fileLevel = "level4x.level";
                                break;
                        }
                        break;

                    case 4:
                        switch (currentLevel) {
                            case 0:
                                fileLevel = "level51.level";
                                break;
                            case 1:
                                fileLevel = "level52.level";
                                break;
                            case 2:
                                fileLevel = "level53.level";
                                break;
                            case 3:
                                fileLevel = "level54.level";
                                break;
                            case 4:
                                fileLevel = "level55.level";
                                break;
                            case 5:
                                fileLevel = "level56.level";
                                break;
                            case 6:
                                fileLevel = "level57.level";
                                break;
                            case 7:
                                fileLevel = "level58.level";
                                break;
                            case 8:
                                fileLevel = "level59.level";
                                break;
                            case 9:
                                fileLevel = "level5x.level";
                                break;
                        }
                        break;
                    case 666:
                        SDL_Log("The Final Mission");
                        fileLevel = "levelX.level";
                        scene = 3;
                        SDL_Log("scene 1st reading: %d", scene);
                        break;
                }
            }


            IncLastLevel();

            OnLoad(fileLevel);
            SDL_Log("Level file loaded %s", fileLevel);

            levelCompleted = false;
            gamePlay = 0;
            DELAY = 10;
            DELAY_ROCKET = 10;
            DELAY_BOMB = 50;
            bombCounter = 3;
            attack = 20;
            b = -256;
            speed_inc = 5;


            SDL_ShowCursor(0);


            setVolume(volumeTuning);

            /*
            std::stringstream ss;
            ss.str(tempSoundLevel);
            std::string s = ss.str();
            */

            /** Main soundtrack (play on background...) */
            SDL_Log("passing level soundtrack: %s", tempSoundLevel);
            SDL_Log("tempSoundLevel lenght: %d", strlen(tempSoundLevel));
            SDL_Log("tempSoundLevel sizeof: %d", sizeof(tempSoundLevel));
            CSoundBank::SoundControl.Play2(tempSoundLevel);

            //CSoundBank::SoundControl.Play2("RoleMusic_Theme1");

            //CSoundBank::SoundControl.PlayOGG("LostInTheDawn.ogg");


            /** INIT GALAXY MAP */

            if (CGalaxy::GalaxyControl.OnLoad() == false) {
                CApp::Logger.OnLog(__FILE__, __LINE__, "Galaxy Map loading ERROR!", "");
                SDL_Log("Galaxy Map loading error");
            }


            /** INIT AREA */

            if (CArea::AreaControl.OnLoad() == false) {
                SDL_Log("Area Map loading error");
            }


            //-----INIT PLAYER----------------------------------------------------------
            SDL_Log("init Player");

            int tempMyShip = CAppStateIntro::GetInstance()->GetPlayerShip();
            //int tempMyShip = 4;

            char *player_ini = "";

            Player = new CPlayer();



            if (Player) {
                switch (tempMyShip) {
                    case 1:
                        Player->entityTexture = "RedSmall_anim";
                        player_ini = "playerA.ini";

                        Player->Type = ENTITY_TYPE_PLAYER;
                        Player->X = WWIDTH / 2 - 64;
                        Player->Y = WHEIGHT - 300;
                        Player->mPosX = 448;
                        Player->mPosY = 600;
                        Player->mVelX = 0;
                        Player->mVelY = 0;
                        Player->originalW = 348;
                        Player->originalH = 450;
                        Player->Width = Player->originalW * OVERALL_RATIO;
                        Player->Height = Player->originalH * OVERALL_RATIO;
                        Player->Dead = false;
                        Player->expired = false;
                        Player->GodMODE = false;
                        Player->setFireMode(CPlayer::FIRE_SINGLE);
                        Player->ID = 0;
                        //SDL_Log("Player Stamina reading");
                        Player->stamina = 0;
                        Player->PlayerStat.PlayerScore = 0000;
                        Player->playerHonor = 0;
                        Player->mySHIP = 1;
                        Player->SetPlayerShotCounter(30);
                        Player->OnInit();

                        break;
                    case 2:
                        Player->entityTexture = "BlueSmall_anim";
                        player_ini = "playerB.ini";

                        Player->Type = ENTITY_TYPE_PLAYER;
                        Player->X = WWIDTH / 2 - 64;
                        Player->Y = WHEIGHT - 300;
                        Player->mPosX = 448;
                        Player->mPosY = 600;
                        Player->mVelX = 0;
                        Player->mVelY = 0;
                        Player->originalW = 387;
                        Player->originalH = 400;
                        Player->Width = Player->originalW * OVERALL_RATIO;
                        Player->Height = Player->originalH * OVERALL_RATIO;
                        Player->Dead = false;
                        Player->expired = false;
                        Player->GodMODE = false;
                        Player->setFireMode(CPlayer::FIRE_SMARTROCKET);
                        Player->ID = 0;
                        Player->stamina = 0;
                        Player->PlayerStat.PlayerScore = 0000;
                        Player->playerHonor = 0;
                        Player->mySHIP = 2;
                        Player->SetPlayerShotCounter(30);
                        Player->OnInit();

                        break;
                    case 3:
                        Player->entityTexture = "GreenSmall_anim";
                        player_ini = "playerC.ini";

                        Player->Type = ENTITY_TYPE_PLAYER;
                        Player->X = WWIDTH / 2 - 64;
                        Player->Y = WHEIGHT - 300;
                        Player->mPosX = 448;
                        Player->mPosY = 600;
                        Player->mVelX = 0;
                        Player->mVelY = 0;
                        Player->originalW = 517;
                        Player->originalH = 400;
                        Player->Width = Player->originalW * OVERALL_RATIO;
                        Player->Height = Player->originalH * OVERALL_RATIO;
                        Player->Dead = false;
                        Player->expired = false;
                        Player->GodMODE = false;
                        Player->setFireMode(CPlayer::FIRE_GAMMARAY);
                        Player->ID = 0;
                        Player->stamina = 0;
                        Player->PlayerStat.PlayerScore = 0000;
                        Player->playerHonor = 0;
                        Player->mySHIP = 3;
                        Player->SetPlayerShotCounter(35);
                        Player->OnInit();

                        break;

                    case 4:
                        Player->entityTexture = "YellowStronger_anim";
                        player_ini = "playerD.ini";

                        Player->Type = ENTITY_TYPE_PLAYER;
                        Player->X = WWIDTH / 2 - 64;
                        Player->Y = WHEIGHT - 300;
                        Player->mPosX = 448;
                        Player->mPosY = 600;
                        Player->mVelX = 0;
                        Player->mVelY = 0;
                        Player->originalW = 450;
                        Player->originalH = 400;
                        Player->Width = Player->originalW * OVERALL_RATIO;
                        Player->Height = Player->originalH * OVERALL_RATIO;
                        Player->Dead = false;
                        Player->expired = false;
                        Player->GodMODE = false;
                        Player->setFireMode(CPlayer::FIRE_SMARTROCKET);
                        Player->ID = 0;
                        Player->stamina = 0;
                        Player->PlayerStat.PlayerScore = 0000;
                        Player->playerHonor = 0;
                        Player->mySHIP = 4;
                        Player->SetPlayerShotCounter(40);
                        Player->OnInit();

                        break;
                }


                CEntity::EntityList.push_back(Player);
                CEntity::EntityMap[Player->ID]=Player;
                SDL_Log("Player instance ID: %d", Player->ID);
                SDL_Log("Player shot rate: %d", Player->GetPlayerShoCounter());

            } else {
                SDL_Log("unable to init Player entity");
            }

            count_M1 = count_M2 = count_M3 = count_M4 = count_M5 = count_M6 = 0;


            SDL_Log("reading playerX.ini");
            std::string gameData[10];
            const int TOTAL_DATA = 10;


            char buffer[512] = {"\0"};
            SDL_RWops *ig = SDL_RWFromFile(player_ini, "rb");
            SDL_RWread(ig, buffer, sizeof(buffer), 3);
            SDL_RWclose(ig);



            /*
        #ifdef _WIN32
            char *line = strtok(_strdup(buffer), "\r\n");
        #else
            char *line = strtok(strdup(buffer), ";");
        #endif
            */

            SDL_Log("Player Maximum Level reached");
            // Player Maximum Level reached
            char *tk = strtok(strdup(buffer), ";");
            SDL_Log("MaxLevel: %d", atoi(tk));
            Player->SetLevelMax(atoi(tk));


            // Player Max Speed
            tk = strtok(NULL, ";");
            Player->SetMaxSpeed(atof(tk));
            SDL_Log("MaxSpeed: %f1.2", atof(tk));

            // Player Max Accel
            tk = strtok(NULL, ";");
            Player->SetMaxAccel(atof(tk));
            SDL_Log("MaxAccel: %f1.2", atof(tk));

            // Player Plasma Enabled
            bool bp;
            tk = strtok(NULL, ";");
            std::stringstream(tk) >> bp;
            Player->SetPlasma(bp);
            SDL_Log("Plasma? %d", tk);

            // Player Gamma Ray Enabled
            bool bg;
            tk = strtok(NULL, ";");
            std::istringstream(tk) >> bg;
            Player->SetGammaRay(true);
            SDL_Log("GammaRay? %d", tk);

            // Player armor
            tk = strtok(NULL, ";");
            int tempARM;
            std::istringstream(tk) >> tempARM;
            Player->SetPlayerArmor(tempARM);
            Player->PRE_armor = tempARM;
            SDL_Log("Player armor: %d", tempARM);

            // Player stamina
            tk = strtok(NULL, ";");
            int tempSTM;
            std::istringstream(tk) >> tempSTM;
            Player->SetPlayerStamina(tempSTM);
            Player->PRE_stamina = tempSTM;
            SDL_Log("Player stamina: %d", tempSTM);
            //Player->PlayerHealth = GetPlayerStamina();

            // Player Shot Ratio
            tk = strtok(NULL, ";");
            int tempRATIO;
            std::istringstream(tk) >> tempRATIO;
            Player->SetPlayerShotCounter(tempRATIO);
            SDL_Log("Player ratio: %d", tempRATIO);


            //CGenerator::setXC(WWIDTH * 0.60);
            CGenerator::xc = (WWIDTH / 2) + 50;

            PLYHUD.x = 10;
            PLYHUD.y = 10;
            PLYHUD.x2 = 0;
            PLYHUD.y2 = 0;
            PLYHUD.w2 = 676;
            PLYHUD.h2 = 169;
            PLYHUD.w = PLYHUD.w2 * OVERALL_RATIO;
            PLYHUD.h = PLYHUD.h2 * OVERALL_RATIO;

            PLYHUD.alpha = 255;

            PLYBAR.x = PLYHUD.x + PLYHUD.w * 0.24;
            PLYBAR.y = PLYHUD.y + PLYHUD.h * 0.33;
            PLYBAR.x2 = 0;
            PLYBAR.y2 = 0;
            PLYBAR.w2 = 462;
            PLYBAR.h2 = 60;
            PLYBAR.w = PLYBAR.w2 * OVERALL_RATIO;
            PLYBAR.h = PLYBAR.h2 * OVERALL_RATIO;
            PLYBAR.perc = 0;

            nextState = false;
            DisplayTouch = true;
            /*

            FOR BETA TEST
            CEnemyMM *EnemyZ = new CEnemyMM(500,100);

            if(EnemyZ->OnLoad("IMG/MySpaceship_animatedMM.png", 128, 128) == false)
            {
                CApp::Logger.OnLog( __FILE__, __LINE__, "CEnemySX image load ERROR!", "");
                //return false;
            }
            CEntity::EntityList.push_back(EnemyZ);
            CEnemyMM::EnemyMMList.push_back(EnemyZ);
            std::cout<<"EnemyMMList Size after push: "<<CEnemyMM::EnemyMMList.size()<<"\n";

            */

            //SDL_Log("Call_Interstitial() in OnActivate()");
            //Call_Interstitial();



    }// END IF (!ONPAUSE) *****
    else
    {
        SDL_Log("APPSTAGAME PAUSE = TRUE");
        if (!onReset)
        {
            SDL_Log("APPSTAGAME RESET = FALSE");

            CSoundBank::SoundControl.Resume(tempSoundLevel);
            //CSoundBank::SoundControl.Resume(tempSoundBoss);
        }
        else if (onReset && !nextState) {


            SDL_Log("APPSTAGAME RESET = TRUE");
            SDL_Log("---LEVEL RESTART---");


            onPause = false;
            OnDeactivate();
            onReset = false;
            OnActivate();
        }
        else if (onReset && nextState) {

            SDL_Log("---Player dead - reset ever---");

            onPause = false;
            OnDeactivate();
            onReset = false;


        }
    }

	
	/** create in-game pause button */
	//CAppStateGamePause::GetInstance()->OnActivate();
	//CAppStateGamePause::GetInstance()->createPauseP();


	levelStarted = SDL_GetTicks();

    if(!appMinimized) onPause = false;

    SDL_Log("levelStarted at: %d", levelStarted);

}


//-----------------------------------------------------------------------------
void CAppStateGame::OnDeactivate() {

    
	SDL_Log("Deactivating GameState...");

    if(!onPause)
    {

		MedalEvent = false;
		MedalEventBoss = false;

		countLoop = 0;
		CGenerator::setEE(0);
		scene = 0;
		SDL_Log("on Deactivating gamestate - setEE(0) = %d", CGenerator::getEE());


	    //IMG_Quit();

        //REMOVE background
		SDL_Log("clear Area & Galaxy environments vector");
        CApp::Logger.OnLog( __FILE__, __LINE__, "Cleaning area maps", "");
        CArea::AreaControl.OnCleanup();
		CGalaxy::GalaxyControl.OnCleanup();
		
        // REMOVE Entities

		SDL_Log("clear EntityList vector");
		for (std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end(); ++it)
		{
			delete (*it);
		}
		CEntity::EntityList.clear();

		SDL_Log("clear TargetEnemyMap");
		CEntity::TargetEnemyMap.clear();

		SDL_Log("clear EntityColList vector");
        CEntityCol::EntityColList.clear();


		SDL_Log("EnemyList.size(): %d", CEnemyQueue::EnemyList.size());
		CEnemyQueue::EnemyList.clear();
		SDL_Log("EnemyList.size(): %d", CEnemyQueue::EnemyList.size());


        SDL_Log("EnityMap.size() %d", CEntity::EntityMap.size());
        if(CEntity::EntityMap.size() <= 0) return;
        /*
        for(auto& Iterator : CEntity::EntityMap)
        {
            delete Iterator.second;
        }
         */
        /*
        for(std::map<int, CEntity*>::iterator itm = CEntity::EntityMap.begin(); itm != CEntity::EntityMap.end(); ++itm)
        {
            if(itm->second != NULL)
            {
                SDL_Log("delete map pointer");
                delete (itm->second);
                SDL_Log("erase map raw");
                CEntity::EntityMap.erase(itm);
            }
        }
        */

        CEntity::EntityMap.clear();
        SDL_Log("EnityMap.size() %d", CEntity::EntityMap.size());

        /*
        for(auto& Iterator : CEntity::EntityMap)
        {
            //CEntity* TheEntity = (CEntity*)Iterator.second;

            if(Iterator.second->Dead == true)
            {
                CEntity* TheEntity = (CEntity*)Iterator.second;

                SDL_Log("MM3 map delete");
                delete TheEntity;
                TheEntity = NULL;
            }
        }
        */

		// update levels reached
        if(!onReset)
        {
            SDL_Log("APPSTAGAME RESET = FALSE");

            if (!CAppStateIntro::GetInstance()->GetMothershipComplete()) {
                SDL_Log("mothership boolean flag false");
                CAppStateIntro::GetInstance()->SetMothershipComplete(true);
                bool tempArray[3] = {true, true, false};
                CAppStateIntro::GetInstance()->SetMySpaceship(tempArray);
                SDL_Log("new spaceship acquired: %s", tempArray);

                for (int i = 0; i < 5; i++) {
                    CAppStateIntro::GetInstance()->level_gained[i][0] = 1;
                }
            } else if (levelCompleted) {
                SDL_Log("level completed - currentLevel: %d", currentLevel);
                if (currentLevel < 9)
                    CAppStateIntro::GetInstance()->level_gained[currentMission][currentLevel +
                                                                                1] = 1;
                else if (currentLevel == 9) SDL_Log("BOSS DEFEATED!");
            }
            /*		else
                    {
                        // ELSE statement useless!
                        SDL_Log("mothership boolean flag true");
                        CAppStateIntro::GetInstance()->SetMothershipComplete(true);
                    }
            */

            int temp_stage = 0;
            for(int i=0; i<5; i++)
            {
                if (CAppStateIntro::GetInstance()->stage_complete[i]) temp_stage++;
            }
            if(temp_stage == 4) CAppStateIntro::GetInstance()->SetFinalMission(true);
            else CAppStateIntro::GetInstance()->SetFinalMission(false);





            std::string end = Stringify::Int(CPlayer::GetLevelMax()) + ";" +
                              Stringify::Float(CPlayer::GetMaxSpeed()) + ";1;1;1";
            const char *str = end.c_str();
            SDL_Log("WR to player.ini: %s", str);
            SDL_RWops *rw_player = SDL_RWFromFile("player.ini", "w");
            if (rw_player != NULL) {
                size_t len = SDL_strlen(str);
                if (SDL_RWwrite(rw_player, str, 1, len) != len) {
                    SDL_Log("Couldn't fully write string");
                } else {
                    SDL_Log("Wrote %d 1-byte blocks", len);
                }
                SDL_RWclose(rw_player);
            }

            // writing Game Data
            SDL_Log("saving game data...");

            //set spaceships array
            std::string vectShips = "";
            for (int s = 0; s < 4; s++) {
                vectShips += Stringify::Int(CAppStateIntro::GetInstance()->MySpaceship[s]) + ";";
            }
            vectShips = vectShips + "\n";
            SDL_Log("vectShips: %s", vectShips.c_str());

            // set 3 bool statement
            std::string endgame =
                    Stringify::Int(CAppStateIntro::GetInstance()->GetMothershipComplete()) + ";" +
                    Stringify::Int(CAppStateIntro::GetInstance()->GetAllMission()) + ";" +
                    Stringify::Int(CAppStateIntro::GetInstance()->GetFinalMission()) + ";";



            // set array levels
            std::string vectGame = "";
            for (int x = 0; x < 5; x++) {
                vectGame = vectGame + "\n";
                for (int y = 0; y < 10; y++) {
                    vectGame +=
                            Stringify::Int(CAppStateIntro::GetInstance()->level_gained[x][y]) + ";";
                }
                SDL_Log("vectGame: %s", vectGame.c_str());
            }


            const char *str_ship = vectShips.c_str();
            const char *str_game = endgame.c_str();
            const char *str_vect = vectGame.c_str();

            SDL_Log("str_game cstring %s", str_game);
            SDL_Log("str_game %s", str_game);
            SDL_Log("str_vect %s", str_vect);

            std::string buffer(str_ship);
            buffer.append(str_game);
            buffer.append(str_vect);

            SDL_Log("WR to game.ini: %s", buffer.c_str());
            SDL_RWops *rw_game = SDL_RWFromFile("game.ini", "wb");
            if (rw_game != NULL) {
                size_t len = SDL_strlen(buffer.c_str());
                if (SDL_RWwrite(rw_game, buffer.c_str(), 1, len) != len) {
                    SDL_Log("Couldn't fully write string");
                } else {
                    SDL_Log("Wrote %d 1-byte blocks", len);
                }
                SDL_RWclose(rw_game);
            }

            // check file just saved
            SDL_Log("reading game.ini");
            std::string gameData[500];
            const int TOTAL_DATA = 500;
            char buffer1[1024] = {"\0"};
            char *game_ini = "game.ini";

            SDL_RWops *ig = SDL_RWFromFile(game_ini, "r");
            SDL_RWread(ig, buffer1, sizeof(buffer1), 4);
            SDL_RWclose(ig);

            SDL_Log("game.ini: %s", buffer1);

            CPlayer::PlayerStat.IncTOTscore(CPlayer::PlayerStat.PlayerScore);
            SDL_Log("updated player Total Score: %d", CPlayer::PlayerStat.GetTOTscore());

        }

        SDL_Log("Stop sound");
        CSoundBank::SoundControl.Halt(-1);


        // writing Player Data
        SDL_Log("saving Player data...");





    }
    else
    {

        SDL_Log("APPSTATEGAME OnPause");
		CSoundBank::SoundControl.Pause(tempSoundLevel);
		CSoundBank::SoundControl.Pause(tempSoundBoss);
		//CApp::Logger.OnLog(__FILE__, __LINE__, "Player Honor", Stringify::Int(Player->playerHonor));
		//CApp::Logger.OnLog(__FILE__, __LINE__, "Player star SX", Stringify::Int(Player->starSX));
		//CApp::Logger.OnLog(__FILE__, __LINE__, "Player star MM", Stringify::Int(Player->starMM));
		//CApp::Logger.OnLog(__FILE__, __LINE__, "Player star M1", Stringify::Int(Player->starM1));
		//CApp::Logger.OnLog(__FILE__, __LINE__, "Player star BB", Stringify::Int(Player->starBB));
	}

	
    SDL_Log("Deactivating GameState completed");
}


//-----------------------------------------------------------------------------
void CAppStateGame::OnLoop() {


    ///SDL_Log("CAppStateGame new loop");

    if(!onPause)
    {

        setVolume(volumeTuning);

        /// ENTITY STL POINTERS QUEUE DELETE
        for (Uint32 i = 0; i < CEntity::EntityList.size(); i++) {
            if (!CEntity::EntityList[i]) continue;

            CEntity::EntityList[i]->EntityDEL();
        }

        a = 0;
        c = (rand() % 600 + 100);

        TimeLeft = SDL_GetTicks();

        gamePlay = SDL_GetTicks();

        enemy_Timer += CFPS::FPSControl.GetSpeedFactor();
        enemy_Fire += CFPS::FPSControl.GetSpeedFactor();
        interval += CFPS::FPSControl.GetSpeedFactor();
        BOSS_interval += CFPS::FPSControl.GetSpeedFactor();



        for (Uint32 i = 0; i < CEntity::EntityList.size(); i++)
        {
            if (!CEntity::EntityList[i]) continue;
            {
                CEntity::EntityList[i]->OnLoop();
            }
        }




        /// ENEMY GENERATOR
        //SDL_Log("levelStarted: %d", levelStarted);
        //SDL_Log("gamePlay: %d\n", gamePlay);
        if (gamePlay > levelStarted + 4000)
        {
            CGenerator::EnemyMaker.OnGenerator(countLoop, gamePlay);
            //SDL_Log("Spawner invocated!");
        }

        //SDL_Log("EntityList Size: %d", CEntity::EntityList.size());

        //***ENTITY COLLISION CHECK***
        for (Uint32 i = 0; i < CEntityCol::EntityColList.size(); i++)
        {
            CEntity *EntityA = CEntityCol::EntityColList[i].EntityA;
            CEntity *EntityB = CEntityCol::EntityColList[i].EntityB;

            SDL_Log("EntityA ID %d", EntityA->ID);
            SDL_Log("EntityB ID %d", EntityB->ID);

            if (EntityA == NULL || EntityB == NULL) {
                SDL_Log("EntityA/B = NULL... break for");
                break;
            }



            if (EntityA->OnCollision(EntityB) && EntityB->OnCollision(EntityA)) {
                //EntityA->OnCollision(EntityB);
                //EntityB->OnCollision(EntityA);
                CEntityCol::EntityColList.clear();
            }
        }

        //CApp::Logger.OnLog( __FILE__, __LINE__, "Clear EntityColList", "");
        //CEntityCol::EntityColList.clear();





        /*
        for(auto& it : CEntity::EntityList)
        {

            if(!(it)) continue;
            if (it->Dead)
            {
                it->EntityDEL();
            }
        }
        */

        /// CHECK PLAYER ALIVE
        TimeOut = SDL_GetTicks();
        if (this->nextState)
        {
            //DisplayTouch = false;
            //SDL_Log("Player dead - step1\n");
            if (TimeOut > this->DeadTime + 5000)
            {
                SDL_Log("Player dead - set APPSTATEPAUSE_GAMEOVER");
                //CAppStateManager::SetActiveAppState(APPSTATE_GAMEOVER);
                //Call_Interstitial();
                SDL_Delay(2000);
                SDL_Log("CAppStateGame, gameover level: %d", currentLevel);
                SDL_Log("set APPSTATE_PAUSE");
                onPause = false;
                onReset = true;
                //nextState = false;
                CAppStateGamePause::setActiveMenu(CAppStateGamePause::GAME_OVER);
                CAppStateManager::SetActiveAppState(APPSTATE_PAUSE);
            }
        }


        ////////////////////////////
        /// CHECK LEVEL COMPLETE ///
        ////////////////////////////
        if (levelCompleted) {
            //CPlayer::PlayerStat.setFireMode(CPlayer::FIRE_NONE);
            //IncLastLevel();
            while (true) {
                if (TimeOut > BossTimeDeath + 8000) {
                    CPlayer::PlayerStat.SetMaxSpeed(15);
                    DisplayTouch = false;
                    Player->OnMove(0.0, -(speed_inc));
                    speed_inc += 2;
                    if (TimeOut > BossTimeDeath + 14000) {
                        if (!nextState) {
                            CSoundBank::SoundControl.Pause(tempSoundLevel);
                            CSoundBank::SoundControl.Pause(tempSoundBoss);
                            //Call_Interstitial();
                            SDL_Delay(2000);
                            SDL_Log("CAppStateGame, level %d completed!", currentLevel);
                            SDL_Log("set APPSTATE_PAUSE");
                            onPause = false;
                            SDL_Log("AppStateGame onPause = false");
                            CAppStateGamePause::menuTrans = true;
                            CAppStateGamePause::setActiveMenu(CAppStateGamePause::COMPLETED);
                            CAppStateManager::SetActiveAppState(APPSTATE_PAUSE);
                        }
                    }
                }
                break;
            }
        }

        /*
        /// event once caller
        if (CPlayer::PlayerStat.PlayerScore >= 800 && CPlayer::PlayerStat.PlayerScore <= 1200)
        {
            if (MedalEventBoss)
            {
                CGenerator::EnemyMaker.CreateMedal_6_Event();
                MedalEventBoss = false;
            }
        }
        */

        /// poll events queue
        SDL_Event e;
        while (SDL_PollEvent(&e)) {

            switch (e.type) {

                case CGenerator::BOSS:
                    //SDL_Log("event type = BossEventType");
                    //SwitchPlayerFiremode(CPlayer::FIRE_SINGLE);
                    e.drop;
                    break;

                case CGenerator::FIRE_TRIPLE:
                    SDL_Log("event type = Medal_1_triple");
                    MedalHonor = new CMedal((WWIDTH / 2) + 50, -100, 0, 30, "powerup_01",
                                            ENTITY_FLAG_NONE,
                                            BEZIER);

                    MedalHonor->entityTexture = "Icon_medal_triple";
                    MedalHonor->Width = 199 * OVERALL_RATIO;
                    MedalHonor->Height = 198 * OVERALL_RATIO;
                    MedalHonor->medalReward = MEDAL_TRIPLE;
                    MedalHonor->OnInit();

                    CEntity::EntityList.push_back(MedalHonor);
                    //e.drop;
                    break;

                case CGenerator::FIRE_PENTA:
                    SDL_Log("event type = Medal_2_penta");
                    MedalHonor = new CMedal((WWIDTH / 2) + 100, -100, 0, 30, "powerup_01",
                                            ENTITY_FLAG_NONE,
                                            BEZIER);

                    MedalHonor->entityTexture = "Icon_medal_penta";
                    MedalHonor->Width = 199 * OVERALL_RATIO;
                    MedalHonor->Height = 198 * OVERALL_RATIO;
                    MedalHonor->medalReward = MEDAL_PENTA;
                    MedalHonor->OnInit();

                    CEntity::EntityList.push_back(MedalHonor);
                    //e.drop;
                    break;

                case CGenerator::FIRE_ROCKET:
                    SDL_Log("event type = Medal_3_rocket");
                    MedalHonor = new CMedal((WWIDTH / 2) + 75, -100, 0, 30, "powerup_01",
                                            ENTITY_FLAG_NONE,
                                            BEZIER);

                    MedalHonor->entityTexture = "Icon_medal_rocket";
                    MedalHonor->Width = 199 * OVERALL_RATIO;
                    MedalHonor->Height = 198 * OVERALL_RATIO;
                    MedalHonor->medalReward = MEDAL_ROCKET;
                    MedalHonor->OnInit();

                    CEntity::EntityList.push_back(MedalHonor);
                    //e.drop;
                    break;

                case CGenerator::FIRE_GAMMARAY:
                    SDL_Log("event type = Medal_4_gammaray");
                    MedalHonor = new CMedal((WWIDTH / 2) + 90, -100, 0, 30, "powerup_01",
                                            ENTITY_FLAG_NONE,
                                            BEZIER);

                    MedalHonor->entityTexture = "Icon_medal_gammaray";
                    MedalHonor->Width = 200 * OVERALL_RATIO;
                    MedalHonor->Height = 198 * OVERALL_RATIO;
                    MedalHonor->medalReward = MEDAL_GAMMARAY;
                    MedalHonor->OnInit();

                    CEntity::EntityList.push_back(MedalHonor);
                    //e.drop;
                    break;

                case CGenerator::FIRE_TOTAL:
                    SDL_Log("event type = Medal_5_combotot");
                    MedalHonor = new CMedal((WWIDTH / 2) + 120, -100, 0, 30, "powerup_01",
                                            ENTITY_FLAG_NONE,
                                            BEZIER);

                    MedalHonor->entityTexture = "Icon_medal_combotot";
                    MedalHonor->Width = 199 * OVERALL_RATIO;
                    MedalHonor->Height = 198 * OVERALL_RATIO;
                    MedalHonor->medalReward = MEDAL_COMBOTOT;
                    MedalHonor->OnInit();

                    CEntity::EntityList.push_back(MedalHonor);
                    //e.drop;
                    break;

                case CGenerator::BONUS_POINT:
                    SDL_Log("event type = Medal_6_bonus_points");
                    MedalHonor = new CMedal((WWIDTH / 2) + 120, -100, 0, 30, "powerup_01",
                                            ENTITY_FLAG_NONE,
                                            BEZIER);

                    MedalHonor->entityTexture = "IconFireUp";
                    MedalHonor->Width = 135 * OVERALL_RATIO;
                    MedalHonor->Height = 135 * OVERALL_RATIO;
                    MedalHonor->medalReward = MEDAL_NONE;
                    MedalHonor->OnInit();

                    CEntity::EntityList.push_back(MedalHonor);
                    //e.drop;
                    break;

                default:
                    break;

            }
        }

        /// ENTITY STL POINTERS QUEUE DELETE
        for (Uint32 i = 0; i < CEntity::EntityList.size(); i++) {
            if (!CEntity::EntityList[i]) continue;

            CEntity::EntityList[i]->EntityDEL();
        }

        CountEnemy();

        countLoop++;
        ///SDL_Log("CAppStateGame end loop");


    }

}




//-----------------------------------------------------------------------------
//-----RENDERING FUNCTION-------------------------------------------------------
//-----------------------------------------------------------------------------
void CAppStateGame::OnRender() {

	SDL_SetRenderDrawColor(Renderer, 0x00, 0xFF, 0x00, 0xFF);

    if(Renderer) SDL_RenderClear(Renderer);


	/** Menu Rendering 
	for (std::vector<CMenu*>::iterator it = CAppStateGamePause::vectorMenu.begin(); it != CAppStateGamePause::vectorMenu.end(); ++it)
	{
		if (!(*it)) continue;
		(*it)->onRender();
	}
	*/



/** Background: black color */
	
    SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = WWIDTH;
	Rect.h = WHEIGHT;

	
	/// Background deep galaxy
	//SDL_Log("StateGame render galaxy\n");
	CGalaxy::GalaxyControl.OnRender(CCamera::CameraControl.GetX(), CCamera::CameraControl.GetYgal());


	/// Background starfield
	//SDL_Log("StateGame render area\n");
	CArea::AreaControl.OnRender(CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());


	
//-----Laser ENEMY-----
    /// render laser enemies
    for (Uint32 i = 0; i < CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i]) continue;
        //if (CEntity::EntityList[i]->Type != ENTITY_TYPE_MyBULLET || CEntity::EntityList[i]->Type != ENTITY_TYPE_PLAYER)
        if (CEntity::EntityList[i]->Type == ENTITY_TYPE_LASER)
            CEntity::EntityList[i]->OnRender();
    }



//-----ENTITIES-----

    /// render generic entities
    for (auto& it : CEntity::EntityList)
    {
        if(it->Type != ENTITY_TYPE_PLAYER || it->Type != ENTITY_TYPE_PARTICLE || it->Type != ENTITY_TYPE_LASER || it->Type != ENTITY_TYPE_MyBULLET || it->Type != ENTITY_TYPE_GAMMARAY || it->Flags != ENTITY_FLAG_CANNON)
        {
            it->OnRender();
        }
    }

    /// render Boss cannon
    for (auto& it : CEntity::EntityList)
    {
        if(it->Flags == ENTITY_FLAG_CANNON)
        {
            it->OnRender();
        }
    }

    /// render player's ammo
    for (auto& it : CEntity::EntityList)
    {
        if(it->Type == ENTITY_TYPE_MyBULLET || it->Type == ENTITY_TYPE_GAMMARAY)
        {
            it->OnRender();
        }
    }

    /*
	for (Uint32 i = 0; i < CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i]) continue;
        //if (CEntity::EntityList[i]->Type != ENTITY_TYPE_MyBULLET || CEntity::EntityList[i]->Type != ENTITY_TYPE_PLAYER)
        if (CEntity::EntityList[i]->Type != ENTITY_TYPE_PLAYER || CEntity::EntityList[i]->Type != ENTITY_TYPE_PARTICLE || CEntity::EntityList[i]->Type != ENTITY_TYPE_LASER)
            CEntity::EntityList[i]->OnRender();
    }
    */

    /*
	if (CPopup::GetInstance()->show == true)
	{
		CPopup::GetInstance()->OnRender();
	}
    */


    //-----Render Bullet Player-----
    /*
	for (Uint32 i = 0; i < CEntity::EntityList.size(); i++)
    {
        if (CEntity::EntityList[i]->Type == ENTITY_TYPE_MyBULLET)
            CEntity::EntityList[i]->OnRender();
    }
    */

    /// render boss stamina
    if (CEnemyBOSS1::BossIsAlive && CEnemyBOSS1::getYen() > -450)
    {
        if (CEnemyBOSS1::damage > 0)
        {
            //CEnemyBOSS1::OnRenderStamina();
			//CPlayerStat::PlayerStat.OnRender(0.0, WWIDTH - 260, 10, (CEnemyBOSS1::damage * 2), 30, 0);
            CGenerator::BOSSBAR.perc = ((float)CEnemyBOSS1::damage / 100) * OVERALL_ENEMY_RATIO;
            //CPlayerStat::RenderStaminaPlayer("HealthBOSSbar", "HealthBOSShud", CGenerator::BOSSHUD, CGenerator::BOSSBAR);
        	CPlayerStat::RenderStaminaFlip("HealthBOSSbar", "HealthBOSShud", CGenerator::BOSSHUD, CGenerator::BOSSBAR);
		}
    }

    /// render player
	for (Uint32 i = 0; i < CEntity::EntityList.size(); i++)
	{
		if(!CEntity::EntityList[i]) continue;
		if (CEntity::EntityList[i]->Type == ENTITY_TYPE_PLAYER)
        {
            CEntity::EntityList[i]->OnRender();
        }
	}

    /// render particle effects
    for (Uint32 i = 0; i < CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i]) continue;
        if (CEntity::EntityList[i]->Type == ENTITY_TYPE_PARTICLE)
        {
            CEntity::EntityList[i]->OnRender();
        }
    }

	/** in-game option button*/
	//CAppStateGamePause::GetInstance()->OnRender();


//-----STATISTICS-----
	// points
    //CPlayerStat::PlayerStat.OnRender(10, 10, 150, 30);

	// stamina

    if (Player->stamina > 0 && nextState == false)
    {
        //CPlayerStat::PlayerStat.OnRender(255, 200, 10, Player->stamina *2, 30);
    	PLYBAR.perc = (((float)Player->stamina) / 100) * OVERALL_ENEMY_RATIO;
        //SDL_Log("PLYperc: %1.2f", PLYBAR.perc);
        CPlayerStat::RenderStaminaPlayer("HealthBAR", "HealthHUD", PLYHUD, PLYBAR);
	}




	
    if (Renderer) SDL_RenderPresent(Renderer);



}


//-----------------------------------------------------------------------------








//-----------------------------------------------------------------------------
CAppStateGame* CAppStateGame::GetInstance() {

    return &Instance;

}

//-----------------------------------------------------------------------------
SDL_Renderer* CAppStateGame::GetRenderer() {

    return Renderer;

}

//-----------------------------------------------------------------------------
SDL_Window* CAppStateGame::GetWindow() {

    return Window;

}


//-----------------------------------------------------------------------------
void CAppStateGame::ResetLastLevel() {

	lastLevel = 0;

}

void CAppStateGame::OnMinimize() {

	SDL_Log("app minimized");

	lastPause = SDL_GetTicks();
	appMinimized = true;
	SDL_Log("AppStateGame appMinimized: %d", appMinimized);
	onPause = true;
	interval = 0;
	CAppStateManager::SetActiveAppState(APPSTATE_PAUSE);

}

void CAppStateGame::OnRestore() {

	appMinimized = false;
	onPause = false;
	SDL_Log("app restored");
	//int timeTEMP= SDL_GetTicks() - lastPause;
	//CFPS::FPSControl.SetOldTime(timeTEMP);
		
}

/*
bool CAppStateGame::SetOnPause(bool pause) {

	onPause = pause;

}

bool CAppStateGame::GetOnPause() {

	return onPause;

}
*/

void CAppStateGame::SwitchPlayerFiremode(int fm) {

	Player->setFireMode(CPlayer::FireMode(fm));

}

int CAppStateGame::CountEnemy() {

    EnemyAlive = 0;
    for (Uint32 i = 0; i < CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i]) continue;
        if (CEntity::EntityList[i]->Type == ENTITY_TYPE_GENERIC || CEntity::EntityList[i]->Type == ENTITY_TYPE_ENEMY)
        {
            EnemyAlive++;
        }
    }

    //SDL_Log("CountEnemy %d", EnemyAlive);
    return EnemyAlive;

}

void CAppStateGame::showADS() {

    SDL_Log("showADS()");

    // Your Android AdMob app ID.
    const char* kAdMobAppID = "ca-app-pub-4619763349706955~3272015465";
    //const char* kAdMobAppID = "ca-app-pub-3940256099942544~3347511713";

    //const char* kBannerAdUnit = "ca-app-pub-3940256099942544/1033173712";
    const char* kInterstitialAdUnit = "ca-app-pub-3940256099942544/1033173712";
    //const char* kInterstitialAdUnit = "ca-app-pub-3940256099942544/8691691433";


    env = GetEnv();
    activity = GetActivity();

    //CheckJNIException();

    //---- INIT FIREBASE ADMOB ----

    jclass clazz(GetEnv()->GetObjectClass(GetActivity()));


    SDL_Log("firebase::app::Create()");
    firebase::App* app;
    app = firebase::App::Create(env, activity);

    // find the Java class of the activity. It should be SDLActivity or a subclass of it.

    SDL_Log("Created the Firebase App %x.", static_cast<int>(reinterpret_cast<intptr_t>(app)));

    // Initialize the AdMob library with your AdMob app ID.
    SDL_Log("firebase::Admob::Initialize()");
    firebase::admob::Initialize(*app, kAdMobAppID);



    // If the app is aware of the user's gender, it can be added to the
    // targeting information. Otherwise, "unknown" should be used.
    firebase::admob::AdRequest my_ad_request = {};

    my_ad_request.gender = firebase::admob::kGenderUnknown;

    // The user's birthday, if known. Note that months are indexed from one.
    my_ad_request.birthday_day = 30;
    my_ad_request.birthday_month = 10;
    my_ad_request.birthday_year = 1980;

    // Additional keywords to be used in targeting.
    static const char* kKeywords[] = {"AdMob", "C++", "Fun"};
    my_ad_request.keyword_count = sizeof(kKeywords) / sizeof(kKeywords[0]);
    my_ad_request.keywords = kKeywords;

    // "Extra" key value pairs can be added to the request as well.
    static const firebase::admob::KeyValuePair kRequestExtras[] = {{"the_name_of_an_extra", "the_value_for_that_extra"}};
    my_ad_request.extras_count = sizeof(kRequestExtras) / sizeof(kRequestExtras[0]);
    my_ad_request.extras = kRequestExtras;

    // Register the device IDs associated with any devices that will be used to
    // test your app. Below are sample test device IDs used for making the ad request.
    static const char* kTestDeviceIDs[] = {"AC155169C72F797E7DE8F1D51A847D8D","TEST_EMULATOR"};
    my_ad_request.test_device_id_count = sizeof(kTestDeviceIDs) / sizeof(kTestDeviceIDs[0]);
    my_ad_request.test_device_ids = kTestDeviceIDs;


    SDL_Log("new interstitial");

    namespace admob = ::firebase::admob;

    firebase::admob::InterstitialAd* interstitial_ad = new firebase::admob::InterstitialAd();

    SDL_Log("interstitial initialize");
    interstitial_ad->Initialize(static_cast<firebase::admob::AdParent>(GetActivity()), kInterstitialAdUnit);

    // Set the listener.
    //LoggingInterstitialAdListener interstitial_listener;
    //interstitial_ad->SetListener(&interstitial_listener);

    SDL_Log("Loading Interstitial...");
    if (interstitial_ad->InitializeLastResult().status() ==
        ::firebase::kFutureStatusComplete &&
            interstitial_ad->InitializeLastResult().error() ==
        firebase::admob::kAdMobErrorNone) {
        interstitial_ad->LoadAd(my_ad_request);
    }

    if (interstitial_ad->LoadAdLastResult().status() ==
        ::firebase::kFutureStatusComplete &&
        interstitial_ad->LoadAdLastResult().error() ==
        firebase::admob::kAdMobErrorNone) {
        interstitial_ad->Show();
    }


    /*
    firebase::admob::BannerView* banner_view;
    banner_view = new firebase::admob::BannerView();
    const char* kBannerAdUnit = "ca-app-pub-3940256099942544/6300978111";


    firebase::admob::AdSize ad_size;
    ad_size.ad_size_type = firebase::admob::kAdSizeStandard;
    ad_size.width = 320;
    ad_size.height = 50;
    // my_ad_parent is a reference to an iOS UIView or an Android Activity.
    // This is the parent UIView or Activity of the banner view.
    //banner_view->Initialize(static_cast<firebase::admob::AdParent>(GetActivity()), kBannerAdUnit, ad_size);
    */


    SDL_Log("showADS() completed");




}





/*
bool CAppStateGame::ProcessEvents(int msec) {

    struct android_poll_source* source = nullptr;
    int events;
    int looperId = ALooper_pollAll(msec, nullptr, &events, reinterpret_cast<void**>(&source));
    if (looperId >= 0 && source)
    {
        source->process(g_app_state, source);
    }
    return g_destroy_requested | g_restarted;

}



void CAppStateGame::WaitForFutureCompletion(firebase::FutureBase future) {

    while (!ProcessEvents(1000))
    {
        if (future.status() != firebase::kFutureStatusPending)
        {
            break;
        }
    }


    if (future.error() != firebase::admob::kAdMobErrorNone)
    {
        SDL_Log("ERROR: Action failed with error code %d and message %s - $s", future.error(), future.error_message());
    }
}
*/


/*
void CAppStateGame::CheckJNIException() {

    JNIEnv* env = GetEnv();
    if (env->ExceptionCheck()) {
        // Get the exception text.
        jthrowable exception = env->ExceptionOccurred();
        env->ExceptionClear();

        // Convert the exception to a string.
        jclass object_class = env->FindClass("java/lang/Object");
        jmethodID toString =
                env->GetMethodID(object_class, "toString", "()Ljava/lang/String;");
        jstring s = (jstring)env->CallObjectMethod(exception, toString);
        const char* exception_text = env->GetStringUTFChars(s, nullptr);

        // Log the exception text.
        __android_log_print(ANDROID_LOG_INFO, "SDL_main",
                            "-------------------JNI exception:");
        __android_log_print(ANDROID_LOG_INFO, "SDL_main", "%s",
                            exception_text);
        __android_log_print(ANDROID_LOG_INFO, "SDL_main",
                            "-------------------");

        // Also, assert fail.
        assert(false);

        // In the event we didn't assert fail, clean up.
        env->ReleaseStringUTFChars(s, exception_text);
        env->DeleteLocalRef(s);
        env->DeleteLocalRef(exception);
    }
}
 */

void CAppStateGame::Call_Interstitial() {

    SDL_Log("call_Interstitial()");
    interstitialEvent = true;

    env = GetEnv();
    activity = GetActivity();

    jclass cls = env->GetObjectClass(activity);
    //cls = env->FindClass("SDLActivity");

    SDL_Log("step1");
    jmethodID mid = env->GetStaticMethodID(cls, "getContext", "()Landroid/content/Context;");
    if (mid == nullptr)
    {
        SDL_Log("error getting getContext");
        return;
    }


    /*
    SDL_Log("step2");
    jobject context = env->CallObjectMethod(cls, mid);
    if (context == nullptr)
    {
        SDL_Log("error calling getContext");
        return;
    }
    */

    JNIEnv* _env = env;
    SDL_Log("step3");
    jclass _cls = reinterpret_cast<jclass>(_env->NewGlobalRef(cls));

    SDL_Log("step4");
    jmethodID showFullscreenAds = _env->GetStaticMethodID(_cls, "showFullscreenAds", "()V");

    /*
    jobject context = env->CallStaticObjectMethod(_cls, showFullscreenAds);
    if (context == nullptr) {
        SDL_Log("error calling getContext");
        return;
    }
    */

    SDL_Log("step5");
    _env->CallStaticVoidMethod(_cls, showFullscreenAds);

    if(env->ExceptionCheck())
    {
        env->ExceptionDescribe(); // writes to logcat
        env->ExceptionClear();
    }

    _env->DeleteGlobalRef(_cls);

    SDL_Log("end CallInterstital()");

    //SDL_Delay(5000);

}

void CAppStateGame::LotteryEvents(CEntity* Entity) {

    const double start = 1;
    const double stop = 100;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(start, std::nextafter(stop, DBL_MAX));

    int winnerNumber = (int)dist(mt);
    int tempMedal = 0;
    SDL_Log("Medal Event %d", winnerNumber);

    if (winnerNumber >= 1 && winnerNumber <= 50) {

        float x = Entity->EnemyGetX() + Entity->Width / 2;
        float y = Entity->EnemyGetY() + Entity->Height / 2;


        switch (Entity->Size)
        {
            case ENTITY_SIZE_SX: {
                float r = 15;
                MedalHonor = new CMedal(x, y, 1, r, "powerup_02", ENTITY_FLAG_ENEMY_S, BEZIER);

                MedalHonor->entityTexture = "Icon3";
                MedalHonor->Width = (100 * OVERALL_RATIO);
                MedalHonor->Height = (100 * OVERALL_RATIO);
                MedalHonor->OnInit();

                CEntity::EntityList.push_back(MedalHonor);
            }
                break;

            case ENTITY_SIZE_SSX:
                break;

            case ENTITY_SIZE_MM: {
                float r = 35;
                MedalHonor = new CMedal(x, y, 0, r, "powerup_01", ENTITY_FLAG_ENEMY_M1, BEZIER);

                MedalHonor->entityTexture = "Icon1";
                MedalHonor->Width = 100 * OVERALL_RATIO;
                MedalHonor->Height = 100 * OVERALL_RATIO;
                MedalHonor->OnInit();

                CEntity::EntityList.push_back(MedalHonor);
            }
                break;
            default:
                break;
        }
    }


}
