#include "CPlayer.h"
#include "CPlayerStat.h"
#include "CParticle_PlayerXPL.h"
#include "CParticle_Smoke.h"
#include "CShield.h"
#include "CFPS.h"

#include "CAppStateGame.h"

#include "TextureBank.h"
#include "Stringify.h"

#include <iostream>
#include <cmath>

CPlayer CPlayer::PlayerStat;

int CPlayer::starSX					= 0;
int CPlayer::starMM					= 0;
int CPlayer::starM1					= 0;
int CPlayer::starBB					= 0;
int CPlayer::playerCounter			= 0;
int CPlayer::playerAnim             = 0;
int CPlayer::PlayerTOTscore         = 0;
int CPlayer::shotCounter			= 0;
int	CPlayer::LevelMax				= 0;
int CPlayer::DeadTime				= 0;
int CPlayer::rocketMODE             = 0;
int CPlayer::temp_fireMODE          = 0;

int CPlayer::X_P                    = 0;
int CPlayer::Y_P                    = 0;

float CPlayer::Xp					= 0;
float CPlayer::Yp					= 0;
float CPlayer::MaxSpeed				= 0;
float CPlayer::Accel				= 0;

int	CPlayer::armor					= 0;
int CPlayer::stamina				= 0;
int	CPlayer::PRE_armor				= 0;
int CPlayer::PRE_stamina			= 0;

bool CPlayer::PlasmaCannonE			= false;
bool CPlayer::GammaRayE				= false;

int CPlayer::mySHIP                 = 0;
int CPlayer::originalW              = 0;
int CPlayer::originalH              = 0;

int CPlayer::zx                     = 0;
int CPlayer::xx                     = 0;
int CPlayer::H2                     = 0;
int CPlayer::W2                     = 0;
int CPlayer::H1                     = 0;
int CPlayer::W1                     = 0;

float CPlayer::Xb2                  = 0;
float CPlayer::Yb2                  = 0;


CPlayer::CPlayer() {


    onTarget = 0;
    countRocket = 0;
    countSmartRocket = 0;
	enemyID = 0;
    GammaRayOnce = 0;


    Flags = ENTITY_FLAG_PLAYER;
    Type = ENTITY_TYPE_PLAYER;


    rocketMODE = ROCKET_SMART;
    IcanFire = true;



}


void CPlayer::OnInit() {

    X2 = Y2 = 0;

	SpeedX = 0;
	SpeedY = 0;

	switch(mySHIP)
    {

        case 1:     //RedShip
            mColliders.resize(11);

            mVelX = 0;
            mVelY = 0;

            // x - y
            // 2 - 40
            mColliders[0].w = 17;
            mColliders[0].h = 6;

            // 43 - 5
            mColliders[1].w = 25;
            mColliders[1].h = 9;

            // 41 - 8
            mColliders[2].w = 33;
            mColliders[2].h = 14;

            // 40 - 11
            mColliders[3].w = 45;
            mColliders[3].h = 49;

            // 39 - 15
            mColliders[4].w = 72;
            mColliders[4].h = 28;

            // 38 - 18
            mColliders[5].w = 138;
            mColliders[5].h = 12;

            // 37 - 21
            mColliders[6].w = 169;
            mColliders[6].h = 76;

            // 36 - 24
            mColliders[7].w = 325;
            mColliders[7].h = 68;

            // 34 - 28
            mColliders[8].w = 339;
            mColliders[8].h = 63;

            // 32 - 33
            mColliders[9].w = 69;
            mColliders[9].h = 18;

            // 28 - 51
            mColliders[10].w = 47;
            mColliders[10].h = 25;

            break;

        case 2:     // BlueShip
            mColliders.resize(16);

            mVelX = 0;
            mVelY = 0;

            // x - y
            // 2 - 40
            mColliders[0].w = 150;
            mColliders[0].h = 26;

            // 43 - 5
            mColliders[1].w = 172;
            mColliders[1].h = 54;

            // 41 - 8
            mColliders[2].w = 241;
            mColliders[2].h = 63;

            // 40 - 11
            mColliders[3].w = 361;
            mColliders[3].h = 67;

            // 39 - 15
            mColliders[4].w = 387;
            mColliders[4].h = 20;

            // 38 - 18
            mColliders[5].w = 365;
            mColliders[5].h = 12;

            // 37 - 21
            mColliders[6].w = 348;
            mColliders[6].h = 11;

            // 36 - 24
            mColliders[7].w = 331;
            mColliders[7].h = 10;

            // 34 - 28
            mColliders[8].w = 317;
            mColliders[8].h = 9;

            // 32 - 33
            mColliders[9].w = 302;
            mColliders[9].h = 9;

            // 28 - 51
            mColliders[10].w = 287;
            mColliders[10].h = 11;

            // 24 - 53
            mColliders[11].w = 266;
            mColliders[11].h = 14;

            // 28 - 51
            mColliders[12].w = 201;
            mColliders[12].h = 7;

            // 20 - 55
            mColliders[13].w = 143;
            mColliders[13].h = 13;

            // 16 - 57
            mColliders[14].w = 87;
            mColliders[14].h = 8;

            // 11 - 59
            mColliders[15].w = 15;
            mColliders[15].h = 18;

            break;


        case 3:     // GreenShip
            mColliders.resize(7);

            mVelX = 0;
            mVelY = 0;

            // x - y
            // 2 - 40 r13
            mColliders[0].w = 47;
            mColliders[0].h = 24;

            // 43 - 5
            mColliders[1].w = 207;
            mColliders[1].h = 64;

            // 41 - 8
            mColliders[2].w = 515;
            mColliders[2].h = 29;

            // 40 - 11
            mColliders[3].w = 403;
            mColliders[3].h = 98;

            // 39 - 15
            mColliders[4].w = 224;
            mColliders[4].h = 64;

            // 38 - 18
            mColliders[5].w = 275;
            mColliders[5].h = 57;

            // 37 - 21
            mColliders[6].w = 100;
            mColliders[6].h = 15;

            break;


        case 4:     // YellowShip
            mColliders.resize(6);

            mVelX = 0;
            mVelY = 0;

            // x - y
            // 2 - 40
            mColliders[0].w = 157;
            mColliders[0].h = 84;

            // 43 - 5
            mColliders[1].w = 304;
            mColliders[1].h = 94;

            // 41 - 8
            mColliders[2].w = 400;
            mColliders[2].h = 40;

            // 40 - 11
            mColliders[3].w = 442;
            mColliders[3].h = 55;

            // 39 - 15
            mColliders[4].w = 274;
            mColliders[4].h = 86;

            mColliders[5].w = 87;
            mColliders[5].h = 10;

            break;
    }

    for (int set = 0; set < mColliders.size(); set++)
    {
        mColliders[set].w = mColliders[set].w * OVERALL_RATIO;
        mColliders[set].h = mColliders[set].h * OVERALL_RATIO;
    }

	//Initialize colliders relative to position
	shiftColliders();

	//if (fireMODE == FIRE_GAMMARAY) Fire();

    // Engine Glow
    SmokeLow = "EngineRED_anim_high";
    SmokeHigh = "EngineRED_anim_high";


    engOffset.x = 58;
    engOffset.y = 135;

    int SmogW = 15;
    int SmogH = 18;

    SDL_Log("PLAYER SHOT RATE %d", shotCounter);

}


void CPlayer::shiftColliders() {

    switch(mySHIP)
    {
        case 1:     //RedShip
            r = 9 * OVERALL_RATIO;
            break;

        case 2:     // BlueShip
            r = 5 * OVERALL_RATIO;

            break;

        case 3:     // GreenShip
            r = 13 * OVERALL_RATIO;

            break;

        case 4:     // YellowShip
            r = 7 * OVERALL_RATIO;

            break;
    }

    //Go through the dot's collision boxes
    for (int set = 0; set < mColliders.size(); set++)
    {
        //Center the collision box
        mColliders[set].x = PlayerGetX() + ((Width - mColliders[set].w) /2);

        //Set the collision box at its row offset
        mColliders[set].y = PlayerGetY() + r;

        ret[set].h = mColliders[set].h;
        ret[set].w = mColliders[set].w;
        ret[set].x = mColliders[set].x;
        ret[set].y = mColliders[set].y;


        //Move the row offset down the height of the collision box
        r += mColliders[set].h;
    }

}



