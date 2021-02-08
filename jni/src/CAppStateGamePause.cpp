#include "CAppStateGamePause.h"
#include "CAppStateManager.h"
#include "CAppStateGame.h"
#include "CAppStateIntro.h"
#include "CPlayer.h"

#include "CApp.h"
#include "CMenu.h"

#include <iostream>

#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

CAppStateGamePause CAppStateGamePause::Instance;

std::vector<CMenu*> CAppStateGamePause::vectorMenu;

//int CAppStateGame::lastPause = 0;



bool CAppStateGamePause::onPause = true;
bool CAppStateGamePause::mainP = true;
bool CAppStateGamePause::videoP = false;
bool CAppStateGamePause::soundP = false;
bool CAppStateGamePause::back = false;
bool CAppStateGamePause::isRunning = false;
bool CAppStateGamePause::menuTrans = false;
bool CAppStateGamePause::explorer = false;

int CAppStateGamePause::newMenu = MAIN;
int CAppStateGamePause::queueID = 0;



CAppStateGamePause::CAppStateGamePause() {

	SDL_Log("CAppStateGamePause()");

}

void CAppStateGamePause::OnActivate() {

	SDL_Log("start APPSTATE_PAUSE OnActivate()");

	onPause = true;
	//SDL_Log("AppStatePause onPause = true\n");
	DELAY = 50;
	interval = 0;
	StartTime = SDL_GetTicks();

	alpha = 255;
	SDL_ShowCursor(1);

	Window = CAppStateIntro::GetInstance()->GetWindow();
	Renderer = CAppStateIntro::GetInstance()->GetRenderer();
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);

	Width = 1024;
	Height = 768;

	X = Y = 0;

	TextureName1 = "Splash_pausex1024";
	TextureName2 = "Splash_Resume";





	if (CAppStateGame::GetInstance()->onPause)
	{
		SDL_Log("AppStatePause App OnPause: loading Resume Button");
		createResumeP();
		setActiveMenu(MAIN);
	}
	else if (CAppStateGame::GetInstance()->appMinimized)
	{
		SDL_Log("AppStatePause appMinimized");
		createResumeP();
		setActiveMenu(MAIN);
	}

	else if (!CAppStateGame::GetInstance()->levelCompleted)
	{
	    if (CAppStateGame::nextState)
        {
	        SDL_Log("Player Dead >> create game over splash screen");

	        createLevelGameOver();
        }
        else {
            SDL_Log("AppStatePause level completed: create MainP");
            createMainP();
            //createLevelCompleted();
            setActiveMenu(MAIN);
        }
	}
	else if (CAppStateGame::GetInstance()->levelCompleted)
	{
		SDL_Log("AppStatePause next level: create MissionP");
		createLevelCompleted();
	}

	
    SDL_Log("Player score: %d", CPlayer::PlayerStat.PlayerScore);
    SDL_Log("Player honor: %d", CPlayer::PlayerStat.PlayerHonor);
    SDL_Log("Player starSX: %d", CPlayer::PlayerStat.starSX);
    SDL_Log("Player starMM: %d", CPlayer::PlayerStat.starMM);
    SDL_Log("Player starM1: %d", CPlayer::PlayerStat.starM1);
    SDL_Log("Player starBB: %d", CPlayer::PlayerStat.starBB);


}

void CAppStateGamePause::OnDeactivate() {

	SDL_Log("end APPSTATE_PAUSE");
	
	freeMenu();
	
	SDL_ShowCursor(0);

				

}


void CAppStateGamePause::OnMinimize() {

	SDL_Log("AppStatePause: OnMinimize()");

	StartTime = SDL_GetTicks();
	//CAppStateGame::GetInstance()->appMinimized = true;
	//SDL_Log("AppStateGame appMinimized: %d", appMinimized);
	onPause = true;
	
}


