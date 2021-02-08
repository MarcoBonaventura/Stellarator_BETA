#include "CEnemyMM_3.h"
#include "CPlayer.h"
#include "CPlayerStat.h"

#include "CParticle_PlayerXPL.h"
#include "CMedal.h"
#include "CFPS.h"
#include "CAppStateGame.h"
#include "CGenerator.h"
#include "CEnemyQueue.h"

#include "Stringify.h"

#include <iostream>


CEnemyMM_3::CEnemyMM_3(int Xe, int Ye) {

	SDL_Log("CEnemyMM_3()");

	//Offset = X;
	X = Xe;
	Y = Ye;

	Type = ENTITY_TYPE_ENEMY;
	Size = ENTITY_SIZE_MM;

	//AnimState = 0;
	counter = check_time = 0;
	hit = 0;
	//offsetY = 0;

    Ray_once = 0;
    checkLaser = false;
    AnimState = 0;

    time_lapse = laser_time = SDL_GetTicks();
    temp_count = 0;

    MoveRight = true;
	MoveLeft = false;
    MoveDown = true;
    MoveUp = false;

    check_time = 0;

	//bJolly = false;

	//fire = 4;
	//kAcc = 4;

	TimeStart = SDL_GetTicks();
	//shoted = 0;
	//hit = 0;

}

CEnemyMM_3::~CEnemyMM_3() {



}


bool CEnemyMM_3::OnLoad(char *File, int Width, int Height) {

	if (CEntity::OnLoad(File, Width, Height) == false) {
		return false;
	}

	return true;
}

void CEnemyMM_3::OnInit() {

	//SDL_Log("EnemyMM_3 OnInit()"); r41

	mVelX = 0;
	mVelY = 0;

	switch (this->selected) {

	    case 1:

            break;

	    case 2:

	        break;

	    case 3:

        r = 41 * OVERALL_ENEMY_RATIO;
        mColliders.resize(4);

        mColliders[0].w = 114;
        mColliders[0].h = 91;

        mColliders[1].w = 251;
        mColliders[1].h = 58;

        mColliders[2].w = 339;
        mColliders[2].h = 95;

        mColliders[3].w = 316;
        mColliders[3].h = 37;

        break;

	    case 4:

	        break;

    }

	for (int set = 0; set < mColliders.size(); set++)
	{
		mColliders[set].w = mColliders[set].w * OVERALL_ENEMY_RATIO;
		mColliders[set].h = mColliders[set].h * OVERALL_ENEMY_RATIO;
	}

	//Initialize colliders relative to position
	shiftColliders();


}

void CEnemyMM_3::shiftColliders() {

    switch (this->selected) {

        case 1:
            break;

        case 2:
            break;

        case 3:
            r = 41 * OVERALL_ENEMY_RATIO;
            break;

        case 4:
            break;
    }

    for (Uint32 set = 0; set<mColliders.size(); ++set)
    {
        mColliders[set].x = EnemyGetX() + (Width - mColliders[set].w) / 2;
        mColliders[set].y = EnemyGetY() + r;

        ret[set].h = mColliders[set].h;
        ret[set].w = mColliders[set].w;
        ret[set].x = mColliders[set].x;
        ret[set].y = mColliders[set].y;

        r += mColliders[set].h;
    }

}