bool CPlayer::OnLoad(char* File, int Width, int Height, int MaxFrames) {

    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;

    }

    return true;
}

void CPlayer::OnLoop() {

	


	//CollisionLoop();

    /*
	if (starSX < 20) shotCounter = 50;
	if (starSX >= 20 && starSX < 30) shotCounter = 40;
	if (starSX >= 30 && starSX < 40) shotCounter = 30;
	if (starSX >= 40 && starSX < 50) shotCounter = 20;
	*/


    if (!Dead) {
        if (fireMODE != FIRE_GAMMARAY && fireMODE != FIRE_NONE) {
            if (playerCounter % shotCounter == 0) {
                Fire();

            }
        } else {
            if (GammaRayOnce == 0) {
                Fire();
                GammaRayOnce++;
            }
        }
    } else
    {
        fireMODE = FIRE_NONE;
    }



    if (!expired)
    {
		if (CPlayer::stamina <= 0)
		{
			SDL_Log("YOU LOST");
			int XB = PlayerGetX();
			int YB = PlayerGetY();

			CParticle_PlayerXPL *PlayerExplosion = new CParticle_PlayerXPL(XB, YB, "boom_big_01", ENTITY_FLAG_PLAYER);

			PlayerExplosion->W2 = 128;
			PlayerExplosion->H2 = 128;
			PlayerExplosion->Width  = CPlayer::Width;
			PlayerExplosion->Height = CPlayer::Height;
			PlayerExplosion->particleTexture = "Player_EXPL";

			CEntity::EntityList.push_back(PlayerExplosion);


			SDL_Log("set Player environments for closing");
			Dead = true;
			expired = true;

			DeadTime = SDL_GetTicks();
			CAppStateGame::DeadTime = SDL_GetTicks();
			CAppStateGame::nextState = true;

		}

	


	
    }
	/*
	if (playerCounter % 50 == 0)
	{
		SDL_Log("Player fire!");
		Fire();
		playerCounter = 0;
	}
	playerCounter++;
	*/

    //    CShield *myShield = new CShield(PlayerGetX(), PlayerGetY());
    //    CEntity::EntityList.push_back(myShield);

    if(playerCounter %2 == 0)
    {
        if (playerAnim < 7) {
            X2 = originalW * playerAnim;
            playerAnim++;
        } else {
            playerAnim = 0;
        }
    }


	if (!CAppStateGamePause::GetInstance()->onPause) playerCounter++;

    Xp = X;
    Yp = Y;


}


void CPlayer::OnMove(float MoveX, float MoveY) {

	//SDL_Log("MoveX: %1.4f MoveY: %1.4f", MoveX, MoveY);

	//mPosX = X;
	//mPosY = Y;
	//if (MoveX == 0 && MoveY == 0) return;
	/*
	if (MoveX < 0)	{ AccelX = -1; }
	if (MoveX > 0)  { AccelX = 1; }
	if (MoveY < 0)  { AccelY = -1; }
	if (MoveY > 0)  { AccelY = 1; }
	*/

	Accel = 1.5;
	//Accel = 1.5;

	if (!CAppStateGame::GetInstance()->levelCompleted) {
        MoveX += Accel * CFPS::FPSControl.GetSpeedFactor();
	}
	MoveY += Accel * CFPS::FPSControl.GetSpeedFactor();
	

	if (MoveX > MaxSpeed)		MoveX = MaxSpeed;
	if (MoveX < -MaxSpeed)		MoveX = -MaxSpeed;
	if (MoveY > MaxSpeed)		MoveY = MaxSpeed;
	if (MoveY < -MaxSpeed)		MoveY = -MaxSpeed;

	//SDL_Log("MoveX + Acc: %1.4f MoveY + Acc: %1.4f", MoveX, MoveY);
	
	if (PlayerGetX() > 5 && PlayerGetX() < WWIDTH - CPlayer::Width)	{ X += MoveX; }
	else if (PlayerGetX() <= 5 && MoveX > 0)						{ X += MoveX; }
	else if (PlayerGetX() >= WWIDTH - CPlayer::Width && MoveX < 0)	{ X += MoveX; }

	if (!CAppStateGame::GetInstance()->levelCompleted) {
        if (PlayerGetY() > (WHEIGHT * 0.25) && PlayerGetY() < WHEIGHT - CPlayer::Height) { Y += MoveY; }
        else if (PlayerGetY() <= (WHEIGHT * 0.25) && MoveY > 0) { Y += MoveY; }
        else if (PlayerGetY() >= (WHEIGHT * 0.25) && MoveY < 0) { Y += MoveY; }
    }
	else {
	    Y += MoveY;
	}
	
	//X += MoveX;
	//Y += MoveY;

	Xp = X;
	Yp = Y;
	CEntity::X = X;
	CEntity::Y = Y;

	X_P = X;
	Y_P = Y;

	//SDL_Log("player MoveX %1.3f - X %1.3f - Y %1.3f", MoveX, X, Y);

	shiftColliders();


}

void CPlayer::OnRender() {

    //SDL_Log("Player render X: %1.3f - Y: %1.3f", X, Y);

    if(entityRenderer)
    {
        //TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, AnimState * Width, Anim_Control.GetCurrentFrame() * Height, 128, 128, 255);
        TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, X2, Y2, originalW, originalH, 255);
        //SDL_Log("Player moving X2: %d - anim: %d", X2, playerAnim);

        /*
        for(int set = 0; set < mColliders.size(); set++)
        {
            SDL_SetRenderDrawColor(entityRenderer, 0xFF, 0x00, 0xFF, 1);
            SDL_RenderFillRect(entityRenderer, &ret[set]);
        }
        */

    }
    else
    {
        SDL_Log("Player bad rendeder");
    }

}



void CPlayer::OnAnimate() {

    /*
    if (SpeedX != 0) { Anim_Control.MaxFrames = 1; }
    else { Anim_Control.MaxFrames = 0; }
    CEntity::OnAnimate();
    */




}