void CAppStateGamePause::OnRestore() {

	SDL_Log("AppStatePause: OnRestore()");

	if (!onPause)
	{
		LastTime = LastTime - StartTime;
		//std::cout << "OnPausa before lastPause: " << CAppStateGame::lastPause << std::endl;
		CAppStateGame::GetInstance()->lastPause += LastTime;
		//std::cout << "OnPausa LastTime: " << LastTime << " - lastPause: " << CAppStateGame::lastPause << std::endl;
		CAppStateGame::GetInstance()->appMinimized = false;
		//SDL_Delay(200);
		//CAppStateGame::GetInstance()->onPause = false;
        //SDL_Log("in Pause - onReset = %d", CAppStateGame::GetInstance()->onReset);
		CAppStateManager::SetActiveAppState(APPSTATE_GAME);
	}
	

}

void CAppStateGamePause::OnReset() {

	CAppStateGame::GetInstance()->onReset = true;
	SDL_Delay(200);
	CAppStateManager::SetActiveAppState(APPSTATE_GAME);


}

void CAppStateGamePause::setActiveMenu(stateMenu e)
{
	newMenu = e;
}



void CAppStateGamePause::OnLoop() {

	
	/*
    interval++;

    if (alpha > 0) alpha -= 1;
    else if (alpha <= 0) alpha = 255;
	*/

    LastTime = SDL_GetTicks();

	

	for (std::vector<CMenu*>::iterator it = vectorMenu.begin(); it != vectorMenu.end(); ++it)
	{
		(*it)->onLoop();
	}

	
	if (!onPause)
	{
		LastTime = LastTime - StartTime;
		//std::cout << "OnPausa before lastPause: " << CAppStateGame::lastPause << std::endl;
		CAppStateGame::GetInstance()->lastPause += LastTime;
		//std::cout << "OnPausa LastTime: " << LastTime << " - lastPause: " << CAppStateGame::lastPause << std::endl;
		//SDL_Delay(200);
		//CAppStateGame::GetInstance()->appMinimized = false;
		//CAppStateManager::SetActiveAppState(APPSTATE_GAME);
	}
	
	
	// Listening menu active requested
	if (menuTrans)
	{

		freeMenu();
		switch (newMenu)
		{
		case MAIN:
			createMainP();
			break;

		case NEWGAME:
			//CAppStateGame::GetInstance()->Call_Interstitial();
			CAppStateManager::SetActiveAppState(APPSTATE_GAME);
			break;

		case SHIP:
			createHANGAR();
			break;

		case PLAY:
			createEXPLORER();
			break;

        case COMPLETED:
            createLevelCompleted();
            break;

        case GAME_OVER:
			createLevelGameOver();
            break;

		case MISSION:
			createMissionP();
			break;
        /*
		case NEXT:
			createNextP();
			break;
        */
		case RESUME:
			createResumeP();
			break;

		case OPTION:
			createOptP();
			break;

		case VIDEO:
			break;

		case SOUND:
			createSoundP();
			break;

		case BACK:
			if (queueID == 1)
			{
				createMainP();
			}
			else if (queueID == 2)
			{
				createOptP();
			}
			else if (queueID == 3)
			{
				createEXPLORER();
			}
			break;

		case EXIT:
			CAppStateManager::SetActiveAppState(APPSTATE_CREDITS);
			break;
		
		default:
			createMainP();
			break;

		}
		
		
		menuTrans = false;
		//if (newMenu != BACK) oldMenu = newMenu; 
		//CApp::Logger.OnLog(__FILE__, __LINE__, "oldMenu ", Stringify::Int(menuQueue[queueID - 1]));
	}

	

}

void CAppStateGamePause::OnRender() {

    SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);

    if(Renderer) SDL_RenderClear(Renderer);

	for (Uint32 i = 0; i < vectorMenu.size(); i++)
	{
		if (!vectorMenu[i])
		{
			SDL_Log("StateGamePause Renderer NULL");
			continue;
		}
		vectorMenu[i]->onRender();
	}

	

	if (Renderer) SDL_RenderPresent(Renderer);

}

//-----------------------------------------------------------------------------

