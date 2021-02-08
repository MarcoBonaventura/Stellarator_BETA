//=============================================================================
#include "TextureBank.h"
#include "CApp.h"
#include "CAppStateIntro.h"
#include "FileManager.h"
#include "Log.h"
#include "Define.h"
#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

int pointX;
int pointY;
int W_rect;
int H_rect;


int TextureBank::LoaderW = 0;
int TextureBank::LoaderH = 0;
int TextureBank::LoaderBarW = 0;
int TextureBank::LoaderBarH = 0;

int TextureBank::tempFactor = 0;
int TextureBank::tempFactor2 = 0;
SDL_Surface* TextureBank::PrimarySurface = NULL;

std::string TextureBank::entityLoader = "Loader";
std::string TextureBank::entityBar = "Bar";

SLoader TextureBank::LoaderInfo = {};
SBar TextureBank::BarInfo = {};


//=============================================================================
std::map<std::string, Texture*> TextureBank::TexList;

SDL_Renderer* TextureBank::Renderer = NULL;
SDL_Window* TextureBank::Window = NULL;





//=============================================================================
bool TextureBank::OnInit() {

	Cleanup();

	SDL_Log("get Renderer from Intro...");

    Window = CAppStateIntro::GetInstance()->GetWindow();
	Renderer = CAppStateIntro::GetInstance()->GetRenderer();
    PrimarySurface = SDL_GetWindowSurface(Window);

	if(!Renderer)
    {
        SDL_Log("bad Renderer in TextureBank %s", SDL_GetError());
        return false;
    }


    SDL_Point Loader;
    SDL_Point Bar;

    LoaderW = (WWIDTH * 0.90);
	LoaderH = (LoaderW / 4.72);
    //LoaderH = 200;

    Loader.x = (WWIDTH - LoaderW) /2;
    Loader.y = (WHEIGHT - LoaderH) /2;

    LoaderBarW = LoaderW * 0.88;
    //LoaderBarH = (LoaderH /100 * 30);
    LoaderBarH = LoaderH * 0.28;

    tempFactor = ((LoaderW - LoaderBarW) / LoaderBarW) *100;
    tempFactor2 = 100 - tempFactor;
    //Bar.x = (LoaderW /100) * (100 - ((((LoaderW - LoaderBarW) /LoaderW)) *100));
    Bar.x = 95;
	Bar.y = (Loader.y /100) * (100 - ((((LoaderH - LoaderBarH) /LoaderH)) *100));

    //SDL_Log("First Loader >> xL: %d - yL: %d - wL: %d - hL: %d - xB: %d - yB: %d - wB: %d - hB: %d", Loader.x, Loader.y, LoaderW, LoaderH, Bar.x, Bar.y, LoaderBarW, LoaderBarH);

	//SDL_Log("Loader.X %d - Loader.Y %d - LoaderW %d - LoaderH %d", Loader.x, Loader.y, LoaderW, LoaderBarH);
	//SDL_Log("Bar.X %d - Bar.Y %d - BarW %d - BarH %d", Bar.x, Bar.y, LoaderBarW, LoaderBarH);


	LoaderInfo.x = Loader.x;
	LoaderInfo.y = Loader.y;
	LoaderInfo.w = LoaderW;
	LoaderInfo.h = LoaderH;
	LoaderInfo.w2 = 2191;
	LoaderInfo.h2 = 464;
	LoaderInfo.alpha = 255;

	BarInfo.x = (LoaderInfo.w * 0.1) + LoaderInfo.x;
	BarInfo.y = ((LoaderInfo.h * 0.42) + LoaderInfo.y) + 1;
	BarInfo.w = LoaderBarW;
	BarInfo.h = LoaderBarH;
	BarInfo.w2 = 1681;
	BarInfo.h2 = 103;
    BarInfo.perc = 0;


    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);

    SDL_Color BGColor = { 255, 0, 0, 255 };
	SDL_Color FGColor = { 0, 255, 0, 255 };

    /// Loader Progress Bar
    AddTexture(Renderer, "Loader", "Loader.png");
    AddTexture(Renderer, "Bar", "Bar.png");


    //RenderLoaderBKG(Loader.x, Loader.y, LoaderW, LoaderH, 0, 0, 2191, 464, 255);
	//RenderLoaderBar(Bar.x, Bar.y, LoaderBarW, LoaderBarH, 0, 0, 1681, 103, 0.05);
    BarInfo.perc = 0.0;
    RenderPreLoader(LoaderInfo, BarInfo);
    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);

    /// Menu assets
	AddTexture(Renderer, "WindowSmartphoneXXXL", "WindowSmartphoneXXXL.png");
    AddTexture(Renderer, "BackgroundShips2XXL", "BackgroundShips2XXL.png");
    AddTexture(Renderer, "Hangar_bg", "Hangar_bg.png");
	AddTexture(Renderer, "WindowPaused", "WindowPaused.png");
	AddTexture(Renderer, "Window_GameOver", "Window_GameOver.png");
	AddTexture(Renderer, "Window_debrief", "Window_debrief.png");
    AddTexture(Renderer, "Galaxy_final", "Galaxy_final.png");
    AddTexture(Renderer, "HangarRed", "HangarRed.png");
    AddTexture(Renderer, "HangarBlue", "HangarBlue.png");
    AddTexture(Renderer, "HangarGreen", "HangarGreen.png");
    AddTexture(Renderer, "HangarYellowAvail", "HangarYellowAvail.png");
    AddTexture(Renderer, "HangarYellowLocked", "HangarYellowLocked.png");

    BarInfo.perc = 0.08;
    RenderPreLoader(LoaderInfo, BarInfo);

    AddTexture(Renderer, "Play", "Play.png");
	AddTexture(Renderer, "Hangar", "Hangar.png");
	AddTexture(Renderer, "Start", "Start.png");
    AddTexture(Renderer, "Exit", "Exit.png");
    AddTexture(Renderer, "Options", "Options.png");
    AddTexture(Renderer, "Back_xs", "Back_xs.png");
    AddTexture(Renderer, "Resume", "Resume.png");
    AddTexture(Renderer, "Restart", "Restart.png");
    AddTexture(Renderer, "stage_1", "stage_1.png");
    AddTexture(Renderer, "stage_2", "stage_2.png");
    AddTexture(Renderer, "stage_3", "stage_3.png");
    AddTexture(Renderer, "stage_4", "stage_4.png");
    AddTexture(Renderer, "stage_final", "stage_final.png");
	AddTexture(Renderer, "Level_1", "Level_1.png");
    AddTexture(Renderer, "Level_2", "Level_2.png");
    AddTexture(Renderer, "Level_3", "Level_3.png");
    AddTexture(Renderer, "Level_4", "Level_4.png");
    AddTexture(Renderer, "Level_5", "Level_5.png");
    AddTexture(Renderer, "Level_6", "Level_6.png");
    AddTexture(Renderer, "Level_7", "Level_7.png");
    AddTexture(Renderer, "Level_8", "Level_8.png");
    AddTexture(Renderer, "Level_9", "Level_9.png");
    AddTexture(Renderer, "Level_10", "Level_10.png");
	AddTexture(Renderer, "HealthHUD", "HealthHUD.png");
	AddTexture(Renderer, "HealthBAR", "HealthBAR.png");
    AddTexture(Renderer, "HealthBOSShud", "HealthBOSShud.png");
    AddTexture(Renderer, "HealthBOSSbar", "HealthBOSSbar.png");

    /*
    AddTexture(Renderer, "TAG_level_locked", "TAG_level_locked.png");
    AddTexture(Renderer, "TAG_level_available", "TAG_level_available.png");
    AddTexture(Renderer, "TAG_level_1", "TAG_level_1.png");
    AddTexture(Renderer, "TAG_level_2", "TAG_level_2.png");
    AddTexture(Renderer, "TAG_level_3", "TAG_level_3.png");
    AddTexture(Renderer, "TAG_level_4", "TAG_level_4.png");
    AddTexture(Renderer, "TAG_level_5", "TAG_level_5.png");
    AddTexture(Renderer, "TAG_level_X", "TAG_level_X.png");
    */

    BarInfo.perc = 0.30;
    RenderPreLoader(LoaderInfo, BarInfo);
    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);
    /// player ships
	AddTexture(Renderer, "RedSmall_anim", "RedSmall_anim.png");
    AddTexture(Renderer, "BlueSmall_anim", "BlueSmall_anim.png");
	AddTexture(Renderer, "GreenSmall_anim", "GreenSmall_anim.png");
    AddTexture(Renderer, "YellowStronger_anim", "YellowStronger_anim.png");

    BarInfo.perc = 0.32;
    RenderPreLoader(LoaderInfo, BarInfo);
    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);
	/// Enemy Grey Ships
	AddTexture(Renderer, "EnemySX_grey1_anim", "EnemySX_grey1_anim.png");
    AddTexture(Renderer, "EnemySX_grey2_anim", "EnemySX_grey2_anim.png");
	AddTexture(Renderer, "EnemySX_grey3_anim", "EnemySX_grey3_anim.png");
    AddTexture(Renderer, "EnemySX_grey4_anim", "EnemySX_grey4_anim.png");
	AddTexture(Renderer, "EnemySX_grey5_anim", "EnemySX_grey5_anim.png");
    AddTexture(Renderer, "EnemyMM_grey1_anim", "EnemyMM_grey1_anim.png");
    AddTexture(Renderer, "EnemyMM_grey2_anim", "EnemyMM_grey2_anim.png");
    AddTexture(Renderer, "EnemyMM_grey3_anim", "EnemyMM_grey3_anim.png");
    AddTexture(Renderer, "EnemyMM_grey4_anim", "EnemyMM_grey4_anim.png");
    AddTexture(Renderer, "EnemyBOSS_grey1_anim", "EnemyBOSS_grey1_anim.png");
	AddTexture(Renderer, "EnemyBOSS_grey2_anim", "EnemyBOSS_grey2_anim.png");
	AddTexture(Renderer, "EnemyBOSS_grey3_anim", "EnemyBOSS_grey3_anim.png");
	AddTexture(Renderer, "EnemyBOSS_grey4_anim", "EnemyBOSS_grey4_anim.png");
	AddTexture(Renderer, "EnemyBOSS_grey5_anim", "EnemyBOSS_grey5_anim.png");
	AddTexture(Renderer, "EnemyBOSS_grey6_anim", "EnemyBOSS_grey6_anim.png");
	AddTexture(Renderer, "EnemyBOSS_grey7_anim", "EnemyBOSS_grey7_anim.png");
	AddTexture(Renderer, "EnemyBOSS_grey8_anim", "EnemyBOSS_grey8_anim.png");
	AddTexture(Renderer, "EnemyBOSS_grey9_anim", "EnemyBOSS_grey9_anim.png");
	AddTexture(Renderer, "EnemyBOSS_greyX_anim", "EnemyBOSS_greyX_anim.png");

    /// Enemy Dark Ships

    /// Enemy Yellow Ships

    /// Enemy Green Ships


    BarInfo.perc = 0.35;
    RenderPreLoader(LoaderInfo, BarInfo);
    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);
	/// Enemy muzzle & fire
	AddTexture(Renderer, "Enemy_fire_anim_blue", "Enemy_fire_anim_blue.png");
	AddTexture(Renderer, "FireEnemyBlue", "FireEnemyBlue.png");
	AddTexture(Renderer, "White_bullet_SSX", "White_bullet_SSX.png");
	AddTexture(Renderer, "Laser_EnemyPurple_anim", "Laser_EnemyPurple_anim.png");
	AddTexture(Renderer, "EnemyLaserGreen", "EnemyLaserGreen.png");
	AddTexture(Renderer, "EnemyLaserBlue", "EnemyLaserBlue.png");
    AddTexture(Renderer, "EnemyLaserFluo", "EnemyLaserFluo.png");
	AddTexture(Renderer, "Blast_MX20_YW_anim", "Blast_MX20_YW_anim.png");
	AddTexture(Renderer, "CannonBall", "CannonBall.png");

    BarInfo.perc = 0.37;
    RenderPreLoader(LoaderInfo, BarInfo);
    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);

    /// Player's effects & fire
	AddTexture(Renderer, "Boss_red_X", "Boss_red_X.png");
	AddTexture(Renderer, "Boss_Ball_Green", "Boss_Ball_Green.png");
	AddTexture(Renderer, "Boss_yellow_X", "Boss_yellow_X.png");
	AddTexture(Renderer, "Boss_blue_X", "Boss_blue_X.png");
	AddTexture(Renderer, "Boss_bullet_yellow", "Boss_bullet_yellow.png");
	AddTexture(Renderer, "OrangeTailperfect", "OrangeTailperfect.png");
	AddTexture(Renderer, "OrangeScale_Boss", "OrangeScale_Boss.png");
    AddTexture(Renderer, "OrangeBlast__anim_enemy", "OrangeBlast__anim_enemy.png");
	AddTexture(Renderer, "GreenBlast__anim_enemy", "GreenBlast__anim_enemy.png");
	AddTexture(Renderer, "Blast_MX_base", "Blast_MX_base.png");
	AddTexture(Renderer, "BlueBall__flash", "BlueBall__flash.png");
    AddTexture(Renderer, "BlueSpinperfect01", "BlueSpinperfect01.png");
    AddTexture(Renderer, "BlueSpinperfect", "BlueSpinperfect.png");
	AddTexture(Renderer, "GreenSpinperfect", "GreenSpinperfect.png");
	AddTexture(Renderer, "RedSpinperfect", "RedSpinperfect.png");
	AddTexture(Renderer, "OrangeBlast__anim_ply", "OrangeBlast__anim_ply.png");
	AddTexture(Renderer, "OrangeScale__flash2x", "OrangeScale__flash2x.png");
    AddTexture(Renderer, "BlueCircle__anim", "BlueCircle__anim.png");
    AddTexture(Renderer, "Rocket_small3", "Rocket_small3.png");
	AddTexture(Renderer, "Rocket_small2", "Rocket_small2.png");
	AddTexture(Renderer, "Rocket_anim2", "Rocket_anim2.png");
    AddTexture(Renderer, "gammaray_yellow", "gammaray_yellow.png");
	AddTexture(Renderer, "gammaray_light", "gammaray_light.png");
	AddTexture(Renderer, "EnemyLaser", "EnemyLaser.png");
	AddTexture(Renderer, "Enemy_Rocket", "Enemy_Rocket.png");
	AddTexture(Renderer, "Enemy_Bullet_Green", "Enemy_Bullet_Green.png");
	AddTexture(Renderer, "Enemy_Bullet_Yellow", "Enemy_Bullet_Yellow.png");
	AddTexture(Renderer, "Enemy_Laser_red", "Enemy_Laser_red.png");
	AddTexture(Renderer, "smog1", "smog1.png");

    BarInfo.perc = 0.40;
    RenderPreLoader(LoaderInfo, BarInfo);
    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);

	AddTexture(Renderer, "Splash_Intro1_1024", "Splash_Intro1_1024.png");
	AddTexture(Renderer, "EnemyMM_2_baseb", "EnemyMM_2_baseb.png");

	BarInfo.perc = 0.42;
    RenderPreLoader(LoaderInfo, BarInfo);
    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);

    /// Entities explosions
	AddTexture(Renderer, "explSX_01", "explSX_01.png");
	AddTexture(Renderer, "explSX_02", "explSX_02.png");
	AddTexture(Renderer, "explSX_03", "explSX_03.png");
	AddTexture(Renderer, "explSX_04", "explSX_04.png");
	AddTexture(Renderer, "explSX_05", "explSX_05.png");
	AddTexture(Renderer, "explSX_06", "explSX_06.png");
	AddTexture(Renderer, "explSX_07", "explSX_07.png");
	AddTexture(Renderer, "explSX_08", "explSX_08.png");
	AddTexture(Renderer, "explSX_09", "explSX_09.png");
	AddTexture(Renderer, "explSX_10", "explSX_10.png");

	BarInfo.perc = 0.50;
    RenderPreLoader(LoaderInfo, BarInfo);
    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);

	AddTexture(Renderer, "Laser_yellow_anim", "Laser_yellow_anim.png");

	BarInfo.perc = 0.52;
	RenderPreLoader(LoaderInfo, BarInfo);
    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);

    /// Medals
	AddTexture(Renderer, "Icon1", "Icon1.png");
    AddTexture(Renderer, "Icon2", "Icon2.png");
    AddTexture(Renderer, "Icon3", "Icon3.png");
    AddTexture(Renderer, "IconX", "IconX.png");
	AddTexture(Renderer, "IconFireUp", "IconFireUp.png");
	AddTexture(Renderer, "Icon_medal_rocket", "Icon_medal_rocket.png");
	AddTexture(Renderer, "Icon_medal_triple", "Icon_medal_triple.png");
	AddTexture(Renderer, "Icon_medal_penta", "Icon_medal_penta.png");
	AddTexture(Renderer, "Icon_medal_gammaray", "Icon_medal_gammaray.png");
	AddTexture(Renderer, "Icon_medal_combotot", "Icon_medal_combotot.png");

	BarInfo.perc = 0.60;
	RenderPreLoader(LoaderInfo, BarInfo);
    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);

    AddTexture(Renderer, "Player_fire_anim", "Player_fire_anim.png");
	AddTexture(Renderer, "Player_fire_anim_smart", "Player_fire_anim_smart.png");
	AddTexture(Renderer, "Player_fire_animPIX", "Player_fire_animPIX.png");

    BarInfo.perc = 0.65;
    RenderPreLoader(LoaderInfo, BarInfo);
    SDL_Log("LoaderInfo x %d, y %d, w %d, h %d, x2 %d, y2 %d, w2 %d, h2 %d, alpha %d",LoaderInfo.x, LoaderInfo.y, LoaderInfo.w, LoaderInfo.h, LoaderInfo.x2, LoaderInfo.w2, LoaderInfo.h2, LoaderInfo.alpha);

	AddTexture(Renderer, "Splash_CreditsRolls", "Splash_CreditsRolls.png");
	AddTexture(Renderer, "Splash_Lose2_1024", "Splash_Lose2_1024.jpg");
	AddTexture(Renderer, "CannonBall", "CannonBall.png");
	AddTexture(Renderer, "Tile_bg_256x256_DEEP", "Tile_bg_256x256_DEEP.png");
	AddTexture(Renderer, "Tile_bg_256x256_NEAR", "Tile_bg_256x256_NEAR.png");
	AddTexture(Renderer, "Tile_bg_256x256_trans", "Tile_bg_256x256_trans.png");
	AddTexture(Renderer, "Blast_SX_blueMINI", "Blast_SX_blueMINI.png");
	AddTexture(Renderer, "Blast_SX_greenMINI", "Blast_SX_greenMINI.png");
	AddTexture(Renderer, "Blast_SX_lightblueMINI", "Blast_SX_lightblueMINI.png");
	AddTexture(Renderer, "Blast_SX_pink", "Blast_SX_pink.png");
	AddTexture(Renderer, "Blast_SX_pinkMINI", "Blast_SX_pinkMINI.png");
	AddTexture(Renderer, "Blast_SX_red", "Blast_SX_red.png");
	AddTexture(Renderer, "Blast_SX_redMINI", "Blast_SX_redMINI.png");
	AddTexture(Renderer, "Blast_MX_YW_anim", "Blast_MX_YW_anim.png");
	AddTexture(Renderer, "Blast_MX50_YW_anim", "Blast_MX50_YW_anim.png");
	AddTexture(Renderer, "Player_EXPL", "Player_EXPL.png");

	BarInfo.perc = 0.85;
    RenderPreLoader(LoaderInfo, BarInfo);

    BarInfo.perc = 1.0;
	RenderPreLoader(LoaderInfo, BarInfo);

	return true;

}

