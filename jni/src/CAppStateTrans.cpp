#include "CAppStateTrans.h"
#include "CAppStateManager.h"
#include "CAppStateGame.h"
#include "CAppStateIntro.h"

#include "CApp.h"
#include "CMenu.h"

#include <iostream>

#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

CAppStateTrans CAppStateTrans::Instance;

std::vector<CMenu*> CAppStateTrans::vectorMenu;

//int CAppStateGame::lastPause = 0;



bool CAppStateTrans::onPause = true;
bool CAppStateTrans::mainP = true;
bool CAppStateTrans::videoP = false;
bool CAppStateTrans::soundP = false;
bool CAppStateTrans::back = false;
bool CAppStateTrans::isRunning = false;
bool CAppStateTrans::menuTrans = false;

int CAppStateTrans::newMenu = MAIN;
int CAppStateTrans::queueID = 0;



CAppStateTrans::CAppStateTrans() {

	SDL_Log("CAppStateTrans()");

}

void CAppStateTrans::OnActivate() {

	SDL_Log("start APPSTATE_PAUSE\n");

		onPause = true;
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


		// initializing main Menu
		createMainP();
		setActiveMenu(MAIN);
		
		//menuQueue[] = { MAIN, OPTION, VIDEO, SOUND };
}

void CAppStateTrans::OnDeactivate() {

	SDL_Log("end APPSTATE_PAUSE\n");
		/*
		if (Menu)
		{
		CApp::Logger.OnLog(__FILE__, __LINE__, "remove Menu", "");
		Menu->onDelete();
		Menu = NULL;
		}
		*/

		/*
		for (std::vector<CMenu*>::iterator it = vectorMenu.begin(); it != vectorMenu.end();)
		{
		if ((*it))
		{
		//(*it)->onDelete();
		//delete *it;
		//it = vectorMenu.erase();
		CApp::Logger.OnLog(__FILE__, __LINE__, "CMenu deleted", "");
		}
		else
		{
		it++;
		}
		}
		
		if (mainP)
		{
			if (Menu)
			{
				Menu->onDelete();
				Menu = NULL;
			}
			if (Play)
			{
				Play->onDelete();
				Play = NULL;
			}
			if (Exit)
			{
				Exit->onDelete();
				Exit = NULL;
			}
		}
		*/
		freeMenu();
		//vectorMenu.clear();

		SDL_ShowCursor(0);
				

}

void CAppStateTrans::setActiveMenu(stateMenu e)
{
	newMenu = e;
}