void CAppStateGamePause::OnKeyDown(SDL_Keysym sym) {
	/*
    switch(sym.sym)
	{
        case SDLK_p: {
            if (interval > DELAY)
            {
				isRunning = true;
                LastTime = LastTime - StartTime;
                //std::cout<<"OnPausa before lastPause: "<<CAppStateGame::lastPause<<std::endl;
                CAppStateGame::lastPause += LastTime;
                //std::cout<<"OnPausa LastTime: "<<LastTime<<" - lastPause: "<<CAppStateGame::lastPause<<std::endl;
                CAppStateManager::SetActiveAppState(APPSTATE_GAME);
                interval = 0;
            }
            break;
        }

        case SDLK_ESCAPE: {
			isRunning = true;
            CAppStateManager::SetActiveAppState(APPSTATE_GAME);
            break;
        }

        default: {}
	}
	*/
}


//-----------------------------------------------------------------------------
void CAppStateGamePause::OnKeyUp(SDL_Keysym sym) {

	/*
    switch(sym.sym) {

		// do nothing

        default: {
        }
    }
	*/

}



void CAppStateGamePause::OnTouchedDown(float tX, float tY)
{
	//SDL_Log("StateGamePause::OnTouchedDown\n");
	
	SDL_Event e;
	SDL_PollEvent(&e);
	e.type = SDL_FINGERDOWN;
	e.tfinger.x = tX;
	e.tfinger.y = tY;

	float tXw = (float)tX * (float)WWIDTH;
	float tYh = (float)tY * (float)WHEIGHT;
	//LOGD("OnTouchedDown tfinger: (%1.4f, %1.4f)", tX, tY);
	//SDL_Log("OnTouchedDown tfinger : %1.4f, %1.4f", tX, tY);
	//SDL_Log("OnTouchedDown X - Y: %d - %d", tXw, tYh);
	//LOGD("OnTouchedUp WWIDTH&WHEIGHT: %d x %d", WWIDTH, WHEIGHT);
	
	for (auto event : vectorMenu)
	{
		event->handleEvent(&e);
	}
	
}



void CAppStateGamePause::OnTouchedUp(float tX, float tY)
{
	//SDL_Log("StateGamePause::OnTouchedUp\n");

	
	SDL_Event e;
	SDL_PollEvent(&e);
	e.type = SDL_FINGERUP;
	e.tfinger.x = tX;
	e.tfinger.y = tY;

	int tXw = tX * WWIDTH;
	int tYh = tY * WHEIGHT;
	
	
	for (auto event : vectorMenu)
	{
        if (event)
		event->handleEvent(&e);
	}
	
}



void CAppStateGamePause::OnTouchedMove(float tX, float tY, float dX, float dY)
{
	//SDL_Log("StateGamePause::OnTouchedMove\n");
	
	SDL_Event e;
	SDL_PollEvent(&e);


	e.type = SDL_FINGERMOTION;
	e.tfinger.x = tX;
	e.tfinger.y = tY;
	e.tfinger.dx = dX;
	e.tfinger.dy = dY;

	//int tXw = tX * WWIDTH;
	//int tYh = tY * WHEIGHT;
	//int dXw = dX * WWIDTH;
	//int dYh = dY * WHEIGHT;
	//LOGD("OnTouchedMove X - Y: %d - %d", tXw, tYh);

	for (auto event : vectorMenu)
	{
		event->handleEvent(&e);
	}
	
}


void CAppStateGamePause::freeMenu()
{

	for (std::vector<CMenu*>::iterator it = vectorMenu.begin(); it != vectorMenu.end(); ++it)
	{
		if (!(*it)) continue;
		(*it)->onDelete();
		(*it) = NULL;
	}

	vectorMenu.clear();
	SDL_Log("menu items deleted, vectorMenu size: %d", vectorMenu.size());

}


