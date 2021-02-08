#include "CCannon.h"
#include "CEnemyBOSS1.h"
#include "CParticle_XPL.h"
#include "Stringify.h"
#include <string>

#include <iostream>
#include <algorithm>
#include <functional>

#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


int CCannon::Xen = 0;
int CCannon::Yen = 0;

CCannon::CCannon() {}

CCannon::CCannon(int X, int Y, int pos) {

	this->X = X;
	this->Y = Y;

	offset.x = this->X;
	offset.y = this->Y;

	this->X = CEnemyBOSS1::getXen() + offset.x;
	this->Y = CEnemyBOSS1::getYen() + offset.y;

	Type = ENTITY_TYPE_ENEMY;
	Size = ENTITY_SIZE_BOSS;
	Flags = ENTITY_FLAG_CANNON;

	boom = false;
    degreeUP = false;
    degreeDOWN = false;
	AnimState = 0;
    counter = 0;
	hit = 0;
	degrees = 0;
    //pivot->x = 15;
    //pivot->y = 15;

	position.X = CannonGetX();
	position.Y = CannonGetY();

	posDSX = pos;

	SDL_Log("Cannon constructor pos: %d - X: %d - Y: %d", posDSX, this->X, this->Y);


}

CCannon::~CCannon() {

	SDL_Log("Cannon deleted");

}

void CCannon::OnInit() {

	mColliders.resize(1);

	switch (posDSX)
	{
	case 0:     // sx
		mColliders[0].w = Width;
		mColliders[0].h = Height;
		break;

	case 1:     // dx
		mColliders[0].w = Width;
		mColliders[0].h = Height;
		break;
	}

    SDL_Log("cannon Width %d - Height %d", Width, Height);
	shiftColliders();


}


bool CCannon::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if (CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
		return false;
	}

	return true;
}

void CCannon::OnLoop() {

	OnMove();
	shiftColliders();
	CollisionLoop();

	if (hit %5 == 0) {
	    CEnemyBOSS1::vanish = true;
	}

	if (hit >= 20)
	{
		SDL_Log("cannon %d destroyed, hit= %d",posDSX, hit);
		if (posDSX == 0) {
		    CEnemyBOSS1::CannonSxIsAlive = false;
		}
		else if (posDSX == 1) {
		    CEnemyBOSS1::CannonDxIsAlive = false;
		}
		Dead = true;
	}

	/*
    if (degrees == 90)
    {
        degreeDOWN = true;
        degreeUP = false;
    }
    else if (this->degrees == -90)
    {
        degreeDOWN = false;
        degreeUP = true;
    }
	if (degrees == 30 || degrees == 0 || degrees == -30)
	{
		//OnFire(degrees);
	}
    */

	if (CEnemyBOSS1::GetCanFire()) {
        if (counter % 40 == 0) {
            OnFire(0);
        }
    }

	counter++;

    if (AnimState > 0) AnimState = 0;

}


void CCannon::OnMove() {

	
	switch (posDSX)
	{
        case 0:		/// sx
            X = CEnemyBOSS1::getXen() + offset.x;
            Y = CEnemyBOSS1::getYen() + offset.y;
            /*
            if (counter %2 == 0)
            {
                if (degreeUP)   degrees++;
                if (degreeDOWN) degrees--;
            }
            */
            break;

        case 1:  	/// dx
            X = CEnemyBOSS1::getXen() + offset.x;
            Y = CEnemyBOSS1::getYen() + offset.y;
            /*
            if (counter %2 == 0)
            {
                if (degreeUP)   degrees++;
                if (degreeDOWN) degrees--;
            }
            */
            break;
	}

	//SDL_Log("GetXen X: %d  Y: %d", CEnemyBOSS1::getXen(), CEnemyBOSS1::getYen());
    //SDL_Log("cannon %d - X: %d - Y: %d", posDSX, X, Y);
    //if (this->degrees < 90) this->degrees++;


    Xen = X;
	Yen = Y;
	
	shiftColliders();


}


