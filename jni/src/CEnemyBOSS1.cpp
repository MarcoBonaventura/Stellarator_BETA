#include "CEnemyBOSS1.h"

#include "CPlayer.h"
#include "CPlayerStat.h"
#include "CBullet.h"
#include "CFPS.h"
#include "CMedal.h"
#include "Stringify.h"

#include "CAppStateGame.h"
#include <iostream>

#include <android/log.h>

#define  LOG_TAG "SDL/APP"


#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


int CEnemyBOSS1::damage = 10;
int CEnemyBOSS1::Xen = 300;
int CEnemyBOSS1::Yen = -900;
int CEnemyBOSS1::DeadTime = 0;
int CEnemyBOSS1::countPopup = 0;

bool CEnemyBOSS1::BossIsAlive = true;
bool CEnemyBOSS1::CannonSxIsAlive = false;

bool CAppStateGame::levelCompleted = false;




CEnemyBOSS1::CEnemyBOSS1(int x, int y, BossPath move) {

	SDL_Log("BOSS ID %d created! x: %d - y: %d", this->ID, x, y);

    /*
	filename[0] = "Bubble1"; 
	filename[1] = "Bubble2";
	filename[2] = "Bubble3";
	filename[3] = "Bubble4";
	//filename[4] = "Bubble5";
    */

    Offset = X;
    path = move;


    speed = 0;
    now = 3;
    intro = true;

    counter = 0;
    //alpha = alphaINIT;
    alpha = 4;
    alpha_inc = 15;

    alpha_channel = 255;

    X = x;
    Y = y;

    pos_A = false;
    pos_B = true;
    pos_C = false;



    timeToMove = SDL_GetTicks();
    timeToFire = 0;

    fire = 4;

    Move        = true;
    MoveRight   = false;
    MoveLeft    = false;
    MoveDown    = true;
    MoveUp      = false;

    //damage = 100;

    TimeStart = SDL_GetTicks();

    Type = ENTITY_TYPE_BOSS;
    Size = ENTITY_SIZE_BOSS;
    Flags = ENTITY_FLAG_BOSS;
    Dead = false;
    BossIsAlive = true;

    shooted = 0;
    forward = 2;
    hit = 0;
}


CEnemyBOSS1::~CEnemyBOSS1() {

}


//=============================================================================
bool CEnemyBOSS1::OnLoad(char *File, int Width, int Height) {

    if(CEntity::OnLoad(File, Width, Height) == false) {

        return false;
    }

    return true;

}


void CEnemyBOSS1::OnInit() {

    circuitBoss[0].x = 10;
    circuitBoss[0].y = 10;
    circuitBoss[1].x = WWIDTH * 0.25;
    circuitBoss[1].y = WHEIGHT * 0.1;
    circuitBoss[2].x = WWIDTH * 0.55;
    circuitBoss[2].y = WHEIGHT * 0.2;
    circuitBoss[3].x = (WWIDTH - Width) - 10;
    circuitBoss[3].y = 100;

    for (int i = 0; i < 4; i++) {
        SDL_Log("circuitBoss[%d].x = %d", i, circuitBoss[i].x);
        SDL_Log("circuitBoss[%d].y = %d", i, circuitBoss[i].y);
    }

    posA.x = 0;
    posA.y = WHEIGHT * 0.1;

    posB.x = (WWIDTH / 2) - (this->Width / 2);
    posB.y = WHEIGHT * 0.1;

    posC.x = (WWIDTH) - this->Width;
    posC.y = WHEIGHT * 0.1;

    mVelX = 0;
    mVelY = 0;

    switch (selected)
    {
        case 1:

        mColliders.resize(2);

        mColliders[0].w = 396;
        mColliders[0].h = 49;

        mColliders[1].w = 286;
        mColliders[1].h = 55;


        case 4:
            mColliders.resize(1);
            mColliders[0].w = Width;
            mColliders[0].h = Height;
            r = 0;
        break;

        case 5:
            mColliders.resize(1);
            mColliders[0].w = Width;
            mColliders[0].h = Height;
            r = 0;
        break;


    }

    for (int set = 0; set < mColliders.size(); set++)
    {
        mColliders[set].w = mColliders[set].w * OVERALL_ENEMY_RATIO;
        mColliders[set].h = mColliders[set].h * OVERALL_ENEMY_RATIO;
    }
	shiftColliders();

}

void CEnemyBOSS1::shiftColliders() {

    switch (this->selected)
    {
        case 1:
            r = 250 * OVERALL_ENEMY_RATIO;
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            r = 0;
            break;

        case 5:
            r = 0;
            break;
    }

    for (int set = 0; set < mColliders.size(); set++)
    {
        mColliders[set].x = EnemyGetX() + (Width - mColliders[set].w) /2;
        mColliders[set].y = EnemyGetY() + r;
        r += mColliders[set].h;
    }

}


//=============================================================================
void CEnemyBOSS1::OnLoop() {

    //if (alpha >= alphaSTOP) alpha = alphaINIT;

    playerX = CPlayer::PlayerStat.PlayerGetXp();
    ply_w = CPlayer::PlayerStat.Width / 2;



    OnMove();
	shiftColliders();
    CollisionLoop();

	/*
	if (!CannonSxIsAlive)
	{
        if(EnemyGetX() > 0)
        {
            //SDL_Log("BOSS OnLOOP(), CannonIsAlive == FALSE");
            CollisionLoop();
        }
    }
    */


	IA();

    



	


	/* popup->GetInstance()->OnLoop();
	
	if(damage == 90) { j = 0; BossPopup(j); }
    if(damage == 65) { j = 1; BossPopup(j); }
    if(damage == 45) { j = 2; BossPopup(j); }
    if(damage == 15) { j = 3; BossPopup(j); }
	*/

    if (AnimState > 0) AnimState = 0;


    counter++;

}


//-----------------------------------------------------------------------------
void CEnemyBOSS1::BossPopup(int j) {

    bx = EnemyGetX();
    by = EnemyGetY();

    /*
	popup->GetInstance()->OnLoad();
	popup->GetInstance()->entityTexture = Stringify::Char(filename[j]);
	popup->GetInstance()->show = true;
	popup->GetInstance()->setX(bx +310);
	popup->GetInstance()->setY(by);
	

	if (countPopup < 1)
	{
		//popup = CPopup::GetInstance();

		/*
		CApp::Logger.OnLog(__FILE__, __LINE__, "popup name: ", Stringify::Char(filename[j]));
		popup->entityTexture = Stringify::Char(filename[j]);
		popup->Xp = bx;
		popup->Yp = by;
		popup->Width = 150;
		popup->Height = 100;
		popup->Type = ENTITY_TYPE_PARTICLE;
		popup->Size = ENTITY_SIZE_PP;
		popup->Flags = ENTITY_FLAG_MAPONLY;
		popup->Expired = false;
		popup->Dead = false;
		countPopup++;

		CEntity::EntityList.push_back(popup);
		*/
	//}
//
}


