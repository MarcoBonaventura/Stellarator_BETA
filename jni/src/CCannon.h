#ifndef _CCANNON_H_
#define _CCANNON_H_

#include "CEntity.h"
#include "CBulletEnemy_S.h"
#include "CBulletBOSS1.h"
#include "CBulletEnemy.h"
#include <random>

struct targetPoint
{
	float xPoint;
	float yPoint;
};

class CCannon : public CEntity {

	int     		xBoom, yBoom, posDSX;
	int     		AnimState, counter;
	int				hit;
	double 			degrees;
	bool 			degreeUP, degreeDOWN;
	targetPoint 	tgt;
	//SDL_Point 	pivot = {15,15};
    SDL_Point*   	pivot = NULL;
	SDL_Renderer*   myRenderer;
	CBulletEnemy_S* CannonBall;
	CBulletEnemy*	CannonFireSx1;
	CBulletEnemy*	CannonFireSx2;
	CBulletEnemy* 	CannonFireDx1;
	CBulletEnemy* 	CannonFireDx2;

	SDL_Point		offset;

	static const int MaxRow = 1000;
	float   pathLine[MaxRow][2];
	float   DeltaX, DeltaY, m, q;

    char *muzzle;
    SDL_Point pnt_muzzle_sx;
    SDL_Point pnt_muzzle_dx;

    static int Xen;
    static int Yen;
	
public:

	CCannon();
	CCannon(int X, int Y, int pos);
	~CCannon();

	//static int TEXTURE_WIDTH;
	//static int TEXTURE_HEIGHT;

	int			selected;
	

	virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames);

	void OnInit();

	void OnLoop();

	void OnMove();

	void OnFire(double dgr);

	void Engine();

	virtual void OnAnimate();

	virtual void OnRender();

	virtual void OnCleanup();

	virtual void EntityDEL();

	void shiftColliders();

	std::vector<SDL_Rect>& getColliders();

	void OnDeleteEnemy();

	bool OnCollision(CEntity *Entity);

	virtual void CollisionLoop();

	int CannonGetX();

	int CannonGetY();

	void SetTarget (targetPoint tempoint)
	{
		tgt.xPoint = tempoint.xPoint;
		tgt.yPoint = tempoint.yPoint;
	}
	targetPoint GetTarget ()
	{
		return tgt;
	}

	static int GetXen();
	static int GetYen();
	int GetHitted();

};

#endif