void CAppStateTrans::OnLoop() {

	

    interval++;

    if (alpha > 0) alpha -= 2;
    else if (alpha <= 0) alpha = 255;

    LastTime = SDL_GetTicks();

	

	for (std::vector<CMenu*>::iterator it = vectorMenu.begin(); it != vectorMenu.end(); ++it)
	{
		(*it)->onLoop();
	}
	if (!onPause)
	{
		LastTime = LastTime - StartTime;
		//std::cout << "OnPausa before lastPause: " << CAppStateGame::lastPause << std::endl;
		CAppStateGame::lastPause += LastTime;
		//std::cout << "OnPausa LastTime: " << LastTime << " - lastPause: " << CAppStateGame::lastPause << std::endl;
		SDL_Delay(200);
		CAppStateManager::SetActiveAppState(APPSTATE_GAME);
	}
	
	
	// Listening menu active requested
	if (menuTrans)
	{
		freeMenu();
		switch (newMenu)
		{
		case MAIN:
			break;

		case NEWGAME:
			break;

		case PLAY:
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
				//stuff missing...
			}
			break;

		case EXIT:
			CAppStateManager::SetActiveAppState(APPSTATE_GAMEOVER);
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

void CAppStateTrans::OnRender() {

    if(Renderer) SDL_RenderClear(Renderer);

	/*
    if (Renderer)
    {
        TextureBank::Get(TextureName1)->Render(X, Y, Width, Height, 255);
		
        TextureBank::Get(TextureName2)->Render(212, 500, 600, 150, 0, 0, 600, 150, alpha);
    }
    else
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "bad Renderer", "");
    }
	*/

	/*
	for (std::vector<CMenu*>::iterator it = vectorMenu.begin(); it != vectorMenu.end(); ++it)
	{
		(*it)->onRender();
	}
	*/


	for (Uint32 i = 0; i < vectorMenu.size(); i++)
	{
		if (!vectorMenu[i])
		{
			SDL_Log("StateGamePause Renderer NULL\n");
			continue;
		}
		vectorMenu[i]->onRender();

	}

	if (Renderer) SDL_RenderPresent(Renderer);


}

//-----------------------------------------------------------------------------

void CAppStateTrans::OnKeyDown(SDL_Keysym sym) {

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
}


//-----------------------------------------------------------------------------
void CAppStateTrans::OnKeyUp(SDL_Keysym sym) {

    switch(sym.sym) {

		// do nothing

        default: {
        }
    }


}



void CAppStateTrans::OnTouchedDown(float tX, float tY)
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



void CAppStateTrans::OnTouchedUp(float tX, float tY)
{
	//SDL_Log("StateGamePause::OnTouchedUp\n");
	
	
	SDL_Event e;
	SDL_PollEvent(&e);
	e.type = SDL_FINGERUP;
	e.tfinger.x = tX;
	e.tfinger.y = tY;

	int tXw = tX * WWIDTH;
	int tYh = tY * WHEIGHT;
	//LOGD("OnTouchedUp X - Y: %d - %d", tXw, tYh);
	
	for (auto event : vectorMenu)
	{
		event->handleEvent(&e);
	}
	
}



void CAppStateTrans::OnTouchedMove(float tX, float tY)
{
	//SDL_Log("StateGamePause::OnTouchedMove\n");
	
	SDL_Event e;
	SDL_PollEvent(&e);
	e.type = SDL_FINGERMOTION;
	e.tfinger.x = tX;
	e.tfinger.y = tY;

	int tXw = tX * WWIDTH;
	int tYh = tY * WHEIGHT;
	//LOGD("OnTouchedMove X - Y: %d - %d", tXw, tYh);
	
}


void CAppStateTrans::freeMenu()
{
	for (std::vector<CMenu*>::iterator it = vectorMenu.begin(); it != vectorMenu.end(); ++it)
	{
		if (!(*it)) continue;
		(*it)->onDelete();
		(*it) = NULL;
	}
	vectorMenu.clear();
	SDL_Log("menu items deleted\n");

}


/* create the main menu buttons set */
void CAppStateTrans::createMainP()
{
	SDL_Log("create Panel background\n");
	/* the Panel background 
		Panel = CMenuFactory::getFactory()->CreateMenu("panel");
		Panel->init();
		vectorMenu.push_back(Panel);
	*/


	/* Button Play */
		SDL_Log("create button play\n");
		Play = CMenuFactory::getFactory()->CreateMenu("play");
		Play->init();
		vectorMenu.push_back(Play);
	

	/* Button Options */
		SDL_Log("create button options\n");
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
}

/* remove the main menu buttons set */
void CAppStateTrans::removeMainP()
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
	if (Exit)
	{
		Exit->onDelete();
		Exit = NULL;
	}

	vectorMenu.clear();
	
}

/* create the options panel buttons set */
void CAppStateTrans::createOptP()
{
	SDL_Log("create video items set\n");

	Video = CMenuFactory::getFactory()->CreateMenu("video");
	Video->init();
	vectorMenu.push_back(Video);

	Sound = CMenuFactory::getFactory()->CreateMenu("sound");
	Sound->init();
	vectorMenu.push_back(Sound);

	Return = CMenuFactory::getFactory()->CreateMenu("return");
	Return->init();
	vectorMenu.push_back(Return);
	
	queueID = 1;
}

/* Remove the options panel buttons set */
void CAppStateTrans::removeOptP()
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

	vectorMenu.clear();

}


/* create the sound panel buttons set */
void CAppStateTrans::createSoundP()
{
	SDL_Log("create sound items set\n");

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
void CAppStateTrans::removeSoundP()
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

	vectorMenu.clear();

	
}


//-----------------------------------------------------------------------------
CAppStateTrans* CAppStateTrans::GetInstance() {

    return &Instance;

}

void CMenu::onLoop()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "CMenu:onLoop() OVERIDE", "");
}