//=============================================================================
bool CEnemyBOSS1::CanFire() {

    switch (path) {

        case BOSS_SEEK:
            if (EnemyGetY() >= 100) {
                CPlayer::PlayerStat.RestoreFireMode();
                return true;
            }
            else return false;

        case BOSS_ABC:
            if (!MoveDown) {
                CPlayer::PlayerStat.RestoreFireMode();
                return true;
                }
                else return false;

        case BOSS_RANDOM:

            return true;

        case BOSS_LF_RX:
            if (!Move) {
                CPlayer::PlayerStat.RestoreFireMode();
                return true;
            }
            else {
                return false;
            }

        case BOSS_CIRCUIT:
            if (!intro) {
                CPlayer::PlayerStat.RestoreFireMode();
                return true;
            } else {
                return false;
            }

        case BOSS_VANISH:
            if (!intro && !Move) {
                CPlayer::PlayerStat.RestoreFireMode();
                return true;
            } else {
                return false;
            }

            default:
                CPlayer::PlayerStat.RestoreFireMode();
                return false;

    }


}



//=============================================================================
void CEnemyBOSS1::OnMove() {

	Xen = X;
	Yen = Y;


    switch (path) {

        case BOSS_SEEK: {

            if ((EnemyGetX() + (Width / 2)) < (playerX + ply_w)) {
                if (EnemyGetX() <= (WWIDTH - this->Width)) {
                    MoveLeft = false;
                    MoveRight = true;
                }
            }
            if ((EnemyGetX() + (Width / 2)) > (playerX + ply_w)) {
                if (EnemyGetX() >= (0)) {
                    MoveLeft = true;
                    MoveRight = false;
                }
            }


            if (EnemyGetY() >= (WHEIGHT * 0.1)) {
                MoveUp = true;
                MoveDown = false;
            }
            if (EnemyGetY() <= (100)) {
                MoveUp = false;
                MoveDown = true;
            }

            if (MoveLeft) {
                X -= 1;
                if (damage < 60) {
                    X -= 2;
                }
                if (damage < 30) {
                    X -= 3;
                }
                if (damage < 15) {
                    X -= 3;
                }
            }
            if (MoveRight) {
                X += 1;
                if (damage < 60) {
                    X += 2;
                }
                if (damage < 30) {
                    X += 3;
                }
                if (damage < 15) {
                    X += 3;
                }
            }

            if (MoveUp) {
                Y -= 2;
            }
            if (MoveDown) {
                Y += 2;
            }
        }
            break;

        case BOSS_ABC: {
            if (pos_A) {
                if (EnemyGetX() <=
                    posA.x) {
                    IA();
                    MoveLeft = false;
                }
                if (SDL_GetTicks() > timeToMove + 8000) {
                    pos_A = false;
                    pos_C = true;
                    MoveRight = true;
                    timeToMove = SDL_GetTicks();
                }
            }

            if (pos_B) {
                if (MoveDown || EnemyGetX() < posB.x) {
                    if (EnemyGetY() > posB.y) {
                        IA();
                        MoveDown = false;
                        MoveLeft = false;
                    }
                }
                if (SDL_GetTicks() > timeToMove + 8000) {
                    pos_C = true;
                    MoveRight = true;
                    pos_B = false;
                    timeToMove = SDL_GetTicks();
                }
            }

            if (pos_C) {
                if (EnemyGetX() > posC.x) {
                    IA();
                    MoveRight = false;
                }
                if (SDL_GetTicks() > timeToMove + 8000) {
                    pos_C = false;
                    MoveLeft = true;
                    pos_A = true;
                    timeToMove = SDL_GetTicks();
                }
            }

            if (MoveDown) Y += 4;
            if (MoveRight) X += 5;
            if (MoveLeft) X -= 5;
        }
            break;

        case BOSS_RANDOM:

            break;

        case BOSS_LF_RX:
        {
            if (pos_C) {
                if (EnemyGetX() >= WWIDTH - this->Width) {
                    MoveRight = Move = MoveDown = MoveUp = false;
                }
                if (SDL_GetTicks() > timeToMove + 10000) {
                    pos_C = false;
                    MoveLeft = MoveUp = Move = pos_A = true;
                    timeToMove = SDL_GetTicks();
                }
            }
            if (pos_A) {
                if (EnemyGetX() <= 0) {
                    MoveLeft = Move = MoveRight = MoveDown = false;
                }
                if (SDL_GetTicks() > timeToMove + 10000) {
                    MoveRight = Move = MoveUp = pos_C = true;
                    pos_A = false;
                    timeToMove = SDL_GetTicks();
                }
            }

            if (EnemyGetY() >= (WHEIGHT * 0.1)) {
                    MoveUp = true;
                    MoveDown = false;
             }

            if (EnemyGetY() <= (100)) {
                MoveUp = false;
                MoveDown = true;
            }

            if (MoveLeft) {
                X -= 2;
                if (damage < 60) {
                    X -= 3;
                }
                if (damage < 30) {
                    X -= 4;
                }
            }

            if (MoveRight) {
                X += 2;
                if (damage < 60) {
                    X += 3;
                }
                if (damage < 30) {
                    X += 4;
                }
            }

            if (MoveUp) {
                Y -= 3;
            }
            if (MoveDown) {
                Y += 3;
            }
        }
            break;

        case BOSS_CIRCUIT: {

            if (intro) {
                MoveRight = true;
            }

            if (Move && !intro) {
                if (speed <= MaxRow) {
                    if (EnemyGetX() != circuitBoss[now].x &&
                        EnemyGetY() != circuitBoss[now].y) {
                        X = escapeLine[speed][0];
                        Y = escapeLine[speed][1];
                        speed += 2;
                        //SDL_Log("Boss X %d - Y %d", EnemyGetX(), EnemyGetY());
                        SDL_Log("Boss X %d - Y %d", X, Y);
                    } else {
                        Move = false;
                        speed = 0;
                    }
                }
            }

            if (MoveRight) {
                if (EnemyGetX() < circuitBoss[0].x) {
                    X += 4;
                } else {
                    MoveRight = Move = intro =false;
                }
            }
        }
        break;

        case BOSS_VANISH: {

            if (intro) {
                MoveLeft = true;
            }

            if (MoveLeft) {
                if (EnemyGetX() > circuitBoss[3].x) {
                    X -= 4;
                } else {
                    MoveLeft = Move = intro = false;
                }
            }

            if (Move) {

                alpha_channel -= 5;
                SDL_Log("Move = true : alpha_channel %1.2f", alpha_channel);
                if (alpha_channel <= 0) {

                    X = circuitBoss[now].x;
                    Y = circuitBoss[now].y;
                    alpha_channel = 0;
                    Move = false;
                }
            } else {
                if (alpha_channel < 255) {
                    alpha_channel += 5;
                    SDL_Log("Move = false : alpha_channel %1.2f", alpha_channel);
                }
            }

        }
            break;


    }

    //OnAnimate();
	    
}


