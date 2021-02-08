#ifndef _CPLAYER_H_
    #define _CPLAYER_H_

#include "CEntity.h"
#include "CBullet.h"
#include "CBulletSmart.h"
#include "CGammaRay.h"
#include "CBomb.h"
//#include "CParticle_Smoke.h"
#include "CParticles.h"
#include "CAnimation.h"

#define EVENT_BUF_SIZE 256

#define PI 3.14159265



class CPlayer : public CEntity {

public:
	enum FireMode
	{
		FIRE_SINGLE 		= 0,
		FIRE_TRIPLE 		= 1,
		FIRE_PENTA			= 2,
		FIRE_ROCKET 		= 3,
		FIRE_SMARTROCKET 	= 4,
		FIRE_SEEKROCKET     = 5,
		FIRE_GAMMARAY 		= 6,
		FIRE_COMBO1			= 7, 	// single + rocket
		FIRE_COMBO2			= 8, 	// triple + rocket
		FIRE_COMBO3         = 9, 	// penta/esa + rocket
		FIRE_COMBO4			= 10,	// gammaray + rocket
		FIRE_COMBOTOTAL		= 11, 	// triple + rocket + gammaray
		FIRE_NONE			= 12
	};

	enum RocketMode
	{
		ROCKET_NORMAL 	= 0,
		ROCKET_SMART 	= 1,
		ROCKET_SEEK     = 2
	};



private:

	CBullet*			Bull;
	CBullet*            Bull2;
	CBomb*				Rocket;
	CBomb*				Bomb;
	CGammaRay*			GammaRaySX;
    CGammaRay*          GammaRayDX;
	CBulletSmart*		RocketSmart;
	int					GammaRayOnce;

    static const int    MaxRow = 600;
    float               pathLine[MaxRow][2];
    double              pathDegree[MaxRow][1];

    double              degrees; //inclinazione retta in radianti


	static bool			GammaRayE;
	static bool			PlasmaCannonE;
	static float		MaxSpeed, Accel;
	static int			playerCounter, playerAnim, shotCounter, LevelMax;
	static int      	zx, xx, W1, H1, W2, H2;
	static int			rocketMODE;
	static float		Xb2, Yb2;

	int					TimeOut, counter, countRocket, countSmartRocket;
	int					enemyID;
	int             	onTarget;
    int             	X2, Y2;
    int                 r;

    char*	        	SmokeLow;
    char*           	SmokeHigh;
	char*				MuzzleSX;
	char*				MuzzleDX;
	char*				BulletTexture;
    SDL_Point			engOffset;
    SDL_Rect			ret[20];

    bool				IcanFire;
		

public:

	CPlayer();

	std::string		myTexture;

	static CPlayer	PlayerStat;
	
    static int		DeadTime;
	static int		fireMODE;
	static int 		temp_fireMODE;
	static int		armor;
	static int		PRE_armor;
	static int		stamina;
	static int		PRE_stamina;
	static bool		GodMODE;

    static int      mySHIP;
    static int      originalW, originalH;
    
	static int		PlayerHonor;
	static int 		PlayerTOTscore;
	static int		starSX;
	static int		starMM;
	static int		starM1; 
	static int		starBB;

	static float	Xp;
	static float	Yp;
	static int      X_P;
	static int      Y_P;
	float			X, Y;

	bool			canFire;
	bool			expired;
        
    void OnInit();

    bool OnLoad(char *File, int Width, int Height, int MaxFrames);

    void OnLoop();

    void OnRender();

    //void OnCleanup();

    void OnAnimate();

    bool OnCollision(CEntity *Entity);

    void CollisionLoop();

    void shiftColliders();

    std::vector<SDL_Rect>& getColliders();

    void OnCleanup();

	void OnMove(float MoveX, float MoveY);

	void StopMove();
	void StopMoveX();
	void StopMoveY();

    void Shoot();

    void Fire();
	static void setFireMode(FireMode fm);
	static void RestoreFireMode();
	void manageWeapons(int switchFire);

	void FireSingle(char* MuzzleSX, char* MuzzleDX, SDL_Point pnt_muzzleSX, SDL_Point pnt_muzzleDX, int muzzleW, int muzzleH, float Xb, float Yb, int zx, int W1, int H1, int W2, int H2, char* txt);
	void FireTriple(char* MuzzleSX, char* MuzzleDX, SDL_Point pnt_muzzleSX, SDL_Point pnt_muzzleDX, int muzzleW, int muzzleH, float Xb, float Yb, int xx, int zx, int W1, int H1, int W2, int H2, char*txt);
	void FireQuad(char* MuzzleSX, char* MuzzleDX, SDL_Point pnt_muzzleSX, SDL_Point pnt_muzzleDX, int muzzleW, int muzzleH, float Xb, float Yb, int xx, int zx, int W1, int H1, int W2, int H2, char* txt);
	void FirePenta(char* MuzzleSX, char* MuzzleDX, SDL_Point pnt_muzzleSX, SDL_Point pnt_muzzleDX, int muzzleW, int muzzleH, float Xb, float Yb, int xx, int zx, int W1, int H1, int W2, int H2, char* txt);
    void FireEsa(char* MuzzleSX, char* MuzzleDX, SDL_Point pnt_muzzleSX, SDL_Point pnt_muzzleDX, int muzzleW, int muzzleH, float Xb, float Yb, int xx, int zx, int W1, int H1, int W2, int H2, char* txt);
	void FireRocket(float Xb, float Yb);
	void FireGammaRay(int Xb, int Yb, int H, int w_off);

    void DropBomb();

    void ScoreInc();

    float			PlayerGetX();
	float			PlayerGetY();
	static float	PlayerGetXp();
	static float	PlayerGetYp();
	static int      GetPlayerX();
	static int      GetPlayerY();

	static bool		GetGammaRay() { return GammaRayE; }
	static void		SetGammaRay(bool enable) { GammaRayE = enable; }

	static bool		GetPlasma() { return PlasmaCannonE; }
	static void		SetPlasma(bool enable) { PlasmaCannonE = enable; }

	static float	GetMaxSpeed() { return MaxSpeed; }
	static void	    SetMaxSpeed(float newSpeed) { MaxSpeed = newSpeed; }
		
	static float	GetMaxAccel() { return Accel; }
	static void 	SetMaxAccel(float Acc) { Accel = Acc; }

	static int		GetLevelMax() { return LevelMax; }
	static void		SetLevelMax(int level) { LevelMax = level; }

	static int		GetPlayerArmor() { return armor; }
	static void		SetPlayerArmor(int arm) { armor = arm; }

	static int		GetPlayerStamina() { return stamina; }
	static void 	SetPlayerStamina(int stm) { stamina = stm; }
		
	static void		SetPlayerShotCounter(int newCounter) { shotCounter = newCounter; }
	static int		GetPlayerShoCounter() { return shotCounter; }

	static void 	IncTOTscore(int scored) { PlayerTOTscore += scored; }
	static void		ResetTOTscore() {PlayerTOTscore = 0; }
	static int 		GetTOTscore() { return PlayerTOTscore; }

	void            switchPlayerFire();
	bool 			SetEnabledFire(bool shot);
	bool			GetDisabledFire();

	int 			GetPlayerID();
	static void 	PlayerReset();

};


#endif