void CEnemyMM_3::OnLoop() {

	OnMove();
    shiftColliders();
    CollisionLoop();


	if (CanFire())
    {
        if (LaserCheck())
        {
            time_lapse = SDL_GetTicks();
            if (time_lapse > laser_time + 3000)
            {
				Ray_once = 0;
			}
		}
        if (Ray_once == 0)
        {
            if (AnimState < 9)
            {
                SDL_SetRenderDrawColor(entityRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(entityRenderer, (EnemyGetX() + 98 * OVERALL_ENEMY_RATIO),
                                   (EnemyGetY() + 316 * OVERALL_ENEMY_RATIO),
                                   (EnemyGetX() + 98 * OVERALL_ENEMY_RATIO), WHEIGHT);
                SDL_RenderDrawLine(entityRenderer, (EnemyGetX() + 300 * OVERALL_ENEMY_RATIO),
                                   (EnemyGetY() + 316 * OVERALL_ENEMY_RATIO),
                                   (EnemyGetX() + 300 * OVERALL_ENEMY_RATIO), WHEIGHT);
                SDL_RenderPresent(entityRenderer);

                if(this->counter %10 == 0)
                {
                    AnimState++;
                }
            } else {
                AnimState = 0;
                SDL_Log("Laser SHOT!");
                OnGammaRaySX();
                OnGammaRayDX();
                Ray_once++;
            }
        }
    }


    OnAnimate();

    counter++;

	if (this->Dead)
	{
		if (!CEntity::TargetEnemyMap.empty())
		{
			if(CEntity::TargetEnemyMap.find(this->ID) != CEntity::TargetEnemyMap.end())
			{
				std::map<int, CEntity*>::iterator iter;
				iter = CEntity::TargetEnemyMap.find(this->ID);
				CEntity::TargetEnemyMap.erase(iter);
				SDL_Log("enemyMM3_OnLoop() ID %d erased from map", this->ID);
			}
		}
	}

}

bool CEnemyMM_3::CanFire() {

	if (EnemyGetY() > 0)
	{
		//SDL_Log("EnemyMM_3 CanFire = TRUE");
		return true;
	}
	else
	{
		//SDL_Log("EnemyMM_3 CanFire = FALSE");
		return false;
	}

}

void CEnemyMM_3::OnMove() {

	if (EnemyGetX() >= (WWIDTH - this->Width -250 ))    { MoveLeft = true; MoveRight = false; }
	if (EnemyGetX() <= (250))                           { MoveLeft = false; MoveRight = true; }

    if (EnemyGetY() >= (WHEIGHT * 0.2))                 { MoveUp = true; MoveDown = false;      }
    if (EnemyGetY() <= (0))                             { MoveUp = false; MoveDown = true;      }

    if (MoveLeft)   { X += -2; }
    if (MoveRight)  { X += 2; }

    if (MoveUp)     { Y += -1.5;   }
    if (MoveDown)   { Y += 2;      }

	//SDL_Log("EnemyMM_3 x: %d - y: %d", Xe, Ye);



}


void CEnemyMM_3::OnAnimate() {

	if (AnimState == 10) AnimState = 0;

}

int CEnemyMM_3::reset_kAcc() {

	//return kAcc = 4;

}


void CEnemyMM_3::OnRender() {

    CEntity::OnRender();

    if (entityRenderer)
	{
		TextureBank::Get(this->entityTexture)->Render(this->X, this->Y, this->Width, this->Height, this->W2 * AnimState, 0, W2, H2, 255);

		/*
		for(int set=0; set<mColliders.size(); set++)
		{
		SDL_SetRenderDrawColor(entityRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(entityRenderer, &ret[set]);
		}
		*/

	}
	else
	{
		SDL_Log("EnemyMM3::OnRender() BAD RENDERER!");
	}

}


void CEnemyMM_3::OnCleanup() {

    /*
	for (int i = 0; i<MaxRow; i++)
	{
		delete[] pathLine[i];
	}
	delete[] pathLine;
    */

}

void CEnemyMM_3::OnFireSX() {

	//SDL_Log("EnemyMM_3 fire sx!");
	float perc = 0;
	
	for (int i = 0; i < 6; i++)
	{
		px1 = EnemyGetX() + 145;
		py1 = EnemyGetY() + 375;

		px2 = (WWIDTH / 100) * perc;
		py2 = WHEIGHT;

		//SDL_Log("px1: %d  py1: %d", px1, py1);

		DeltaX = px2 - px1;
		DeltaY = py2 - py1;
		m = DeltaX / DeltaY;
		q = -(m)* py1 + px1;


		for (int indexX = 0; indexX < MaxRow; indexX++)
		{
			px1 = m * py1 + q;
			if (i == 0 || i == 5) py1 += 1;
			if (i == 1 || i == 4) py1 += 1.05;
			if (i == 2 || i == 3) py1 += 1.1;
			pathLine[indexX][0] = px1;
			pathLine[indexX][1] = py1;
			/*
			if (DeltaX >= WWIDTH / 2)        { py1 += 1; }
			else if (DeltaX < WWIDTH / 2)    { py1 += 2; }
			else if (DeltaX < -WWIDTH / 2)   { py1 += 1; }
			*/
		}

		BullEnemy = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_ENEMY_F);

		BullEnemy->W2 = 20;
		BullEnemy->H2 = 20;
		BullEnemy->Width = BullEnemy->W2 * OVERALL_ENEMY_RATIO;
		BullEnemy->Height = BullEnemy->H2 * OVERALL_ENEMY_RATIO;
		BullEnemy->entityTexture = "Blast_MX20_YW_anim";
		BullEnemy->Size = ENTITY_SIZE_BB;
		BullEnemy->OnInit();

		CEntity::EntityList.push_back(BullEnemy);

		perc += 20;

	}



	/*
	int g = -5;
	for (int i = 0; i < 11; i++)
	{
		int px1 = EnemyGetX() + 145;
		int py1 = EnemyGetY() + 375;

		BullEnemy = new CBulletEnemy_S(px1, py1, 2, g, "laser_07", ENTITY_FLAG_ENEMY_M);
		BullEnemy->Width = 20;
		BullEnemy->Height = 20;
		BullEnemy->entityTexture = "Blast_MX20_YW_anim";
		BullEnemy->Dead = false;
		BullEnemy->Type = ENTITY_TYPE_BULLET_E;
		BullEnemy->Size = ENTITY_SIZE_BB;
		BullEnemy->selectCollider = ENTITY_FLAG_ENEMY_M;
		BullEnemy->OnInit();

		CEntity::EntityList.push_back(BullEnemy);
		g++;
	}
	*/

}