void CEnemyBOSS1::OnEscape(SDL_Point escape) {

    int tempX1 = EnemyGetX();
    int tempY1 = EnemyGetY();

    float delta_X = escape.x - tempX1;
    float delta_Y = escape.y - tempY1;
    float mm = delta_X / delta_Y;
    float qq = -(mm) * tempY1 + tempX1;


    for (int index = 0; index < MaxRow; index++) {

        tempX1 = mm * tempY1 + qq;

        escapeLine[index][0] = tempX1;
        escapeLine[index][1] = tempY1;

        if (EnemyGetY() < escape.y) tempY1 += 1;
        if (EnemyGetY() > escape.y) tempY1 -= 1;

    }


}

void CEnemyBOSS1::OnVanish() {




}

//=============================================================================
void CEnemyBOSS1::OnAnimate() {




}


//=============================================================================
void CEnemyBOSS1::OnRender() {

    if (entityRenderer)
    {
        TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, W2 * AnimState, 0, W2, H2, alpha_channel);
    }
    else
    {
        //CApp::Logger.OnLog( __FILE__, __LINE__, "bad Renderer", "");
    }

}


//=============================================================================
void CEnemyBOSS1::OnCleanup() {


}



//=============================================================================
void CEnemyBOSS1::IA() {

    switch (path) {

        case BOSS_SEEK:

            if (CanFire()) {
                int deltaX;
                if (EnemyGetX() < playerX) {
                    deltaX = (playerX + (ply_w / 2)) - (EnemyGetX() + (Width / 2));
                } else {
                    deltaX = (EnemyGetX() + (Width / 2)) - (playerX + (ply_w / 2));
                }

                if (EnemyGetX() > 0) {
                    if ((deltaX > -200 && deltaX < 200)) {
                        if (CAppStateGame::countLoop % 20 == 0) {
                            OnCaga();
                            shooted++;
                        }
                    } else {
                        if (damage <= 100 && damage > 60) {
                            if (CAppStateGame::countLoop % 40 == 0) OnFire();
                        }
                        if (damage <= 60 && damage > 30) {
                            if (CAppStateGame::countLoop % 30 == 0) OnFire();
                        }
                        if (damage <= 30 && damage > 15) {
                            if (CAppStateGame::countLoop % 25 == 0) OnFire();
                        }
                        if (damage <= 15) {
                            if (CAppStateGame::countLoop % 20 == 0) OnFire();
                        }
                    }
                }
            }
            break;

        case BOSS_ABC:

            if (CanFire()) {
                switch (selected) {

                    case 1: {

                        if (!MoveLeft && !MoveRight) {
                            if (damage <= 100 && damage > 60) {
                                if (CAppStateGame::countLoop % 35 == 0) OnFire();
                            }
                            if (damage <= 60 && damage > 30) {
                                if (CAppStateGame::countLoop % 30 == 0) OnFire();
                            }
                            if (damage <= 30 && damage > 15) {
                                if (CAppStateGame::countLoop % 25 == 0) OnFire();
                            }
                            if (damage <= 15) {
                                if (CAppStateGame::countLoop % 20 == 0) OnFire();
                            }
                        }
                        else if (MoveLeft || MoveRight) {
                            if (CAppStateGame::countLoop % 20 == 0) {
                                OnCaga();
                            }
                        }
                    }
                    break;

                    case 2:
                        break;

                    case 3: {

                        if (!MoveLeft && !MoveRight) {
                            if (damage <= 100 && damage > 60) {
                                if (CAppStateGame::countLoop % 35 == 0) OnCaga();
                            }
                            if (damage <= 60 && damage > 30) {
                                if (CAppStateGame::countLoop % 30 == 0) OnCaga();
                            }
                            if (damage <= 30 && damage > 15) {
                                if (CAppStateGame::countLoop % 25 == 0) OnCaga();
                            }
                            if (damage <= 15) {
                                if (CAppStateGame::countLoop % 20 == 0) OnCaga();
                            }
                        } else if (MoveLeft || MoveRight) {
                            if (CAppStateGame::countLoop % 20 == 0) {
                                OnFire();
                            }
                        }
                    }
                        break;

                    case 4: {
                        if (!Move) {
                            if (damage <= 100 && damage > 60) {
                                if (CAppStateGame::countLoop % 35 == 0) OnCaga();
                            }
                            if (damage <= 60 && damage > 30) {
                                if (CAppStateGame::countLoop % 30 == 0) OnCaga();
                            }
                            if (damage <= 30 && damage > 15) {
                                if (CAppStateGame::countLoop % 25 == 0) OnCaga();
                            }
                            if (damage <= 15) {
                                if (CAppStateGame::countLoop % 20 == 0) OnCaga();
                            }
                        } else if (MoveLeft || MoveRight) {
                            if (CAppStateGame::countLoop % 40 == 0) {
                                OnCaga2();
                            }
                        }

                    }

                }
            }
            break;

        case BOSS_RANDOM:

            break;

        case BOSS_LF_RX: {

            if (CanFire()) {
                if (!MoveLeft && !MoveRight) {
                    if (damage <= 100 && damage > 60) {
                        if (CAppStateGame::countLoop % 60 == 0) {
                            OnFire2();
                            forward = 2;
                        }
                    }
                    if (damage <= 60 && damage > 30) {
                        if (CAppStateGame::countLoop % 50 == 0) {
                            OnFire2();
                            forward = 3;
                            alpha_inc = 12;
                        }
                    }
                    if (damage <= 30 && damage > 15) {
                        if (CAppStateGame::countLoop % 30 == 0) {
                            OnFire2();
                            forward = 4;
                            alpha_inc = 10;
                        }
                    }
                    if (damage <= 15) {
                        if (CAppStateGame::countLoop % 30 == 0) {
                            OnFire2();
                            forward = 5;
                            alpha_inc = 8;
                        }
                    }
                } else if (MoveLeft || MoveRight) {

                }
            }
        }
            break;


        case BOSS_CIRCUIT: {

            if (CanFire()) {
                if (!Move) {
                    if (damage <= 100 && damage > 60) {
                        if (CAppStateGame::countLoop % 35 == 0) OnCaga();
                    }
                    if (damage <= 60 && damage > 30) {
                        if (CAppStateGame::countLoop % 30 == 0) OnCaga();
                    }
                    if (damage <= 30 && damage > 15) {
                        if (CAppStateGame::countLoop % 25 == 0) OnCaga();
                    }
                    if (damage <= 15) {
                        if (CAppStateGame::countLoop % 20 == 0) OnCaga();
                    }
                } else if (Move && !intro) {
                    if (CAppStateGame::countLoop % 40 == 0) {
                        OnCaga2();
                    }
                }

            }
        }
        break;

        case BOSS_VANISH: {

            if (CanFire()) {
                if (!Move) {
                    //if (counter > timeToFire + 50) {
                        if (shooted < 10) {
                            OnFire();
                            shooted++;
                        }
                        //shooted = 0;
                    //}
                    //timeToFire = counter;
                }
            }

        }
        break;

        

    }



}



