#include "CAppStateIntro.h"
#include "CAppStateManager.h"
#include "CAppStateGame.h"
#include "CApp.h"
#include "CSoundBank.h"
#include "TextureBank.h"
#include "CMenu.h"
#include "Stringify.h"

#include <iostream>
#include <sstream>
#include <memory>

CAppStateIntro CAppStateIntro::Instance;

int CAppStateIntro::spaceship = 1;

bool CAppStateIntro::mothership_completed = false;
bool CAppStateIntro::all_mission = false;
bool CAppStateIntro::final_mission = false;
bool CAppStateIntro::level_gained[][MAX_MISSION] = { { 0 } };
bool CAppStateIntro::MySpaceship[SHIPS] = { 0 };
bool CAppStateIntro::stage_complete[STAGE] = { 0 };
/*
bool CAppStateIntro::level_gained[][MAX_MISSION] = { { false, false, false, false, false, false, false, false, false, false },
{ false, false, false, false, false, false, false, false, false, false },
{ false, false, false, false, false, false, false, false, false, false },
{ false, false, false, false, false, false, false, false, false, false },
{ false, false, false, false, false, false, false, false, false, false } };
*/


CAppStateIntro::CAppStateIntro() {

    SDL_Log("CAppStateIntro()");

    alpha = 255;
    step = 0;

    nextState = true;
	
}



void CAppStateIntro::OnActivate() {

    TextureName = "Splash_Intro1_1024";
	
	
	
	SDL_CreateWindowAndRenderer(WWIDTH, WHEIGHT, SDL_WINDOW_FULLSCREEN, &Window, &Renderer);
	/*SDL_CreateWindow("demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, SDL_WINDOW_OPENGL);
    if (Window == NULL) SDL_Log("SDL_Window error: %s", SDL_GetError());
    else SDL_Log("SDL_Window created");

    SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Renderer == NULL) SDL_Log("Renderer failed: %s", SDL_GetError());
    else SDL_Log("SDL_Renderer created");
    */
    PrimarySurface = SDL_GetWindowSurface(Window);
	
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0xFF, 0xFF);
    
	
	//SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
	//SDL_RenderSetLogicalSize(Renderer, 1024, 768);


    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_Log("unable to create SDL_IMAGE %s", SDL_GetError());
        //return false;
    }


    if (TextureBank::OnInit() == false)
    {
        SDL_Log("unable to init TextureBank %s", SDL_GetError());
    }

    CSoundBank::SoundControl.OnInit2();


    
	StartTime = SDL_GetTicks();

	CApp::Logger.OnLog(__FILE__, __LINE__, "Play intro theme", "");
	SDL_Log("Play intro theme");
	//CSoundBank::SoundControl.Play2("sound_GalacticTemple");

	
	/*** READING GAME.INI data ***/

	SDL_Log("reading game.ini");
	std::string gameData[500];
	const int TOTAL_DATA = 500;
	char buffer[1024] = { "\0" };
	char* game_ini = "game.ini";

	SDL_RWops* ig = SDL_RWFromFile(game_ini, "rb");
	SDL_RWread(ig, buffer, sizeof(buffer), 4);
	SDL_RWclose(ig);

	char *game_info = strtok(strdup(buffer), ";");

	/*
	#ifdef _WIN32
	char *line = strtok(_strdup(buffer), "\r\n");
	#else
	char *line = strtok(strdup(buffer), ";");
	#endif
	*/

	SDL_Log("game.ini len: %d", SDL_strlen(buffer));
	SDL_Log("game.ini: %s", buffer);

	// get Player's spaceship
	for (int ship = 0; ship < SHIPS; ship++)
	{
		
		bool tempSHIP;
		char* charSHIP;
		charSHIP = game_info;
		std::stringstream(charSHIP) >> tempSHIP;
		MySpaceship[ship] = tempSHIP;
		SDL_Log("MySPaceship[%d]=[%d]", ship, MySpaceship[ship]);
		game_info = strtok(NULL, ";");
	}


	// get mothership mission
	//game_info = strtok(NULL, ";");
	bool temp;
	std::istringstream(game_info) >> temp;
	SetMothershipComplete(temp);

	SDL_Log("mothership mission completed: %d", temp);
	
	// get all mission
	game_info = strtok(NULL, ";");
	std::istringstream(game_info) >> temp;
	SetAllMission(temp);
	SDL_Log("all Mission completed: %d", atoi(game_info));

	// get final mission
	game_info = strtok(NULL, ";");
	std::istringstream(game_info) >> temp;
	SetFinalMission(temp);
	SDL_Log("final Mission: %d", atoi(game_info));

	/*
	// get stage(level) complete
	for (int stage = 0; stage < STAGE; stage++)
    {
        //game_info = strtok(NULL, ";");
        bool tempSTAGE;
        char* charSTAGE;
        charSTAGE = game_info;
        std::stringstream(charSTAGE) >> tempSTAGE;
        stage_complete[stage] = tempSTAGE;
        SDL_Log("stage_complete[%d]=[%d]", stage, stage_complete[stage]);
        game_info = strtok(NULL, ";");
    }
    */

	// get level mission
	SDL_Log("MAX LEVEL %d - MAX MISSION %d", MAX_LEVEL, MAX_MISSION);
	for (int lev = 0; lev < MAX_LEVEL; lev++)
	{
		//game_info = strtok(NULL, "\n");
		SDL_Log("new row");
		for (int mis = 0; mis < MAX_MISSION; mis++)
		{
			game_info = strtok(NULL, ";");
			bool temp;
			char* tempC;
			tempC = game_info;
			std::stringstream(tempC) >> temp;
			level_gained[lev][mis] = temp;
			SDL_Log("level[%d][%d]=[%d]", lev, mis, level_gained[lev][mis]);
			
		}
	}

    SDL_Log("game.ini loaded");
	SetPlayerShip(1);
	SDL_Log("spaceship loaded: %d", spaceship);


	
	
}

