#include "CEnemyMM.h"
#include "CPlayer.h"
#include "CPlayerStat.h"
#include "CBullet.h"
#include "CFPS.h"
#include "Stringify.h"

#include "CAppStateGame.h"

#include <iostream>



CEnemyMM::CEnemyMM(int Xe, int Ye, eMove moving) {

    CAppStateGame::count_M1++;
    CAppStateGame::count_M4++;
    CAppStateGame::count_M5++;
    CAppStateGame::count_M6++;

    X = Xe;
    Y = Ye;

    Offset = X;

    Type = ENTITY_TYPE_ENEMY;
    Size = ENTITY_SIZE_MM;


	AnimState = 0;
	counter = 0;
    motion = moving;
    check_time = 0;

    fire = 4;
    forward = 2;
    alpha_inc = 15;
    alpha_offset = 0;

    hit = 0;

    MoveLeft = MoveRight = MoveUp = pos_A = pos_C = false;
    MoveDown = true;
    degrees = alpha = 0;

    MaxSpeed = 10 * OVERALL_SPEED_RATIO;
    slowDown = 0.3;
    kAcc = 0;

    TimeStart = SDL_GetTicks();
    time_lapse = laser_time = SDL_GetTicks();

    shoted = 0;

    LaserON = false;

    SDL_Log("EnemyMM ID %d", ID);

}

CEnemyMM::~CEnemyMM() {

    CAppStateGame::count_M1--;
    CAppStateGame::count_M4--;
    CAppStateGame::count_M5--;
    CAppStateGame::count_M6--;

    SDL_Log("MM1 count: %d M4: %d - M5: %d", CAppStateGame::count_M1, CAppStateGame::count_M4, CAppStateGame::count_M5);
}


bool CEnemyMM::OnLoad(char *File, int Width, int Height) {

    if(CEntity::OnLoad(File, Width, Height) == false) {
        return false;
    }

    return true;
}