//=============================================================================
void CEnemyBOSS1::OnFire() {

    if (!Dead)
    {

        switch (selected) {

            case 1: {

                px1 = EnemyGetX() + 209 * OVERALL_ENEMY_RATIO;
                py1 = EnemyGetY() + 192 * OVERALL_ENEMY_RATIO;

                px2 = CPlayer::PlayerStat.PlayerGetXp() + CPlayer::PlayerStat.Width / 2;
                py2 = CPlayer::PlayerStat.PlayerGetYp() + CPlayer::PlayerStat.Height / 2;

                DeltaX = px2 - px1;
                DeltaY = py2 - py1;
                m = DeltaX / DeltaY;
                q = -(m) * py1 + px1;

                for (int indexX = 0; indexX < MaxRow; indexX++) {
                    px1 = m * py1 + q;

                    pathLine[indexX][0] = px1;
                    pathLine[indexX][1] = py1;

                    if (path == BOSS_LF_RX) py1 += 2;
                    if (path == BOSS_ABC)   py1 += 1;

                    if (DeltaX >= WWIDTH / 2) { py1 += 3; }
                    else if (DeltaX < WWIDTH / 2) { py1 += 4; }
                    else if (DeltaX < -WWIDTH / 2) { py1 += 3; }

                }

                BullEnemyBoss = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_BOSS);

                BullEnemyBoss->entityTexture = "GreenSpinperfect";
                BullEnemyBoss->W2 = 80;
                BullEnemyBoss->H2 = 80;
                BullEnemyBoss->Width = BullEnemyBoss->W2 * OVERALL_ENEMY_RATIO;
                BullEnemyBoss->Height = BullEnemyBoss->H2 * OVERALL_ENEMY_RATIO;
                BullEnemyBoss->OnInit();

                CEntity::EntityList.push_back(BullEnemyBoss);

            }
            break;

            case 2:
                break;

            case 3: {

                px1 = EnemyGetX() + 248 * OVERALL_ENEMY_RATIO;
                py1 = EnemyGetY() + 205 * OVERALL_ENEMY_RATIO;

                px2 = CPlayer::PlayerStat.PlayerGetXp() + CPlayer::PlayerStat.Width / 2;
                py2 = CPlayer::PlayerStat.PlayerGetYp() + CPlayer::PlayerStat.Height / 2;

                DeltaX = px2 - px1;
                DeltaY = py2 - py1;
                m = DeltaX / DeltaY;
                q = -(m) * py1 + px1;

                for (int indexX = 0; indexX < MaxRow; indexX++) {
                    px1 = m * py1 + q;

                    pathLine[indexX][0] = px1;
                    pathLine[indexX][1] = py1;

                    if (path == BOSS_LF_RX) py1 += 2;
                    if (path == BOSS_ABC)   py1 += 1;

                    if (DeltaX >= WWIDTH / 2) { py1 += 3; }
                    else if (DeltaX < WWIDTH / 2) { py1 += 4; }
                    else if (DeltaX < -WWIDTH / 2) { py1 += 3; }

                }

                BullEnemyBoss = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_BOSS);

                BullEnemyBoss->entityTexture = "Boss_Ball_Green";
                BullEnemyBoss->W2 = 30;
                BullEnemyBoss->H2 = 30;
                BullEnemyBoss->Width = BullEnemyBoss->W2 * OVERALL_ENEMY_RATIO;
                BullEnemyBoss->Height = BullEnemyBoss->H2 * OVERALL_ENEMY_RATIO;
                BullEnemyBoss->OnInit();

                CEntity::EntityList.push_back(BullEnemyBoss);

            }
            break;

            case 4: {

            }
            break;

            case 5: {

                muzzle = "GreenBlast__anim_enemy";
                SDL_Point pnt_muzzle_sx;
                SDL_Point pnt_muzzle_dx;
                int MuzzleW = 89;
                int MuzzleH = 90;

                /// sx bullet
                pnt_muzzle_sx.x = 154 * OVERALL_ENEMY_RATIO;
                pnt_muzzle_sx.y = 404 * OVERALL_ENEMY_RATIO;

                CParticle_Smoke *PlayerMuzzleSX = new CParticle_Smoke(muzzle, muzzle,
                                                                      MuzzleW * OVERALL_ENEMY_RATIO,
                                                                      MuzzleH * OVERALL_ENEMY_RATIO,
                                                                      MuzzleW, MuzzleH,
                                                                      pnt_muzzle_sx, 4,
                                                                      this->ID);

                CEntity::EntityList.push_back(PlayerMuzzleSX);

                px1 = EnemyGetX() + 184 * OVERALL_ENEMY_RATIO;
                py1 = EnemyGetY() + 399 * OVERALL_ENEMY_RATIO;

                px2 = CPlayer::PlayerStat.PlayerGetXp() + CPlayer::PlayerStat.Width / 2;
                py2 = CPlayer::PlayerStat.PlayerGetYp() + CPlayer::PlayerStat.Height / 2;

                DeltaX = px2 - px1;
                DeltaY = py2 - py1;
                m = DeltaX / DeltaY;
                q = -(m) * py1 + px1;

                for (int indexX = 0; indexX < MaxRow; indexX++) {

                    px1 = m * py1 + q;
                    pathLine[indexX][0] = px1;
                    pathLine[indexX][1] = py1;

                    if (DeltaX >= WWIDTH / 2) { py1 += 3; }
                    else if (DeltaX < WWIDTH / 2) { py1 += 4; }
                    else if (DeltaX < -WWIDTH / 2) { py1 += 3; }

                }

                BullEnemyBoss = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_BOSS);

                BullEnemyBoss->entityTexture = "Boss_Ball_Green";
                BullEnemyBoss->W2 = 30;
                BullEnemyBoss->H2 = 30;
                BullEnemyBoss->Width = BullEnemyBoss->W2 * OVERALL_ENEMY_RATIO;
                BullEnemyBoss->Height = BullEnemyBoss->H2 * OVERALL_ENEMY_RATIO;
                BullEnemyBoss->OnInit();


                /// rx bullet
                pnt_muzzle_dx.x = 254 * OVERALL_ENEMY_RATIO;
                pnt_muzzle_dx.y = 404 * OVERALL_ENEMY_RATIO;

                CParticle_Smoke *PlayerMuzzleDX = new CParticle_Smoke(muzzle, muzzle,
                                                                      MuzzleW * OVERALL_ENEMY_RATIO,
                                                                      MuzzleH * OVERALL_ENEMY_RATIO,
                                                                      MuzzleW, MuzzleH,
                                                                      pnt_muzzle_dx, 4,
                                                                      this->ID);

                CEntity::EntityList.push_back(PlayerMuzzleDX);

                px1b = EnemyGetX() + 286 * OVERALL_ENEMY_RATIO;
                py1b = EnemyGetY() + 399 * OVERALL_ENEMY_RATIO;

                DeltaX = px2 - px1b;
                DeltaY = py2 - py1b;
                m = DeltaX / DeltaY;
                q = -(m) * py1b + px1b;

                for (int indexX = 0; indexX < MaxRow; indexX++) {

                    px1b = m * py1b + q;
                    pathLine2[indexX][0] = px1b;
                    pathLine2[indexX][1] = py1b;

                    if (DeltaX >= WWIDTH / 2) { py1b += 3; }
                    else if (DeltaX < WWIDTH / 2) { py1b += 4; }
                    else if (DeltaX < -WWIDTH / 2) { py1b += 3; }

                }

                BullEnemyBoss2 = new CBulletEnemy(px1b, py1b, pathLine2, "laser_06", ENTITY_FLAG_BOSS);

                BullEnemyBoss2->entityTexture = "Boss_Ball_Green";
                BullEnemyBoss2->W2 = 30;
                BullEnemyBoss2->H2 = 30;
                BullEnemyBoss2->Width = BullEnemyBoss2->W2 * OVERALL_ENEMY_RATIO;
                BullEnemyBoss2->Height = BullEnemyBoss2->H2 * OVERALL_ENEMY_RATIO;
                BullEnemyBoss2->OnInit();

                CEntity::EntityList.push_back(BullEnemyBoss);
                CEntity::EntityList.push_back(BullEnemyBoss2);

            }
            break;



        }







    }


}

