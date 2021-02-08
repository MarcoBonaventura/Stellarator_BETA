#ifndef _CSOUNDBANK_H_
    #define _CSOUNDBANK_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <map>
#include <memory>
#include <string>



class CSoundBank {



	//static std::vector<Mix_Chunk*> SoundList;
	//static std::vector<std::string> tempSoundList;
	static std::map<std::string, Mix_Chunk*> mySoundList;
	//static std::map<char[255], Mix_Chunk*> mySoundList;


	public:

        static CSoundBank SoundControl;

		static SDL_Renderer* Renderer;

		/*
		static int	Sound_intro, Sound_PlayerXPL, Sound_explSX1, Sound_explSX2, Sound_explSX3, Sound_PlayerFire, 
					Sound_Main_BG, Sound_BOSSlaser, Sound_Boss, Sound_Medal, Sound_MedalBoss, Sound_BossExpl;
		*/

	public:

        CSoundBank();

		static bool OnInit();

		static bool OnInit2();

        //static bool OnLoad(std::string soundID, const char* file);
		static bool OnLoad(std::string soundID, const char* file);

        static void OnCleanup();

    public:

		static void Play(int channelID, const char* soundID, int loop);

		//static void Play2(std::string soundID);
		static void Play2(char* soundID);

		static void PlayOGG(const char* file_ogg);

		static void Pause(const char* soundID);

		static void Resume(const char* soundID);

		static void Halt(int channelID);

		static void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);

};

#endif
