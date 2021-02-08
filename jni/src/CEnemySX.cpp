#include "CEnemySX.h"
#include "CPlayer.h"
#include "CPlayerStat.h"
#include "CParticle_XPL.h"
#include "Stringify.h"
#include <string>

#include <iostream>
#include <algorithm>
#include <functional>


CEnemySX::CEnemySX() {}

CEnemySX::CEnemySX(int Xe, int Ye) {

    X = Xe;
    Y = Ye;


    boom = false;

    AnimState = 0;
    this->counter   = 0;

    stamina = 25;

    position.X = EnemyGetX();
    position.Y = EnemyGetY();

    Type = ENTITY_TYPE_ENEMY;
    Move = MOVE_DOWN;
    MaxSpeedX = 4 * OVERALL_SPEED_RATIO;
    MaxSpeedY = 4 * OVERALL_SPEED_RATIO;

    SDL_Log("EnemySX ID: %d", this->ID);


}

CEnemySX::~CEnemySX() {


}

void CEnemySX::OnInit() {

    mVelX = 0;
    mVelY = 0;

    switch(selected)
    {
        case 0:
            mColliders.resize(4);

            r = 12;
            mColliders[0].w = 98;
            mColliders[0].h = 52;

            mColliders[1].w = 87;
            mColliders[1].h = 36;

            mColliders[2].w = 60;
            mColliders[2].h = 19;

            mColliders[3].w = 15;
            mColliders[3].h = 15;

            break;

        case 1:
            mColliders.resize(5);

            r = 25;
            mColliders[0].w = 100;
            mColliders[0].h = 56;

            mColliders[1].w = 86;
            mColliders[1].h = 26;

            mColliders[2].w = 63;
            mColliders[2].h = 7;

            mColliders[3].w = 21;
            mColliders[3].h = 7;

            mColliders[4].w = 11;
            mColliders[4].h = 4;

            break;

        case 2:

            mColliders.resize(7);

            r = 63;
            mColliders[0].w = 100;
            mColliders[0].h = 11;

            mColliders[1].w = 88;
            mColliders[1].h = 22;

            mColliders[2].w = 80;
            mColliders[2].h = 10;

            mColliders[3].w = 68;
            mColliders[3].h = 5;

            mColliders[4].w = 57;
            mColliders[4].h = 5;

            mColliders[5].w = 46;
            mColliders[5].h = 4;

            mColliders[6].w = 32;
            mColliders[6].h = 4;

            break;

        case 3:
            mColliders.resize(4);

            r  = 50;
            mColliders[0].w = 100;
            mColliders[0].h = 27;

            mColliders[1].w = 29;
            mColliders[1].h = 11;

            mColliders[2].w = 25;
            mColliders[2].h = 10;

            mColliders[3].w = 24;
            mColliders[3].h = 16;

            break;

        case 4:
            mColliders.resize(5);

            r = 50;
            mColliders[0].w = 100;
            mColliders[0].h = 25;

            mColliders[1].w = 76;
            mColliders[1].h = 22;

            mColliders[2].w = 15;
            mColliders[2].h = 18;

            mColliders[3].w = 7;
            mColliders[3].h = 5;

            mColliders[4].w = 3;
            mColliders[4].h = 3;

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


void CEnemySX::shiftColliders() {

    ret = new SDL_Rect[mColliders.size()];

    switch (selected)
    {
        case 0:
            r = 12 * OVERALL_ENEMY_RATIO;

            break;

        case 1:
            r = 25 * OVERALL_ENEMY_RATIO;

            break;

        case 2:
            r = 63 * OVERALL_ENEMY_RATIO;

            break;

        case 3:
            r  = 50 * OVERALL_ENEMY_RATIO;

            break;

        case 4:
            r = 50 * OVERALL_ENEMY_RATIO;

            break;
    }

    for (int set = 0; set < mColliders.size(); set++)
    {
        mColliders[set].x = EnemyGetX() + ((Width - mColliders[set].w) /2);
        mColliders[set].y = EnemyGetY() + r;



        ret[set].h = mColliders[set].h;
        ret[set].w = mColliders[set].w;
        ret[set].x = mColliders[set].x;
        ret[set].y = mColliders[set].y;

        r += mColliders[set].h;
    }

}

bool CEnemySX::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }

    return true;
}