//=============================================================================
void CEnemyBOSS1::OnFire2() {

    if (!Dead) {

        switch (selected) {

            case 1: {




            }
            break;

            case 2: {

            }
            break;

            case 3: {

                if (pos_C) alpha = 80;
                else if (pos_A) alpha = 100;

                for (int b = 0; b < 4; b++)
                {
                    px1 = EnemyGetX() + 209 * OVERALL_ENEMY_RATIO;
                    py1 = EnemyGetY() + 192 * OVERALL_ENEMY_RATIO;
                    pathLine[0][0] = px1;
                    pathLine[0][1] = py1;

                    SDL_Log("alpha %1.3f", alpha);

                    for (int indexX = 1; indexX < MaxRow; indexX++)
                    {
                        pathLine[indexX][0] =
                                pathLine[indexX - 1][0] + (cos(alpha * (PIG) / 180) * forward * OVERALL_SPEED_RATIO);
                        pathLine[indexX][1] =
                                pathLine[indexX - 1][1] + (sin(alpha * (PIG) / 180) * forward * OVERALL_SPEED_RATIO);
                        //SDL_Log("boss bullet x: %1.3f - y: %1.3f", pathLine[indexX][0],
                        //pathLine[indexX][1]);
                    }

                    BullEnemyBoss = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_BOSS);

                    BullEnemyBoss->entityTexture = "BlueBall__flash";
                    BullEnemyBoss->W2 = 56;
                    BullEnemyBoss->H2 = 56;
                    BullEnemyBoss->Width = BullEnemyBoss->W2 * OVERALL_ENEMY_RATIO;
                    BullEnemyBoss->Height = BullEnemyBoss->H2 * OVERALL_ENEMY_RATIO;
                    BullEnemyBoss->OnInit();

                    CEntity::EntityList.push_back(BullEnemyBoss);

                    if (pos_C) alpha += alpha_inc;
                    else if (pos_A) alpha -= alpha_inc;
                }

            }
            break;

            case 4: {



            }
            break;


            case 5: {


            }
                break;


        }



    }

}