void CEnemyMM::OnInit() {

    mVelX = 0;
    mVelY = 0;

    switch (this->selected)
    {
        case 0:
            r = 20;
            mColliders.resize(15);

            mColliders[0].w = 320;
            mColliders[0].h = 17;

            mColliders[1].w = 254;
            mColliders[1].h = 106;

            mColliders[2].w = 212;
            mColliders[2].h = 52;

            mColliders[3].w = 196;
            mColliders[3].h = 20;

            mColliders[4].w = 180;
            mColliders[4].h = 12;

            mColliders[5].w = 162;
            mColliders[5].h = 10;

            mColliders[6].w = 146;
            mColliders[6].h = 7;

            mColliders[7].w = 128;
            mColliders[7].h = 6;

            mColliders[8].w = 106;
            mColliders[8].h = 6;

            mColliders[9].w = 80;
            mColliders[9].h = 5;

            mColliders[10].w = 44;
            mColliders[10].h = 6;

            mColliders[11].w = 34;
            mColliders[11].h = 6;

            mColliders[12].w = 26;
            mColliders[12].h = 4;

            mColliders[13].w = 18;
            mColliders[13].h = 3;

            mColliders[14].w = 10;
            mColliders[14].h = 3;
            break;

        case 1:

            r = 20;
            mColliders.resize(15);

            mColliders[0].w = 320;
            mColliders[0].h = 17;

            mColliders[1].w = 254;
            mColliders[1].h = 106;

            mColliders[2].w = 212;
            mColliders[2].h = 52;

            mColliders[3].w = 196;
            mColliders[3].h = 20;

            mColliders[4].w = 180;
            mColliders[4].h = 12;

            mColliders[5].w = 162;
            mColliders[5].h = 10;

            mColliders[6].w = 146;
            mColliders[6].h = 7;

            mColliders[7].w = 128;
            mColliders[7].h = 6;

            mColliders[8].w = 106;
            mColliders[8].h = 6;

            mColliders[9].w = 80;
            mColliders[9].h = 5;

            mColliders[10].w = 44;
            mColliders[10].h = 6;

            mColliders[11].w = 34;
            mColliders[11].h = 6;

            mColliders[12].w = 26;
            mColliders[12].h = 4;

            mColliders[13].w = 18;
            mColliders[13].h = 3;

            mColliders[14].w = 10;
            mColliders[14].h = 3;

            break;

        case 2:

            r = 20;
            mColliders.resize(15);

            mColliders[0].w = 320;
            mColliders[0].h = 17;

            mColliders[1].w = 254;
            mColliders[1].h = 106;

            mColliders[2].w = 212;
            mColliders[2].h = 52;

            mColliders[3].w = 196;
            mColliders[3].h = 20;

            mColliders[4].w = 180;
            mColliders[4].h = 12;

            mColliders[5].w = 162;
            mColliders[5].h = 10;

            mColliders[6].w = 146;
            mColliders[6].h = 7;

            mColliders[7].w = 128;
            mColliders[7].h = 6;

            mColliders[8].w = 106;
            mColliders[8].h = 6;

            mColliders[9].w = 80;
            mColliders[9].h = 5;

            mColliders[10].w = 44;
            mColliders[10].h = 6;

            mColliders[11].w = 34;
            mColliders[11].h = 6;

            mColliders[12].w = 26;
            mColliders[12].h = 4;

            mColliders[13].w = 18;
            mColliders[13].h = 3;

            mColliders[14].w = 10;
            mColliders[14].h = 3;

            MoveDown = MoveUp = MoveLeft = MoveRight = false;
            alpha = 90;
            alpha_inc = 3;
            if (CAppStateGame::count_M6 == 1) {
                pos_C = true;
                MoveRight = true;
            }
            else if (CAppStateGame::count_M6 == 2) {
                MoveLeft = true;
                pos_A = true;
            }

            break;

        case 3:
            break;

        case 4:

            r = 20;
            mColliders.resize(15);

            mColliders[0].w = 320;
            mColliders[0].h = 17;

            mColliders[1].w = 254;
            mColliders[1].h = 106;

            mColliders[2].w = 212;
            mColliders[2].h = 52;

            mColliders[3].w = 196;
            mColliders[3].h = 20;

            mColliders[4].w = 180;
            mColliders[4].h = 12;

            mColliders[5].w = 162;
            mColliders[5].h = 10;

            mColliders[6].w = 146;
            mColliders[6].h = 7;

            mColliders[7].w = 128;
            mColliders[7].h = 6;

            mColliders[8].w = 106;
            mColliders[8].h = 6;

            mColliders[9].w = 80;
            mColliders[9].h = 5;

            mColliders[10].w = 44;
            mColliders[10].h = 6;

            mColliders[11].w = 34;
            mColliders[11].h = 6;

            mColliders[12].w = 26;
            mColliders[12].h = 4;

            mColliders[13].w = 18;
            mColliders[13].h = 3;

            mColliders[14].w = 10;
            mColliders[14].h = 3;

            break;

        case 5:
            r = 20;
            mColliders.resize(15);

            mColliders[0].w = 320;
            mColliders[0].h = 17;

            mColliders[1].w = 254;
            mColliders[1].h = 106;

            mColliders[2].w = 212;
            mColliders[2].h = 52;

            mColliders[3].w = 196;
            mColliders[3].h = 20;

            mColliders[4].w = 180;
            mColliders[4].h = 12;

            mColliders[5].w = 162;
            mColliders[5].h = 10;

            mColliders[6].w = 146;
            mColliders[6].h = 7;

            mColliders[7].w = 128;
            mColliders[7].h = 6;

            mColliders[8].w = 106;
            mColliders[8].h = 6;

            mColliders[9].w = 80;
            mColliders[9].h = 5;

            mColliders[10].w = 44;
            mColliders[10].h = 6;

            mColliders[11].w = 34;
            mColliders[11].h = 6;

            mColliders[12].w = 26;
            mColliders[12].h = 4;

            mColliders[13].w = 18;
            mColliders[13].h = 3;

            mColliders[14].w = 10;
            mColliders[14].h = 3;

            if(CAppStateGame::count_M5 == 1) {
                MoveLeft = true;
                MoveRight = false;
            } else {
                MoveRight = true;
                MoveLeft = false;
            }

            break;


    }

    for (int set = 0; set < mColliders.size(); set++)
    {
        mColliders[set].w = mColliders[set].w * OVERALL_ENEMY_RATIO;
        mColliders[set].h = mColliders[set].h * OVERALL_ENEMY_RATIO;
    }

    shiftColliders();




}

