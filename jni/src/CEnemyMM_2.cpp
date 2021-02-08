#include "CEnemyMM_2.h"
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


CEnemyMM_2::CEnemyMM_2(int Xe, int Ye) {

    CAppStateGame::count_M2++;

    X = Xe;
    Y = Ye;

    Offset = X;

    Type = ENTITY_TYPE_ENEMY;
    Size = ENTITY_SIZE_MM;

	AnimState = 0;
	counter = 0;
	offsetY = 0;

    MoveDown = true;
    MaxSpeed = MaxSpeedY = 10 * OVERALL_SPEED_RATIO;


    fireDX = false;
    fireSX = true;

    bJolly = false;

    fire = 4;
    kAcc = 10 * OVERALL_SPEED_RATIO;
    slowDown = 0.3;

    TimeStart = SDL_GetTicks();
    shoted = 0;
    hit = 0;

}

CEnemyMM_2::~CEnemyMM_2() {

    CAppStateGame::count_M2--;

}


bool CEnemyMM_2::OnLoad(char *File, int Width, int Height) {
    if(CEntity::OnLoad(File, Width, Height) == false) {
        return false;
    }

    return true;
}

void CEnemyMM_2::OnInit() {

    mVelX = 0;
    mVelY = 0;

    switch (this->selected) {

        case 1:
            break;

        case 2:

            r = 23 * OVERALL_ENEMY_RATIO;
            mColliders.resize(8);

            mColliders[0].w = 291;
            mColliders[0].h = 70;

            mColliders[1].w = 359;
            mColliders[1].h = 32;

            mColliders[2].w = 339;
            mColliders[2].h = 18;

            mColliders[3].w = 303;
            mColliders[3].h = 18;

            mColliders[4].w = 256;
            mColliders[4].h = 71;

            mColliders[5].w = 245;
            mColliders[5].h = 38;

            mColliders[6].w = 235;
            mColliders[6].h = 22;

            mColliders[7].w = 242;
            mColliders[7].h = 30;

            break;

        case 3:

            break;

        case 4:

            break;

    }

    for (Uint32 set = 0; set < mColliders.size(); ++set)
    {
        mColliders[set].w = mColliders[set].w * OVERALL_ENEMY_RATIO;
        mColliders[set].h = mColliders[set].h * OVERALL_ENEMY_RATIO;
    }

	shiftColliders();

}

void CEnemyMM_2::shiftColliders() {

    switch (this->selected) {

        case 1:
            break;

        case 2:
            r = 23 * OVERALL_ENEMY_RATIO;
            break;

        case 3:
            break;

        case 4:
            break;
    }


    for (Uint32 set = 0; set<mColliders.size(); ++set)
    {
        mColliders[set].x = EnemyGetX() + (Width - mColliders[set].w) /2;
        mColliders[set].y = EnemyGetY() + r;

        ret[set].h = mColliders[set].h;
        ret[set].w = mColliders[set].w;
        ret[set].x = mColliders[set].x;
        ret[set].y = mColliders[set].y;

        r += mColliders[set].h;
    }

}

void CEnemyMM_2::OnLoop() {


    OnMove();
    shiftColliders();
    CollisionLoop();

	int Limit = EnemyGetY();
    if (Limit > WHEIGHT)
    {
        Dead = true;
    }

	OnAnimate();

    if (kAcc < 0) kAcc = 0;

    if (CanFire()) {

            OnFire();

    }

    counter++;

    if (this->Dead) {
        if (!CEntity::TargetEnemyMap.empty()) {
            std::map<int, CEntity *>::iterator iter;
            if (CEntity::TargetEnemyMap.find(ID) != CEntity::TargetEnemyMap.end()) {
                SDL_Log("enemyMM2_OnLoop() ID %d erased from map", ID);
                iter = CEntity::TargetEnemyMap.find(ID);
                CEntity::TargetEnemyMap.erase(iter);
            }
        }
    }

}

bool CEnemyMM_2::CanFire() {

    if (MaxSpeed <= 0)
    {
        int temp_level = CAppStateGame::GetInstance()->currentLevel + 1;

        if (counter >= 200) {
            if (counter % (200 / temp_level) == 0) {
                return true;
            }
            else return false;
        }
        else return false;
    }
    else return false;

}

void CEnemyMM_2::OnMove() {

    if (MoveDown)
    {
        if (Y > 0 && counter < 1000)
        {
            if (MaxSpeed > 0)
            {
                MaxSpeed -= slowDown;
            }
            else
            {
                MaxSpeed = 0;
            }
        }
        else
        {
            if (MaxSpeed < MaxSpeedY) {
                MaxSpeed += slowDown;
            } else MaxSpeed = MaxSpeedY;
        }
        Y += MaxSpeed;
    }


    /*
    if (MoveDown)  {
        if (MaxSpeed < MaxSpeedY) {
            MaxSpeed += slowDown;
        } else MaxSpeed = MaxSpeedY;
        Y += MaxSpeed;
    }
    */

}


void CEnemyMM_2::OnAnimate() {

    if(AnimState == 10) AnimState = 0;

}

int CEnemyMM_2::reset_kAcc() {

	return kAcc = 4;

}


