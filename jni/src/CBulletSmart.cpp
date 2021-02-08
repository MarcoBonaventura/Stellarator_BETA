#include "CApp.h"
#include "CBulletSmart.h"
#include "Stringify.h"
#include "CAppStateIntro.h"

#include <cstdlib>
#include <cmath>

int CBulletSmart::rocketMOVE         = 0;
SDL_Renderer* CBulletSmart::Renderer = NULL;

//=============================================================================
CBulletSmart::CBulletSmart(int x1, int y1, float vettore[][2], double degrees[][1], int targetID, char* soundFX, eFlag F) {

	//SDL_Log("CBulletSmart() step1");

    this->Xbe = x1;
    this->Ybe = y1;

    kAcc = 0.004;
    accX = 0;
    accY = 0;

    Type = ENTITY_TYPE_MyBULLET;
    Size = ENTITY_SIZE_BOMB;
    Flags = ENTITY_FLAG_NONE;

	AnimState = 0;
	this->lockID = targetID;
    //degrees = 0;
    this->Dead = false;
    //m = 1;

    selectCollider = F;

    //vet = vettore;
    i = j = ii = 0;
    k = 3 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(10)));


    for (int z=0; z<2000; z++)
    {
        vet[z][0] = vettore[z][0];
        vet[z][1] = vettore[z][1];
        vetG[z][0] = degrees[z][0];
        points[z].x = vet[z][0];
        points[z].y = vet[z][1];
    }

    /*vet = vettore;
    i = j = 0;
    for (int z=0; z<2000; z++)
    {
        vet[z][0] = vettore[z][0];
        vet[z][1] = vettore[z][1];
    }
	*/


    /* Player fire sound effect */
    //CSoundBank::SoundControl.Play2(soundFX);

    SDL_Log("smartRocket ID: %d  Y: %d", this->lockID, this->Ybe);

}

//=============================================================================
CBulletSmart::~CBulletSmart() {
	
    //CApp::Logger.OnLog( __FILE__, __LINE__, "delete CBulletEnemy()", "");
	
}

void CBulletSmart::OnInit() {

	//SDL_Log("CBulletSmart OnInit()");

    mVelX = 0;
    mVelY = 0;

	mColliders.resize(1);

	mColliders[0].w = 39 * OVERALL_RATIO;
	mColliders[0].h = 75 * OVERALL_RATIO;

	shiftColliders();

    Renderer = CAppStateIntro::GetInstance()->GetRenderer();


    if (lockID != 0)
    {


        for (auto& itr : EntityList)
        {
            if(!(itr)) continue;
            if ((itr)->Type == ENTITY_TYPE_ENEMY)
            {
                if ((itr)->ID == lockID)
                {
                    // 1st coords
                    cp[0].x = BulletGetX();
                    cp[0].y = BulletGetY();

                    if ((itr)->EnemyGetY() < WHEIGHT * 0.5)
                    {
                        // 2nd coords
                        cp[1].x = cp[0].x;
                        cp[1].y = cp[0].y - 100;

                        // 3d coords
                        cp[2].x = cp[0].x;
                        cp[2].y = cp[1].y - 100;
                    }
                    else
                    {
                        // 2nd coords
                        cp[1].x = cp[0].x;
                        cp[1].y = cp[0].y - 200;

                        // 3d coords
                        cp[2].x = cp[0].x;
                        cp[2].y = cp[1].y - 200;
                    }
                    // last coords
                    cp[3].x = (itr)->EnemyGetX() + (itr)->Width / 2;
                    cp[3].y = (itr)->EnemyGetY() + (itr)->Height / 2;
                    //if(lockID == 4) SDL_Log("rocket target x-y %1.2f-%1.2f", cp[3].x, cp[3].y);
                }
            }
        }
    } else
    {
        cp[0].x = Xbe;
        cp[0].y = Ybe;

        cp[1].x = Xbe;
        cp[1].y = cp[0].y - WHEIGHT * 0.15;

        cp[2].x = cp[1].x + 50;
        cp[2].y = cp[1].y - WHEIGHT * 0.1;

        cp[3].x = cp[1].x - 50;
        cp[3].y = -100;
    }


    //PathLine(cp, POINTS_COUNT, curve);
    PathLine(POINTS_COUNT);
}