void CEnemySX::OnLoop() {

    //SDL_Log("EnemyXS ID %d start loop", this->ID);

    OnMove();
    shiftColliders();
	CollisionLoop();

    int LimitX = EnemyGetX();
    int LimitY = EnemyGetY();
    switch (Size)
    {
        case ENTITY_SIZE_SX:
            if (LimitY > WHEIGHT)
            {
                Dead = true;
            }
            break;

        case ENTITY_SIZE_SSX:
            if (LimitX > WWIDTH)
            {
                Dead = true;
            }
            if (counter %20 == 0)
            {
                //OnFire();
            }
            break;
    }


    if (stamina <= 0) Dead = true;


    if (Dead)
    {
        if (!CEntity::TargetEnemyMap.empty())
        {
            if(CEntity::TargetEnemyMap.find(this->ID) != CEntity::TargetEnemyMap.end())
            {
                std::map<int, CEntity*>::iterator iter;
                iter = CEntity::TargetEnemyMap.find(this->ID);
                CEntity::TargetEnemyMap.erase(iter);
                SDL_Log("enemy ID %d erased from map", this->ID);
            }
        }
    }

    //SDL_Log("EnemyXS Id %d end loop", this->ID);

}


void CEnemySX::OnMove() {

    switch (Size)
    {
        case ENTITY_SIZE_SSX:
            X += MaxSpeedX;
            break;
        case ENTITY_SIZE_SX:
            Y += MaxSpeedY + 1;
            break;
        default:
            Y += MaxSpeedY;
    }

}

void CEnemySX::OnFire() {


    SDL_Point SSx;
    SSx.x = EnemyGetX() + 62;
    SSx.y = EnemyGetY() + 110;

    CBulletEnemy_S* BulletSSX = new CBulletEnemy_S(SSx.x, SSx.y, 15, 0, "laser_07", ENTITY_FLAG_ENEMY_S);

    BulletSSX->entityTexture = "White_bullet_SSX";
    BulletSSX->Width = 25;
    BulletSSX->Height = 40;
    BulletSSX->Type = ENTITY_TYPE_BULLET_E;
    BulletSSX->Size = ENTITY_SIZE_SSX;
    BulletSSX->Dead = false;
    BulletSSX->selectCollider = ENTITY_FLAG_ENEMY_S;

    CEntity::EntityList.push_back(BulletSSX);


}

void CEnemySX::Engine() {

	int engineX = EnemyGetX() + 15;
	int engineY = EnemyGetY() + 9;
	std::string str = "";
	for (int n = 0; n < 4; n++)
	{
		if (selected == 0)
		{
			int prob = rand() % 2;
			switch (prob)
			{
			case 0:
				str = "smogOrange1";
				break;
			case 1:
				str = "smogOrange2";
				break;
			case 2:
				str = "smogOrange3";
				break;
			default:
				break;
			}

			/*
			ENGINE = new CParticle_Smoke();
			ENGINE->X = engineX;
			ENGINE->Y = engineY;
			ENGINE->Width = 4;
			ENGINE->Height = 4;
			ENGINE->particleTexture = str;
			ENGINE->counter = 0;
			ENGINE->alphaSmoke = 255;

			CEntity::EntityList.push_back(ENGINE);
			engineX += 4;
			*/
		}
	}
	
}



std::vector<SDL_Rect>& CEnemySX::getColliders() {

	return this->mColliders;

}

void CEnemySX::OnAnimate() {

	if (AnimState < 12) AnimState++;
	else AnimState = 0;

}


