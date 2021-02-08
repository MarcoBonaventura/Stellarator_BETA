#include "CEnemySX_move.h"
#include "CPlayer.h"
#include "CPlayerStat.h"
#include "CParticle_XPL.h"
#include "CAppStateGame.h"


#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <random>


int CEnemySX_move::shoted       = 0;
int CEnemySX_move::X1           = 0;
int CEnemySX_move::Y1           = 0;

CEnemySX_move::CEnemySX_move(int Xe, int Ye, eMove moving) {

    X = Xe;
    Y = Ye;

	X2 = 0;
	animFrame = 0;
    stamina = 25;

	Type = ENTITY_TYPE_ENEMY;

	MaxSpeedX = MaxSpeed = 9 * OVERALL_SPEED_RATIO;
	MinSpeedX = 3 * OVERALL_SPEED_RATIO;
	slowDown = 0.1;
	EnemyLimit.y = Y;

    boom = true;
	triggerFIRE = 0;

    AnimState = 0;

    position.X = EnemyGetX();
    position.Y = EnemyGetY();


    alpha   = 4.7f;
    ray     = 4.0f;

    MoveRight = false;
    MoveLeft  = true;
    MoveDown  = false;
    MoveUp    = false;

    Move = ENTmoving = moving;
    motion = moving;

    OnInit();

	counter = 0;
    temp_ct = counter;

    SDL_Log("EnemySXmove() ID: %d", this->ID);

}

CEnemySX_move::~CEnemySX_move() {



}


bool CEnemySX_move::OnLoad(char* File, int Width, int Height, int MaxFrames) {

    CEnemySX::OnLoad(File, Width, Height, MaxFrames);

	return true;

}


void CEnemySX_move::OnInit() {

    CEnemySX::OnInit();

    //Initialize colliders relative to position
	shiftColliders();


}


void CEnemySX_move::shiftColliders() {

    CEnemySX::shiftColliders();

}

void CEnemySX_move::OnLoop() {

    OnMove();
    shiftColliders();
    CollisionLoop();

    //if (MaxSpeed == 0) CollisionLoop();

    int LimitX = EnemyGetX();
    int LimitY = EnemyGetY();
    switch (Move)
    {
        case MOVE_DOWN:
            if (LimitY > WHEIGHT)
            {
                this->Dead = true;
            }
            break;

        case MOVE_DX:
            if (LimitX > WWIDTH)
            {
                this->Dead = true;
            }
            if (this->X > WWIDTH * 0.65)
            {
                if (boom) {
                    OnFire();
                    boom = false;
                }
            }
            break;

        case MOVE_SX:
            if (LimitX < -150)
            {
                this->Dead = true;
            }
            if (this->X < WWIDTH * 0.30)
            {
                if (boom) {
                    OnFire();
                    boom = false;
                }
            }
            break;

        case ESCAPE_DX:
            if (LimitX > WWIDTH)
            {
                this->Dead = true;
            }
            if (this->X > WWIDTH * 0.65)
            {
                if (boom) {
                    OnFire();
                    boom = false;
                }
            }
            break;

        case ESCAPE_SX:
            if (LimitX < -150)
            {
                this->Dead = true;
            }
            if (this->X < WWIDTH * 0.30)
            {
                if (boom) {
                    OnFire();
                    boom = false;
                }
            }
            break;

        case PYRAMID:

            if (MaxSpeed == 0)
            {
                if (booleanFIRE())  {
                    OnFire();
                }
            }
            if (Y > WHEIGHT) this->Dead = true;
            break;

        case DIAMOND:

            if (MaxSpeed == 0){
                {
                    if (booleanFIRE()) {
                        OnFire();
                    }
                }
            }
            if (Y > WHEIGHT) this->Dead = true;
            break;

        case GRID:

            if (MaxSpeed == 0) {
                if (booleanFIRE()) {
                    OnFire();
                }
            }
            break;
    }



	//if(this->counter % 10 == 0) OnAnimate();
	this->counter++;

    if (this->stamina <= 0) this->Dead = true;

    if (this->Dead)
    {
        if (!CEntity::TargetEnemyMap.empty())
        {
            if(CEntity::TargetEnemyMap.find(this->ID) != CEntity::TargetEnemyMap.end())
            {
                std::map<int, CEntity*>::iterator iter;
                iter = CEntity::TargetEnemyMap.find(this->ID);
                CEntity::TargetEnemyMap.erase(iter);
                SDL_Log("OnLoop enemy ID %d erased from map", this->ID);
            }
        }
    }



}

void CEnemySX_move::OnAnimate() {

	CEnemySX::OnAnimate();

}


