#include "CApp.h"
#include "CBullet.h"
#include "CMedal.h"
#include "CPlayer.h"


#include <cstdlib>


//=============================================================================
CBullet::CBullet(int X, int Y, int Z, int W, int H, std::string soundFX) {

	//SDL_Log("Bullet player created");

    Xb = X;
    Yb = Y;

    zOffset = Z;

    Type = ENTITY_TYPE_MyBULLET;
    this->Dead = false;


    W2 = W;
    H2 = H;
    //Width = 10;
    //Height = 10;


    /** Player fire sound effect */
    //CSoundBank::SoundControl.Play2(soundFX);
	//CSoundBank::SoundControl.PlayOGG("test2.ogg");

	SDL_Log("Ply bullet ID: %d", this->ID);
}

//=============================================================================
CBullet::~CBullet() {


    CApp::Logger.OnLog( __FILE__, __LINE__, "delete CBullet()", "");



}


void CBullet::OnInit() {

    mColliders.resize(1);

    mVelX = 0;
    mVelY = 0;

    // x - y
    // 17 - 17


    switch(CPlayer::PlayerStat.mySHIP)
    {
        case 1:
            mColliders[0].w = 22;
            mColliders[0].h = 60;
            break;

        case 2:
            mColliders[0].w = 25;
            mColliders[0].h = 45;
            break;

        case 3:
            mColliders[0].w = 22;
            mColliders[0].h = 60;
            break;

        case 4:
            mColliders[0].w = 22;
            mColliders[0].h = 60;
            break;
    }

    mColliders[0].w = mColliders[0].w * OVERALL_BULLET_RATIO;
    mColliders[0].h = mColliders[0].h * OVERALL_BULLET_RATIO;

    //Initialize colliders relative to position
	shiftColliders();


}


void CBullet::shiftColliders() {

    //The row offset

    switch(CPlayer::PlayerStat.mySHIP)
    {
        case 1:
            r = 0;
            break;

        case 2:
            r = 17 * OVERALL_BULLET_RATIO;
            break;

        case 3:
            r = 0;
            break;

        case 4:
            r = 0;
            break;
    }

    //Go through the dot's collision boxes

    //Center the collision box
    mColliders[0].x = BulletGetX() + (Width - mColliders[0].w) / 2;

    //Set the collision box at its row offset
    mColliders[0].y = BulletGetY() + r;

    ret.h = mColliders[0].h;
    ret.w = mColliders[0].w;
    ret.x = mColliders[0].x;
    ret.y = mColliders[0].y;

    //Move the row offset down the height of the collision box
    r += mColliders[0].h;


}


//=============================================================================
bool CBullet::OnLoad(char *File, int Width, int Height, int MaxFrames) {

    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }

    return true;

}

//=============================================================================
void CBullet::OnLoop() {

    //SDL_Log("Bullet ID %d start loop", this->ID);

    OnMove();
    shiftColliders();
	CollisionLoop();

    int horizon = BulletGetY();
    int sidewall = BulletGetX();
    if (horizon < 0 || sidewall < 0 || sidewall > WWIDTH)
    {
        this->Dead = true;
        //EntityDEL();
        //OnDeleteBullet();
        //OnCleanup();
    }

    /*
    if (zOffset < 0) zOffset += -1;
    else if (zOffset == 0) zOffset = 0;
    else if (zOffset > 0) zOffset += 1;
    */

    //SDL_Log("EnemyXS ID %d  end loop", this->ID);


}

//=============================================================================
void CBullet::OnMove() {

    //Yb += -((CFPS::FPSControl.GetSpeedFactor() * 30) );
    shiftColliders();

    Yb += -30 * OVERALL_SPEED_RATIO;
    Xb += zOffset;

}

//=============================================================================
void CBullet::OnRender() {

    X = Xb;
    Y = Yb;

	if (entityRenderer)
	{
		//SDL_Log("Bullet player Renderer");
		TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, 0, 0, W2, H2, 255);

        //SDL_SetRenderDrawColor(entityRenderer, 0x00, 0xFF, 0x00, 0xFF);
        //SDL_RenderFillRect(entityRenderer, &ret);

	}
	else
	{
		SDL_Log("bad Bullet player Renderer, error %s", SDL_GetError());
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

    //CApp::Logger.OnLog( __FILE__, __LINE__, "CBullet::OnRender()", "");

}


//=============================================================================
void CBullet::CollisionLoop() {

    //CApp::Logger.OnLog( __FILE__, __LINE__, "CBullet::CollisionLoop()", "");

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
bool CBullet::OnCollision(CEntity *Entity) {



    SDL_Log("entity Bullet ID: %d collision with entity ID: %d", this->ID, Entity->ID);

    //if (Entity->Size == ENTITY_SIZE_BOSS || Entity->Flags == ENTITY_FLAG_ENEMY_F || Entity->Flags == ENTITY_FLAG_ENEMY_M)
    if (Entity->Type == ENTITY_TYPE_ENEMY || Entity->Type == ENTITY_TYPE_BOSS)
    {
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
            default:anim_filename = "explSX_01"; break;
        }

        int XB = BulletGetX() -20;
        int YB = BulletGetY() -20;

       

        CParticle_XPL* bulletExplosion = new CParticle_XPL(XB, YB, NONE, EXPLOSION, "boom_02");

        bulletExplosion->particleTexture = anim_filename;
        bulletExplosion->W2      = 64;
        bulletExplosion->H2      = 64;
        bulletExplosion->Width   = bulletExplosion->W2 * OVERALL_RATIO;
        bulletExplosion->Height  = bulletExplosion->H2 * OVERALL_RATIO;
        bulletExplosion->Expired = false;
        bulletExplosion->Dead    = false;
        bulletExplosion->Type    = ENTITY_TYPE_PARTICLE;
        bulletExplosion->Flags   = ENTITY_FLAG_MAPONLY;
        bulletExplosion->Size    = ENTITY_SIZE_PP;

        CEntity::EntityList.push_back(bulletExplosion);

        Dead = true;

    }



    return true;

}




std::vector<SDL_Rect>& CBullet::getColliders() {

	return mColliders;

}


//=============================================================================
bool CBullet::Fire() {

    return true;

}


//=============================================================================
void CBullet::OnCleanup() {



 }



void CBullet::EntityDEL() {

    CEntity::EntityDEL();

/*
   
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead == true)
        {
            SDL_Log("delete Bullet ID: %d",(*it)->ID);
			(*it)->OnCleanup();
			delete (*it);
			(it) = CEntity::EntityList.erase(it);

            
        }
        else
        {
            it++;
        }
    }
    //std::cout<<"EntityListSize CBullet after iterator: "<<CEntity::EntityList.size()<<"\n";
    //CApp::Logger.OnLog( __FILE__, __LINE__, "outside Entity CBullet vector iterator ", "");
*/


}




int CBullet::BulletGetX() {

    return this->Xb;
}

int CBullet::BulletGetY() {

    return this->Yb;
}