void CEnemySX::OnRender() {

    if (entityRenderer)
    {
		TextureBank::Get(entityTexture)->Render(this->X, this->Y, this->Width, this->Height, this->W2 * this->AnimState, 0, this->W2, this->H2, 255);
        /*
        for(int set = 0; set < mColliders.size(); set++)
        {
            SDL_SetRenderDrawColor(entityRenderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(entityRenderer, &ret[set]);
        }
        */
    }
    else
    {
        SDL_Log("CEnemySX::OnRender() BAD RENDERER: %s", SDL_GetError());
    }


}

void CEnemySX::OnCleanup() {


}


//=============================================================================
void CEnemySX::CollisionLoop() {

    for (int i=0; i<CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i])
        {
            continue;
        }
        if(this != CEntity::EntityList[i])
            CEntity::CheckCollision(CEntity::EntityList[i]);
    }

}


bool CEnemySX::OnCollision(CEntity *Entity) {


    if (EnemyGetY() >1)
    {


        SDL_Log("entity EnemySX ID: %d collision with entity bullet ID: %d", this->ID, Entity->ID);

        if (Entity->Type == ENTITY_TYPE_MyBULLET || Entity->Type == ENTITY_TYPE_GAMMARAY || Entity->Type == ENTITY_TYPE_PLAYER)
        {
            CPlayer::PlayerStat.PlayerScore += 100;

            switch (rand() % 9) {
                case 0:
                    anim_filename = "explSX_01";
                    break;
                case 1:
                    anim_filename = "explSX_02";
                    break;
                case 2:
                    anim_filename = "explSX_03";
                    break;
                case 3:
                    anim_filename = "explSX_04";
                    break;
                case 4:
                    anim_filename = "explSX_05";
                    break;
                case 5:
                    anim_filename = "explSX_06";
                    break;
                case 6:
                    anim_filename = "explSX_07";
                    break;
                case 7:
                    anim_filename = "explSX_08";
                    break;
                case 8:
                    anim_filename = "explSX_09";
                    break;
                case 9:
                    anim_filename = "explSX_10";
                    break;
            }


            /// create explosion particle effect
            int XB = EnemyGetX();
            int YB = EnemyGetY();

            CParticle_XPL *Explosion = new CParticle_XPL(XB, YB, MOVE_DOWN, EXPLOSION, "boom_02");

            Explosion->particleTexture = anim_filename;
            Explosion->W2 = 64;
            Explosion->H2 = 64;
            Explosion->Width = this->Width;
            Explosion->Height = this->Height;
            Explosion->OnInit();

            CEntity::EntityList.push_back(Explosion);


            /// create medal reward
            float x = EnemyGetX() + 75;
            float y = EnemyGetY() + 75;
            float r = 15;

            MedalHonor = new CMedal(x, y, 1, r, "powerup_02", ENTITY_FLAG_ENEMY_S, BEZIER);

            MedalHonor->entityTexture = "Icon3";
            MedalHonor->Width = (100 * OVERALL_RATIO);
            MedalHonor->Height = (100 * OVERALL_RATIO);
            MedalHonor->OnInit();

            CEntity::EntityList.push_back(MedalHonor);



            /// remove enemy entity from std::map
            std::map<int, CEntity *>::iterator iter;
            if (CEntity::TargetEnemyMap.find(ID) != CEntity::TargetEnemyMap.end()) {
                SDL_Log("enemysx EntityDel() ID %d erased from map", ID);
                iter = CEntity::TargetEnemyMap.find(ID);
                CEntity::TargetEnemyMap.erase(iter);
            }


        }

        this->Dead = true;

    }

    return true;


}


void CEnemySX::OnDeleteEnemy() {



}


void CEnemySX::EntityDEL() {

    //SDL_Log("EnemySX::EntityDEL()");

    CEntity::EntityDEL();

/*
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead)
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

    //SDL_Log("EntityListSize CEnemySX after iterator %d", EntityList.size());
*/



}


int CEnemySX::EnemyGetX() {

    return this->X;
}

int CEnemySX::EnemyGetY() {

    return this->Y;
}

int CEnemySX::EnemyGetMoving() {

    return this->Move;

}