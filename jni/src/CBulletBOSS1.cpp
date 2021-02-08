#include "CApp.h"
#include "CBulletBOSS1.h"
#include "CPlayer.h"
#include "CEnemyBOSS1.h"

#include <cstdlib>


//=============================================================================
CBulletBOSS1::CBulletBOSS1(int x1, int y1, char* soundFX, eFlag F) {

    
    this->X = x1;
    this->Y = y1;

	selectCollider = F;
	Type = ENTITY_TYPE_BULLET_E;
	Size = ENTITY_SIZE_BB;

	MoveUp = MoveLeft = MoveRight = false;
	MoveDown = true;

    degree = i = j = 0;

    Dead = false;
    isAlive = true;
    enemyOFFSET.x = x1;
    enemyOFFSET.y = y1;
    kAcc = 1;


    /** Player fire sound effect */
    CSoundBank::SoundControl.Play2(soundFX);


}

//=============================================================================
CBulletBOSS1::~CBulletBOSS1() {


}



//=============================================================================
bool CBulletBOSS1::OnLoad(char *File, int Width, int Height, int MaxFrames) {

    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }

    return true;

}


void CBulletBOSS1::OnInit() {

    mVelX = 0;
    mVelY = 0;

    switch(selectCollider)
    {
        case ENTITY_FLAG_ENEMY_M:
            mColliders.resize(1);
            mColliders[0].w = 32;
            mColliders[0].h = 9;
        break;

        case ENTITY_FLAG_ENEMY_F:
            mColliders.resize(1);
            mColliders[0].w = 13;
            mColliders[0].h = 13;
        break;

        case ENTITY_FLAG_BOSS:
            mColliders.resize(1);
            mColliders[0].w = Width;
            mColliders[0].h = Height;
        break;

        default:
            mColliders.resize(1);
            mColliders[0].w = 30;
            mColliders[0].h = 40;
        break;
    }
    for (int set = 0; set < mColliders.size(); set++)
    {
        mColliders[set].w = mColliders[set].w * OVERALL_ENEMY_RATIO;
        mColliders[set].h = mColliders[set].h * OVERALL_ENEMY_RATIO;
    }
	shiftColliders();
	
}

void CBulletBOSS1::shiftColliders() {

    switch (this->selectCollider)
    {
        case ENTITY_FLAG_ENEMY_M:
            r = 0;
            break;

        case ENTITY_FLAG_ENEMY_F:
            r = 0;
            break;

        case ENTITY_FLAG_BOSS:
           //r = 28 * OVERALL_ENEMY_RATIO;
            r = 0;
            break;

        default:
            r = 0;
            break;
    }

    for (int set = 0; set < mColliders.size(); set++)
    {
        mColliders[set].x = BulletGetX() + (Width - mColliders[set].w) /2;
        mColliders[set].y = BulletGetY() + r;
        r += mColliders[set].h;
    }

}

//=============================================================================
void CBulletBOSS1::OnLoop() {

    OnMove();
	shiftColliders();
	CollisionLoop();

    int horizon   = BulletGetY();
    int ordBullet = BulletGetX();

    if (horizon > WHEIGHT || ordBullet < 0 || ordBullet > WWIDTH)
    {
        Dead = true;
    }


}

//=============================================================================
void CBulletBOSS1::OnMove() {

    switch (Move) {

        case NONE:
            Y += 30 * OVERALL_SPEED_RATIO;
            break;

        case SNAKE:

            if (BulletGetX() > enemyOFFSET.x + 20 * OVERALL_RATIO) {
                MoveRight = false;
                MoveLeft = true;
            }
            if (BulletGetX() < enemyOFFSET.x - 20 * OVERALL_RATIO) {
                MoveLeft = false;
                MoveRight = true;
            }

            if (MoveDown)   {
                Y += (1 + kAcc) * OVERALL_SPEED_RATIO;
                kAcc++;
            }
            if (MoveRight)  X += 1 * OVERALL_SPEED_RATIO;
            if (MoveLeft)   X -= 1 * OVERALL_SPEED_RATIO;

            break;
    }



}

//=============================================================================
void CBulletBOSS1::OnRender() {

    if (entityRenderer)
    {
        TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, 0, 0, W2, H2, 255);
    }
    else
    {
        SDL_Log("BulletBoss::OnRender() BAD RENDERER! %s", SDL_GetError());
    }

}


//=============================================================================
void CBulletBOSS1::OnCleanup() {


 }




void CBulletBOSS1::EntityDEL() {

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

            /*
            for (int i=0; i<MaxRow; i++)
            {
                delete [] vet[i];
            }
            delete [] vet;
            */

             /*
        }
        else
        {
            it++;
        }
    }
    std::cout<<"EntityListSize CBulletBOSS1 after iterator: "<<CEntity::EntityList.size()<<"\n";
    //CApp::Logger.OnLog( __FILE__, __LINE__, "outside Entity CBullet vector iterator ", "");
   
    */


}

//=============================================================================
bool CBulletBOSS1::OnCollision(CEntity *Entity) {

    Dead = true;


    std::cout<<"CBulletBOSS1::OnCollision()";

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
    int YB = BulletGetY() + Height / 2;

    bulletExplosion = new CParticle_XPL(XB, YB, NONE, EXPLOSION, "boom_02");

    bulletExplosion->particleTexture = anim_filename;
    bulletExplosion->W2 = 64;
    bulletExplosion->H2 = 64;
    bulletExplosion->Width  = bulletExplosion->W2 * OVERALL_RATIO;
    bulletExplosion->Height = bulletExplosion->H2 * OVERALL_RATIO;

    CEntity::EntityList.push_back(bulletExplosion);
    
    return true;

}


void CBulletBOSS1::CollisionLoop() {

	for (Uint32 i = 0; i<CEntity::EntityList.size(); i++)
	{
		if (!CEntity::EntityList[i])
		{
			continue;
		}
		CEntity::CheckCollision(CEntity::EntityList[i]);
	}

}


std::vector<SDL_Rect>& CBulletBOSS1::getColliders() {

	return mColliders;

}

//=============================================================================
bool CBulletBOSS1::Fire() {

    return true;

}

int CBulletBOSS1::BulletGetX() {

    return this->X;
}

int CBulletBOSS1::BulletGetY() {

    return this->Y;
}
