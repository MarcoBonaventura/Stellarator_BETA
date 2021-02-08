//==============================================================================
#include "CApp.h"
#include "CAppStateIntro.h"
#include "TextureBank.h"

//==============================================================================
void CApp::OnCleanup() {


    CApp::Logger.OnLog( __FILE__, __LINE__, "set APPSTATE_NONE", "");
	//CAppStateManager::SetActiveAppState(APPSTATE_NONE);

    CApp::Logger.OnLog( __FILE__, __LINE__, "clear textures", "");
    TextureBank::Cleanup();

    SDL_Renderer* Renderer = CAppStateIntro::GetInstance()->GetRenderer();
    SDL_Window*   Window   = CAppStateIntro::GetInstance()->GetWindow();

    if(Renderer)
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "clear Renderer", "");
        SDL_DestroyRenderer(Renderer);
        Renderer = NULL;
    }

    if(Window)
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "clear window", "");
        SDL_DestroyWindow(Window);
        Window = NULL;
    }

	CApp::Logger.OnLog( __FILE__, __LINE__, "close SDL2 TTF", "");
    void TTF_CloseFont();
    void TTF_Quit();

    CApp::Logger.OnLog( __FILE__, __LINE__, "quit SDL IMG", "");
    IMG_Quit();

	CApp::Logger.OnLog(__FILE__, __LINE__, "SDL_MIXXER QUIT", "");
	Mix_CloseAudio();
	
	CApp::Logger.OnLog(__FILE__, __LINE__, "Cleaning audio", "");
	CSoundBank::OnCleanup();

	

	
		
}

//==============================================================================
