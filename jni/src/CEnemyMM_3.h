#ifndef _CENEMYMM_3_H_
#define _CENEMYMM_3_H_

#include "CEntity.h"
#include "CBulletEnemy_S.h"
#include "CBulletEnemy.h"
#include "CMedal.h"
#include "CGammaRayEnemy.h"



class CEnemyMM_3 : public CEntity {

public:

	CBulletEnemy		*BullEnemy;
	CMedal              *MedalHonor;
	static const int MaxRow = 2000;
	float pathLine[MaxRow][2];
	int indexX, indexY;
	int offsetY;
    int ray_x, ray_y, ray_w, ray_h, temp_h;

	SDL_Rect    ret[10];

	CGammaRayEnemy* 	RayDX;
	CGammaRayEnemy*		RaySX;
	int 				Ray_once;
    bool                checkLaser;

    int selected;

private:

	int LimitX_dx;
	int LimitX_sx;
	
	// fattore di accelerazione
	float kAcc;

	//pathline variables for enemyBullet
	float px1;       //ascissa x1 del punto p1
	float px2;       //ascissa x2 del punto p2
	float py1;       //ordinata y1 del punto p1
	float py2;       //ordinata y2 del punto p2

	float DeltaX;           //delta px2 - px1
	float DeltaY;           //delta py2 - py1

	float m;                //coefficiente angolare
	float q;                //ordinata all'origine (intercetta)



    int temp_count;

	bool CanFire();

	int reset_kAcc();


public:

	CEnemyMM_3(int Xe, int Ye);
	~CEnemyMM_3();


	bool OnLoad(char* File, int Width, int Height);

	void OnInit();

	void OnLoop();

	void OnMove();

	void OnAnimate();

	void OnFireSX();
	void OnGammaRaySX();
	void OnGammaRayDX();

	void OnRender();

	void OnCleanup();

	void EntityDEL();

	bool OnCollision(CEntity *Entity);

	void CollisionLoop();

	void shiftColliders();

	std::vector<SDL_Rect>& getColliders();

	int EnemyGetX();

	int EnemyGetY();

    bool LaserCheck();


};

#endif