void CPlayer::CollisionLoop() {

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

bool CPlayer::OnCollision(CEntity *Entity) {



    if (!GodMODE)
    {
        switch (Entity->Size)
        {
            case ENTITY_SIZE_SX:
                stamina += -15 + armor;
                if (SDL_HapticRumblePlay(mouseHaptic, 0.20, 80) != 0)
                {
                    SDL_Log("Warning: Unable to play rumble! %s", SDL_GetError());
                }
                break;

            case ENTITY_SIZE_SSX:
                stamina += -0.01;
                if (SDL_HapticRumblePlay(mouseHaptic, 0.10, 80) != 0)
                {
                    SDL_Log("Warning: Unable to play rumble! %s", SDL_GetError());
                }
			break;

            case ENTITY_SIZE_MM:
                stamina += -5 + armor;
                if (SDL_HapticRumblePlay(mouseHaptic, 0.30, 80) != 0)
                {
                    SDL_Log("Warning: Unable to play rumble! %s", SDL_GetError());
                }
			break;

            case ENTITY_SIZE_BB:
                stamina += -10 + armor;
                if (SDL_HapticRumblePlay(mouseHaptic, 0.10, 80) != 0)
                {
                    SDL_Log("Warning: Unable to play rumble! %s", SDL_GetError());
                }
			break;

            case ENTITY_SIZE_AST:
                Dead = true;
                if (SDL_HapticRumblePlay(mouseHaptic, 0.100, 100) != 0)
                {
                    SDL_Log("Warning: Unable to play rumble! %s", SDL_GetError());
                }
			break;

            case ENTITY_SIZE_MEDAL:
                stamina += Entity->medalHonor;
				//fireMODE = FIRE_TRIPLE;
				PlayerHonor += Entity->medalHonor;

                if (SDL_HapticRumblePlay(mouseHaptic, 0.10, 50) != 0)
                {
                    SDL_Log("Warning: Unable to play rumble! %s", SDL_GetError());
                }

			break;

            case ENTITY_SIZE_JOLLY:
                shotCounter -= 10;
                if (SDL_HapticRumblePlay(mouseHaptic, 0.10, 80) != 0)
                {
                    SDL_Log("Warning: Unable to play rumble! %s", SDL_GetError());
                }
                if(shotCounter < 5) shotCounter = 5;
                //SetPlayerShotCounter(shotCounter);
                //fireMODE = FIRE_TRIPLE;
            break;
        }

		switch (Entity->Flags)
		{
			case ENTITY_FLAG_ENEMY_S:
				starSX++;
			break;

			case ENTITY_FLAG_ENEMY_M:
				starMM++;
			break;

			case ENTITY_FLAG_ENEMY_M1:
				starM1++;
			break;

			case ENTITY_FLAG_BOSS:
				starBB++;
			break;
		}


    }

    SDL_Log("player stamina: %d", stamina);

    if (Entity->Type == ENTITY_TYPE_MEDAL) manageWeapons(Entity->medalReward);

    return true;

}




std::vector<SDL_Rect>& CPlayer::getColliders() {

	return this->mColliders;

}


void CPlayer::OnCleanup() {

    CEntity::OnCleanup();

}





void CPlayer::StopMove() {

	CEntity::StopMove();

}

void CPlayer::StopMoveX() {

	CEntity::StopMoveX();

}

void CPlayer::StopMoveY() {

	CEntity::StopMoveY();

}


void Shoot() {

    //SDL_Thread *thread = NULL;
    //thread = SDL_CreateThread(CPlayer::Fire, NULL );

}


void CPlayer::Fire() {



    if (!Dead)
    {
        if (IcanFire)
        {
            switch (mySHIP)
            {
                case 1:
                {

                    Xb = PlayerGetX() + (9 * OVERALL_RATIO);
                    Yb = PlayerGetY() + (50 * OVERALL_RATIO);

                    Xb2 = PlayerGetX() + (320 * OVERALL_RATIO);
                    Yb2 = PlayerGetY() + (50 * OVERALL_RATIO);

                    int rocket_sx_x = PlayerGetX() + (0 * OVERALL_RATIO);
                    int rocket_sx_y = PlayerGetY() + (126 * OVERALL_RATIO);
                    int rocket_dx_x = PlayerGetX() + (309 * OVERALL_RATIO);
                    int rocket_dx_y = PlayerGetY() + (126 * OVERALL_RATIO);

                    W2 = 22;
                    H2 = 80;
                    W1 = W2 * OVERALL_BULLET_RATIO;
                    H1 = H2 * OVERALL_BULLET_RATIO;

                    int temp_PLY_off_W = 154;

                    BulletTexture = "OrangeTailperfect";

                    // Muzzle Effects
                    MuzzleSX = "OrangeBlast__anim_ply";
                    MuzzleDX = "OrangeBlast__anim_ply";
                    SDL_Point pnt_muzzle_sx;
                    SDL_Point pnt_muzzle_dx;
                    pnt_muzzle_sx.x = -24 * OVERALL_RATIO;
                    pnt_muzzle_sx.y = 117 * OVERALL_RATIO;
                    pnt_muzzle_dx.x = 285 * OVERALL_RATIO;
                    pnt_muzzle_dx.y = 117 * OVERALL_RATIO;

                    int MuzzleW = 89;
                    int MuzzleH = 90;

                    switch (fireMODE) {

                        // ONE SHOT PER BUTTON-PRESS
                        case FIRE_SINGLE: {

                            zx = 0;

                            FireSingle(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, zx, W1, H1, W2, H2, BulletTexture);

                        }

                            break;

                            //ENABLE TRIPLE FIRING!!
                        case FIRE_TRIPLE: {

                            float tempX = (PlayerGetX() + Width / 2) - 4;
                            xx = int(tempX);
                            zx = -1;

                            FireTriple(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, Xb2, zx, W1, H1, W2, H2,
                                       BulletTexture);

                        }

                            break;

                        case FIRE_PENTA: {

                            float tempX = (PlayerGetX() + Width / 2) - 4;
                            zx = -2;
                            xx = int(tempX);

                            FirePenta(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                      MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2,
                                      BulletTexture);
                        }

                            break;


                            /// SMART ROCKET
                        case FIRE_SMARTROCKET: {
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                            //SDL_Log("tempX: %1.2f", tempX);
                            //SDL_Log("tempY: %1.2f", tempY);
                            //SDL_Log("enemyID: %d", enemyID);

                        }
                            break;


                            /// SEEK ROCKET
                        case FIRE_SEEKROCKET: {
                            rocketMODE = ROCKET_SEEK;

                            SDL_Log("initialize RocketSeek");
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }

                            countRocket++;
                            countSmartRocket++;

                            //SDL_Log("tempX: %1.2f", tempX);
                            //SDL_Log("tempY: %1.2f", tempY);
                            //SDL_Log("enemyID: %d", enemyID);

                        }
                            break;


                            /// THE GAMMA RAY!!!!
                        case FIRE_GAMMARAY: {

                            SDL_Log("FIRE_GAMMARAY");

                            // 15w xa35 xb78 y-119

                            Xb = 54;
                            Yb = 0;
                            int H = PlayerGetY();
                            int w_off = temp_PLY_off_W * OVERALL_RATIO;

                            FireGammaRay(Xb, Yb, H, w_off);

                        }

                            break;


                        case FIRE_COMBO1: {

                            zx = 0;

                            FireSingle(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, zx, W1, H1, W2, H2, BulletTexture);

                            rocketMODE = ROCKET_SMART;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;
                        }
                            break;

                        case FIRE_COMBO2: {

                            float tempX = (PlayerGetX() + Width / 2) - 4;
                            xx = int(tempX);
                            zx = -1;

                            FireTriple(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2,
                                       BulletTexture);


                            rocketMODE = ROCKET_SMART;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;
                        }
                            break;


                        case FIRE_COMBO3: {

                            float tempX = (PlayerGetX() + Width / 2) - 4;
                            zx = -2;
                            xx = int(tempX);

                            FirePenta(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                      MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2,
                                      BulletTexture);


                            rocketMODE = ROCKET_SMART;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;
                        }
                            break;

                        case FIRE_COMBO4: {

                            rocketMODE = ROCKET_SMART;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                            Xb = 54;
                            Yb = 0;

                            int w_off = temp_PLY_off_W * OVERALL_RATIO;
                            int H = PlayerGetY();

                            FireGammaRay((int) Xb, (int) Yb, H, w_off);

                        }
                            break;


                        case FIRE_COMBOTOTAL: {

                            float tempXb = (PlayerGetX() + Width / 2) - 4;
                            xx = int(tempXb);
                            zx = -1;

                            FireTriple(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2,
                                       BulletTexture);

                            rocketMODE = ROCKET_SMART;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                            Xb = 54;
                            Yb = 0;
                            int H = PlayerGetY();
                            int w_off = temp_PLY_off_W * OVERALL_RATIO;
                            FireGammaRay((int) Xb, (int) Yb, H, w_off);

                            break;
                        }

                        case FIRE_NONE:
                            break;

                    } //END SWITCH FIREMODE
                }

                    break;

                case 2: {

                    Xb = (PlayerGetX() + (112 * OVERALL_RATIO));
                    Yb = (PlayerGetY() - (75 * OVERALL_RATIO));

                    Xb2 = (PlayerGetX() + (236 * OVERALL_RATIO));
                    Yb2 = (PlayerGetY() - (75 * OVERALL_RATIO));

                    int rocket_sx_x = PlayerGetX() + (113 * OVERALL_RATIO);
                    int rocket_sx_y = PlayerGetY() + (5 * OVERALL_RATIO);
                    int rocket_dx_x = PlayerGetX() + (236 * OVERALL_RATIO);
                    int rocket_dx_y = PlayerGetY() + (5 * OVERALL_RATIO);

                    W2 = 80;
                    H2 = 80;
                    W1 = W2 * OVERALL_BULLET_RATIO;
                    H1 = H2 * OVERALL_BULLET_RATIO;

                    int temp_PLY_off_W = 174;

                    BulletTexture = "BlueSpinperfect01";

                    // Muzzle Effects
                    MuzzleSX = "BlueCircle__anim";
                    MuzzleDX = "BlueCircle__anim";
                    SDL_Point pnt_muzzle_sx;
                    SDL_Point pnt_muzzle_dx;
                    pnt_muzzle_sx.x = 37 * OVERALL_RATIO;
                    pnt_muzzle_sx.y = -16 * OVERALL_RATIO;
                    pnt_muzzle_dx.x = 162 * OVERALL_RATIO;
                    pnt_muzzle_dx.y = -12 * OVERALL_RATIO;

                    int MuzzleW = 177;
                    int MuzzleH = 25;

                    switch (fireMODE) {

                        // ONE SHOT PER BUTTON-PRESS
                        case FIRE_SINGLE: {

                            zx = 0;

                            FireSingle(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, zx, W1, H1, W2, H2, BulletTexture);

                        }

                            break;


                            //ENABLE TRIPLE FIRING!!
                        case FIRE_TRIPLE: {

                            int zx = -2;
                            int xx = -15;

                            FireQuad(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                     MuzzleH, Xb, Yb, Xb2, zx, W1, H1, W2, H2, BulletTexture);

                        }

                            break;

                        case FIRE_PENTA: {

                            int zx = -2;
                            int xx = -15;

                            FireEsa(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                    MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2, BulletTexture);
                        }

                            break;


                            /// SMART ROCKET
                        case FIRE_SMARTROCKET: {
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }

                            countRocket++;
                            countSmartRocket++;

                        }
                            break;


                            /// SEEK ROCKET
                        case FIRE_SEEKROCKET: {
                            rocketMODE = ROCKET_SEEK;

                            SDL_Log("initialize RocketSeek");
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }

                            countRocket++;
                            countSmartRocket++;

                            //SDL_Log("tempX: %1.2f", tempX);
                            //SDL_Log("tempY: %1.2f", tempY);
                            //SDL_Log("enemyID: %d", enemyID);

                        }
                            break;


                            // THE GAMMA RAY!!!!
                        case FIRE_GAMMARAY: {

                            // 15w xa35 xb78 y-119

                            int H = PlayerGetY();
                            int w_off = temp_PLY_off_W * OVERALL_RATIO;

                            FireGammaRay((int) 54, (int) Yb, H, w_off);

                        }

                            break;


                        case FIRE_COMBO1: {

                            zx = 0;

                            FireSingle(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, zx, W1, H1, W2, H2, BulletTexture);

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                        }
                            break;

                        case FIRE_COMBO2: {

                            int zx = -2;
                            int xx = -15;

                            FireQuad(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                     MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2, BulletTexture);

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                        }
                            break;


                        case FIRE_COMBO3: {

                            int zx = -2;
                            int xx = -15;

                            FireEsa(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                    MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2, BulletTexture);


                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                        }
                            break;


                        case FIRE_COMBO4: {

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                            int H = PlayerGetY();
                            int w_off = temp_PLY_off_W * OVERALL_RATIO;

                            FireGammaRay((int) 54, (int) Yb, H, w_off);

                        }
                            break;


                        case FIRE_COMBOTOTAL: {

                            int zx = -2;
                            int xx = -15;

                            FireQuad(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                     MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2, BulletTexture);

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                            int w_off = temp_PLY_off_W * OVERALL_RATIO;
                            int H = PlayerGetY();

                            FireGammaRay((int) 54, (int) Yb, H, w_off);

                        }
                            break;

                        case FIRE_NONE:
                            break;

                    } //END SWITCH FIREMODE

                }
                    break;


                case 3: {

                    Xb = (PlayerGetX() + (155 * OVERALL_RATIO));
                    Yb = (PlayerGetY() - (90 * OVERALL_RATIO));

                    Xb2 = (PlayerGetX() + (338 * OVERALL_RATIO));
                    Yb2 = (PlayerGetY() - (90 * OVERALL_RATIO));

                    int rocket_sx_x = PlayerGetX() + (124 * OVERALL_RATIO);
                    int rocket_sx_y = PlayerGetY() + (96 * OVERALL_RATIO);
                    int rocket_dx_x = PlayerGetX() + (354 * OVERALL_RATIO);
                    int rocket_dx_y = PlayerGetY() + (96 * OVERALL_RATIO);

                    W2 = 22;
                    H2 = 80;
                    W1 = W2 * OVERALL_BULLET_RATIO;
                    H1 = H2 * OVERALL_BULLET_RATIO;

                    int temp_PLY_off_W = 238;

                    BulletTexture = "OrangeTailperfect";

                    // Muzzle Effects
                    MuzzleSX = "OrangeBlast__anim_ply";
                    MuzzleDX = "OrangeBlast__anim_ply";
                    SDL_Point pnt_muzzle_sx;
                    SDL_Point pnt_muzzle_dx;
                    pnt_muzzle_sx.x = 123 * OVERALL_RATIO;
                    pnt_muzzle_sx.y = -47 * OVERALL_RATIO;
                    pnt_muzzle_dx.x = 305 * OVERALL_RATIO;
                    pnt_muzzle_dx.y = -47 * OVERALL_RATIO;

                    int MuzzleW = 89;
                    int MuzzleH = 90;

                    switch (fireMODE) {

                        /// ONE SHOT PER BUTTON-PRESS
                        case FIRE_SINGLE: {

                            int zx = 0;

                            FireSingle(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, zx, W1, H1, W2, H2, BulletTexture);

                        }

                            break;


                            /// ENABLE TRIPLE FIRING!!
                        case FIRE_TRIPLE: {

                            float tempX = (PlayerGetX() + Width / 2) - 4;
                            xx = int(tempX);
                            zx = -1;

                            FireTriple(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, Xb2, zx, W1, H1, W2, H2,
                                       BulletTexture);

                        }

                            break;

                        case FIRE_PENTA: {

                            float tempX = (PlayerGetX() + Width / 2) - 4;
                            zx = -2;
                            xx = int(tempX);

                            FirePenta(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                      MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2,
                                      BulletTexture);
                        }

                            break;



                            /// SMART ROCKET
                        case FIRE_SMARTROCKET: {
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                        }
                            break;


                            /// SEEK ROCKET
                        case FIRE_SEEKROCKET: {
                            rocketMODE = ROCKET_SEEK;

                            SDL_Log("initialize RocketSeek");
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }

                            countRocket++;
                            countSmartRocket++;

                            //SDL_Log("tempX: %1.2f", tempX);
                            //SDL_Log("tempY: %1.2f", tempY);
                            //SDL_Log("enemyID: %d", enemyID);

                        }
                            break;


                            // THE GAMMA RAY!!!!
                        case FIRE_GAMMARAY: {

                            SDL_Log("FIRE_GAMMARAY");

                            // 15w x_dx51 x_sx114 y-114

                            int w_off = temp_PLY_off_W * OVERALL_RATIO;
                            int H = PlayerGetY();

                            FireGammaRay((int) 80, (int) Yb, H, w_off);

                        }

                            break;


                        case FIRE_COMBO1: {

                            int zx = 0;

                            FireSingle(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, zx, W1, H1, W2, H2, BulletTexture);

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                        }
                            break;

                        case FIRE_COMBO2: {

                            float tempX = (PlayerGetX() + Width / 2) - 4;
                            xx = int(tempX);
                            zx = -1;

                            FireTriple(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2,
                                       BulletTexture);

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                        }
                            break;


                        case FIRE_COMBO3: {

                            float tempX = (PlayerGetX() + Width / 2) - 4;
                            zx = -2;
                            xx = int(tempX);

                            FirePenta(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                      MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2,
                                      BulletTexture);

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                        }
                            break;

                        case FIRE_COMBO4: {

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                            int w_off = temp_PLY_off_W * OVERALL_RATIO;
                            int H = PlayerGetY();

                            FireGammaRay((int) 80, (int) Yb, H, w_off);

                        }
                            break;


                        case FIRE_COMBOTOTAL: {

                            float tempXb = (PlayerGetX() + Width / 2) - 4;
                            xx = int(tempXb);
                            zx = -1;

                            FireTriple(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb

                                       , xx, zx, W1, H1, W2, H2,
                                       BulletTexture);

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                            int w_off = temp_PLY_off_W * OVERALL_RATIO;
                            int H = PlayerGetY();

                            FireGammaRay((int) 80, (int) Yb, H, w_off);

                        }
                            break;

                        case FIRE_NONE:
                            break;

                    } //END SWITCH FIREMODE
                }

                    break;


                case 4: {

                    Xb = (PlayerGetX() + (50 * OVERALL_RATIO));
                    Yb = (PlayerGetY() - (1 * OVERALL_RATIO));

                    Xb2 = (PlayerGetX() + (345 * OVERALL_RATIO));
                    Yb2 = (PlayerGetY() - (1 * OVERALL_RATIO));

                    int rocket_sx_x = PlayerGetX() + (9 * OVERALL_RATIO);
                    int rocket_sx_y = PlayerGetY() + (170 * OVERALL_RATIO);
                    int rocket_dx_x = PlayerGetX() + (402 * OVERALL_RATIO);
                    int rocket_dx_y = PlayerGetY() + (170 * OVERALL_RATIO);

                    W2 = 50;
                    H2 = 50;
                    W1 = W2 * OVERALL_BULLET_RATIO;
                    H1 = H2 * OVERALL_BULLET_RATIO;

                    int temp_PLY_off_W = 207;

                    BulletTexture = "OrangeScale__flash2x";

                    // Muzzle Effects
                    MuzzleSX = "OrangeBlast__anim_ply";
                    MuzzleDX = "OrangeBlast__anim_ply";
                    SDL_Point pnt_muzzle_sx;
                    SDL_Point pnt_muzzle_dx;
                    pnt_muzzle_sx.x = 36 * OVERALL_RATIO;
                    pnt_muzzle_sx.y = 2 * OVERALL_RATIO;
                    pnt_muzzle_dx.x = 325 * OVERALL_RATIO;
                    pnt_muzzle_dx.y = 2 * OVERALL_RATIO;

                    int MuzzleW = 89;
                    int MuzzleH = 90;

                    switch (fireMODE) {

                        // ONE SHOT PER BUTTON-PRESS
                        case FIRE_SINGLE: {

                            int zx = 0;

                            FireSingle(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, zx, W1, H1, W2, H2, BulletTexture);

                        }

                            break;


                            //ENABLE TRIPLE FIRING!!
                        case FIRE_TRIPLE: {

                            int zx = -2;
                            int xx = -15;

                            FireQuad(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                     MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2, BulletTexture);

                        }

                            break;

                        case FIRE_PENTA: {

                            int zx = -2;
                            int xx = -15;

                            FireEsa(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                    MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2, BulletTexture);
                        }

                            break;


                            /// SMART ROCKET
                        case FIRE_SMARTROCKET: {
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                        }
                            break;


                            /// SEEK ROCKET
                        case FIRE_SEEKROCKET: {
                            rocketMODE = ROCKET_SEEK;

                            SDL_Log("initialize RocketSeek");
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }

                            countRocket++;
                            countSmartRocket++;

                            //SDL_Log("tempX: %1.2f", tempX);
                            //SDL_Log("tempY: %1.2f", tempY);
                            //SDL_Log("enemyID: %d", enemyID);

                        }
                            break;


                            // THE GAMMA RAY!!!!
                        case FIRE_GAMMARAY: {

                            // 15w xa35 xb78 y-119
                            Xb = PlayerGetX() + (207 * OVERALL_RATIO);

                            int w_off = temp_PLY_off_W * OVERALL_RATIO;
                            int H = PlayerGetY() + (17 * OVERALL_RATIO);

                            FireGammaRay(Xb, Yb, H, w_off);

                        }
                            break;


                        case FIRE_COMBO1: {

                            int zx = 0;

                            FireSingle(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                       MuzzleH, Xb, Yb, zx, W1, H1, W2, H2, BulletTexture);

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                        }
                            break;

                        case FIRE_COMBO2: {

                            int zx = -2;
                            int xx = -15;

                            FireQuad(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                     MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2, BulletTexture);

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                        }
                            break;


                        case FIRE_COMBO3: {

                            int zx = -2;
                            int xx = -15;

                            FireEsa(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                    MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2, BulletTexture);

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                        }
                            break;


                        case FIRE_COMBO4: {

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                            int w_off = temp_PLY_off_W * OVERALL_RATIO;
                            int H = PlayerGetY();

                            FireGammaRay((int) 80, (int) Yb, H, w_off);

                        }
                            break;


                        case FIRE_COMBOTOTAL: {

                            int zx = -2;
                            int xx = -15;

                            FireQuad(MuzzleSX, MuzzleDX, pnt_muzzle_sx, pnt_muzzle_dx, MuzzleW,
                                     MuzzleH, Xb, Yb, xx, zx, W1, H1, W2, H2, BulletTexture);

                            rocketMODE = FIRE_SMARTROCKET;
                            if (countRocket % 2 == 0) {
                                FireRocket(rocket_sx_x, rocket_sx_y);
                            } else {
                                FireRocket(rocket_dx_x, rocket_dx_y);
                            }
                            countRocket++;
                            countSmartRocket++;

                            int H = PlayerGetY();
                            int w_off = temp_PLY_off_W * OVERALL_RATIO;

                            FireGammaRay((int) 80, (int) Yb, H, w_off);

                        }
                            break;

                        case FIRE_NONE:
                            break;

                    } //END SWITCH FIREMODE
                }

                    break;


            }   // END SWITCH mySHIP
        }

    }



}