void CAppStateIntro::OnDeactivate() {



    /*
    if(PrimarySurface)
    {
        SDL_FreeSurface(PrimarySurface);
        PrimarySurface = NULL;
        CApp::Logger.OnLog( __FILE__, __LINE__, "*PrimarySurface destroyed", "");
    }

    //REMOVE SDL_Mixer
    CSoundBank::SoundControl.OnCleanup();
    //Mix_CloseAudio();

    //TextureBank::Cleanup();


	if(Renderer)
    {
		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;
		CApp::Logger.OnLog( __FILE__, __LINE__, "*Renderer destroyed", "");
	}



	if(Window)
    {
		SDL_DestroyWindow(Window);
		Window = NULL;
		CApp::Logger.OnLog( __FILE__, __LINE__, "*Window destroyed", "");
	}
    */

	//IMG_Quit();
	//SDL_Quit();

	SDL_Log("stop intro sound");
	//CSoundBank::SoundControl.Halt(-1);

}

void CAppStateIntro::OnLoop() {

	



    //CApp::Logger.OnLog( __FILE__, __LINE__, "CAppStateIntro OnLoop() START", "");
	SDL_Log("CAppStateIntro OnLoop() START");

    /** jump the Intro!! */
    //nextState = false;

    while (!nextState)
    {

    if (SDL_GetTicks() < StartTime +40000)
    {
        if (SDL_GetTicks() < StartTime +30000)
        {
            if (SDL_GetTicks() < StartTime +20000)
            {
                if (SDL_GetTicks() < StartTime +10000)
                {
                    if (SDL_GetTicks() > StartTime +7000)
                    {
                        if (step != 1)
                        {
                            if (alpha > 0)
                            {
                                alpha -= 1;
                                break;
                            }
                            else
                            {
                                step = 1;
                                Step1();
                                alpha = 255;
                            }
                        }
                    }
                    break;
                } //end IF 10000ms

                if (SDL_GetTicks() > StartTime +17000)
                {
                    if (step != 2)
                    {
                        if (alpha > 0)
                        {
                            alpha -= 1;
                            break;
                        }
                        else
                        {
                            step = 2;
                            Step2();
                            alpha = 255;
                        }
                    }
                }
                break;
            } // end IF 20000ms

            if (SDL_GetTicks() > StartTime +27000)
            {
                if (step != 3)
                {
                    if (alpha > 0)
                    {
                        alpha -= 1;
                        break;
                    }
                    else
                    {
                        step = 3;
                        Step3();
                        alpha = 255;
                    }
                }
            }
            break;
        } // end IF 30000ms

        if (SDL_GetTicks() > StartTime +35000)
        {
            if (alpha > 0)
            {
                alpha -= 1;
                break;
            }

        }
        break;
    }
    else
    {
        nextState = true;
        break;
    }


    }; //end WHILE




/*
    if(StartTime + 10000 < SDL_GetTicks()) {
        CAppStateManager::SetActiveAppState(APPSTATE_GAME);
    }

    if (StartTime +5000 < SDL_GetTicks())
        {
            if (alpha > 0) alpha -= 1;
        }
*/
    //std::cout<<"INTRO alpha: "<<alpha<<std::endl;
    //std::cout<<SDL_GetTicks()<<std::endl;


   //CApp::Logger.OnLog( __FILE__, __LINE__, "CAppStateIntro OnLoop() END", "");
	
	SDL_Log("goto APPSTATE_PAUSE");
    if (nextState) CAppStateManager::SetActiveAppState(APPSTATE_PAUSE);


}