//=============================================================================
void CBulletSmart::PathLine(Point4D cp[4], int numberOfPoints, Point4D curve[POINTS_COUNT]) {

    //SDL_Log("return rocket coords");

    float dt;
    int   i;

    dt = 1.0 / (numberOfPoints - 1);

    for (i = 0; i < numberOfPoints; i++)
    {
        //SDL_Log("OnMove3 i: %d", i);

        curve[i] = PointOnCubicBezier(cp, i*dt, this->k);
        points[i].x = (int)curve[i].x;
        points[i].y = (int)curve[i].y;
        //if (lockID == 4) SDL_Log("rocket curve points[%d].x %d - points[%d].y %d", i, points[i].x, i, points[i].y);
    }

    //SDL_Log("rocket curve populated");


}

//=============================================================================
void CBulletSmart::PathLine(int numberOfPoints) {

    //SDL_Log("return rocket coords");

    if(lockID != 0)
    {
        for (auto& itr : EntityList)
        {
            if(!(itr)) continue;
            if ((itr)->Type == ENTITY_TYPE_ENEMY)
            {
                if ((itr)->ID == lockID)
                {
                    // last coords
                    float temp_x3 = (itr)->EnemyGetX() + (itr)->Width / 2;
                    float temp_y3 = (itr)->EnemyGetY() + (itr)->Height / 2;

                    cp[3].x = temp_x3;

                    if (temp_y3 <= cp[2].y + 100) {
                        cp[3].y = temp_y3;
                        cp[2].y += 1;
                    } else {
                        cp[3].y = cp[2].y + 50;
                    }


                    //if(lockID == 4) SDL_Log("rocket target x-y %1.2f-%1.2f", cp[3].x, cp[3].y);
                }
            }
        }
    }




    float dt;
    int   i;

    dt = 1.0 / (numberOfPoints - 1);

    for (i = 0; i < numberOfPoints; i++)
    {
        //SDL_Log("OnMove3 i: %d", i);

        curve[i] = PointOnCubicBezier(cp, i*dt, this->k);
        points[i].x = (int)curve[i].x;
        points[i].y = (int)curve[i].y;
        //if (lockID == 4) SDL_Log("rocket curve points[%d].x %d - points[%d].y %d", i, points[i].x, i, points[i].y);
    }

    //SDL_Log("rocket curve populated");


}


//=============================================================================
bool CBulletSmart::OnLoad(char *File, int Width, int Height, int MaxFrames) {

    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }

    return true;

}

//=============================================================================
void CBulletSmart::OnLoop() {

	//SDL_Log("CBulletSmart OnLoop()");

	//OnAnimate();

    shiftColliders();
	CollisionLoop();

    horizon   = BulletGetY();
    ordBullet = BulletGetX();
	if (horizon < 0 || horizon > WHEIGHT || ordBullet < -20 || ordBullet > WWIDTH + 20)
    {
		//SDL_Log("bullet ID %d x: %d y: %d", lockID, this->ordBullet, this->horizon);
		this->Dead = true;
		SDL_Log("bulletSmart OnLoop = DEAD");
    }

    /*
    for (auto& itr : EntityList)
    {
        if(!(itr)) continue;
        if ((itr)->Dead)
        {
            int temp_x = curve[ii].x - curve[ii-1].x;
            int temp_y = curve[ii].y - curve[ii-1].y;

             /*
            if(!TargetEnemyMap.empty())
            {
                lockID = TargetEnemyMap.begin()->first;
            }
            if ((itr)->Flags == ENTITY_FLAG_ENEMY_S)
            {
                if ((itr)->ID == lockID)
                {
                    // last coords
                    cp[3].x = (itr)->EnemyGetX() + 75;
                    cp[3].y = (itr)->EnemyGetY() + 75;
                    //if(lockID == 4) SDL_Log("rocket target x-y %1.2f-%1.2f", cp[3].x, cp[3].y);
                }
            }

        }
    }
    */

    int smookey_x1 = BulletGetX() + 7 * OVERALL_RATIO;
    int smookey_y1 = BulletGetY() + 73 * OVERALL_RATIO;
    int smookey_x2 = BulletGetX() + 19 * OVERALL_RATIO;
    int smookey_y2 = BulletGetY() + 77 * OVERALL_RATIO;
    int smookey_x3 = BulletGetX() + 12 * OVERALL_RATIO;
    int smookey_y3 = BulletGetY() + 90 * OVERALL_RATIO;

    int smookey_w = 15 * OVERALL_RATIO;
    int smookey_h = 15 * OVERALL_RATIO;



    CParticle_Smooky *smooky1 = new CParticle_Smooky(smookey_x1, smookey_y1, smookey_w, smookey_h, 255);
    CEntity::EntityList.push_back(smooky1);

    CParticle_Smooky *smooky2 = new CParticle_Smooky(smookey_x2, smookey_y2, smookey_w, smookey_h, 255);
    CEntity::EntityList.push_back(smooky2);

    CParticle_Smooky *smooky3 = new CParticle_Smooky(smookey_x3, smookey_y3, smookey_w, smookey_h, 255);
    CEntity::EntityList.push_back(smooky3);


    OnMove();
    PathLine(POINTS_COUNT);


}