/* create the main menu buttons set */
void CAppStateGamePause::createMainP()
{

	SDL_Log("CreateMainP()");
	/* Panel Background */
		//createBACKGROUND();

    BACKGROUND = CMenuFactory::getFactory()->CreateMenu("background");
    BACKGROUND->displayButton = false;
    BACKGROUND->init();
    vectorMenu.push_back(BACKGROUND);
	
	/* Button Play */
		SDL_Log("create button play");
		Play = CMenuFactory::getFactory()->CreateMenu("play");
		Play->init();
		vectorMenu.push_back(Play);
	
	/* Button Ship */
		SDL_Log("create buttone SHIP");
		MotherShip = CMenuFactory::getFactory()->CreateMenu("ship");
		MotherShip->init();
		vectorMenu.push_back(MotherShip);

	/* Button Options */
		SDL_Log("create button options");
		Option = CMenuFactory::getFactory()->CreateMenu("option");
		if (Option == NULL)
		{
			CApp::Logger.OnLog(__FILE__, __LINE__, "Errore creating Option", "");
		}
		else
		{
			Option->init();
			vectorMenu.push_back(Option);
			CApp::Logger.OnLog(__FILE__, __LINE__, "Option created", "");
		}


	/* Button Exit */
		SDL_Log("create button exit\n");
		Exit = CMenuFactory::getFactory()->CreateMenu("exit");
		Exit->init();
		vectorMenu.push_back(Exit);
				
		queueID = 0;

		SDL_Event sdlevent;
		sdlevent.type = SDL_FINGERDOWN;

		SDL_PushEvent(&sdlevent);


}

/* remove the main menu buttons set */
void CAppStateGamePause::removeMainP()
{

	if (Option)
	{
		Option->onDelete();
		Option = NULL;
	}

	if (Play)
	{
		Play->onDelete();
		Play = NULL;
	}

	if (MotherShip)
	{
		MotherShip->onDelete();
		MotherShip = NULL;
	}

	if (Exit)
	{
		Exit->onDelete();
		Exit = NULL;
	}

	removeBACKGROUND();

	vectorMenu.clear();
	
}


/* create the next menu buttons set */
void CAppStateGamePause::createNextP()
{
	
	/* Panel Background */
	createBACKGROUND();

	/* Button Next */
	SDL_Log("create button next");
	Next = CMenuFactory::getFactory()->CreateMenu("next");
	Next->init();
	vectorMenu.push_back(Next);
	
	queueID = 0;

	//CAppStateGamePause::onPause = false;

}

/* remove the next menu buttons set */
void CAppStateGamePause::removeNextP()
{
	SDL_Log("create button next");
	
	if (Next)
	{
		Next->onDelete();
		Next = NULL;
	}

	removeBACKGROUND();
	
	vectorMenu.clear();

}

void CAppStateGamePause::createResumeP()
{

	/* Panel Background */
	SDL_Log("createResumeP()");

	/* Background */
	BACKGROUND = CMenuFactory::getFactory()->CreateMenu("background");
	BACKGROUND->init2();
	vectorMenu.push_back(BACKGROUND);


	/* Button Resume */
	//SDL_Log("create button resume");
	Resume = CMenuFactory::getFactory()->CreateMenu("resume");
	//if (CAppStateGame::GetInstance()->interstitialEvent)
    	//Resume->init2();
    //else
    Resume->init();
	vectorMenu.push_back(Resume);

    /* Button Next */
    //SDL_Log("create button next");
	if (!CAppStateGame::GetInstance()->interstitialEvent)
	{
        Next = CMenuFactory::getFactory()->CreateMenu("next");
        Next->init();
        vectorMenu.push_back(Next);


        /* Button Exit-to-Menu */
        //SDL_Log("create button exit");
        Exit = CMenuFactory::getFactory()->CreateMenu("exit");
        Exit->init2();
        vectorMenu.push_back(Exit);
    }

	queueID = 0;
}

void CAppStateGamePause::removeResumeP()
{

    if (Exit)
    {
        Exit->onDelete();
        Exit = NULL;
    }
    if (Next)
    {
        Next->onDelete();
        Next = NULL;
    }
	if (Resume)
	{
		Resume->onDelete();
		Resume = NULL;
	}

	removeBACKGROUND();

	vectorMenu.clear();

}