void CEnemySX_move::OnMove() {

    switch (Move)
    {
        case MOVE_DX:

            if(MaxSpeed > MinSpeedX)
            {
                if (X > WWIDTH * 0.20)
                {
                    MaxSpeed -= slowDown;
                }
            }
            else
            {
                //MaxSpeedX = 2;
            }
            //SDL_Log("MaxSpeedX %1.2f - slowDown %1.2f - Xe %d", MaxSpeedX, slowDown, Xe);
            X += MaxSpeed;

            break;

        case MOVE_SX:

            if(MaxSpeed > MinSpeedX)
            {
                if (X < WWIDTH * 0.80)
                {
                    MaxSpeed -= slowDown;
                    //if (slowDown < 0.5) slowDown += 0.05;

                }

            }
            //SDL_Log("MaxSpeedX %1.2f - slowDown %1.2f - Xe %d", MaxSpeedX, slowDown, Xe);
            X -= MaxSpeed;

            break;


        case ESCAPE_DX:

            if(MaxSpeed > MinSpeedX && X < WWIDTH * 0.50)
            {
                if (X > WWIDTH * 0.20)
                {
                    MaxSpeed -= slowDown;
                }
            }
            else
            {
                if (MaxSpeed < MaxSpeedX) MaxSpeed += slowDown;
            }

            //SDL_Log("MaxSpeedX %1.2f - slowDown %1.2f - Xe %d", MaxSpeedX, slowDown, Xe);
            X += MaxSpeed;

            break;


        case ESCAPE_SX:

            if(MaxSpeed > MinSpeedX && X > WWIDTH * 0.50)
            {
                if (X < WWIDTH * 0.80)
                {
                    MaxSpeed -= slowDown;
                }
            }
            else
            {
                if (MaxSpeed < MaxSpeedX) MaxSpeed += slowDown;
            }

            //SDL_Log("MaxSpeedX %1.2f - slowDown %1.2f - Xe %d", MaxSpeedX, slowDown, Xe);
            X -= MaxSpeed;

            break;


        case MOVE_DOWN:

            Y += 4;

            break;


        case PYRAMID:

            if(this->Y > -500 * OVERALL_SPEED_RATIO - (EnemyLimit.y)) {
                if (MaxSpeed > 0) {
                    MaxSpeed -= slowDown;
                } else MaxSpeed = 0;
            }
            this->Y += MaxSpeed;

            break;


        case DIAMOND:

            if(this->Y > (WHEIGHT * 0.15) + EnemyLimit.y) {
                if (MaxSpeed > 0) {
                    MaxSpeed -= slowDown;
                } else MaxSpeed = 0;
            }
            this->Y += MaxSpeed;

            break;

        case GRID:

            if(this->Y > (WHEIGHT * 0.15) + EnemyLimit.y) {
                if (MaxSpeed > 0) {
                    MaxSpeed -= slowDown;
                } else MaxSpeed = 0;
            }
            this->Y += MaxSpeed;

            break;

        default:

            Y += 4;
    }


    shiftColliders();

}


void CEnemySX_move::OnRender() {

    //CEnemySX::OnRender();

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
        SDL_Log("CEnemySX_move::OnRender() BAD RENDERER: %s",SDL_GetError());
    }

}


bool CEnemySX_move::canFIRE() {

    int temp_level = CAppStateGame::GetInstance()->currentLevel + 1;

    if (counter >= 200) {
        if (counter % (200 / temp_level) == 0) {
            return true;
        }
    }

    return false;

}

bool CEnemySX_move::booleanFIRE() {

    const double start = 200;
    const double stop = 400;

    int temp_level = CAppStateGame::GetInstance()->currentLevel + 1;
    //int temp_level = 10;

    if (counter >= 200) {
        if (counter >= temp_ct) {

            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> dist(start, std::nextafter(stop, DBL_MAX));

            int nowFIRE = (int) dist(mt);

            if (counter % (nowFIRE / temp_level) == 0) {

                temp_ct = counter +50;
                return true;
            }
        }
    }

    return false;

}