//=============================================================================
void CBulletSmart::OnMove() {

	//SDL_Log("CBulletSmart OnMove()");
	switch(rocketMOVE)
	{
        case DESTROY:
            {
                temp_xbe = points[POINTS_COUNT - 10].x - points[POINTS_COUNT - 1].x;
                temp_ybe = points[POINTS_COUNT - 10].y - points[POINTS_COUNT - 1].y;

                if (ii < POINTS_COUNT)
                {
                    //SDL_Log("rocket DESTROY OnMove()");
                    Xbe = points[ii].x;
                    Ybe = points[ii].y;

                    //SDL_Log("ii %d - Xbe %d - Ybe %d", ii, Xbe, Ybe);

                    if (ii > 10)
                    {
                        double deltaX = curve[ii - 10].x - curve[ii].x;
                        double deltaY = curve[ii - 10].y - curve[ii].y;
                        m = deltaX / deltaY;
                        degrees = atan((double) m) * 180 / PI;

                        if (deltaX > 0 && m < 0) degrees += 180;
                        if (deltaX < 0 && m > 0) degrees -= 180;

                        int tempG = degrees;
                        //SDL_Log("rocket ID %d ii %d deltaY: %1.3f m: %1.3f degree %d",lockID, ii, deltaY, m, -(tempG));
                    } else {
                        degrees = 1;
                    }
                    ii += 10;

                }
                else
                {
                    //SDL_Log("curve finished ii %d - Xbe %d - Ybe %d", ii, Xbe, Ybe);
                    //SDL_Log("temp_xbe 1st %1.3f - temp_xbe 2nd %1.3f", points[POINTS_COUNT - 8].x, points[POINTS_COUNT - 1].x);
                    //SDL_Log("temp_ybe 1st %1.3f - temp_ybe 2nd %1.3f", points[POINTS_COUNT - 8].y, points[POINTS_COUNT - 1].y);
                    //SDL_Log("ii: %d temp_xbe %1.3f temp_ybe %1.3f", ii, temp_xbe, temp_ybe);
                    if (temp_xbe == 0) temp_xbe = 10;
                    if (temp_ybe == 0 ) temp_ybe = 10;

                    m = temp_xbe / temp_ybe;
                    degrees = atan((double) m) * 180 / PI;

                    if (temp_xbe > 0 && m < 0) degrees += 180;
                    if (temp_xbe < 0 && m > 0) degrees -= 180;

                    Xbe -= temp_xbe;
                    Ybe -= temp_ybe;
                }
                //if(lockID == 11) SDL_Log(" rocket ID %d - Xbe - Ybe %d-%d - degree %1.3f", lockID, Xbe, Ybe, degrees);
            }
            break;

        case SEEKandDESTROY:
            {
                Xbe = vet[i][0];
                Ybe = vet[i][1];
                degrees = vetG[i][0];

                //if (lockID == 11) SDL_Log("Xbe - Ybe %d-%d - degrees %d", Xbe, Ybe, degrees);
                i++;
            }
            break;
    }

    shiftColliders();
	//OnAnimate();




}

void CBulletSmart::OnAnimate() {

	if (AnimState < 4) AnimState++;
	else AnimState = 0;

}

//=============================================================================
void CBulletSmart::OnRender() {

    this->X = this->Xbe;
    this->Y = this->Ybe;

    if (entityRenderer)
    {
        TextureBank::Get(entityTexture)->Render(this->X, this->Y, this->Width, this->Height, this->Width * AnimState, 0, this->W2, this->H2, -(degrees), NULL, 255);

        //SDL_SetRenderDrawColor(entityRenderer, 0x00, 0x00, 0xFF, 0xFF);
        //SDL_RenderFillRect(entityRenderer, &ret);

    }
    else
    {

    }
    //SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawLines(Renderer, points, POINTS_COUNT);
    //SDL_RenderDrawPoints(Renderer, points, POINTS_COUNT);

}


//=============================================================================
void CBulletSmart::OnCleanup() {



 }




