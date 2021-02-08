#include "CApp.h"
#include "CBulletEnemy_S.h"
#include "CParticle_XPL.h"
#include "Stringify.h"

#include <cstdlib>


//=============================================================================
CBulletEnemy_S::CBulletEnemy_S(int x1, int y1, float speed, float g, char* soundFX, eFlag F) {


    //SDL_Log("Bullet Enemy S exploded");
    //SDL_Log("x: %d - y: %d", x1, y1);

    X = x1;
    Y = y1;
	speedBullet = speed * OVERALL_SPEED_RATIO;
	gBullet = g;
    selectCollider = F;
    this->AnimState = 0;
    Dead = false;

    Type = ENTITY_TYPE_BULLET_E;
    Size = ENTITY_SIZE_BB;

    /** Player fire sound effect */
    CSoundBank::SoundControl.Play2(soundFX);


}

//=============================================================================
CBulletEnemy_S::~CBulletEnemy_S() {


}

void CBulletEnemy_S::OnInit() {

    mVelX = 0;
    mVelY = 0;


    switch(selectCollider)
    {
        case ENTITY_FLAG_ENEMY_S:
            mColliders.resize(1);
            mColliders[0].w = 25;
            mColliders[0].h = 40;
        break;

        case ENTITY_FLAG_ENEMY_M:
            mColliders.resize(1);
            mColliders[0].w = 23;
            mColliders[0].h = 37;
        break;

        case ENTITY_FLAG_ENEMY_M2:
            mColliders.resize(1);
            mColliders[0].w = 24;
            mColliders[0].h = 24;
            break;

        case ENTITY_FLAG_ENEMY_F:
            mColliders.resize(1);
            mColliders[0].w = 24;
            mColliders[0].h = 48;
        break;

        default:
            mColliders.resize(1);
            mColliders[0].w = 32;
            mColliders[0].h = 9;
        break;
    }

    for (int set = 0; set < mColliders.size(); ++set)
    {
        mColliders[set].w = mColliders[set].w * OVERALL_ENEMY_RATIO;
        mColliders[set].h = mColliders[set].h * OVERALL_ENEMY_RATIO;
    }

    shiftColliders();

}

void CBulletEnemy_S::shiftColliders() {

    switch (selectCollider)
    {
        case ENTITY_FLAG_ENEMY_S:
            r = 0;
            break;

        case ENTITY_FLAG_ENEMY_M:
            r = 46 * OVERALL_ENEMY_RATIO;
            break;

        case ENTITY_FLAG_ENEMY_M2:
            r = 17 * OVERALL_ENEMY_RATIO;
            break;

        case ENTITY_FLAG_ENEMY_F:
            r = 65 * OVERALL_ENEMY_RATIO;
            break;

        default:
            r = 0;
            break;
    }

    //Go through the dot's collision boxes
    for (int set=0; set<mColliders.size(); ++set)
    {
        //Center the collision box
        mColliders[set].x = BulletGetX() + (Width - mColliders[set].w) /2;

        //Set the collision box at its row offset
        mColliders[set].y = BulletGetY() + r;

        //Move the row offset down the height of the collision box
        r += mColliders[set].h;
    }

}

//=============================================================================
bool CBulletEnemy_S::OnLoad(char *File, int Width, int Height, int MaxFrames) {

    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }

    return true;

}

//=============================================================================
void CBulletEnemy_S::OnLoop() {

    OnMove();
    shiftColliders();
	CollisionLoop();

    int horizon   = BulletGetY();

    if (horizon > WHEIGHT + 50)
    {
        Dead = true;
    }



}

//=============================================================================
void CBulletEnemy_S::OnMove() {

	Y += speedBullet;

    OnAnimate();

}

void CBulletEnemy_S::OnAnimate() {

	//if (this->AnimState < 12) this->AnimState++;
	//else AnimState = 0;

}

//=============================================================================
void CBulletEnemy_S::OnRender() {

    if (entityRenderer)
    {
		TextureBank::Get(entityTexture)->Render(this->X, this->Y, this->Width, this->Height, this->Width * this->AnimState, 0, this->W2, this->H2, 255);
    }
    else
    {
        SDL_Log("BulletEnemy_S::OnRender() BAD RENDERER! %s", SDL_GetError());
    }


}


//=============================================================================
void CBulletEnemy_S::OnCleanup() {


 }




void CBulletEnemy_S::EntityDEL() {

    CEntity::EntityDEL();

    /*
   
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead == true)
        {
            
            delete *it;
            it = CEntity::EntityList.erase(it);
            CApp::Logger.OnLog( __FILE__, __LINE__, "Entity CBulletEnemy_S deleted", "");
           
        }
        else
        {
            it++;
        }
    }
    std::cout<<"EntityListSize CBulletEnemy_S after iterator: "<<CEntity::EntityList.size()<<"\n";
   
    */


}

//=============================================================================
bool CBulletEnemy_S::OnCollision(CEntity *Entity) {

    Dead = true;

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

    int XB = BulletGetX() + Width / 2;
    int YB = BulletGetY()  + Height / 2;

   

    CParticle_XPL *bulletExplosion = new CParticle_XPL(XB, YB, NONE, EXPLOSION, "boom_02");

    bulletExplosion->particleTexture = anim_filename;
    bulletExplosion->W2 = 64;
    bulletExplosion->H2 = 64;
    bulletExplosion->Width  = bulletExplosion->W2 * OVERALL_RATIO;
    bulletExplosion->Height = bulletExplosion->W2 * OVERALL_RATIO;

    CEntity::EntityList.push_back(bulletExplosion);
   



    return true;

}


//=============================================================================
void CBulletEnemy_S::CollisionLoop() {

    for (int i=0; i<CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i])
        {
            continue;
        }
        CEntity::CheckCollision(CEntity::EntityList[i]);
    }


}


std::vector<SDL_Rect>& CBulletEnemy_S::getColliders() {

	return mColliders;

}

//=============================================================================
bool CBulletEnemy_S::Fire() {

    return true;

}

int CBulletEnemy_S::BulletGetX() {

    return this->X;
}

int CBulletEnemy_S::BulletGetY() {

    return this->Y;
}