//-----------------------------------------------------------------------------
void TextureBank::Cleanup() {

	if(TexList.size() <= 0) return;

	for(auto& Iterator : TexList)
    {
		Texture* TheTexture = (Texture*)Iterator.second;

		if(TheTexture)
        {
			delete TheTexture;
			TheTexture = NULL;
		}
	}

	TexList.clear();
}

//=============================================================================
void TextureBank::AddTexture(SDL_Renderer* Renderer, std::string ID, std::string Filename) {

    if(ID == "") return;

    Texture* NewTexture = new Texture();
    if(NewTexture->OnLoad(Renderer, Filename) == false)
    {
		SDL_Log("unable to load Texture %s, error: %s", Filename.c_str(), SDL_GetError());
		//Log("Unable to Load Texture: %s", ID.c_str());
		//CApp::Logger.OnLog( __FILE__, __LINE__, "Unable to load Texture", "");
		return;
	}
	else
	{
		SDL_Log("loaded Texture %s", Filename.c_str());
	}

    TexList[ID] = NewTexture;

}

//-----------------------------------------------------------------------------
Texture* TextureBank::Get(std::string ID) {

	if(TexList.find(ID) == TexList.end())
    {
        //CApp::Logger.OnLog( __FILE__, __LINE__, "Texture not found", ID);
		SDL_Log("Texture not found: %s into Assets", ID.c_str());
		LOGD("LOGD Texture not found: %s into Assets", ID.c_str());
		SDL_Log("error: %s", SDL_GetError());
		
        return 0;
    }

    //CApp::Logger.OnLog( __FILE__, __LINE__, "Texture found ", ID);
	return TexList[ID];


}

