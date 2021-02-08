#ifndef __CAPPSTATEINTRO_H__
    #define __CAPPSTATEINTRO_H__

#include "CAppState.h"

#include "Texture.h"

//#include <array>


class CAppStateIntro : public CAppState {

    private:

		static const int MAX_LEVEL = 5;
		static const int MAX_MISSION = 10;
		static const int SHIPS = 4;
		static const int STAGE = 5;
        static CAppStateIntro Instance;

        int alpha, alpha_transparent;
		int StartTime, step;
		int intro_sound;
		int gameMission, gameDecibel;

        bool nextState;
		static bool mothership_completed, all_mission, final_mission;
		static int spaceship;

		std::string     TextureName;
        SDL_Renderer*   Renderer = NULL;
        SDL_Window*     Window = NULL;
        SDL_Surface*    PrimarySurface;

    private:

        CAppStateIntro();

        void Step1();

        void Step2();

        void Step3();

        void Step4();

    public:

        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender();

    public:

        static CAppStateIntro* GetInstance();

        SDL_Renderer* GetRenderer();

        SDL_Window*   GetWindow();

		void SetGameMission(int mm) { gameMission = mm; }
		int	 GetGameMission() { return gameMission; }

		void SetGameDecibel(int dcbl) { gameDecibel = dcbl; }
		int  GetGameDecibel() { return gameDecibel; }

		static void SetPlayerShip(int ship) { spaceship = ship; }
		static int  GetPlayerShip() { return spaceship; }

		void SetMothershipComplete(bool ms_done)  { mothership_completed = ms_done; }
		bool GetMothershipComplete() { return mothership_completed; }

		void SetAllMission(bool ms_all)  { all_mission = ms_all; }
		bool GetAllMission() { return all_mission; }

		void SetFinalMission(bool ms_end)  { final_mission = ms_end; }
		bool GetFinalMission() { return final_mission; }

		void SetLevelGained(bool level_gain[][10]);
		bool GetLevelGained();

		void SetStageComplete(int stage) {stage_complete[stage] = true; }
		bool GetStageComplete() { return stage_complete; }

		void SetMySpaceship(bool myShip[]);
		bool GetMySpaceship();

		static bool level_gained[MAX_LEVEL][MAX_MISSION]; 
		static bool MySpaceship[SHIPS];
		static bool stage_complete[STAGE];
};

#endif