void CPlayer::FireSingle(char* MuzzleSX, char* MuzzleDX, SDL_Point pnt_muzzleSX, SDL_Point pnt_muzzleDX, int muzzleW, int muzzleH, float Xb, float Yb, int zx, int W1, int H1, int W2, int H2, char* txt) {

    CParticle_Smoke *PlayerMuzzleSX = new CParticle_Smoke(MuzzleSX, MuzzleDX, muzzleW * OVERALL_RATIO, muzzleH * OVERALL_RATIO, muzzleW, muzzleH, pnt_muzzleSX, 0, this->ID);
    CParticle_Smoke *PlayerMuzzleDX = new CParticle_Smoke(MuzzleSX, MuzzleDX, muzzleW * OVERALL_RATIO, muzzleH * OVERALL_RATIO, muzzleW, muzzleH, pnt_muzzleDX, 0, this->ID);

    CEntity::EntityList.push_back(PlayerMuzzleSX);
    CEntity::EntityList.push_back(PlayerMuzzleDX);

    // sx cannon fire
    Bull = new CBullet(Xb, Yb, zx, W2, H2, "laser_05");

    Bull->entityTexture = txt;
    Bull->Width = W1;
    Bull->Height = H1;
    Bull->Dead = false;
    Bull->Size = ENTITY_SIZE_PB;
    Bull->OnInit();


    CEntity::EntityList.push_back(Bull);

    // dx cannon fire
    Bull2 = new CBullet(Xb2, Yb2, zx, W2, H2, "laser_05");

    Bull2->entityTexture = txt;
    Bull2->Width = W1;
    Bull2->Height = H1;
    Bull2->Dead = false;
    Bull2->Size = ENTITY_SIZE_PB;
    Bull2->OnInit();

    CEntity::EntityList.push_back(Bull2);


}


