#ifndef _CGAMMARAY_H
#define _CGAMMARAY_H


#include "CEntity.h"
#include "CPlayer.h"
#include "CParticle_XPL.h"
#include "CParticle_Smoke.h"



class CGammaRay : public CEntity {

	int zOffset;
	int wOffset;
	SDL_Point	PlayerOffset;


	float Xg, Yg;


public:

	CGammaRay(int X, int Y, int w_off, int Z, std::string soundFX);
	~CGammaRay();

public:

	int W2, H2;
	static bool collision;

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

	float GammaRayGetX();

	float GammaRayGetY();

};




#endif
