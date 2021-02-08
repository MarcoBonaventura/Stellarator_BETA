#define _CRT_SECURE_NO_DEPRECATE

#include "CPlayerStat.h"
#include "CAppStateGame.h"
#include "TextureBank.h"

#include <iostream>
#include <string>

CPlayerStat CPlayerStat::PlayerStat;


SHud CPlayerStat::HudPlayer = {};
SBarStamina CPlayerStat::BarPlayer = {};
std::string CPlayerStat::PlayerStamina = "HealthBAR";
std::string CPlayerStat::PlayerHUD = "HealthHUD";
std::string CPlayerStat::StaminaBOSS = "HealtBOSSbar";
std::string CPlayerStat::BOSShud = "HealthBOSShud";

SDL_Renderer* CPlayerStat::statRenderer = NULL;


CPlayerStat::CPlayerStat() {

    X = Y = 10;
    Xe = 200;
    Ye = 10;
    W = 150;
    H = 50;

    TextInGameColor = {0xf2, 0xf2, 0xf2};
    bg_color        = {0x00, 0x00, 0x00};
	scoreColor		= {0xf2, 0xf2, 0xf2};

    SDL_Surface *Surf_base      = NULL;
    SDL_Surface *messagesScore  = NULL;
    SDL_Surface *Surf_Stamina   = NULL;
    SDL_Surface *Surf_Damage    = NULL;
    SDL_Surface *Surf_Credits   = NULL;

    //Stamina = {200, 10, 400, 50};


    int Temp = CPlayer::PlayerStat.PlayerScore;
    n = sprintf (ScorePlayer, "%d", Temp);

    PlayerStamina = "HealthBAR";
    PlayerHUD     = "HealthHUD";



}

bool CPlayerStat::OnLoad() {

    Window = CAppStateGame::GetInstance()->GetWindow();

    statRenderer = CAppStateGame::GetInstance()->GetRenderer();

	if ((fontInGame = TTF_OpenFontRW(SDL_RWFromFile("Digital2.ttf", "r"), 1, 48)) == NULL)
	{
		SDL_Log("error loading fonts player Digital2.ttf\n");
		return false;
	}
	if ((fontScore = TTF_OpenFontRW(SDL_RWFromFile("Capsmall.ttf", "r"), 1, 48)) == NULL)
	{
		SDL_Log("error loading fonts player Capsmall.ttf\n");
		return false;
	}


    return true;

}


// RENDER PLAYER STAT SURFACE AND TEXT
void CPlayerStat::OnRender(int X, int Y, int W, int H) {

	SDL_SetRenderDrawColor(statRenderer, 0xFF, 0x00, 0x00, 0xFF);

    SDL_Rect renderQuad = {X, Y, W, H};

    if(!(messagesScore = TTF_RenderText_Blended(fontInGame, ScorePlayer, TextInGameColor)))
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "TTF_RenderText_Shaded() ERROR!", "");
        return;
    }
    else
    {
        txtTexture = SDL_CreateTextureFromSurface(statRenderer, messagesScore);

        if(statRenderer)
        {
            SDL_RenderCopy(statRenderer, txtTexture, NULL, &renderQuad);
        }
        else
        {
            CApp::Logger.OnLog( __FILE__, __LINE__, "bad PlayerStat renderer", "");
        }
    }

    OnUpdate();



}

// RENDER BONUS OWNED IN WIN PAGE
void CPlayerStat::OnRender(int X, int Y, int W, int H, int score, SDL_Surface* ScoreSurface) {

	SDL_Rect renderQuad = { X, Y, W, H };

	if (ScoreSurface) SDL_FreeSurface(ScoreSurface);

	if (txtTexture)    SDL_DestroyTexture(txtTexture);

	int Temp = score;
	n = sprintf(tempScore, "%d", Temp);

	if (!(messagesScore = TTF_RenderText_Blended(fontScore, tempScore, scoreColor)))
	{
        SDL_Log("TTF_RenderText_Shaded() ERROR: %c", SDL_GetError());
		return;
	}
	else
	{
		txtTexture = SDL_CreateTextureFromSurface(statRenderer, messagesScore);

		if (statRenderer)
		{
			SDL_RenderCopy(statRenderer, txtTexture, NULL, &renderQuad);
            //SDL_Log("Player StarSS: %d", tempScore);
		}
		else
		{
            SDL_Log("bad PlayerStat renderer: %c", SDL_GetError());
		}
	}

	


}