/// X3 FIRE
void CPlayer::FireTriple(char* MuzzleSX, char* MuzzleDX, SDL_Point pnt_muzzleSX, SDL_Point pnt_muzzleDX, int muzzleW, int muzzleH, float Xb, float Yb, int xx, int zx, int W1, int H1, int W2, int H2, char* txt) {

    CParticle_Smoke *PlayerMuzzleSX = new CParticle_Smoke(MuzzleSX, MuzzleDX, muzzleW * OVERALL_RATIO, muzzleH * OVERALL_RATIO, muzzleW, muzzleH, pnt_muzzleSX, 0, this->ID);
    CParticle_Smoke *PlayerMuzzleDX = new CParticle_Smoke(MuzzleSX, MuzzleDX, muzzleW * OVERALL_RATIO, muzzleH * OVERALL_RATIO, muzzleW, muzzleH, pnt_muzzleDX, 0, this->ID);

    CEntity::EntityList.push_back(PlayerMuzzleSX);
    CEntity::EntityList.push_back(PlayerMuzzleDX);

    for (int z = 0; z < 3; z++)
    {

        // sx cannon
        if (z == 0) {
            Bull = new CBullet(Xb, Yb +5, zx, W2, H2, "laser_04");
        }
        else if (z == 1) {
            Bull = new CBullet(Xb, Yb, zx, W2, H2, "laser_04");
        }else if (z == 2) {
            Bull = new CBullet(Xb, Yb +5, zx, W2, H2, "laser_04");
        }

        Bull->entityTexture = txt;
        Bull->Width = W1;
        Bull->Height = H1;
        Bull->Size = ENTITY_SIZE_PB;
        Bull->Dead = false;
        Bull->OnInit();

        // dx cannon
        if (z == 0) {
            Bull2 = new CBullet(Xb2, Yb2 +5, zx, W2, H2, "laser_04");
        }
        else if (z == 1) {
            Bull2 = new CBullet(Xb2, Yb2, zx, W2, H2, "laser_04");
        }else if (z == 2) {
            Bull2 = new CBullet(Xb2, Yb2 +5, zx, W2, H2, "laser_04");
        }

        Bull2->entityTexture = txt;
        Bull2->Width = W1;
        Bull2->Height = H1;
        Bull2->Size = ENTITY_SIZE_PB;
        Bull2->Dead = false;
        Bull2->OnInit();


        CEntity::EntityList.push_back(Bull);
        CEntity::EntityList.push_back(Bull2);

        zx += 2;
        //xx += 15;
    }

}