void CEnemyMM::shiftColliders() {

    switch (this->selected)
    {
        case 0:
            r = 20 * OVERALL_ENEMY_RATIO;
            break;
        case 1:
           r = 20 * OVERALL_ENEMY_RATIO;
            break;

        case 2:
            r = 20 * OVERALL_ENEMY_RATIO;
            break;

        case 3:
            break;

        case 4:
            r = 20 * OVERALL_ENEMY_RATIO;
            break;

        case 5:
            r =20 * OVERALL_ENEMY_RATIO;
            break;
    }

    for (int set = 0; set < mColliders.size(); set++)
    {
        mColliders[set].x = EnemyGetX() + (Width - mColliders[set].w) /2;
        mColliders[set].y = EnemyGetY() + r;
        r += mColliders[set].h;
    }

}




void CEnemyMM::OnLoop() {

    OnMove();
    shiftColliders();
    CollisionLoop();

    /// ACTION LOOP
    switch (selected)
    {
        case 0:
            break;
        case 1:
            break;
        case 2:



            break;
        case 3:
            break;
        case 4:
            break;

        case 5:

            if (this->counter > 500)
            {
                MoveDown = true;
                kAcc += 0.025;
                //offsetY = 0;
            }
            break;
    }



    //if (EnemyGetY() == 20) OnFire();


    int Limit = EnemyGetY();
    if (Limit > WHEIGHT)
    {
        Dead = true;
    }


    int temp_level = CAppStateGame::GetInstance()->currentLevel + 1;

    /// FIRE LOOP
    if (CanFire())
    {
        switch (selected)
        {

            case 0: {
                if (!LaserON) {
                    time_lapse = (long)SDL_GetTicks();
                    if (time_lapse > laser_time + 3000) {
                        if (check_time < 50) {
                            SDL_SetRenderDrawColor(entityRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                            SDL_RenderDrawLine(entityRenderer, (EnemyGetX() + 150 * OVERALL_ENEMY_RATIO),
                                               (EnemyGetY() + 249 * OVERALL_ENEMY_RATIO),
                                               (EnemyGetX() + 150 * OVERALL_ENEMY_RATIO), WHEIGHT);
                            SDL_RenderPresent(entityRenderer);
                            check_time++;
                        } else {
                            OnLaser();
                            LaserON = true;
                            check_time = 0;
                        }
                    }
                }
            }
                break;

            case 1: {
                if (counter >= 200)
                {

                        float temp_xE = EnemyGetX() + 130 * OVERALL_ENEMY_RATIO;
                        float temp_yE = EnemyGetY() + 189 * OVERALL_ENEMY_RATIO;

                        float temp_xP = CPlayer::PlayerStat.PlayerGetXp() + CPlayer::PlayerStat.Width / 2;
                        float temp_yP = CPlayer::PlayerStat.PlayerGetYp() + CPlayer::PlayerStat.Height / 2;

                        float temp_xD = temp_xP - temp_xE;
                        float temp_yD = temp_yP - temp_yE;

                        float temp_m = temp_xD / temp_yD;
                        //float temp_q = temp_m * temp_yE + temp_q;

                        //SDL_Log("temp_xD %1.3f - temp_yD %1.3f - temp_m % 1.3f - degrees %1.3f", temp_xD, temp_yD, temp_m, degrees);

                        double temp_degrees = (atan((double) temp_m) * 180 / PI);

                        if (degrees < temp_degrees) degrees += 0.1;
                        else if (degrees > temp_degrees) degrees -= 0.5;

                    if (counter % (200 / temp_level) == 0) {
                        OnFire();
                    }
                }
            }
                break;

            case 2: {

                if (shoted < 3) {
                    if (counter >= 200) {
                        int _div;
                        if (temp_level >= 2) _div = (temp_level / 2) + 1;
                        if (counter % (200 / _div) == 0) {
                            OnFire();
                            alpha += alpha_offset;
                            SDL_Log("OnLoop() ALPHA %1.3f", alpha);
                            shoted++;
                        }
                    }
                }



            }
                break;

            case 3:

                break;

            case 4: /// single laser

                if (!LaserON) {
                    time_lapse = SDL_GetTicks();
                    if (time_lapse > laser_time + 3000) {
                        OnLaser();
                        LaserON = true;

                    }
                }
                break;


            case 5:

                if (counter >= 200) {
                    if (counter % (200 / temp_level) == 0) {
                        OnFire();
                    }
                }

                break;
        }
    }

    OnAnimate();

	if (kAcc < 0) kAcc = 0;

	if (!Laser->GetLaserOnOff()) {
	    LaserON = false;

	}

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
                SDL_Log("enemyMM_OnLoop() ID %d erased from map", this->ID);
            }
        }
    }

}