// RENDER PLAYER STAT STAMINA
void CPlayerStat::OnRender(int staminaColor, int X, int Y, int W, int H) {

    Stamina.h = H;
    Stamina.w = W;
    Stamina.x = X;
    Stamina.y = Y;

    //if (Surf_Stamina == NULL) return;
    //SDL_FillRect(Surf_Stamina, &Stamina, SDL_MapRGB(Surf_Stamina->format, 0, 255, 0));

    //CApp::Logger.OnLog( __FILE__, __LINE__, "render Stamina Player", "");

    SDL_SetRenderDrawColor(statRenderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect(statRenderer, &Stamina);


}


//-----RENDER BOSS STAT DAMAGE-------------------------------------------------
void CPlayerStat::OnRender(float f, int X, int Y, int W, int H, int Z) {

    Damage.h = H;
    Damage.w = W;
    Damage.x = X;
    Damage.y = Y;

    SDL_SetRenderDrawColor(statRenderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect(statRenderer, &Damage);


}


void CPlayerStat::RenderStaminaPlayer(std::string stamina, std::string hud, SHud H, SBarStamina S) {


    HudPlayer = H;
    BarPlayer = S;
    PlayerHUD = hud;
    PlayerStamina = stamina;

    //SDL_SetRenderDrawColor(statRenderer, 0x00, 0x00, 0x00, 0x00);

    //SDL_RenderClear(statRenderer);

    TextureBank::Get(PlayerHUD)->Render(H.x, H.y, H.w, H.h, H.x2, H.y2, H.w2, H.h2, H.alpha);

    TextureBank::Get(PlayerStamina)->Render(S.x, S.y, S.w, S.h, S.x2, S.y2, S.w2, S.h2, S.perc);


    //SDL_RenderPresent(statRenderer);


}


void CPlayerStat::RenderStaminaFlip(std::string stamina, std::string hud, SHud H, SBarStamina S) {


    HudPlayer = H;
    BarPlayer = S;
    PlayerHUD = hud;
    PlayerStamina = stamina;

    //SDL_SetRenderDrawColor(statRenderer, 0x00, 0x00, 0x00, 0x00);

    //SDL_RenderClear(statRenderer);

    TextureBank::Get(PlayerHUD)->Render(H.x, H.y, H.w, H.h, H.x2, H.y2, H.w2, H.h2, H.alpha);

    TextureBank::Get(PlayerStamina)->RenderFlip(S.x, S.y, S.w, S.h, S.x2, S.y2, S.w2, S.h2, S.perc);


    //SDL_RenderPresent(statRenderer);


}


/*
void CPlayerStat::OnRender(SDL_Surface *Surf_Display, int X, int Y, int credits) {

    if(Surf_base == NULL || Surf_Display == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_Credits, X, Y);

    if(!(Surf_Credits = TTF_RenderText_Shaded(fontInGame, textCredits[0], TextInGameColor, bg_color)))
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "TTF_RenderText_Shaded() ERROR!", "");
    }
    else
    {
        SDL_BlitSurface(Surf_Credits, NULL, Surf_Display, NULL);
        OnUpdate();
    }


}
*/


//-----UPDATE PLAYER STATISTICS------------------------------------------------
void CPlayerStat::OnUpdate() {

    //CApp::Logger.OnLog( __FILE__, __LINE__, "updating Player stats", "");

    if(messagesScore) SDL_FreeSurface(messagesScore);

    if(txtTexture)    SDL_DestroyTexture(txtTexture);

    int Temp = CPlayer::PlayerStat.PlayerScore;
    n = sprintf (ScorePlayer, "%d", Temp);
    //printf (ScorePlayer, n);


}


//-----FINAL CREDITS-----------------------------------------------------------
void CPlayerStat::FinaleCredits() {

    textCredits[0]="CREDITS";
    textCredits[1]="Space Commander - a Marco Bonaventura production";
    textCredits[2]="sfsdfsdf sdf sdf sfsd fsd";


}

void CPlayerStat::OnCleaunp() {

    if(messagesScore)
    {
        SDL_FreeSurface(messagesScore);
        messagesScore = NULL;
    }

    if(txtTexture)
    {
        SDL_DestroyTexture(txtTexture);
        txtTexture = NULL;
    }

    CApp::Logger.OnLog( __FILE__, __LINE__, "player stats deleted", "");


}