/// X2 FIRE
void CPlayer::FireQuad(char* MuzzleSX, char* MuzzleDX, SDL_Point pnt_muzzleSX, SDL_Point pnt_muzzleDX, int muzzleW, int muzzleH, float Xb, float Yb, int xx, int zx, int W1, int H1, int W2, int H2, char* txt) {

    CParticle_Smoke *PlayerMuzzleSX = new CParticle_Smoke(MuzzleSX, MuzzleDX, muzzleW * OVERALL_RATIO, muzzleH * OVERALL_RATIO, muzzleW, muzzleH, pnt_muzzleSX, 0, this->ID);
    CParticle_Smoke *PlayerMuzzleDX = new CParticle_Smoke(MuzzleSX, MuzzleDX, muzzleW * OVERALL_RATIO, muzzleH * OVERALL_RATIO, muzzleW, muzzleH, pnt_muzzleDX, 0, this->ID);

    CEntity::EntityList.push_back(PlayerMuzzleSX);
    CEntity::EntityList.push_back(PlayerMuzzleDX);

    for (int z = 0; z < 4; z++)
    {
        if (z%2 == 0)
        {
            Bull = new CBullet(Xb, Yb, zx, W2, H2, "laser_04");

            Bull->entityTexture = txt;
            Bull->Width = W1;
            Bull->Height = H1;
            Bull->Size = ENTITY_SIZE_PB;
            Bull->Dead = false;
            Bull->OnInit();

            CEntity::EntityList.push_back(Bull);

        }
        else
        {
            Bull = new CBullet(Xb2, Yb2, zx, W2, H2, "laser_04");

            Bull->entityTexture = txt;
            Bull->Width = W1;
            Bull->Height = H1;
            Bull->Size = ENTITY_SIZE_PB;
            Bull->Dead = false;
            Bull->OnInit();

            CEntity::EntityList.push_back(Bull);
            zx = 1;
        }

        //xx += 15;
    }

}

/// X5 FIRE
void CPlayer::FirePenta(char* MuzzleSX, char* MuzzleDX, SDL_Point pnt_muzzleSX, SDL_Point pnt_muzzleDX, int muzzleW, int muzzleH, float Xb, float Yb, int xx, int zx, int W1, int H1, int W2, int H2, char* txt) {

    CParticle_Smoke *PlayerMuzzleSX = new CParticle_Smoke(MuzzleSX, MuzzleDX, muzzleW * OVERALL_RATIO, muzzleH * OVERALL_RATIO, muzzleW, muzzleH, pnt_muzzleSX, 0, this->ID);
    CParticle_Smoke *PlayerMuzzleDX = new CParticle_Smoke(MuzzleSX, MuzzleDX, muzzleW * OVERALL_RATIO, muzzleH * OVERALL_RATIO, muzzleW, muzzleH, pnt_muzzleDX, 0, this->ID);

    CEntity::EntityList.push_back(PlayerMuzzleSX);
    CEntity::EntityList.push_back(PlayerMuzzleDX);

    for (int z = 0; z < 5; z++)
    {
        // sx cannon
        if (z == 0) {
            Bull = new CBullet(Xb, Yb +6, zx, W2, H2, "laser_04");
        } else if (z == 1) {
            Bull = new CBullet(Xb, Yb +3, zx, W2, H2, "laser_04");
        } else if (z == 2) {
            Bull = new CBullet(Xb, Yb, zx, W2, H2, "laser_04");
        } else if (z == 3) {
            Bull = new CBullet(Xb, Yb +3, zx, W2, H2, "laser_04");
        } else if (z == 4) {
            Bull = new CBullet(Xb, Yb +6, zx, W2, H2, "laser_04");
        }

        Bull->entityTexture = txt;
        Bull->Width = W1;
        Bull->Height = H1;
        Bull->Size = ENTITY_SIZE_PB;
        Bull->Dead = false;
        Bull->OnInit();

        // dx cannon
        if (z == 0) {
            Bull2 = new CBullet(Xb2, Yb2 +6, zx, W2, H2, "laser_04");
        } else if (z == 1) {
            Bull2 = new CBullet(Xb2, Yb2 +3, zx, W2, H2, "laser_04");
        } else if (z == 2) {
            Bull2 = new CBullet(Xb2, Yb2, zx, W2, H2, "laser_04");
        } else if (z == 3) {
            Bull2 = new CBullet(Xb2, Yb2 +3, zx, W2, H2, "laser_04");
        } else if (z == 4) {
            Bull2 = new CBullet(Xb2, Yb2 +6, zx, W2, H2, "laser_04");
        }


        Bull2->entityTexture = txt;
        Bull2->Width = W1;
        Bull2->Height = H1;
        Bull2->Size = ENTITY_SIZE_PB;
        Bull2->Dead = false;
        Bull2->OnInit();

        CEntity::EntityList.push_back(Bull);
        CEntity::EntityList.push_back(Bull2);

        zx += 1;
        //xx += 15;
    }

}


/// X6 FIRE
void CPlayer::FireEsa(char* MuzzleSX, char* MuzzleDX, SDL_Point pnt_muzzleSX, SDL_Point pnt_muzzleDX, int muzzleW, int muzzleH, float Xb, float Yb, int xx, int zx, int W1, int H1, int W2, int H2, char* txt) {

    CParticle_Smoke *PlayerMuzzleSX = new CParticle_Smoke(MuzzleSX, MuzzleDX, muzzleW * OVERALL_RATIO, muzzleH * OVERALL_RATIO, muzzleW, muzzleH, pnt_muzzleSX, 0, this->ID);
    CParticle_Smoke *PlayerMuzzleDX = new CParticle_Smoke(MuzzleSX, MuzzleDX, muzzleW * OVERALL_RATIO, muzzleH * OVERALL_RATIO, muzzleW, muzzleH, pnt_muzzleDX, 0, this->ID);

    CEntity::EntityList.push_back(PlayerMuzzleSX);
    CEntity::EntityList.push_back(PlayerMuzzleDX);

    for (int z = 0; z < 6; z++)
    {
        if (z%2 == 0)
        {
            Bull = new CBullet(Xb, Yb, zx, W2, H2, "laser_04");

            Bull->entityTexture = txt;
            Bull->Width = W1;
            Bull->Height = H1;
            Bull->Size = ENTITY_SIZE_PB;
            Bull->Dead = false;
            Bull->OnInit();

            CEntity::EntityList.push_back(Bull);

        }
        else if (z%3 == 0)
        {
            Bull = new CBullet(Xb2, Yb2, zx, W2, H2, "laser_04");

            Bull->entityTexture = txt;
            Bull->Width = W1;
            Bull->Height = H1;
            Bull->Size = ENTITY_SIZE_PB;
            Bull->Dead = false;
            Bull->OnInit();

            CEntity::EntityList.push_back(Bull);
            zx = 0;
        }
        else
        {
            Bull = new CBullet(Xb2, Yb2, zx, W2, H2, "laser_04");

            Bull->entityTexture = txt;
            Bull->Width = W1;
            Bull->Height = H1;
            Bull->Size = ENTITY_SIZE_PB;
            Bull->Dead = false;
            Bull->OnInit();

            CEntity::EntityList.push_back(Bull);
            zx = 2;
        }

        //xx += 15;
    }

}