void CEnemyMM::OnAnimate() {

    if (AnimState == 10) AnimState = 0;
	
}



bool CEnemyMM::CanFire() {

    if (MaxSpeed == 0)
    {
        return true;
    }
    else return false;

}



void CEnemyMM::OnMove() {

    switch (selected)
    {

        case 0: {

            if (EnemyGetY() > 0) {
                if (MaxSpeed > 0) {
                    MaxSpeed -= slowDown;
                } else {
                    if (MoveDown)
                    {
                        MaxSpeed = 0;
                        MoveDown = false;
                        MoveRight = true;
                    }
                }
            }

            if (!MoveDown) {
                if (EnemyGetX() >= (WWIDTH - this->Width - 300)) {
                    MoveLeft = true;
                    MoveRight = false;
                }
                if (EnemyGetX() <= (300)) {
                    MoveLeft = false;
                    MoveRight = true;
                }
            }

            if (MoveDown) {
                Y += MaxSpeed;
            }
            if (MoveRight) {
                X += 2;
            }
            if (MoveLeft) {
                X -= 2;
            }
        }
            break;

        case 1: {

            if (this->Y > 0) {
                if (MaxSpeed > 0) {
                    MaxSpeed -= slowDown;
                } else MaxSpeed = 0;
            }
            this->Y += MaxSpeed;
        }
            break;

        case 2: {

            if (pos_A) {
                if (EnemyGetX() <= 0) {
                    MoveLeft = false;
                    MaxSpeed = 0;
                    if (SDL_GetTicks() > time_lapse + 5000) {
                        pos_A = false;
                        pos_C = MoveRight = true;
                        MaxSpeed = 10 * OVERALL_SPEED_RATIO;
                        alpha = 90;
                        alpha_offset = 5;
                        shoted = 0;
                        time_lapse = SDL_GetTicks();
                    }
                }
            }

            if (pos_C) {
                if (EnemyGetX() > WWIDTH - Width) {
                    MoveRight = false;
                    MaxSpeed = 0;
                    if (SDL_GetTicks() > time_lapse + 5000) {
                        pos_C = false;
                        pos_A = MoveLeft = true;
                        MaxSpeed = 10 * OVERALL_SPEED_RATIO;
                        alpha = 90;
                        alpha_offset = -5;
                        shoted = 0;
                        time_lapse = SDL_GetTicks();

                    }
                }
            }

            if (MoveRight) {
                this->X += MaxSpeed;
            }
            if (MoveLeft) {
                this->X -= MaxSpeed;
            }

        }

            break;

        case 3:
            break;

        case 4: {

            if (this->Y > 0) {
                if (MaxSpeed > 0) {
                    MaxSpeed -= slowDown;
                } else MaxSpeed = 0;
            }
            this->Y += MaxSpeed;
        }
            break;

        case 5: {

            if (MoveLeft) {
                if (EnemyGetX() < WWIDTH - Width) {
                    if (MaxSpeed > 0) {
                        MaxSpeed -= slowDown;
                    } else MaxSpeed = 0;
                }
                this->X -= MaxSpeed;
            }
            if (MoveRight) {
                if (EnemyGetX() > 0) {
                    if (MaxSpeed > 0) {
                        MaxSpeed -= slowDown;
                    } else MaxSpeed = 0;
                }
                this->X += MaxSpeed;
            }

            if (MoveDown) {
                Y += 1 * kAcc;
            }
        }
            break;
    }




}




void CEnemyMM::OnRender() {

    if (entityRenderer)
    {
		TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, W2 * AnimState, 0, W2, H2, -(degrees), NULL, 255);
    }
    else
    {
        SDL_Log("EnemyMM1::OnRender() BAD RENDERER!");
    }


}

void CEnemyMM::OnCleanup() {

}




void CEnemyMM::OnLaser() {

    Laser = new CGammaRayEnemy(EnemyGetX() + 142 * OVERALL_ENEMY_RATIO, Ye + 247 * OVERALL_ENEMY_RATIO, this->ID, "laser_05");

    switch (selected) {
        case 0:
            Laser->Size = ENTITY_SIZE_NONE;
            break;

        case 4:
            Laser->Size = ENTITY_SIZE_SX;
            break;
        default:
            break;

    }
    Laser->W2 = 16;
    Laser->H2 = 16;
    Laser->Width = Laser->W2 * OVERALL_ENEMY_RATIO;
    Laser->Height = WHEIGHT;

    Laser->OnInit();

    CEntity::EntityList.push_back(Laser);




};