void CCannon::OnFire(double dgr) {

    muzzle = "GreenBlast__anim_enemy";
    int MuzzleW = 89;
    int MuzzleH = 90;

    /// muzzle sx
    pnt_muzzle_sx.x = CannonGetX() -25 * OVERALL_ENEMY_RATIO;
    pnt_muzzle_sx.y = CannonGetY() + 133 * OVERALL_ENEMY_RATIO;

    CParticle_Smoke *PlayerMuzzleSX = new CParticle_Smoke(muzzle, muzzle,
                                                          (MuzzleW * OVERALL_ENEMY_RATIO),
                                                          (MuzzleH * OVERALL_ENEMY_RATIO),
                                                          MuzzleW, MuzzleH,
                                                          pnt_muzzle_sx, 5,
                                                          ID);

    CEntity::EntityList.push_back(PlayerMuzzleSX);

    pnt_muzzle_dx.x = CannonGetX() + 16 * OVERALL_ENEMY_RATIO;
    pnt_muzzle_dx.y = CannonGetY() + 133 * OVERALL_ENEMY_RATIO;

    /// muzzle dx
    CParticle_Smoke *PlayerMuzzleDX = new CParticle_Smoke(muzzle, muzzle,
                                                          (MuzzleW * OVERALL_ENEMY_RATIO),
                                                          (MuzzleH * OVERALL_ENEMY_RATIO),
                                                          MuzzleW, MuzzleH,
                                                          pnt_muzzle_dx, 5,
                                                          ID);
    CEntity::EntityList.push_back(PlayerMuzzleDX);

    /// first sx fire
    int px1 = CannonGetX() + 6 * OVERALL_ENEMY_RATIO;
    int py1 = CannonGetY() + 126 * OVERALL_ENEMY_RATIO;

    const double start = -200;
    const double stop = WWIDTH + 200;


    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(start, std::nextafter(stop, DBL_MAX));
    int px2 = dist(mt);
    int py2 = WHEIGHT + 200;

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

    CannonFireSx1 = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_BOSS);

    CannonFireSx1->entityTexture = "Boss_Ball_Green";
    CannonFireSx1->W2 = 30;
    CannonFireSx1->H2 = 30;
    CannonFireSx1->Width = CannonFireSx1->W2 * OVERALL_ENEMY_RATIO;
    CannonFireSx1->Height = CannonFireSx1->H2 * OVERALL_ENEMY_RATIO;
    CannonFireSx1->SetRenderRect(true, 0, 255, 0, 50);
    CannonFireSx1->OnInit();

    CEntity::EntityList.push_back(CannonFireSx1);

    /// second sx fire
    px1 = CannonGetX() + 47 * OVERALL_ENEMY_RATIO;
    py1 = CannonGetY() + 126 * OVERALL_ENEMY_RATIO;

    std::random_device rd2;
    std::mt19937 mt2(rd2());
    std::uniform_real_distribution<double> dist2(start, std::nextafter(stop, DBL_MAX));
    px2 = dist2(mt2);
    py2 = WHEIGHT + 200;

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

    CannonFireSx2 = new CBulletEnemy(px1, py1, pathLine, "laser_06", ENTITY_FLAG_BOSS);

    CannonFireSx2->entityTexture = "Boss_Ball_Green";
    CannonFireSx2->W2 = 30;
    CannonFireSx2->H2 = 30;
    CannonFireSx2->Width = CannonFireSx2->W2 * OVERALL_ENEMY_RATIO;
    CannonFireSx2->Height = CannonFireSx2->H2 * OVERALL_ENEMY_RATIO;
    CannonFireSx2->SetRenderRect(true, 0, 255, 0, 50);
    CannonFireSx2->OnInit();

    CEntity::EntityList.push_back(CannonFireSx2);






    /*
    int px1 = 0;
    int py1 = 0;

    float gOffset;
    if (dgr == 30)  { gOffset = -1;  px1 = CannonGetX();      py1 = CannonGetY() + 40;}
    if (dgr == 0)   { gOffset = 0;   px1 = CannonGetX() + 20; py1 = CannonGetY() + 60; }
    if (dgr == -30) { gOffset = 1;   px1 = CannonGetX() + 50; py1 = CannonGetY() + 40;}

    CannonBall = new CBulletEnemy_S(px1, py1, 2, gOffset, "laser_07", ENTITY_FLAG_ENEMY_M);

    CannonBall->entityTexture = "CannonBall";
    CannonBall->Width = 20;
    CannonBall->Height = 20;
    CannonBall->Type = ENTITY_TYPE_BULLET_E;
    CannonBall->Size = ENTITY_SIZE_BB;
    CannonBall->Dead = false;
    CannonBall->selectCollider = ENTITY_FLAG_ENEMY_M;
    CannonBall->OnInit();

    CEntity::EntityList.push_back(CannonBall);
    */

}