/// STANDARD ROCKET
void CPlayer::FireRocket(float Xb,float Yb) {

    switch(rocketMODE)
    {
        /// SMART SEEKING ROCKET /// **************************
        case ROCKET_SMART:
            {
                SDL_Log("countSmartRocket: %d", countSmartRocket);
                SDL_Log("EntityMap size: %d", TargetEnemyMap.size());

                for(auto& it : TargetEnemyMap)
                {
                    SDL_Log("target-id %d enemyID %d", it.first, it.second->ID);
                }

                if(!TargetEnemyMap.empty())
                {
                    if (onTarget == 0 || TargetEnemyMap.find(onTarget) == TargetEnemyMap.end())
                    {
                        SDL_Log("first EntityMap element: %d", TargetEnemyMap.begin()->first);
                        onTarget = TargetEnemyMap.begin()->first;
                        SDL_Log("ASSIGN enemy ID, onTarget INDEX = %d", onTarget);
                        enemyID = TargetEnemyMap[onTarget]->ID;
                        //SDL_Log("smart rocket targeting enemyID: %d", enemyID);
                        //onTarget = countSmartRocket;
                    }
                    else if (onTarget > 0)
                    {
                        SDL_Log("INCREMENT enemy ID, onTarget INDEX = %d", onTarget);
                        if(!(TargetEnemyMap.find(onTarget) == TargetEnemyMap.end())) {
                            enemyID = onTarget;
                            enemyID = TargetEnemyMap[onTarget]->ID;
                            SDL_Log("smart rocket NEXT targeting enemyID: %d", enemyID);

                        } else {
                            SDL_Log("no target found on map");
                        }

                    }

                    /*
                    for(auto& Iterator : TargetEnemyMap)
                    {
                        SDL_Log("TargetEnemyMap First: %d", Iterator.first);
                    }
                    */



                    for (auto& it : EntityList)
                    {
                        if(!(it)) continue;
                        if ((it)->Type == ENTITY_TYPE_ENEMY || (it)->Type == ENTITY_TYPE_BOSS)
                        {
                            if ((it)->ID == enemyID)
                            {
                                if ((it)->EnemyGetX() > 0 && (it)->EnemyGetX() < WWIDTH -100 && (it)->EnemyGetY() > 0 && (it)->EnemyGetY() < WHEIGHT * 0.6)
                                {
                                    float px1 = Xb;
                                    float py1 = Yb;

                                    for (int indexX = 0; indexX < MaxRow; indexX++)
                                    {
                                        pathLine[indexX][0] = px1;
                                        pathLine[indexX][1] = py1;
                                        pathDegree[indexX][0] = 0;

                                        py1 += -10;
                                    }

                                    RocketSmart = new CBulletSmart(Xb, Yb, pathLine, pathDegree,
                                                                   enemyID, "laser_05",
                                                                   ENTITY_FLAG_ENEMY_F);

                                    RocketSmart->entityTexture = "Rocket_small2";
                                    RocketSmart->rocketMOVE = CBulletSmart::DESTROY ;
                                    RocketSmart->W2 = 50;
                                    RocketSmart->H2 = 99;
                                    RocketSmart->Width = (int)RocketSmart->W2 * OVERALL_RATIO;
                                    RocketSmart->Height = (int)RocketSmart->H2 * OVERALL_RATIO;
                                    RocketSmart->Dead = false;
                                    RocketSmart->OnInit();

                                    CEntity::EntityList.push_back(RocketSmart);
                                    onTarget++;
                                }
                                else {
                                    countSmartRocket--;
                                }
                            }
                        }
                    }
                }
                else
                {
                    SDL_Log("targetMap empty");
                    onTarget = 0;
                    enemyID = 0;


                    for (int indexX = 0; indexX < MaxRow; indexX++)
                    {
                        pathLine[indexX][0] = Xb;
                        pathLine[indexX][1] = Yb;
                        pathDegree[indexX][0] = 0;
                    }

                    RocketSmart = new CBulletSmart(Xb, Yb, pathLine, pathDegree,
                                                   enemyID, "laser_05",
                                                   ENTITY_FLAG_ENEMY_F);

                    RocketSmart->entityTexture = "Rocket_small2";
                    RocketSmart->rocketMOVE = CBulletSmart::DESTROY ;
                    RocketSmart->W2 = 50;
                    RocketSmart->H2 = 99;
                    RocketSmart->Width = (int)RocketSmart->W2 * OVERALL_RATIO;
                    RocketSmart->Height = (int)RocketSmart->H2 * OVERALL_RATIO;
                    RocketSmart->Dead = false;
                    RocketSmart->OnInit();

                    CEntity::EntityList.push_back(RocketSmart);

                }


            }
            break;

        /// CANNON ROCKET ///
        case ROCKET_SEEK:
            {
                SDL_Log("countSmartRocket: %d", countSmartRocket);
                SDL_Log("EntityMap size: %d", TargetEnemyMap.size());

                if(!TargetEnemyMap.empty())
                {
                    if (countSmartRocket == 0 || TargetEnemyMap.find(countSmartRocket) == TargetEnemyMap.end())
                    {
                        SDL_Log("first EntityMap element: %d", TargetEnemyMap.begin()->first);
                        countSmartRocket = TargetEnemyMap.begin()->first;
                    }

                    for(auto& Iterator : TargetEnemyMap)
                    {
                        SDL_Log("TargetEnemyMap First: %d", Iterator.first);
                    }

                    SDL_Log("assign enemy ID, counterSmartRocket = %d", countSmartRocket);
                    this->enemyID = TargetEnemyMap[countSmartRocket]->ID;
                    SDL_Log("smart rocket targeting enemyID: %d", enemyID);

                    for (auto& it : EntityList)
                    {
                        if ((it)->Flags == ENTITY_FLAG_ENEMY_S)
                        {
                            if ((it)->ID == enemyID)
                            {
                                if ((it)->EnemyGetX() > 0 && (it)->EnemyGetX() < WWIDTH -100 && (it)->EnemyGetY() > 0)
                                {
                                    float px1 = Xb;
                                    float py1 = Yb;

                                    SDL_Log("retrieve enemy coords");
                                    float px2 = (it)->EnemyGetX() + 75;
                                    float py2 = (it)->EnemyGetY() + 75;
                                    SDL_Log("enemy target: %1.2f - %1.2f", px2, py2);

                                    float DeltaX = px2 - px1;
                                    float DeltaY = py2 - py1;
                                    float m = DeltaX / DeltaY;
                                    float q = -(m) * py1 + px1;

                                    degrees = atan((double) m) * 180 / PI;

                                    for (int indexX = 0; indexX < MaxRow; indexX++) {
                                        px1 = m * py1 + q;

                                        //pathLine[indexX] = new int[2];
                                        pathLine[indexX][0] = px1;
                                        pathLine[indexX][1] = py1;
                                        pathDegree[indexX][0] = degrees;

                                        py1 += -15;

                                        if (DeltaX >= WWIDTH / 2) { py1 += 2; }
                                        else if (DeltaX < WWIDTH / 2) { py1 += 3; }
                                        else if (DeltaX < -WWIDTH / 2) { py1 += 2; }


                                        //if(indexX > 0) tempY += pathLine[indexX][0] - pathLine[indexX - 1][0];
                                    }

                                    RocketSmart = new CBulletSmart(Xb, Yb, pathLine, pathDegree,
                                                                   enemyID, "laser_05",
                                                                   ENTITY_FLAG_ENEMY_F);

                                    RocketSmart->entityTexture = "Rocket_anim2";
                                    RocketSmart->rocketMOVE = CBulletSmart::SEEKandDESTROY;
                                    RocketSmart->W2 = 39;
                                    RocketSmart->H2 = 150;
                                    RocketSmart->Width = (int)RocketSmart->W2 * OVERALL_RATIO;
                                    RocketSmart->Height = (int)RocketSmart->H2 * OVERALL_RATIO;
                                    RocketSmart->Dead = false;
                                    RocketSmart->OnInit();

                                    CEntity::EntityList.push_back(RocketSmart);
                                }
                                else {
                                    countSmartRocket--;
                                }
                            }
                        }
                    }
                }
                else
                {
                    countSmartRocket = 0;
                    this->enemyID = 0;

                    Rocket = new CBomb(Xb, Yb, 2);

                    Rocket->entityTexture = "Rocket_anim2";
                    Rocket->Width = 15;
                    Rocket->Height = 107;
                    Rocket->W2 = 39;
                    Rocket->H2 = 150;
                    Rocket->OnInit();

                    CEntity::EntityList.push_back(Rocket);

                }


            }
                break;


    }


    SDL_Log("new countSmartRocket: %d", countSmartRocket);


}