void CEnemyMM::OnFire() {

    switch (selected)
    {
        case 1: {

            if (!Dead) {
                px1 = EnemyGetX() + Width / 2;
                py1 = EnemyGetY() + Height / 2;

                px2 = CPlayer::PlayerGetXp() + CPlayer::PlayerStat.Width / 2;
                py2 = CPlayer::PlayerGetYp() + CPlayer::PlayerStat.Height / 2;

                DeltaX = px2 - px1;
                DeltaY = py2 - py1;
                m = DeltaX / DeltaY;
                q = -(m) * py1 + px1;

                for (int indexX = 0; indexX < MaxRow; indexX++) {
                    px1 = m * py1 + q;

                    pathLine[indexX][0] = px1;
                    pathLine[indexX][1] = py1;

                    py1 += 1;

                    if (DeltaX >= WWIDTH / 2) { py1 += 2; }
                    else if (DeltaX < WWIDTH / 2) { py1 += 3; }
                    else if (DeltaX < -WWIDTH / 2) { py1 += 2; }
                }

                BullEnemy = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_ENEMY_M);
                BullEnemy->W2 = 100;
                BullEnemy->H2 = 100;
                BullEnemy->Width = BullEnemy->W2 * OVERALL_BULLET_RATIO;
                BullEnemy->Height = BullEnemy->H2 * OVERALL_BULLET_RATIO;
                BullEnemy->entityTexture = "Boss_blue_X";
                BullEnemy->OnInit();

                CEntity::EntityList.push_back(BullEnemy);


            }
        }
            break;

        case 2: {



            for (int b = 0; b < 4; b++) {
                px1 = EnemyGetX() + (Width / 2) - (56 * OVERALL_ENEMY_RATIO);
                py1 = EnemyGetY() + Height / 2;
                pathLine[0][0] = px1;
                pathLine[0][1] = py1;

                SDL_Log("alpha %1.3f", alpha);

                for (int indexX = 1; indexX < MaxRow; indexX++) {
                    pathLine[indexX][0] =
                            pathLine[indexX - 1][0] +
                            (cos(alpha * (PIG) / 180) * forward * OVERALL_SPEED_RATIO);
                    pathLine[indexX][1] =
                            pathLine[indexX - 1][1] +
                            (sin(alpha * (PIG) / 180) * forward * OVERALL_SPEED_RATIO);
                    //SDL_Log("boss bullet x: %1.3f - y: %1.3f", pathLine[indexX][0],
                    //pathLine[indexX][1]);
                }

                BullEnemy = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_BOSS);

                BullEnemy->entityTexture = "BlueBall__flash";
                BullEnemy->W2 = 56;
                BullEnemy->H2 = 56;
                BullEnemy->Width = BullEnemy->W2 * OVERALL_ENEMY_RATIO;
                BullEnemy->Height = BullEnemy->H2 * OVERALL_ENEMY_RATIO;
                BullEnemy->OnInit();

                CEntity::EntityList.push_back(BullEnemy);

                if (pos_C) alpha += alpha_inc;
                else if (pos_A) alpha -= alpha_inc;
            }
        }
            break;

        case 3:
            break;

        case 4: {

            if (!Dead) {

                px1 = EnemyGetX() + 130 * OVERALL_ENEMY_RATIO;
                py1 = EnemyGetY() + 189 * OVERALL_ENEMY_RATIO;

                px2 = CPlayer::PlayerGetXp() + CPlayer::PlayerStat.Width / 2;
                py2 = CPlayer::PlayerGetYp() + CPlayer::PlayerStat.Height / 2;

                DeltaX = px2 - px1;
                DeltaY = py2 - py1;
                m = DeltaX / DeltaY;
                q = -(m) * py1 + px1;

                for (int indexX = 0; indexX < MaxRow; indexX++) {
                    px1 = m * py1 + q;

                    pathLine[indexX][0] = px1;
                    pathLine[indexX][1] = py1;

                    py1 += 1;

                    if (DeltaX >= WWIDTH / 2) { py1 += 2; }
                    else if (DeltaX < WWIDTH / 2) { py1 += 3; }
                    else if (DeltaX < -WWIDTH / 2) { py1 += 2; }
                }

                BullEnemy = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_ENEMY_M);
                BullEnemy->W2 = 80;
                BullEnemy->H2 = 80;
                BullEnemy->Width = BullEnemy->W2 * OVERALL_ENEMY_RATIO;
                BullEnemy->Height = BullEnemy->H2 * OVERALL_ENEMY_RATIO;
                BullEnemy->entityTexture = "GreenSpinperfect";
                BullEnemy->OnInit();

                CEntity::EntityList.push_back(BullEnemy);


            }
        }
        break;

        case 5: {

            int temp_x;
            int temp_y;

            if (shoted % 2 == 0) {
                temp_x = EnemyGetX() + 110 * OVERALL_ENEMY_RATIO;
                temp_y = EnemyGetY() + 157 * OVERALL_ENEMY_RATIO;
            } else {
                temp_x = EnemyGetX() + 240 * OVERALL_ENEMY_RATIO;
                temp_y = EnemyGetY() + 157 * OVERALL_ENEMY_RATIO;
            }

            BullEnemyStd = new CBulletEnemy_S(temp_x, temp_y, 20, 0, "laser_07",
                                              ENTITY_FLAG_ENEMY_M);

            shoted++;
            BullEnemyStd->entityTexture = "OrangeScale__flash2x";
            BullEnemyStd->W2 = 50;
            BullEnemyStd->H2 = 50;
            BullEnemyStd->Width = BullEnemyStd->W2 * OVERALL_ENEMY_RATIO;
            BullEnemyStd->Height = BullEnemyStd->H2 * OVERALL_ENEMY_RATIO;
            BullEnemyStd->selectCollider = ENTITY_FLAG_ENEMY_M;
            BullEnemyStd->OnInit();

            CEntity::EntityList.push_back(BullEnemyStd);
        }
            break;


    }

}