void TextureBank::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor)
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


void TextureBank::RenderLoaderBar(int x, int y, int w, int h, int x2, int y2, int w2, int h2, float Percent)
{

	SDL_Rect Source = {x, y, w ,h};
	SDL_Rect Dest = {x2, y2, w2, h2};

    SDL_Log("RenderLoaderBar() >> xB: %d - yB: %d - wB: %d - hB: %d - x2: %d - y2: %d - w2: %d - h2: %d - perc: %f1.2", x, y, w, h, x2, y2, w2, h2, Percent);

	//SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);

    SDL_RenderClear(Renderer);

    Get(entityBar)->Render(x, y, w, h, x2, y2, w2, h2, Percent);

    SDL_RenderPresent(Renderer);

}

void TextureBank::RenderLoaderBKG(int x, int y, int w, int h, int x2, int y2, int w2, int h2, int alpha)
{


    //SDL_Log("RenderLoaderBKG() >> xB: %d - yB: %d - wB: %d - hB: %d - x2: %d - y2: %d - w2: %d - h2: %d", x, y, w, h, x2, y2, w2, h2);



    SDL_SetRenderDrawColor(Renderer, 0x19, 0x19, 0x19, 0xFF);

	SDL_RenderClear(Renderer);

    Get(entityLoader)->Render(x, y, w, h, x2, y2, w2, h2, alpha);

	SDL_RenderPresent(Renderer);


}


void TextureBank::RenderPreLoader(SLoader L, SBar B)
{

    SDL_SetRenderDrawColor(Renderer, 0xFF, 0x00, 0x00, 0xFF);

    SDL_RenderClear(Renderer);

    Get(entityBar)->Render(B.x, B.y, B.w, B.h, B.x2, B.y2, B.w2, B.h2, B.perc);

    Get(entityLoader)->Render(L.x, L.y, L.w, L.h, L.x2, L.y2, L.w2, L.h2, L.alpha);

    SDL_RenderPresent(Renderer);

}

void TextureBank::RenderPostLoader()
{
    BarInfo.perc = 1.0;
    RenderPreLoader(LoaderInfo, BarInfo);

}



SLoader TextureBank::GetLoader()
{

	return LoaderInfo;

}

SBar TextureBank::GetBar()
{

	return BarInfo;

}