/// GAMMA RAY
void CPlayer::FireGammaRay(int Xb, int Yb, int H, int w_off) {

    GammaRaySX = new CGammaRay(Xb, Yb, w_off, this->ID, "laser_05");

    GammaRaySX->entityTexture = "gammaray_yellow";
    GammaRaySX->Width = 40 * OVERALL_RATIO;
    GammaRaySX->Height = H;
    GammaRaySX->W2 = 40;
    GammaRaySX->H2 = 100;
    GammaRaySX->OnInit();

    CEntity::EntityList.push_back(GammaRaySX);


}


/// NUKE
void CPlayer::DropBomb() {

    if (!Dead)
    {
        Xb = (PlayerGetX() +64);
        Yb = (PlayerGetY() -75);
      
        CApp::Logger.OnLog( __FILE__, __LINE__, "new CBomb", "");
        Bomb = new CBomb(Xb, Yb, 2);


        if(Bomb->OnLoad("IMG/pippo_bomb.png", 50, 77, 0) == false)
        {
            std::cout << "EXCP: Error loading file pippo_bomb.png\n";
            //return false;
        }

        CApp::Logger.OnLog( __FILE__, __LINE__, "EntityList pushback CBomb", "");
        CEntity::EntityList.push_back(Bomb);
        //CBullet::BulletList.push_back(Bull);
        //std::cout << "Bulletlist size: "<<CBullet::BulletList.size()<<"\n";
        //}
     
    }


}



void CPlayer::ScoreInc() {

    //CPlayerStat::PlayerStat.OnUpdate();


}


float CPlayer::PlayerGetX() {

    //return *XXP;
    return this->X;

}

float CPlayer::PlayerGetY() {

    //return *YYP;
    return this->Y;

}

float CPlayer::PlayerGetXp() {

	return Xp;

}

float CPlayer::PlayerGetYp() {

	return Yp;

}

int CPlayer::GetPlayerX() {

    return X_P;

}

int CPlayer::GetPlayerY() {

    return  Y_P;

}

void CPlayer::setFireMode(FireMode fm) {

    //SDL_Log("player set firemode %d", fm);

    temp_fireMODE = fireMODE;

	fireMODE = fm;

}

void CPlayer::RestoreFireMode() {

    //SDL_Log("player restore firemode %d", temp_fireMODE);
    fireMODE = temp_fireMODE;

}

void CPlayer::PlayerReset() {

    starM1 = 0;
    starMM = 0;
    starSX = 0;
    starBB = 0;

    stamina = PRE_stamina;
    armor = PRE_armor;

    Xp = WWIDTH / 2 - 64;
    Yp = WHEIGHT - 300;

    setFireMode(FIRE_SINGLE);

    switch (mySHIP)
    {
        case 1:
            SetPlayerShotCounter(30);
            break;
        case 2:
            SetPlayerShotCounter(30);
            break;
        case 3:
            SetPlayerShotCounter(35);
            break;
        case 4:
            SetPlayerShotCounter(40);
            break;
    }

}

void CPlayer::manageWeapons(int switchFire) {

    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Type == ENTITY_TYPE_GAMMARAY)
        {
            (*it)->Dead = true;
            SDL_Log("gammaray deactivated");
            (*it)->OnCleanup();
            delete *it;
            it = CEntity::EntityList.erase(it);
            GammaRayOnce = 0;
            SDL_Log("gammaray: vector element erased");
        }
        else
        {
            it++;
        }
    }


    switch(switchFire)
    {
        case MEDAL_NONE:
            SDL_Log("Medal_none got");
            break;

        case MEDAL_TRIPLE:

            SDL_Log("Medal_triple got");

            switch(fireMODE)
            {
                case FIRE_NONE:
                    break;

                case FIRE_SINGLE:
                    setFireMode(FIRE_TRIPLE);
                    break;

                case FIRE_TRIPLE:
                    break;

                case FIRE_PENTA:
                    setFireMode(FIRE_TRIPLE);
                    break;

                case FIRE_GAMMARAY:
                    setFireMode(FIRE_TRIPLE);
                    break;

                case FIRE_COMBO1:
                    setFireMode(FIRE_COMBO2);
                    break;

                case FIRE_COMBO3:
                    setFireMode(FIRE_COMBO2);
                    break;

                case FIRE_COMBO4:
                    setFireMode(FIRE_TRIPLE);
                    break;

                default:
                    setFireMode(FIRE_TRIPLE);
                    break;
            }
            break;

        case MEDAL_PENTA:

            SDL_Log("Medal_penta got");

            switch(fireMODE)
            {
                case FIRE_NONE:
                    break;

                case FIRE_SINGLE:
                    setFireMode(FIRE_PENTA);
                    break;

                case FIRE_TRIPLE:
                    setFireMode(FIRE_PENTA);
                    break;

                case FIRE_PENTA:
                    break;

                case FIRE_GAMMARAY:
                    setFireMode(FIRE_PENTA);
                    break;

                case FIRE_COMBO1:
                    setFireMode(FIRE_COMBO3);
                    break;

                case FIRE_COMBO2:
                    setFireMode(FIRE_COMBO3);
                    break;

                case FIRE_COMBO3:
                    setFireMode(FIRE_PENTA);
                    break;

                case FIRE_COMBO4:
                    setFireMode(FIRE_PENTA);
                    break;

                default:
                    setFireMode(FIRE_PENTA);
                    break;
            }
            break;

        case MEDAL_GAMMARAY:

            SDL_Log("Medal_gammaray got");

            switch(fireMODE)
            {
                case FIRE_NONE:
                    break;

                case FIRE_SINGLE:
                    setFireMode(FIRE_GAMMARAY);
                    break;

                case FIRE_TRIPLE:
                    setFireMode(FIRE_GAMMARAY);
                    break;

                case FIRE_PENTA:
                    setFireMode(FIRE_GAMMARAY);
                    break;

                case FIRE_GAMMARAY:
                    setFireMode(FIRE_GAMMARAY);
                    break;

                case FIRE_COMBO1:
                    setFireMode(FIRE_GAMMARAY);
                    break;

                case FIRE_COMBO2:
                    setFireMode(FIRE_GAMMARAY);
                    break;

                case FIRE_COMBO3:
                    setFireMode(FIRE_GAMMARAY);
                    break;

                case FIRE_COMBO4:
                    break;

                default:
                    setFireMode(FIRE_GAMMARAY);
                    break;
            }
            break;

        case MEDAL_ROCKET:

            SDL_Log("Medal_rocket got");

            switch(fireMODE)
            {
                case FIRE_NONE:
                    break;

                case FIRE_SINGLE:
                    setFireMode(FIRE_COMBO1);
                    break;

                case FIRE_TRIPLE:
                    setFireMode(FIRE_COMBO2);
                    break;

                case FIRE_PENTA:
                    setFireMode(FIRE_COMBO3);
                    break;

                case FIRE_GAMMARAY:
                    setFireMode(FIRE_COMBO4);
                    break;

                case FIRE_COMBO1:
                    break;

                case FIRE_COMBO2:
                    break;

                case FIRE_COMBO3:
                    break;

                case FIRE_COMBO4:
                    break;

                default:
                    setFireMode(FIRE_COMBO1);
                    break;
            }
            break;

        case MEDAL_COMBOTOT:

            SDL_Log("Medal_combotot got");

            setFireMode(FIRE_COMBOTOTAL);
            break;

            default:
                SDL_Log("Medal_combo default got");
                //setFireMode(FIRE_COMBOTOTAL);
                break;



    }

}


bool CPlayer::SetEnabledFire(bool shot) {

    IcanFire = shot;

}

bool CPlayer::GetDisabledFire() {

    return IcanFire;

}

void CPlayer::switchPlayerFire() {

    IcanFire = !IcanFire;

}