/* create the options panel buttons set */
void CAppStateGamePause::createOptP()
{

	//createBACKGROUND();
	BACKGROUND2 = CMenuFactory::getFactory()->CreateMenu("background2");
	BACKGROUND2->init();
	vectorMenu.push_back(BACKGROUND2);

    SDL_Log("create sound items set");
    /*
    ButtonVolSX = CMenuFactory::getFactory()->CreateMenu("volumesx");
    ButtonVolSX->init();
    vectorMenu.push_back(ButtonVolSX);

    SoundBar = CMenuFactory::getFactory()->CreateMenu("soundbar");
    SoundBar->init();
    vectorMenu.push_back(SoundBar);

    ButtonVolDX = CMenuFactory::getFactory()->CreateMenu("volumedx");
    ButtonVolDX->init();
    vectorMenu.push_back(ButtonVolDX);
    */


	queueID = 1;
}

/* Remove the options panel buttons set */
void CAppStateGamePause::removeOptP()
{
	if (Video)
	{
		Video->onDelete();
		Video = NULL;
	}

	if (Sound)
	{
		Sound->onDelete();
		Sound = NULL;
	}

	if (Return)
	{
		Return->onDelete();
		Return = NULL;
	}

	if (BACKGROUND2)
	{
		BACKGROUND2->onDelete();
		BACKGROUND2 = NULL;
	}

	vectorMenu.clear();

}

void CAppStateGamePause::createPauseP() {

	SDL_Log("create PauseP button");
	createResumeP();

	/*
	SDL_Log("create PauseP VIDEO items set\n");
	Video = CMenuFactory::getFactory()->CreateMenu("video");
	Video->init();
	vectorMenu.push_back(Video);

	SDL_Log("create PAuseP SOUND items set\n");
	Sound = CMenuFactory::getFactory()->CreateMenu("sound");
	Sound->init();
	vectorMenu.push_back(Sound);
	*/

	queueID = 0;
	
}


void CAppStateGamePause::createLevelCompleted() {


	SDL_Log("CreateLevelCompleted()");

	BACKGROUND2 = CMenuFactory::getFactory()->CreateMenu("background2");
    BACKGROUND2->init2();
    vectorMenu.push_back(BACKGROUND2);


	Debrief = CMenuFactory::getFactory()->CreateMenu("debrief");
	Debrief->init();
	vectorMenu.push_back(Debrief);



    Play = CMenuFactory::getFactory()->CreateMenu("play");
    Play->init2();
    vectorMenu.push_back(Play);

    SDL_Event sdlevent;
    sdlevent.type = SDL_FINGERDOWN;

    SDL_PushEvent(&sdlevent);


    queueID = 1;

}



void CAppStateGamePause::removeLevelCompleted() {

    if (Play)
    {
        Play->onDelete();
        Play = NULL;
    }

    if (Debrief)
    {
        Debrief->onDelete();
        Debrief = NULL;
    }

	if (BACKGROUND2)
	{
		BACKGROUND2->onDelete();
		BACKGROUND2 = NULL;
	}

	vectorMenu.clear();


}

void CAppStateGamePause::createLevelGameOver() {

	SDL_Log("createLevelGameOver()");

	/* Background */
	BACKGROUND = CMenuFactory::getFactory()->CreateMenu("background2");

	vectorMenu.push_back(BACKGROUND);

    Next = CMenuFactory::getFactory()->CreateMenu("next");
    //if (CAppStateGame::GetInstance()->interstitialEvent)
    //Resume->init2();
    //else
    Next->init2();
    vectorMenu.push_back(Next);


	/* Button Next */
	//SDL_Log("create button next");
	/*
	if (!CAppStateGame::GetInstance()->interstitialEvent)
	{
		Next = CMenuFactory::getFactory()->CreateMenu("next");
		Next->init();
		vectorMenu.push_back(Next);


		/* Button Exit-to-Menu */
		//SDL_Log("create button exit");
		/*
		Exit = CMenuFactory::getFactory()->CreateMenu("exit");
		Exit->init2();
		vectorMenu.push_back(Exit);
	}
	*/


	queueID = 1;


}

void CAppStateGamePause::removeLevelGameOver() {

	if (Next)
	{
        Next->onDelete();
        Next = NULL;
	}

	removeBACKGROUND();

	vectorMenu.clear();

}