void CEnemySX_move::OnFire() {


    SDL_Log("ssxMOVE fire");

    switch (EnemyFireMode) {

        case NORMAL:
            {
                SDL_Point SSx;
                SSx.x = this->EnemyGetX() + 62;
                SSx.y = this->EnemyGetY() + 110;

                BulletSSX = new CBulletEnemy_S(SSx.x, SSx.y, 17, 0, "laser_07", ENTITY_FLAG_ENEMY_S);

                BulletSSX->entityTexture = "White_bullet_SSX";
                BulletSSX->Width = 28;
                BulletSSX->Height = 40;
                BulletSSX->Type = ENTITY_TYPE_BULLET_E;
                BulletSSX->Size = ENTITY_SIZE_SSX;
                BulletSSX->Flags = ENTITY_FLAG_ENEMY_S;
                BulletSSX->Dead = false;
                BulletSSX->OnInit();

                CEntity::EntityList.push_back(BulletSSX);
            }
        break;

        case SNIPER:
            {
                float px1 = EnemyGetX();
                float py1 = EnemyGetY();

                float px2 = CPlayer::PlayerGetXp() + CPlayer::PlayerStat.Width / 2;
                float py2 = CPlayer::PlayerGetYp() + CPlayer::PlayerStat.Height / 2;
                SDL_Log("player target: %1.2f - %1.2f", px2, py2);

                float DeltaX = px2 - px1;
                float DeltaY = py2 - py1;
                float m   = DeltaX / DeltaY;
                float q   =  -(m) * py1 + px1;

                for (int indexX = 0; indexX < MaxRow; indexX++)
                {
                    px1 = m * py1 + q;

                    //pathLine[indexX] = new int[2];
                    pathLine[indexX][0] = px1;
                    pathLine[indexX][1] = py1;

                    py1 += 1;

                    if (DeltaX >= WWIDTH /2)        { py1 += 2; }
                    else if (DeltaX < WWIDTH /2)    { py1 += 3; }
                    else if (DeltaX < -WWIDTH /2)   { py1 += 2; }


                    //if(indexX > 0) tempY += pathLine[indexX][0] - pathLine[indexX - 1][0];
                }

                BullEnemy = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_ENEMY_F);
                BullEnemy->W2 = 20;
                BullEnemy->H2 = 20;
                BullEnemy->Width = BullEnemy->W2 * OVERALL_BULLET_RATIO;
                BullEnemy->Height = BullEnemy->H2 * OVERALL_BULLET_RATIO;
                BullEnemy->entityTexture = "CannonBall";
                BullEnemy->OnInit();

                CEntity::EntityList.push_back(BullEnemy);

            }
            break;

        default:

            SDL_Point SSx;
            SSx.x = this->EnemyGetX() + 62;
            SSx.y = this->EnemyGetY() + 110;

            BulletSSX = new CBulletEnemy_S(SSx.x, SSx.y, 17, 0, "laser_07", ENTITY_FLAG_ENEMY_S);

            BulletSSX->entityTexture = "White_bullet_SSX";
            BulletSSX->Width = 28;
            BulletSSX->Height = 40;
            BulletSSX->Type = ENTITY_TYPE_BULLET_E;
            BulletSSX->Size = ENTITY_SIZE_SSX;
            BulletSSX->Flags = ENTITY_FLAG_ENEMY_S;
            BulletSSX->Dead = false;
            BulletSSX->OnInit();

            CEntity::EntityList.push_back(BulletSSX);

    }


}

void CEnemySX_move::OnCleanup() {

    CEnemySX::OnCleanup();

}


//=============================================================================
void CEnemySX_move::CollisionLoop() {


    CEnemySX::CollisionLoop();

    /*
    for (Uint32 i = 0; i < CEntity::EntityList.size(); i++) {
        if (!CEntity::EntityList[i]) {
            continue;
        }
        if (this != CEntity::EntityList[i])
            CEntity::CheckCollision(CEntity::EntityList[i]);
    }
     */

}


bool CEnemySX_move::OnCollision(CEntity *Entity) {


    if (Entity->Type == ENTITY_TYPE_MyBULLET || Entity->Type == ENTITY_TYPE_GAMMARAY || Entity->Type == ENTITY_TYPE_PLAYER)
    {
        this->Dead = true;
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

        int XB = EnemyGetX();
        int YB = EnemyGetY();


        CParticle_XPL *Explosion = new CParticle_XPL(XB, YB, motion, EXPLOSION, "boom_02");

        Explosion->particleTexture = anim_filename;
        Explosion->W2 = 64;
        Explosion->H2 = 64;
        Explosion->Width = this->Width;
        Explosion->Height = this->Height;
        Explosion->OnInit();

        CEntity::EntityList.push_back(Explosion);

        if (!CEntity::TargetEnemyMap.empty()) {
            std::map<int, CEntity *>::iterator iter;
            if (CEntity::TargetEnemyMap.find(ID) != CEntity::TargetEnemyMap.end()) {
                SDL_Log("enemysx_move OnCollision() ID %d erased from map", ID);
                iter = CEntity::TargetEnemyMap.find(ID);
                CEntity::TargetEnemyMap.erase(iter);
            }
        }
    }

    return true;

}


std::vector<SDL_Rect>& CEnemySX_move::getColliders() {

	return mColliders;

}


void CEnemySX_move::OnDeleteEnemy() {



}


void CEnemySX_move::EntityDEL() {

    //SDL_Log("EnemySX_move::EntityDEL()");

    CEnemySX::EntityDEL();

    /*

    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead)
        {
            (*it)->OnCleanup();
            delete *it;
            it = CEntity::EntityList.erase(it);
            SDL_Log("EnemySX_move deleted");
        }
        else
        {
            it++;
        }
    }

    */

}



int CEnemySX_move::EnemyGetX() {

    return this->X;
}

int CEnemySX_move::EnemyGetY() {

    return this->Y;
}


int CEnemySX_move::GetEntityMoving() {

    return this->Move;

}