void CBulletSmart::EntityDEL() {

    //SDL_Log("EntityListSize CBulletEnemy before iterator: %d", CEntity::EntityList.size());

    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead)
        {
            //(*it)->OnCleanup();
            delete *it;
            it = CEntity::EntityList.erase(it);
            SDL_Log("CBulletSmart deleted");
        }
        else
        {
            it++;
        }
    }


    /*
    auto it = EntityList.begin();
    while(it != EntityList.end())
    {
        if(this->Dead)
        {
            SDL_Log("EnemySX_move ID %d deleted", ID);
            it = EntityList.erase(it);
        } else {
            ++it;
        }
    }
    */
    /*
    for(auto& it : EntityList)
    {
        if(it->Dead)
        {
            SDL_Log("BulletSmart ID: %d = DEAD", it->ID);
            EntityList.erase(it);
            delete it;
            //CEntity::EntityList.erase(it);


        }
    }
    */

    //SDL_Log("EntityListSize CBulletEnemy after iterator: %d", CEntity::EntityList.size());



}


//=============================================================================
void CBulletSmart::CollisionLoop() {

    for (int i=0; i<CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i])
        {
            continue;
        }
        CEntity::CheckCollision(CEntity::EntityList[i]);
    }


}


//=============================================================================
bool CBulletSmart::OnCollision(CEntity *Entity) {

	SDL_Log("CBulletSmart OnCollision()");
	this->Dead = true;

	/*
    switch (rand() % 9)
    {
        case 0: anim_filename = "explSX_01"; break;
        case 1: anim_filename = "explSX_02"; break;
        case 2: anim_filename = "explSX_03"; break;
        case 3: anim_filename = "explSX_04"; break;
        case 4: anim_filename = "explSX_05"; break;
        case 5: anim_filename = "explSX_06"; break;
        case 6: anim_filename = "explSX_07"; break;
        case 7: anim_filename = "explSX_08"; break;
        case 8: anim_filename = "explSX_09"; break;
        case 9: anim_filename = "explSX_10"; break;
    }

    int XB = BulletGetX() +7;
    int YB = BulletGetY() +5;



	CParticle_XPL* bulletExplosion = new CParticle_XPL(XB, YB, +2, "boom_02");

    bulletExplosion->particleTexture = anim_filename;
    bulletExplosion->Width  = 64;
    bulletExplosion->Height = 64;
    bulletExplosion->Expired = false;
    bulletExplosion->Type  = ENTITY_TYPE_PARTICLE;
    bulletExplosion->Flags = ENTITY_FLAG_MAPONLY;
    bulletExplosion->Size  = ENTITY_SIZE_PP;

    CEntity::EntityList.push_back(bulletExplosion);
    */


    return true;

}


void CBulletSmart::shiftColliders() {

	//The row offset
	int r = 0;

	//Go through the dot's collision boxes

	//Center the collision box
	mColliders[0].x = this->BulletGetX() + (Width - mColliders[0].w) / 2;

	//Set the collision box at its row offset
	mColliders[0].y = this->BulletGetY() + r;

    ret.h = mColliders[0].h;
    ret.w = mColliders[0].w;
    ret.x = mColliders[0].x;
    ret.y = mColliders[0].y;

	//Move the row offset down the height of the collision box
	r += mColliders[0].h;

	

}


std::vector<SDL_Rect>& CBulletSmart::getColliders() {

	return mColliders;

}

//=============================================================================
bool CBulletSmart::Fire() {

    return true;

}

int CBulletSmart::BulletGetX() {

    return this->Xbe;
}

int CBulletSmart::BulletGetY() {

    return this->Ybe;
}

Point4D CBulletSmart::PointOnCubicBezier(Point4D cp[4], float t, float k)
{
    float   ax, bx, cx;
    float   ay, by, cy;
    float   tSquared, tCubed;
    Point4D result;

    /* calcolo dei coefficienti del polinomio */

    cx = k * (cp[1].x - cp[0].x);
    bx = k * (cp[2].x - cp[1].x) - cx;
    ax = cp[3].x - cp[0].x - cx - bx;

    cy = k * (cp[1].y - cp[0].y);
    by = k * (cp[2].y - cp[1].y) - cy;
    ay = cp[3].y - cp[0].y - cy - by;

    /* calcolo del punto della curva in relazione a t */

    tSquared = t * t;
    tCubed = tSquared * t;

    result.x = (ax * tCubed) + (bx * tSquared) + (cx * t) + cp[0].x;
    result.y = (ay * tCubed) + (by * tSquared) + (cy * t) + cp[0].y;

    //SDL_Log("Medal PointOnCubicBezier()");

    return result;

}
