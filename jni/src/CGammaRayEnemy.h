#ifndef _CGAMMARAYENEMY_H
#define _CGAMMARAYENEMY_H


#include "CEntity.h"
#include "CParticle_XPL.h"



class CGammaRayEnemy : public CEntity {

	int enemy_ID, animstate;
	SDL_Point	EnemyOffset;
	static bool LaserAlive;


	SDL_Point 	*pivot = NULL;
	SDL_Point   Laser_pivot;
    SDL_Rect    ret;

	bool 		degreeUP, degreeDOWN;
	double 		degree;


public:

	CGammaRayEnemy(int X, int Y, int Z, std::string soundFX);
	~CGammaRayEnemy();

public:

	int W2, H2;

	bool OnLoad(char* File, int Width, int Height, int MaxFrames);

	void OnInit();

	void OnLoop();

	void OnMove();

	void OnRender();

	void OnCleanup();

	void EntityDEL();

	bool OnCollision(CEntity *Entity);

	void CollisionLoop();

	void shiftColliders();

	std::vector<SDL_Rect>& getColliders();

	bool Fire();

	int GammaRayGetX();

	int GammaRayGetY();

	void SetGammaRayDegree(double degree);

	static bool GetLaserOnOff();

};




#endif