//=============================================================================
void CEnemyBOSS1::OnCaga() {

    muzzle = "OrangeBlast__anim_enemy";
    SDL_Point pnt_muzzle_sx;
    SDL_Point pnt_muzzle_dx;
    int MuzzleW = 89;
    int MuzzleH = 90;

    switch (path) {

        case BOSS_SEEK:
            {
            if (shooted > 1) shooted = 0;
            //SDL_Log("BOSS new shooted %d", shooted);


            int MuzzleW = 89;
            int MuzzleH = 90;

            if (shooted == 0) {
                pnt_muzzle_sx.x = 183 * OVERALL_ENEMY_RATIO;
                pnt_muzzle_sx.y = 323 * OVERALL_ENEMY_RATIO;

                CParticle_Smoke *PlayerMuzzleSX = new CParticle_Smoke(muzzle, muzzle,
                                                                      MuzzleW * OVERALL_ENEMY_RATIO,
                                                                      MuzzleH * OVERALL_ENEMY_RATIO,
                                                                      MuzzleW, MuzzleH,
                                                                      pnt_muzzle_sx, 4,
                                                                      this->ID);

                CEntity::EntityList.push_back(PlayerMuzzleSX);

                cx1 = EnemyGetX() + 200 * OVERALL_ENEMY_RATIO;
                cy1 = EnemyGetY() + 313 * OVERALL_ENEMY_RATIO;
            } else if (shooted == 1) {
                pnt_muzzle_dx.x = 225 * OVERALL_ENEMY_RATIO;
                pnt_muzzle_dx.y = 323 * OVERALL_ENEMY_RATIO;

                CParticle_Smoke *PlayerMuzzleDX = new CParticle_Smoke(muzzle, muzzle,
                                                                      MuzzleW * OVERALL_ENEMY_RATIO,
                                                                      MuzzleH * OVERALL_ENEMY_RATIO,
                                                                      MuzzleW, MuzzleH,
                                                                      pnt_muzzle_dx, 4,
                                                                      this->ID);
                CEntity::EntityList.push_back(PlayerMuzzleDX);

                cx1 = EnemyGetX() + 242 * OVERALL_ENEMY_RATIO;
                cy1 = EnemyGetY() + 313 * OVERALL_ENEMY_RATIO;
            }

            BullEnemyBossCaga = new CBulletBOSS1(cx1, cy1, "laser_07", ENTITY_FLAG_BOSS);

            BullEnemyBossCaga->entityTexture = "Boss_bullet_yellow";
            BullEnemyBossCaga->W2 = 75;
            BullEnemyBossCaga->H2 = 100;
            BullEnemyBossCaga->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
            BullEnemyBossCaga->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
            BullEnemyBossCaga->Move = NONE;
            BullEnemyBossCaga->OnInit();

            CEntity::EntityList.push_back(BullEnemyBossCaga);
            }
            break;

        case BOSS_ABC:
            {
                switch (selected) {

                    case 1: {

                        cx1 = EnemyGetX() + 23 * OVERALL_ENEMY_RATIO;
                        cy1 = EnemyGetY() + 114 * OVERALL_ENEMY_RATIO;

                        cx2 = EnemyGetX() + 403 * OVERALL_ENEMY_RATIO;
                        cy2 = EnemyGetY() + 114 * OVERALL_ENEMY_RATIO;


                        BullEnemyBossCaga = new CBulletBOSS1(cx1, cy1, "laser_07",
                                                             ENTITY_FLAG_BOSS);

                        BullEnemyBossCaga->entityTexture = "Enemy_Laser_red";
                        BullEnemyBossCaga->W2 = 45;
                        BullEnemyBossCaga->H2 = 159;
                        BullEnemyBossCaga->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga->OnInit();

                        CEntity::EntityList.push_back(BullEnemyBossCaga);

                        BullEnemyBossCaga2 = new CBulletBOSS1(cx2, cy2, "laser_07",
                                                              ENTITY_FLAG_BOSS);

                        BullEnemyBossCaga2->entityTexture = "Enemy_Laser_red";
                        BullEnemyBossCaga2->W2 = 45;
                        BullEnemyBossCaga2->H2 = 159;
                        BullEnemyBossCaga2->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga2->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga2->Move = NONE;
                        BullEnemyBossCaga2->OnInit();

                        CEntity::EntityList.push_back(BullEnemyBossCaga2);
                    }
                        break;

                    case 2: {

                        cx1 = EnemyGetX() + 23 * OVERALL_ENEMY_RATIO;
                        cy1 = EnemyGetY() + 114 * OVERALL_ENEMY_RATIO;

                        cx2 = EnemyGetX() + 403 * OVERALL_ENEMY_RATIO;
                        cy2 = EnemyGetY() + 114 * OVERALL_ENEMY_RATIO;


                        BullEnemyBossCaga = new CBulletBOSS1(cx1, cy1, "laser_07", ENTITY_FLAG_BOSS);

                        BullEnemyBossCaga->entityTexture = "Enemy_Laser_red";
                        BullEnemyBossCaga->W2 = 45;
                        BullEnemyBossCaga->H2 = 159;
                        BullEnemyBossCaga->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga->OnInit();

                        CEntity::EntityList.push_back(BullEnemyBossCaga);

                        BullEnemyBossCaga2 = new CBulletBOSS1(cx2, cy2, "laser_07", ENTITY_FLAG_BOSS);

                        BullEnemyBossCaga2->entityTexture = "Enemy_Laser_red";
                        BullEnemyBossCaga2->W2 = 45;
                        BullEnemyBossCaga2->H2 = 159;
                        BullEnemyBossCaga2->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga2->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga2->OnInit();

                        CEntity::EntityList.push_back(BullEnemyBossCaga2);

                    }

                        break;

                    case 3: {

                        cx1 = EnemyGetX() + 218 * OVERALL_ENEMY_RATIO;
                        cy1 = EnemyGetY() + 274 * OVERALL_ENEMY_RATIO;

                        cx2 = EnemyGetX() + 286 * OVERALL_ENEMY_RATIO;
                        cy2 = EnemyGetY() + 274 * OVERALL_ENEMY_RATIO;


                        BullEnemyBossCaga = new CBulletBOSS1(cx1, cy1, "laser_07", ENTITY_FLAG_BOSS);

                        BullEnemyBossCaga->entityTexture = "Enemy_Bullet_Green";
                        BullEnemyBossCaga->W2 = 22;
                        BullEnemyBossCaga->H2 = 60;
                        BullEnemyBossCaga->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga->OnInit();

                        CEntity::EntityList.push_back(BullEnemyBossCaga);

                        BullEnemyBossCaga2 = new CBulletBOSS1(cx2, cy2, "laser_07", ENTITY_FLAG_BOSS);

                        BullEnemyBossCaga2->entityTexture = "Enemy_Bullet_Green";
                        BullEnemyBossCaga2->W2 = 22;
                        BullEnemyBossCaga2->H2 = 60;
                        BullEnemyBossCaga2->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga2->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
                        BullEnemyBossCaga2->OnInit();

                        CEntity::EntityList.push_back(BullEnemyBossCaga2);

                    }
                        break;

                    case 4: {



                        //if (shooted == 0) {

                            /// muzzle sx
                            pnt_muzzle_sx.x = 137 * OVERALL_ENEMY_RATIO;
                            pnt_muzzle_sx.y = 319 * OVERALL_ENEMY_RATIO;

                            CParticle_Smoke *PlayerMuzzleSX = new CParticle_Smoke(muzzle, muzzle,
                                                                                  (MuzzleW * OVERALL_ENEMY_RATIO),
                                                                                  (MuzzleH * OVERALL_ENEMY_RATIO),
                                                                                  MuzzleW, MuzzleH,
                                                                                  pnt_muzzle_sx, 4,
                                                                                  this->ID);

                            CEntity::EntityList.push_back(PlayerMuzzleSX);

                            pnt_muzzle_dx.x = 171 * OVERALL_ENEMY_RATIO;
                            pnt_muzzle_dx.y = 319 * OVERALL_ENEMY_RATIO;

                            /// muzzle dx
                            CParticle_Smoke *PlayerMuzzleDX = new CParticle_Smoke(muzzle, muzzle,
                                                                                  (MuzzleW * OVERALL_ENEMY_RATIO),
                                                                                  (MuzzleH * OVERALL_ENEMY_RATIO),
                                                                                  MuzzleW, MuzzleH,
                                                                                  pnt_muzzle_dx, 4,
                                                                                  this->ID);
                            CEntity::EntityList.push_back(PlayerMuzzleDX);

                            /// bullet sx
                            cx1 = EnemyGetX() + 177 * OVERALL_ENEMY_RATIO;
                            cy1 = EnemyGetY() + 318 * OVERALL_ENEMY_RATIO;

                            cx2 = EnemyGetX() + 210 * OVERALL_ENEMY_RATIO;
                            cy2 = EnemyGetY() + 318 * OVERALL_ENEMY_RATIO;


                            BullEnemyBossCaga = new CBulletBOSS1(cx1, cy1, "laser_07", ENTITY_FLAG_BOSS);

                            BullEnemyBossCaga->entityTexture = "Enemy_Bullet_Green";
                            BullEnemyBossCaga->W2 = 22;
                            BullEnemyBossCaga->H2 = 60;
                            BullEnemyBossCaga->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
                            BullEnemyBossCaga->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
                            BullEnemyBossCaga->Move = NONE;
                            BullEnemyBossCaga->OnInit();

                            CEntity::EntityList.push_back(BullEnemyBossCaga);

                            /// bullet dx
                            BullEnemyBossCaga2 = new CBulletBOSS1(cx2, cy2, "laser_07", ENTITY_FLAG_BOSS);

                            BullEnemyBossCaga2->entityTexture = "Enemy_Bullet_Green";
                            BullEnemyBossCaga2->W2 = 22;
                            BullEnemyBossCaga2->H2 = 60;
                            BullEnemyBossCaga2->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
                            BullEnemyBossCaga2->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
                            BullEnemyBossCaga2->Move = NONE;
                            BullEnemyBossCaga2->OnInit();

                            CEntity::EntityList.push_back(BullEnemyBossCaga2);

                    }
                    break;

                }

            }
            break;

        case BOSS_RANDOM:

            break;

        case BOSS_LF_RX:

            break;

        case BOSS_CIRCUIT:

        {

            /// muzzle sx
            pnt_muzzle_sx.x = 137 * OVERALL_ENEMY_RATIO;
            pnt_muzzle_sx.y = 319 * OVERALL_ENEMY_RATIO;

            CParticle_Smoke *PlayerMuzzleSX = new CParticle_Smoke(muzzle, muzzle,
                                                                  (MuzzleW * OVERALL_ENEMY_RATIO),
                                                                  (MuzzleH * OVERALL_ENEMY_RATIO),
                                                                  MuzzleW, MuzzleH,
                                                                  pnt_muzzle_sx, 4,
                                                                  this->ID);

            CEntity::EntityList.push_back(PlayerMuzzleSX);

            pnt_muzzle_dx.x = 171 * OVERALL_ENEMY_RATIO;
            pnt_muzzle_dx.y = 319 * OVERALL_ENEMY_RATIO;

            /// muzzle dx
            CParticle_Smoke *PlayerMuzzleDX = new CParticle_Smoke(muzzle, muzzle,
                                                                  (MuzzleW * OVERALL_ENEMY_RATIO),
                                                                  (MuzzleH * OVERALL_ENEMY_RATIO),
                                                                  MuzzleW, MuzzleH,
                                                                  pnt_muzzle_dx, 4,
                                                                  this->ID);
            CEntity::EntityList.push_back(PlayerMuzzleDX);

            /// bullet sx
            cx1 = EnemyGetX() + 177 * OVERALL_ENEMY_RATIO;
            cy1 = EnemyGetY() + 318 * OVERALL_ENEMY_RATIO;

            cx2 = EnemyGetX() + 210 * OVERALL_ENEMY_RATIO;
            cy2 = EnemyGetY() + 318 * OVERALL_ENEMY_RATIO;


            BullEnemyBossCaga = new CBulletBOSS1(cx1, cy1, "laser_07", ENTITY_FLAG_BOSS);

            BullEnemyBossCaga->entityTexture = "Enemy_Bullet_Green";
            BullEnemyBossCaga->W2 = 22;
            BullEnemyBossCaga->H2 = 60;
            BullEnemyBossCaga->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
            BullEnemyBossCaga->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
            BullEnemyBossCaga->Move = NONE;
            BullEnemyBossCaga->OnInit();

            CEntity::EntityList.push_back(BullEnemyBossCaga);

            /// bullet dx
            BullEnemyBossCaga2 = new CBulletBOSS1(cx2, cy2, "laser_07", ENTITY_FLAG_BOSS);

            BullEnemyBossCaga2->entityTexture = "Enemy_Bullet_Green";
            BullEnemyBossCaga2->W2 = 22;
            BullEnemyBossCaga2->H2 = 60;
            BullEnemyBossCaga2->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
            BullEnemyBossCaga2->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
            BullEnemyBossCaga2->Move = NONE;
            BullEnemyBossCaga2->OnInit();

            CEntity::EntityList.push_back(BullEnemyBossCaga2);

        }

            break;
    }




}



