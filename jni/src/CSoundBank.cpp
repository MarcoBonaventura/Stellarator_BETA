#include "CSoundBank.h"
#include "FileManager.h"
#include "Stringify.h"
#include "CApp.h"
#include "CAppStateIntro.h"
#include "TextureBank.h"

#include "Define.h"
#include <memory>
//#include <WinBase.h>


CSoundBank CSoundBank::SoundControl;

SDL_Renderer* CSoundBank::Renderer = NULL;

std::map<std::string, Mix_Chunk*> CSoundBank::mySoundList;
//std::vector<Mix_Chunk*> SoundList;


Mix_Music *music = NULL;




CSoundBank::CSoundBank() {



}

bool CSoundBank::OnInit() {

	OnCleanup();

		
	return true;

}


bool CSoundBank::OnInit2() {

	OnCleanup();
	
	//std::vector<std::string> Files = FileManager::GetFilesInFolder("Sounds"); // Relative to CWD

	Renderer = CAppStateIntro::GetInstance()->GetRenderer();
	
	SDL_Log("loading audio file\n");
	
	SDL_Color BGColor = { 255, 0, 0, 255 };
	SDL_Color FGColor = { 0, 255, 0, 255 };


	SLoader L;
	SBar 	B;


	/*
	int pointX = (WWIDTH / 100) * 10;
	int pointY = (WHEIGHT / 100) * 50;

	int W_rect = (WWIDTH / 100) * 90;
	int H_rect = 100;
	*/

	OnLoad("RoleMusic_Theme1", "RoleMusic_Theme1.ogg");
	OnLoad("sound_LastMinute", "sound_LastMinute.ogg");
	OnLoad("powerup_02", "powerup_02.ogg");
	OnLoad("boom_01", "boom_01.ogg");
	OnLoad("boom_02", "boom_02.ogg");
	OnLoad("boom_03", "boom_03.ogg");
	OnLoad("boom_04", "boom_04.ogg");
	OnLoad("boom_05", "boom_05.ogg");
	OnLoad("boom_06", "boom_06.ogg");
	OnLoad("boom_07", "boom_07.ogg");
	OnLoad("boom_08", "boom_08.ogg");
	OnLoad("boom_09", "boom_09.ogg");
	OnLoad("boom_big_01", "boom_big_01.ogg");
	OnLoad("boom_big_02", "boom_big_02.ogg");
	OnLoad("laser_01", "laser_01.ogg");
	OnLoad("laser_02", "laser_02.ogg");
	OnLoad("laser_03", "laser_03.ogg");
	OnLoad("laser_04", "laser_04.ogg");
	OnLoad("laser_05", "laser_05.ogg");
	OnLoad("laser_06", "laser_06.ogg");
	OnLoad("laser_07", "laser_07.ogg");
	OnLoad("laser_08", "laser_08.ogg");
	OnLoad("laser_09", "laser_09.ogg");
	OnLoad("powerup_02", "powerup_02.ogg");
	//RenderHPBar(pointX, pointY, W_rect, H_rect, 1.0f, FGColor, BGColor);


	TextureBank::RenderPostLoader();

	SDL_Delay(500);
	
	return true;

}


bool CSoundBank::OnLoad(std::string soundID, const char* file) {

	if (file == "") return false;

	//soundID[strlen(soundID)] = '\0';

	char* buffer = const_cast<char*>(soundID.c_str());
	//char* buffer2 = new char[buffer.str_len() + 1];
	//buffer2[strlen()] = '\0';

	Mix_Chunk* TempSound;
	
	if ((TempSound = Mix_LoadWAV(file)) == NULL)
	{
		SDL_Log("unable to load audio file: %s", file);
		SDL_Log("SDL_Mixer error: %s", SDL_GetError());
		return false;
	}

	mySoundList[buffer] = TempSound;
	SDL_Log("audio file loaded: %s %s", buffer, file);
	//SDL_Log("audio file lenght: %d", strlen(buffer));
	//SDL_Log("audio file sizeof: %d", sizeof(buffer));


	return true;

}

void CSoundBank::OnCleanup() {

	CApp::Logger.OnLog(__FILE__, __LINE__, "cleaning mySoundList map", "");
    if (mySoundList.size() <= 0) return;
	
	for (std::map<std::string, Mix_Chunk*>::iterator it = mySoundList.begin(); it != mySoundList.end(); ++it)
	{
		Mix_FreeChunk(it->second);
	}

	mySoundList.clear();
		
}

void CSoundBank::Play(int channelID, const char* soundID, int loop) {

	if (mySoundList.find(soundID) == mySoundList.end())
	{
		SDL_Log("audio file non found: %s", soundID);
		return;
	}

	Mix_PlayChannel(channelID, mySoundList[soundID], loop);
	
}

void CSoundBank::Play2(char* soundID) {

	//soundID[strlen(soundID) - 1] = '\0';

	if (mySoundList.find(soundID) == mySoundList.end())
	{
		SDL_Log("audio file non found: %s", soundID);

		return;
	}

	Mix_PlayChannel(-1, mySoundList[soundID], 0);

}

void CSoundBank::PlayOGG(const char* file_ogg) {

	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS(file_ogg);
	SDL_Log("audio file loading... %s", file_ogg);
	if (!music) SDL_Log("Mix_PlayLoadMus error: %s\n", Mix_GetError());

	Mix_VolumeMusic(128);
	
	if (Mix_PlayMusic(music, 1) != 0)
	{
		SDL_Log("Mix_PlayMusic: %s\n", Mix_GetError());
	}


}

void CSoundBank::Pause(const char* soundID) {

    if(mySoundList[soundID] == NULL) return;

    Mix_Pause(-1);

}


void CSoundBank::Resume(const char* soundID) {

    if(mySoundList[soundID] == NULL) return;

    Mix_Resume(-1);

}

void CSoundBank::Halt(int channelID) {

	Mix_HaltChannel(channelID);

}


void CSoundBank::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor) 
{
	SDL_Log("FillRect");

	if (Renderer)
	{
		Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
		SDL_Color old;
		SDL_GetRenderDrawColor(Renderer, &old.r, &old.g, &old.g, &old.a);
		SDL_Rect bgrect = { x, y, w, h };
		SDL_SetRenderDrawColor(Renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
		SDL_RenderFillRect(Renderer, &bgrect);
		SDL_SetRenderDrawColor(Renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
		int pw = (int)((float)w * Percent);
		//int px = x + (w - pw);
		SDL_Rect fgrect = { x, y, pw, h };
		SDL_RenderFillRect(Renderer, &fgrect);
		SDL_SetRenderDrawColor(Renderer, old.r, old.g, old.b, old.a);
		SDL_RenderPresent(Renderer);
	}
	else
	{
		SDL_Log("Bad Renderer %s", SDL_GetError());
	}
	
}