void CEnemyMM_2::OnRender() {

    if (entityRenderer)
    {
		TextureBank::Get(entityTexture)->Render(this->X, this->Y, this->Width, this->Height, this->W2 * AnimState, 0, this->W2, this->H2, 255);

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
        SDL_Log("EnemyMM2::OnRender() BAD RENDERER!");
    }


}


void CEnemyMM_2::OnCleanup() {

    for (int i = 0; i<MaxRow; i++)
	{
	//	delete [] pathLine[i];
	}
	//delete [] pathLine;

}

void CEnemyMM_2::OnFire() {


    if (!Dead)
    {
        if (this->fireSX)
        {
            // LEFT FIRE

            px1 = EnemyGetX() + 120 * OVERALL_ENEMY_RATIO;
            py1 = EnemyGetY() + 239 * OVERALL_ENEMY_RATIO;
            this->fireSX = false;
        }
        else
        {
            // RIGHT FIRE

            px1 = EnemyGetX() + 276 * OVERALL_ENEMY_RATIO;
            py1 = EnemyGetY() + 239 * OVERALL_ENEMY_RATIO;
            this->fireSX = true;
        }

        BullEnemy = new CBulletEnemy_S(px1, py1, 12, 0, "laser_07", ENTITY_FLAG_ENEMY_M2);
        shoted++;
        BullEnemy->entityTexture = "BlueBall__flash";
        BullEnemy->W2 = 56;
        BullEnemy->H2 = 56;
        BullEnemy->Width = BullEnemy->W2 * OVERALL_ENEMY_RATIO;
        BullEnemy->Height = BullEnemy->H2 * OVERALL_ENEMY_RATIO;
        BullEnemy->OnInit();

        CEntity::EntityList.push_back(BullEnemy);

    }


    /*** targeted fire ***
	if (this->Dead == false)
	{
		px1 = EnemyGetX() + 105;
		py1 = EnemyGetY() + 118;
		//std::cout<<"EnemyGetX: "<<px1<<std::endl;
		//std::cout<<"EnemyGetY: "<<py1<<std::endl;

		px2 = CEntity::GetX() + 64;
		py2 = CEntity::GetY() + 64;
		//std::cout<<"CEnemyMM_2 - EnemyBullet Xdest: "<<px2<<" - Ydest: "<<py2<<std::endl;

		DeltaX = px2 - px1;
		DeltaY = py2 - py1;
		m = DeltaX / DeltaY;
		q = -(m)* py1 + px1;


		for (int indexX = 0; indexX < MaxRow; indexX++)
		{
			px1 = m * py1 + q;

			//pathLine[indexX] = new int[2];
			pathLine[indexX][0] = px1;
			pathLine[indexX][1] = py1;

			if (DeltaX >= WWIDTH / 2)        { py1 += 3; }
			else if (DeltaX < WWIDTH / 2)    { py1 += 3.5; }
			else if (DeltaX < -WWIDTH / 2)   { py1 += 3; }

			//std::cout<<"pathLine["<<indexX<<"][0]: "<<pathLine[indexX][0]<<std::endl;
			//std::cout<<"pathLine["<<indexX<<"][1]: "<<pathLine[indexX][1]<<std::endl;
		}

		//int XB = (EnemyGetX() +60);
		//int YB = (EnemyGetY() +110);



		CApp::Logger.OnLog(__FILE__, __LINE__, "CEnemyMM_2  new CBulletEnemy", "");
		BullEnemy = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_ENEMY_F);
		shoted++;
		BullEnemy->Width = 21;
		BullEnemy->Height = 21;
		BullEnemy->entityTexture = "Blast_SX_pink";
		BullEnemy->Dead = false;
		BullEnemy->Type = ENTITY_TYPE_BULLET_E;
		BullEnemy->Size = ENTITY_SIZE_BB;
		BullEnemy->OnInit();

		CEntity::EntityList.push_back(BullEnemy);
		

		
	}
    */

}



//=============================================================================
void CEnemyMM_2::CollisionLoop() {

    for (Uint32 i = 0; i<CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i])
        {
            continue;
        }
        CEntity::CheckCollision(CEntity::EntityList[i]);
    }

}


bool CEnemyMM_2::OnCollision(CEntity *Entity) {

    if (MaxSpeed == 0)
	{
        if (Entity->Type == ENTITY_TYPE_GAMMARAY || Entity->Size == ENTITY_SIZE_BOMB) hit += 5;
        else if (Entity->Type == ENTITY_TYPE_MyBULLET) hit++;

        AnimState = 10;

		if (hit > 20)
		{
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

            if (!CEntity::TargetEnemyMap.empty()) {
                std::map<int, CEntity *>::iterator iter;
                if (CEntity::TargetEnemyMap.find(ID) != CEntity::TargetEnemyMap.end()) {
                    SDL_Log("enemyMM2_OnCollision() ID %d erased from map", ID);
                    iter = CEntity::TargetEnemyMap.find(ID);
                    CEntity::TargetEnemyMap.erase(iter);
                }
            }
		}
	}

    return true;

}


std::vector<SDL_Rect>& CEnemyMM_2::getColliders() {

	return mColliders;

}

void CEnemyMM_2::EntityDEL() {

    CEntity::EntityDEL();

    /*
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead == true)
        {
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

int CEnemyMM_2::EnemyGetX() {

    return this->X;
}

int CEnemyMM_2::EnemyGetY() {

    return this->Y;
}