//=============================================================================
void CEnemyBOSS1::OnCaga2() {

    switch (path) {

        case BOSS_SEEK:
            break;

        case BOSS_ABC: {

            switch (selected) {

                case 1:
                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4: {

                    cx1 = EnemyGetX() + 139 * OVERALL_ENEMY_RATIO;
                    cy1 = EnemyGetY() + 205 * OVERALL_ENEMY_RATIO;

                    cx2 = EnemyGetX() + 227 * OVERALL_ENEMY_RATIO;
                    cy2 = EnemyGetY() + 205 * OVERALL_ENEMY_RATIO;


                    /// rocket SX
                    BullEnemyBossCaga = new CBulletBOSS1(cx1, cy1, "laser_07", ENTITY_FLAG_BOSS);

                    BullEnemyBossCaga->entityTexture = "Enemy_Rocket";
                    BullEnemyBossCaga->W2 = 34;
                    BullEnemyBossCaga->H2 = 94;
                    BullEnemyBossCaga->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
                    BullEnemyBossCaga->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
                    BullEnemyBossCaga->Move = SNAKE;
                    BullEnemyBossCaga->MoveLeft = true;
                    BullEnemyBossCaga->OnInit();

                    CEntity::EntityList.push_back(BullEnemyBossCaga);

                    /// rocket DX
                    BullEnemyBossCaga2 = new CBulletBOSS1(cx2, cy2, "laser_07", ENTITY_FLAG_BOSS);

                    BullEnemyBossCaga2->entityTexture = "Enemy_Rocket";
                    BullEnemyBossCaga2->W2 = 34;
                    BullEnemyBossCaga2->H2 = 94;
                    BullEnemyBossCaga2->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
                    BullEnemyBossCaga2->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
                    BullEnemyBossCaga2->Move = SNAKE;
                    BullEnemyBossCaga2->MoveRight = true;
                    BullEnemyBossCaga2->OnInit();

                    CEntity::EntityList.push_back(BullEnemyBossCaga2);

                }
                break;

            }
        }

            break;

        case BOSS_LF_RX:
            break;

        case BOSS_RANDOM:
            break;

        case BOSS_CIRCUIT: {

            cx1 = EnemyGetX() + 139 * OVERALL_ENEMY_RATIO;
            cy1 = EnemyGetY() + 205 * OVERALL_ENEMY_RATIO;

            cx2 = EnemyGetX() + 227 * OVERALL_ENEMY_RATIO;
            cy2 = EnemyGetY() + 205 * OVERALL_ENEMY_RATIO;


            /// rocket SX
            BullEnemyBossCaga = new CBulletBOSS1(cx1, cy1, "laser_07", ENTITY_FLAG_BOSS);

            BullEnemyBossCaga->entityTexture = "Enemy_Rocket";
            BullEnemyBossCaga->W2 = 34;
            BullEnemyBossCaga->H2 = 94;
            BullEnemyBossCaga->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
            BullEnemyBossCaga->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
            BullEnemyBossCaga->Move = SNAKE;
            BullEnemyBossCaga->MoveLeft = true;
            BullEnemyBossCaga->OnInit();

            CEntity::EntityList.push_back(BullEnemyBossCaga);

            /// rocket DX
            BullEnemyBossCaga2 = new CBulletBOSS1(cx2, cy2, "laser_07", ENTITY_FLAG_BOSS);

            BullEnemyBossCaga2->entityTexture = "Enemy_Rocket";
            BullEnemyBossCaga2->W2 = 34;
            BullEnemyBossCaga2->H2 = 94;
            BullEnemyBossCaga2->Width = BullEnemyBossCaga->W2 * OVERALL_BULLET_RATIO;
            BullEnemyBossCaga2->Height = BullEnemyBossCaga->H2 * OVERALL_BULLET_RATIO;
            BullEnemyBossCaga2->Move = SNAKE;
            BullEnemyBossCaga2->MoveRight = true;
            BullEnemyBossCaga2->OnInit();

            CEntity::EntityList.push_back(BullEnemyBossCaga2);

        }
            break;

    }


}