void CAppStateGamePause::removePauseP() {

	removeResumeP();

	if (Video)
	{
		Video->onDelete();
		Video = NULL;
	}

	if (Sound)
	{
		Sound->onDelete();
		Sound = NULL;
	}
	
}


/* create the sound panel buttons set */
void CAppStateGamePause::createSoundP()
{

	/* Background */
	createBACKGROUND();

	SDL_Log("create sound items set");

	ButtonVolSX = CMenuFactory::getFactory()->CreateMenu("volumesx");
	ButtonVolSX->init();
	vectorMenu.push_back(ButtonVolSX);
	
	SoundBar = CMenuFactory::getFactory()->CreateMenu("soundbar");
	SoundBar->init();
	vectorMenu.push_back(SoundBar);

	ButtonVolDX = CMenuFactory::getFactory()->CreateMenu("volumedx");
	ButtonVolDX->init();
	vectorMenu.push_back(ButtonVolDX);

	Return = CMenuFactory::getFactory()->CreateMenu("return");
	Return->init();
	vectorMenu.push_back(Return);

	queueID = 2;

}


/* Remove the sound panel buttons set */
void CAppStateGamePause::removeSoundP()
{
	if (ButtonVolSX)
	{
		ButtonVolSX->onDelete();
		ButtonVolSX = NULL;
	}

	if (ButtonVolDX)
	{
		ButtonVolDX->onDelete();
		ButtonVolDX = NULL;
	}

	if (SoundBar)
	{
		SoundBar->onDelete();
		SoundBar = NULL;
	}

	if (Return)
	{
		Return->onDelete();
		Return = NULL;
	}

	removeBACKGROUND();

	vectorMenu.clear();

	
}

void CAppStateGamePause::createBACKGROUND() {

	SDL_Log("createBACKGROUND()");

	/* Background */
	BACKGROUND = CMenuFactory::getFactory()->CreateMenu("background");
	BACKGROUND->init();
    vectorMenu.push_back(BACKGROUND);
}


void CAppStateGamePause::removeBACKGROUND() {

	if (BACKGROUND)
	{
		BACKGROUND->onDelete();
		delete BACKGROUND;
		BACKGROUND = NULL;
	}

	vectorMenu.clear();

}

void CAppStateGamePause::createHANGAR() {

	SDL_Log("createHangar()");

	HANGAR = CMenuFactory::getFactory()->CreateMenu("hangar");
    HANGAR->init();
    vectorMenu.push_back(HANGAR);


    ShipA = CMenuFactory::getFactory()->CreateMenu("shipA");
	ShipA->init();
	vectorMenu.push_back(ShipA);

	ShipB = CMenuFactory::getFactory()->CreateMenu("shipB");
	ShipB->init();
	vectorMenu.push_back(ShipB);

	ShipC = CMenuFactory::getFactory()->CreateMenu("shipC");
	ShipC->init();
	vectorMenu.push_back(ShipC);

    ShipX = CMenuFactory::getFactory()->CreateMenu("shipX");
    if (CAppStateIntro::GetInstance()->MySpaceship[3])
    {
        ShipX->init();
    }
    else
    {
        ShipX->init2();
    }


    vectorMenu.push_back(ShipX);

    BACKGROUND = CMenuFactory::getFactory()->CreateMenu("background");
    vectorMenu.push_back(BACKGROUND);

	/*
    Return = CMenuFactory::getFactory()->CreateMenu("return");
    Return->init();
    vectorMenu.push_back(Return);
	*/

	SDL_Event sdlevent;
	sdlevent.type = SDL_FINGERDOWN;

	SDL_PushEvent(&sdlevent);

	queueID = 1;

}


void CAppStateGamePause::removeHANGAR() {


	removeBACKGROUND();

	if (Return)
	{
		Return->onDelete();
		delete Return;
		Return = NULL;
	}

	if (ShipA)
	{
		ShipA->onDelete();
		delete ShipA;
		ShipA = NULL;
	}

	if (ShipB)
	{
		ShipB->onDelete();
		delete ShipB;
		ShipB = NULL;
	}

	if (ShipC)
	{
		ShipC->onDelete();
		delete ShipC;
		ShipC = NULL;
	}

    if (ShipX)
    {
        ShipX->onDelete();
        delete ShipX;
        ShipX = NULL;
    }

	if (HANGAR)
	{
		HANGAR->onDelete();
		delete HANGAR;
		HANGAR = NULL;
	}

	vectorMenu.clear();

}