void CCannon::Engine() {

	
}

void CCannon::shiftColliders() {

	int r = 0;

    for (int set = 0; set < mColliders.size(); set++)
    {
        mColliders[set].x = CannonGetX() + (Width - mColliders[set].w) /2;
        mColliders[set].y = CannonGetY() + r;
        r += mColliders[set].h;
    }

}

std::vector<SDL_Rect>& CCannon::getColliders() {

	return this->mColliders;

}

void CCannon::OnAnimate() {

	
}


void CCannon::OnRender() {

	//CApp::Logger.OnLog( __FILE__, __LINE__, "CEnemySX::OnRender()", "");

	if (entityRenderer)
	{
        TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, W2 * AnimState, 0, W2, H2, 255);
	}
	else
	{
        SDL_Log("Boss Cannon BAD renderer %s", SDL_GetError());
	}


}

void CCannon::OnCleanup() {


}


//=============================================================================
void CCannon::CollisionLoop() {

	for (int i = 0; i<CEntity::EntityList.size(); i++)
	{
		if (!CEntity::EntityList[i])
		{
			continue;
		}
		if (this != CEntity::EntityList[i])
			CEntity::CheckCollision(CEntity::EntityList[i]);
	}


}


bool CCannon::OnCollision(CEntity *Entity) {

    if (Entity->Type == ENTITY_TYPE_MyBULLET) {

        hit++;

        AnimState = 1;
        //SDL_Log("cannon hit n %d", hit);

        if (hit >= 20) {

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

            int XB = CannonGetX();
            int YB = CannonGetY();


            CParticle_XPL *Explosion = new CParticle_XPL(XB, YB, NONE, EXPLOSION, "boom_02");

            Explosion->particleTexture = anim_filename;
            Explosion->W2 = 128;
            Explosion->H2 = 128;
            Explosion->Width = Explosion->W2 * OVERALL_ENEMY_RATIO;
            Explosion->Height = Explosion->H2 * OVERALL_ENEMY_RATIO;
            Explosion->Expired = false;
            Explosion->Type = ENTITY_TYPE_PARTICLE;
            Explosion->Flags = ENTITY_FLAG_MAPONLY;
            Explosion->Size = ENTITY_SIZE_PP;

            CEntity::EntityList.push_back(Explosion);

            //int x = CannonGetX();
            //int y = CannonGetY();
            //int r = 15;
        }
    }

	return true;
	

}




void CCannon::OnDeleteEnemy() {



}


void CCannon::EntityDEL() {


    CEntity::EntityDEL();

    /*
	for (std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
	{
		if (!(*it)) continue;
		if ((*it)->Dead == true)
		{

			(*it)->OnCleanup();
			delete *it;
			it = CEntity::EntityList.erase(it);
			SDL_Log("EnemySX deleted\n");
		}
		else
		{
			it++;
		}
	}
    */

}



int CCannon::CannonGetX() {

	return this->X;
}

int CCannon::CannonGetY() {

	return this->Y;
}

int CCannon::GetXen() {

    return Xen;

}

int CCannon::GetYen() {

    return Yen;

}

int CCannon::GetHitted() {

    return this->hit;

}