//=============================================================================
bool CEnemyBOSS1::OnCollision(CEntity *Entity) {

    if (CanFire())
    {

        if (!CPlayer::PlayerStat.Dead)
        {

            hit++;
            //SDL_Log("BOSS OnCollision() CannonIsAlive: %s", CCannon::CannonIsAlive);
            if (Entity->Flags == ENTITY_FLAG_GAMMARAY) {
                damage -= 1;
            }

            switch (Entity->Size) {

                case ENTITY_SIZE_PB:
                    damage -= 2;
                    break;

                case ENTITY_SIZE_MM:
                    damage -= 3;
                    break;

                case ENTITY_SIZE_BOMB:
                    damage -=4;
                    break;
            }

            if (path == BOSS_CIRCUIT) {
                if (Move) {
                    damage += 1;
                }
            }

            AnimState = 1;

            if (damage <= 0) {
                LOGD("Boss dead, level completed!");
                BossIsAlive = false;
                CAppStateGame::levelCompleted = true;
                CAppStateGame::BossTimeDeath = SDL_GetTicks();
                Dead = true;

                CPlayer::PlayerStat.PlayerScore += 2000;
                CPlayer::PlayerStat.setFireMode(CPlayer::FIRE_NONE);


                int XB = EnemyGetX();
                int YB = EnemyGetY();

                CParticle_PlayerXPL *PlayerExplosion = new CParticle_PlayerXPL(XB, YB,
                                                                               "boom_big_01",
                                                                               ENTITY_FLAG_BOSS);

                PlayerExplosion->W2 = 128;
                PlayerExplosion->H2 = 128;
                PlayerExplosion->Width = this->Width / 2;
                PlayerExplosion->Height = this->Height / 2;
                PlayerExplosion->particleTexture = "Player_EXPL";

                CEntity::EntityList.push_back(PlayerExplosion);


                int r = 35;
                //generate medal
                for (int h = 0; h < 10; h++) {
                    //int x = XB +113;
                    //int y = YB +55;
                    //LOGD("Boss Medal...");
                    MedalBoss = new CMedal(XB + (Width / 2), YB + (Height / 2), 5, r, "powerup_01",
                                           ENTITY_FLAG_BOSS, BEZIER_BOSS);
                    //LOGD("Boss Medal created");

                    MedalBoss->entityTexture = "IconX";
                    MedalBoss->Width = 188 * OVERALL_RATIO;
                    MedalBoss->Height = 179 * OVERALL_RATIO;
                    MedalBoss->Type = ENTITY_TYPE_MEDAL;
                    MedalBoss->Size = ENTITY_SIZE_MEDAL;
                    MedalBoss->OnInit();

                    CEntity::EntityList.push_back(MedalBoss);
                    XB += 25;
                    YB += 15;
                    r += 15;
                }
            }


            /// Boss escape!
            switch (path) {

                case BOSS_CIRCUIT: {

                    if (!Move) {
                        int sel;
                        /*
                        const double start = 0;
                        const double stop = 3;

                        do {
                            std::random_device rd;
                            std::mt19937 mt(rd());
                            std::uniform_real_distribution<double> dist(start,
                                                                        std::nextafter(stop, DBL_MAX));

                            sel = (int) dist(mt);
                            SDL_Log("next Boss moves: %d", sel);
                        } while (sel != now);
                        */
                        if (now == 0) sel = 2;
                        if (now == 1) sel = 0;
                        if (now == 2) sel = 3;
                        if (now == 3) sel = 1;

                        OnEscape(circuitBoss[sel]);
                        now = sel;
                        Move = true;
                    }

                }
                    break;

                case BOSS_VANISH: {

                    int sel;

                    if (hit > 6) {
                        hit = 0;
                        Move = true;
                        if (now == 0) sel = 2;
                        if (now == 1) sel = 0;
                        if (now == 2) sel = 3;
                        if (now == 3) sel = 1;
                        now = sel;
                        //OnVanish();
                    }

                }
                    break;

                default:
                    break;


            }

        }
    }

    return true;

}


void CEnemyBOSS1::CollisionLoop() {

	for (Uint32 i = 0; i<CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i])
        {
            continue;
        }
        CEntity::CheckCollision(CEntity::EntityList[i]);
    }

}

std::vector<SDL_Rect>& CEnemyBOSS1::getColliders() {

	return mColliders;

}


//=============================================================================
void CEnemyBOSS1::EntityDEL() {

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
            //CEnemySX::EnemySXList.erase(it);

            for (int i=0; i<MaxRow; i++)
            {
                delete[] &pathLine[i];
            }
            delete[] &pathLine;
			SDL_Log("Boss deleted");
        }
        else
        {
            it++;
        }
    }
    */

}



//=============================================================================
int CEnemyBOSS1::EnemyGetX() {

    return this->X;
}


//=============================================================================
int CEnemyBOSS1::EnemyGetY() {

    return this->Y;
}


//=============================================================================
int CEnemyBOSS1::getXen() {

    return Xen;

}


//=============================================================================
int CEnemyBOSS1::getYen() {

    return Yen;

}