void CAppStateGamePause::createEXPLORER() {

	SDL_Log("createEXPLORER()");

	/* Explorer */
	//SDL_Log("create galaxy explorer");
		
	Explorer = CMenuFactory::getFactory()->CreateMenu("explorer");
	Explorer->init();
	vectorMenu.push_back(Explorer);
	
	//SDL_Log("create Level0 tag Explorer");
	/*
	Level0 = CMenuFactory::getFactory()->CreateMenu("level0");
	Level0->init();
	vectorMenu.push_back(Level0);
    */
	Level1 = CMenuFactory::getFactory()->CreateMenu("level1");
	if (!CAppStateIntro::GetInstance()->stage_complete[1])
    {
        SDL_Log("false stage_complete[0]=[%d]", CAppStateIntro::GetInstance()->stage_complete[1]);
	    Level1->init();
    }
	else
    {
        SDL_Log("true stage_complete[0]=[%d]", CAppStateIntro::GetInstance()->stage_complete[1]);
	    Level1->init2();
    }
	vectorMenu.push_back(Level1);

    Level2 = CMenuFactory::getFactory()->CreateMenu("level2");
    if (!CAppStateIntro::GetInstance()->stage_complete[2]) Level2->init();
    else Level2->init2();
    vectorMenu.push_back(Level2);

    Level3 = CMenuFactory::getFactory()->CreateMenu("level3");
    if (!CAppStateIntro::GetInstance()->stage_complete[3]) Level3->init();
    else Level3->init2();
    vectorMenu.push_back(Level3);

    Level4 = CMenuFactory::getFactory()->CreateMenu("level4");
    if (!CAppStateIntro::GetInstance()->stage_complete[4]) Level4->init();
    else Level4->init2();
    vectorMenu.push_back(Level4);

	LevelX = CMenuFactory::getFactory()->CreateMenu("levelX");
	if(CAppStateIntro::GetInstance()->GetFinalMission()) LevelX->init();
	else LevelX->init2();
	vectorMenu.push_back(LevelX);

	/*
	Return = CMenuFactory::getFactory()->CreateMenu("return");
	Return->init2();
	vectorMenu.push_back(Return);
    */

    BACKGROUND = CMenuFactory::getFactory()->CreateMenu("background");
    vectorMenu.push_back(BACKGROUND);

	queueID = 1;
	
	SDL_Event sdlevent;
	sdlevent.type = SDL_FINGERDOWN;

	SDL_PushEvent(&sdlevent);


}

void CAppStateGamePause::removeEXPLORER() {

	
	if (Return)
	{
		Return->onDelete();
		delete Return;
		Return = NULL;
	}
	
	if (Level1)
	{
		Level1->onDelete();
		delete Level1;
		Level1 = NULL;
	}

    if (Level2)
    {
        Level2->onDelete();
        delete Level2;
        Level2 = NULL;
    }

    if (Level3)
    {
        Level3->onDelete();
        delete Level3;
        Level3 = NULL;
    }

    if (Level4)
    {
        Level4->onDelete();
        delete Level4;
        Level4 = NULL;
    }

	if (LevelX)
	{
		LevelX->onDelete();
		delete LevelX;
		LevelX = NULL;
	}

	if (Explorer)
	{
		Explorer->onDelete();
		delete Explorer;
		Explorer = NULL;
	}

	removeBACKGROUND();

	vectorMenu.clear();

}


