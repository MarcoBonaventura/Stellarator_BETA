#ifndef _CPLAYERSTAT_H_
    #define _CPLAYERSTAT_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include "TextureBank.h"

#include <string>

#include "CApp.h"
#include "CPlayer.h"


struct SHud{

	int x;
	int y;
	int w;
	int h;
	int x2;
	int y2;
	int w2;
	int h2;
	int alpha;

};

struct SBarStamina {

	int x;
	int y;
	int w;
	int h;
	int x2;
	int y2;
	int w2;
	int h2;
	float perc;

};



class CPlayerStat {

    public:

        static CPlayerStat  PlayerStat;

        int X, Y, W, H, n, Xe, Ye;

    private:

        TTF_Font        *fontInGame;
		TTF_Font		*fontScore;
        SDL_Color       TextInGameColor;
        SDL_Color       bg_color;
		SDL_Color		scoreColor;

        char            ScorePlayer[255];
        char            *textCredits[255];

		char			tempScore[255];

        static SDL_Renderer*   statRenderer;

        SDL_Window*     Window;

        SDL_Surface*    PrimarySurface;

		static SHud			    HudPlayer, HudBOSS;
		static SBarStamina		BarPlayer, BarBOSS;
		static std::string		PlayerStamina;
		static std::string		PlayerHUD;
        static std::string      StaminaBOSS;
        static std::string      BOSShud;



    public:
        SDL_Surface     *Surf_base;
        SDL_Surface     *messagesScore = NULL;
        SDL_Surface     *Surf_Stamina;
        SDL_Surface     *Surf_Damage;
        SDL_Surface     *Surf_Credits;


        SDL_Texture*    txtTexture;
        SDL_Rect        Stamina;
        SDL_Rect        Damage;

    public:

        CPlayerStat();

        bool    OnLoad();

        //void    OnRender(SDL_Surface *Surf_Display, int X, int Y);
		void    OnRender(int X, int Y, int W, int H, int score, SDL_Surface* ScoreSurface);
        void    OnRender(int staminaColor, int X, int Y, int W, int H);
        void    OnRender(int X, int Y, int W, int H);
        void    OnRender(float f, int X, int Y, int W, int H, int Z);

		static void	RenderStaminaPlayer(std::string stamina, std::string hud, SHud H, SBarStamina S);
		static void	RenderStaminaFlip(std::string stamina, std::string hud, SHud H, SBarStamina S);

        //void    OnRender();

        void OnCleaunp();



        //void    OnRenderText(TTF_Font *fontInGame, const char *ScorePlayer, SDL_Color TextInGameColor);

        void    OnUpdate();

        void    FinaleCredits();

		char	GetScorePlayer() { return *ScorePlayer; }

};

#endif