//=============================================================================
void CEnemyMM::CollisionLoop() {

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


bool CEnemyMM::OnCollision(CEntity *Entity) {

    if (CanFire())
    {
        if (Entity->Type == ENTITY_TYPE_GAMMARAY  || Entity->Size == ENTITY_SIZE_BOMB) {
            hit += 5;
            SDL_Log("Enemy MM 1hit: %d", hit);
        }
        else {
            hit++;
            SDL_Log("Enemy MM 2hit: %d", hit);
        }



        AnimState = 10;

        if (hit > 20)
        {
            CPlayer::PlayerStat.PlayerScore += 300;
            //std::cout<<"Score: "<<CPlayer::PlayerStat.PlayerScore<<"\n";


            int XB = EnemyGetX();
            int YB = EnemyGetY();

            CParticle_PlayerXPL *PlayerExplosion = new CParticle_PlayerXPL(XB, YB, "boom_big_01", ENTITY_FLAG_ENEMY_F);

            PlayerExplosion->W2 = 128;
            PlayerExplosion->H2 = 128;
            PlayerExplosion->Width = this->Width;
            PlayerExplosion->Height = this->Height;
            PlayerExplosion->particleTexture = "Player_EXPL";

            CEntity::EntityList.push_back(PlayerExplosion);


            float x = EnemyGetX();
            float y = EnemyGetY() - 15;
            float r = 15;
            // create grade for Player
            MedalHonor = new CMedal(x, y, 3, r, "powerup_02", ENTITY_FLAG_ENEMY_M, BEZIER);

            MedalHonor->entityTexture = "Icon2";
            MedalHonor->Width = 100 * OVERALL_RATIO;
            MedalHonor->Height = 100 * OVERALL_RATIO;
            MedalHonor->OnInit();

            CEntity::EntityList.push_back(MedalHonor);

            Dead = true;

            if (this->Dead) {
                if (!CEntity::TargetEnemyMap.empty()) {
                    std::map<int, CEntity *>::iterator iter;
                    if (CEntity::TargetEnemyMap.find(ID) != CEntity::TargetEnemyMap.end()) {
                        SDL_Log("enemyMM_OnCollision() ID %d erased from map", ID);
                        iter = CEntity::TargetEnemyMap.find(ID);
                        CEntity::TargetEnemyMap.erase(iter);
                    }
                }
            }
        }
    }

    return true;

}

std::vector<SDL_Rect>& CEnemyMM::getColliders() {

	return mColliders;

}



void CEnemyMM::EntityDEL() {

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
    std::cout<<"EnemyListSize after iterator: "<<CEntity::EntityList.size()<<"\n";
    */

}




int CEnemyMM::EnemyGetX() {

    return this->X;
}

int CEnemyMM::EnemyGetY() {

    return this->Y;
}