//=====SCENE 1=================================================================
void CAppStateIntro::Step1() {

    TextureName = "Splash_Intro2_1024";
    //CApp::Logger.OnLog( __FILE__, __LINE__, "changed texture to ", TextureName);

}

//=====SCENE 2=================================================================
void CAppStateIntro::Step2() {

    //CApp::Logger.OnLog( __FILE__, __LINE__, "changed texture to ", TextureName);
    TextureName = "Splash_Intro3_1024";

}

//=====SCENE 3=================================================================
void CAppStateIntro::Step3() {

    //CApp::Logger.OnLog( __FILE__, __LINE__, "changed texture to ", TextureName);
    TextureName = "Splash_Intro4_1024";

}

//=====SCENE 4=================================================================
void CAppStateIntro::Step4() {

    //CApp::Logger.OnLog( __FILE__, __LINE__, "changed texture to ", TextureName);
    TextureName = "Splash_Intro5_1024";

}

void CAppStateIntro::OnRender() {

    SDL_Log("CAppStateIntro OnRender()");


    if(Renderer)
    {
        //CApp::Logger.OnLog( __FILE__, __LINE__, "Clearing *Renderer...", "");
        SDL_RenderClear(Renderer);


        //CApp::Logger.OnLog( __FILE__, __LINE__, "Get Texture...", "");
        TextureBank::Get(TextureName)->Render(0, 0, WWIDTH, WHEIGHT, alpha);

        //CApp::Logger.OnLog( __FILE__, __LINE__, "Rendering Texture...", "");
        SDL_RenderPresent(Renderer);
    }
    else
    {
		//SDL_Log("CAppStateIntro bad Renderer\n");
		//CApp::Logger.OnLog( __FILE__, __LINE__, "bad Renderer", "");
    }

    //SDL_Delay(500);

}


void CAppStateIntro::SetLevelGained(bool level[][10]) {

	for (int i = 0; i < MAX_LEVEL; i++)
	{
		for (int j = 0; j < MAX_MISSION; j++)
		{
			level_gained[i][j] = level;
		}
	}

}

bool CAppStateIntro::GetLevelGained() {

	return level_gained;
}


void CAppStateIntro::SetMySpaceship(bool myShip[]) {

	for (int i = 0; i < 3; i++)
	{
		MySpaceship[i] = myShip[i];
	}

}

bool CAppStateIntro::GetMySpaceship() {

	return MySpaceship;

}


CAppStateIntro* CAppStateIntro::GetInstance() {

    return &Instance;

}

//-----------------------------------------------------------------------------
SDL_Renderer* CAppStateIntro::GetRenderer() {

    return Renderer;

}


//-----------------------------------------------------------------------------
SDL_Window* CAppStateIntro::GetWindow() {

    return  Window;

}