void CAppStateGamePause::createMissionP() {

	SDL_Log("createMissionP()");

	//CAppStateGame::GetInstance()->interstitialEvent = true;


	//createBACKGROUND();
    BACKGROUND2 = CMenuFactory::getFactory()->CreateMenu("background2");
    BACKGROUND2->init();
    vectorMenu.push_back(BACKGROUND2);

    // Mission0
	Mission0 = CMenuFactory::getFactory()->CreateMenu("mission0");
	if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][0] == true) Mission0->init();
	else Mission0->init2();
	vectorMenu.push_back(Mission0);

	// Mission1
	Mission1 = CMenuFactory::getFactory()->CreateMenu("mission1");
	if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][1] == true) Mission1->init();
	else Mission1->init2();
	vectorMenu.push_back(Mission1);

	// Mission2
	Mission2 = CMenuFactory::getFactory()->CreateMenu("mission2");
	if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][2] == true) Mission2->init();
	else Mission2->init2();
	vectorMenu.push_back(Mission2);

	// Mission3
	Mission3 = CMenuFactory::getFactory()->CreateMenu("mission3");
	if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][3] == true) Mission3->init();
	else Mission3->init2();
	vectorMenu.push_back(Mission3);

	// Mission4
	Mission4 = CMenuFactory::getFactory()->CreateMenu("mission4");
	if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][4] == true) Mission4->init();
	else Mission4->init2();
	vectorMenu.push_back(Mission4);

    // Mission5
    Mission5 = CMenuFactory::getFactory()->CreateMenu("mission5");
    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][5] == true) Mission5->init();
    else Mission5->init2();
    vectorMenu.push_back(Mission5);

    // Mission6
    Mission6 = CMenuFactory::getFactory()->CreateMenu("mission6");
    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][6] == true) Mission6->init();
    else Mission6->init2();
    vectorMenu.push_back(Mission6);

    // Mission7
    Mission7 = CMenuFactory::getFactory()->CreateMenu("mission7");
    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][7] == true) Mission7->init();
    else Mission7->init2();
    vectorMenu.push_back(Mission7);

    // Mission8
    Mission8 = CMenuFactory::getFactory()->CreateMenu("mission8");
    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][8] == true) Mission8->init();
    else Mission8->init2();
    vectorMenu.push_back(Mission8);

    // Mission9
    Mission9 = CMenuFactory::getFactory()->CreateMenu("mission9");
    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][9] == true) Mission9->init();
    else Mission9->init2();
    vectorMenu.push_back(Mission9);

	/*
	Return = CMenuFactory::getFactory()->CreateMenu("return");
	Return->init2();
	Return->buttonID = 3;
	vectorMenu.push_back(Return);
    */

    SDL_Event sdlevent;
    sdlevent.type = SDL_FINGERDOWN;

    SDL_PushEvent(&sdlevent);
	
	queueID = 3;
	
}

void CAppStateGamePause::removeMissionP() {

	if (Mission0)
	{
		Mission0->onDelete();
		delete Mission0;
		Mission0 = NULL;
	}

	if (Mission1)
	{
		Mission1->onDelete();
		delete Mission1;
		Mission1 = NULL;
	}

	if (Mission2)
	{
		Mission2->onDelete();
		delete Mission2;
		Mission2 = NULL;
	}

	if (Mission3)
	{
		Mission3->onDelete();
		delete Mission3;
		Mission3 = NULL;
	}

	if (Mission4)
	{
		Mission4->onDelete();
		delete Mission4;
		Mission4 = NULL;
	}

	if (Mission5)
	{
		Mission5->onDelete();
		delete Mission5;
		Mission5 = NULL;
	}

	if (Mission6)
	{
		Mission6->onDelete();
		delete Mission6;
		Mission6 = NULL;
	}

	if (Mission7)
	{
		Mission7->onDelete();
		delete Mission7;
		Mission7 = NULL;
	}

	if (Mission8)
	{
		Mission8->onDelete();
		delete Mission8;
		Mission8 = NULL;
	}

	if (Mission9)
	{
		Mission9->onDelete();
		delete Mission9;
		Mission9 = NULL;
	}

	if (BACKGROUND2)
	{
		BACKGROUND2->onDelete();
		delete BACKGROUND2;
		BACKGROUND2 = NULL;
	}

	vectorMenu.clear();

}


//-----------------------------------------------------------------------------
CAppStateGamePause* CAppStateGamePause::GetInstance() {

    return &Instance;

}

void CMenu::onLoop()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "CMenu:onLoop() OVERIDE", "");
}

