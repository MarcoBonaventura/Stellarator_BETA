//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


#include "Define.h"

#include "CArea.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CEvent.h"
#include "Texture.h"
#include "CSoundBank.h"
#include "TextureBank.h"

#include "CAppStateManager.h"

#include "CPlayerStat.h"





extern SDL_Joystick* gGameController;
extern SDL_Haptic* gControllerHaptic;
extern SDL_Haptic* mouseHaptic;


//==============================================================================
class CApp : public CEvent {


        static CApp Instance;
		static bool game_OVER;

        //SDL_Surface     *Surf_Display;

        //SDL_Window*     Window          = NULL;
        //SDL_Renderer*   Renderer        = NULL;
        SDL_Surface*    PrimarySurface  = NULL;


        bool to_bool(std::string const& s)
        {
            return s != "0";
        }




    public:

        CApp();
        ~CApp();

        static  bool    Running;



        static  CApp* GetInstance();

        static  CApp    Logger;
        static bool     LogFile;

		Texture    Screen;

        int OnExecute();

        bool OnInit();

        void OnEvent(SDL_Event* Event);

        void OnExit();

        void OnLoop();

        void OnRender();



        //WindowContext GetWindowContext();

        void OnCleanup();

        void OnLog(std::string file, int line, std::string message_Text, std::string messageOUT);

		static bool SetGameOver(bool game) { game_OVER = game; }
		static bool GetGameOver() { return game_OVER; }







};

//==============================================================================

#endif