///===========================================================================
void CEnemyMM_3::OnGammaRaySX() {


    RaySX = new CGammaRayEnemy(90 * OVERALL_ENEMY_RATIO, 289 * OVERALL_ENEMY_RATIO, this->ID, "laser_05");

    RaySX->W2 = 16;
    RaySX->H2 = 16;
	RaySX->Width = RaySX->W2 * OVERALL_ENEMY_RATIO;
	RaySX->Height = WHEIGHT;
	RaySX->Size = ENTITY_SIZE_SSX;
	RaySX->OnInit();

    CEntity::EntityList.push_back(RaySX);

}

void CEnemyMM_3::OnGammaRayDX() {


    RayDX = new CGammaRayEnemy(293 * OVERALL_ENEMY_RATIO, 289 * OVERALL_ENEMY_RATIO, this->ID, "laser_05");

    RayDX->W2 = 16;
    RayDX->H2 = 16;
    RayDX->Width = RayDX->W2 * OVERALL_ENEMY_RATIO;
    RayDX->Height = WHEIGHT;
    RayDX->Size = ENTITY_SIZE_SSX;
    RayDX->OnInit();

    CEntity::EntityList.push_back(RayDX);

}



///===========================================================================
void CEnemyMM_3::CollisionLoop() {


	for (Uint32 i = 0; i<CEntity::EntityList.size(); i++)
	{
		if (!CEntity::EntityList[i])
		{
			continue;
		}
		CEntity::CheckCollision(CEntity::EntityList[i]);
	}


}


bool CEnemyMM_3::OnCollision(CEntity *Entity) {


	//SDL_Log("MM3 OnCollision()");

	if (EnemyGetY() >1)
	{

		if (Entity->Type == ENTITY_TYPE_GAMMARAY || Entity->Size == ENTITY_SIZE_BOMB) hit += 5;
		else hit++;

        AnimState = 10;

		if (this->hit > 20)
		{
            SDL_Log("MM3 Dead");

            CEntity::EntityMap[this->ID] = NULL;

			CPlayer::PlayerStat.PlayerScore += 500;

			int XB = EnemyGetX() + 35;
			int YB = EnemyGetY();


			CParticle_PlayerXPL *PlayerExplosion = new CParticle_PlayerXPL(XB, YB, "boom_big_01", ENTITY_FLAG_ENEMY_F);

            PlayerExplosion->W2 = 128;
            PlayerExplosion->H2 = 128;
            PlayerExplosion->Width = this->Width;
            PlayerExplosion->Height = this->Height;
            PlayerExplosion->particleTexture = "Player_EXPL";

			CEntity::EntityList.push_back(PlayerExplosion);


			float x = XB;
			float y = YB - 35;
			float r = 35;

			//generate medal

			MedalHonor = new CMedal(x, y, 0, r, "powerup_01", ENTITY_FLAG_ENEMY_M1, BEZIER);

			MedalHonor->entityTexture = "Icon1";
			MedalHonor->Width = 100 * OVERALL_RATIO;
			MedalHonor->Height = 100 * OVERALL_RATIO;
			MedalHonor->OnInit();

			CEntity::EntityList.push_back(MedalHonor);

			Dead = true;

			if (this->Dead)
			{
				if (!CEntity::TargetEnemyMap.empty())
				{
					if(CEntity::TargetEnemyMap.find(this->ID) != CEntity::TargetEnemyMap.end())
					{
						std::map<int, CEntity*>::iterator iter;
						iter = CEntity::TargetEnemyMap.find(this->ID);
						CEntity::TargetEnemyMap.erase(iter);
						SDL_Log("enemyMM3_OnLoop() ID %d erased from map", this->ID);
					}
				}
			}
		}
	}

    return true;

}


std::vector<SDL_Rect>& CEnemyMM_3::getColliders() {

	return mColliders;

}

void CEnemyMM_3::EntityDEL() {

    CEntity::EntityDEL();

    /*
	for (std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
	{
		if (!(*it)) continue;
		if ((*it)->Dead)
		{
            SDL_Log("MM3 OnCleanuo() call");
			(*it)->OnCleanup();
			delete *it;
			it = CEntity::EntityList.erase(it);
		}
		else
		{
			it++;
		}
	}
    */

}

int CEnemyMM_3::EnemyGetX() {

	return this->X;
}

int CEnemyMM_3::EnemyGetY() {

	return this->Y;
}


bool CEnemyMM_3::LaserCheck() {

    if (!RayDX->GetLaserOnOff() && !RaySX->GetLaserOnOff())
    {
        return true;
    }

    //laser_time = SDL_GetTicks();

	return false;

}