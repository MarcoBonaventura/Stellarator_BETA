#include "CApp.h"
#include "CBomb.h"

#include "CPlayer.h"

#include "CParticle_Smoke.h"



//=============================================================================
CBomb::CBomb(int X, int Y, int soundFX) {

    this->Xb = X;
    this->Yb = Y;

    Y2 = 0;
    X2 = 0;

    Type = ENTITY_TYPE_MyBULLET;
    Size = ENTITY_SIZE_PB;
    Flags = ENTITY_FLAG_NONE;

    Dead = false;
    expired = false;

    kAcc = 0.004;

    counter = 0;

    /** Player fire sound effect */
    //CSoundBank::SoundControl.Play(soundFX);
    SDL_Log("Rocket standard created");

}

//=============================================================================
CBomb::~CBomb() {


    CApp::Logger.OnLog( __FILE__, __LINE__, "delete CBomb()", "");


}


void CBomb::OnInit() {

    mColliders.resize(1);

    mVelX = 0;
    mVelY = 0;

    // x - y
    // 17 - 17
    mColliders[0].w = this->Width;
    mColliders[0].h = this->Height;

    shiftColliders();

    // Muzzle Effects
    /*
    MuzzleSX = "Rocket_small2_glow_green";
    MuzzleDX = "Rocket_small2_glow_green";
    SDL_Point pnt_muzzle_sx;
    SDL_Point pnt_muzzle_dx;
    pnt_muzzle_sx.x = Xb;
    pnt_muzzle_sx.y = Yb + Height;

    int MuzzleW = 39;
    int MuzzleH = 200;

    CParticle_Smoke *RocketGlow = new CParticle_Smoke(MuzzleSX, MuzzleDX,
                                                          15, 75,
                                                          MuzzleW, MuzzleH,
                                                          pnt_muzzle_sx, 1);
    CEntity::EntityList.push_back(RocketGlow);
    */

}



//=============================================================================
bool CBomb::OnLoad(char *File, int Width, int Height, int MaxFrames) {

    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        CApp::Logger.OnLog( __FILE__, __LINE__, "errore loading CBomb image file...", "");
        return false;
    }

    return true;

}

//=============================================================================
void CBomb::OnLoop() {

    shiftColliders();

    OnMove();

    CollisionLoop();


    if (BombGetY() < -70)
    {
        expired = true;
        //Dead = true;
        //
    }
    if (expired)
    {
        if(alpha > 0)
        {
            alpha--;
        }
        else
        {
            Dead = true;
        }
    }

    //if (counter %5 == 0) Smog();


    if (counter == 4) counter = 0;
    X2 = counter * W2;

    counter++;

}

//=============================================================================
void CBomb::OnMove() {

    shiftColliders();

    //Yb += -((CFPS::FPSControl.GetSpeedFactor() * 30) );
    Yb += -1 *kAcc;
    kAcc += 0.3;

    shiftColliders();

}


void CBomb::Smog() {

    SDL_Log("smog emitted");

    SDL_Point offset;
    offset.x = this->BombGetX()+10;
    offset.y = this->BombGetY() + 67;

    char* str1 = "smog1";
    char* str2 = "smog1";

    CParticle_Smoke* smookey = new CParticle_Smoke(str1, str2, 20, 20, 39, 39, offset, 2, this->ID);

    SDL_Log("smog added");

    CEntity::EntityList.push_back(smookey);

    SDL_Log("rocket ID %d", ID);
   // CEntity::EntityMap[this->ID]=smookey;


}

//=============================================================================
void CBomb::OnRender() {

    X = Xb;
    Y = Yb;
    if (entityRenderer)
    {
        //SDL_Log("Bullet player Renderer");
        TextureBank::Get(entityTexture)->Render(this->X, this->Y, this->Width, this->Height, X2, Y2, this->W2, this->H2, 255);
    }
    else
    {
        SDL_Log("bad Bullet player Renderer, error %s", SDL_GetError());
        CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
    }

}

//=============================================================================
void CBomb::OnCleanup() {

    CApp::Logger.OnLog( __FILE__, __LINE__, "CBomb::OnCleanup()", "");



 }



void CBomb::EntityDEL() {


    
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead == true)
        {
            
            /*(*it)->OnCleanup();*/
            delete *it;
            it = CEntity::EntityList.erase(it);
            CApp::Logger.OnLog( __FILE__, __LINE__, "Entity CBomb deleted", "");
            
        }
        else
        {
            it++;
        }
    }
    //CApp::Logger.OnLog( __FILE__, __LINE__, "outside Entity CBullet vector iterator ", "");
    



}

//=============================================================================
bool CBomb::OnCollision(CEntity *Entity) {


    if (Entity->Size == ENTITY_SIZE_BOSS || Entity->Flags == ENTITY_FLAG_ENEMY_F || Entity->Flags == ENTITY_FLAG_ENEMY_M)
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

        int XB = BombGetX() -20;
        int YB = BombGetY() -20;



        CParticle_XPL* bulletExplosion = new CParticle_XPL(XB, YB, NONE, EXPLOSION, "boom_02");

        bulletExplosion->particleTexture = anim_filename;
        bulletExplosion->Width   = 64;
        bulletExplosion->Height  = 64;
        bulletExplosion->Expired = false;
        bulletExplosion->Dead    = false;
        bulletExplosion->Type    = ENTITY_TYPE_PARTICLE;
        bulletExplosion->Flags   = ENTITY_FLAG_MAPONLY;
        bulletExplosion->Size    = ENTITY_SIZE_PP;

        CApp::Logger.OnLog( __FILE__, __LINE__, "TRY new EnemyBullet CParticle_XPL()", "");
        CEntity::EntityList.push_back(bulletExplosion);



    }

    /** UNDER TESTING!!
    if (CPlayer::PlayerStat.PlayerHealth < 30)
    {
        int jolly = rand() % 10;
        if (jolly = 1)
        {
            int x = BulletGetX();
            int y = BulletGetY();
            int r = 20;

            CMedal *MedalHonor = new CMedal(x, y, 100, 50, 0, r, 7);

            if (MedalHonor->OnLoad("IMG/PROTOTIPI/MedalShield.png") == false)
            {
                CApp::Logger.OnLog( __FILE__, __LINE__, "Error loading image Medal honor", "");
            }
            CEntity::EntityList.push_back(MedalHonor);
        }
    }
    */


    Dead = true;

    CApp::Logger.OnLog( __FILE__, __LINE__, "BULLET OnCollision END", "");

    return true;

}


//=============================================================================
void CBomb::CollisionLoop() {

    for (int i=0; i<CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i])
        {
            CApp::Logger.OnLog( __FILE__, __LINE__, "CBullet OnLoop EntityList = NULL", "");
            continue;
        }
        //if(this != CEntity::EntityList[i])
        CEntity::CheckCollision(CEntity::EntityList[i]);
    }

}


void CBomb::shiftColliders() {

    //The row offset
    //int r = 17;
    int r = 0;

    //Go through the dot's collision boxes

    //Center the collision box
    mColliders[0].x = BombGetX() + (Width - mColliders[0].w) /2;

    //Set the collision box at its row offset
    mColliders[0].y = BombGetY() + r;

    //Move the row offset down the height of the collision box
    //r += mColliders[0].h;
}

std::vector<SDL_Rect>& CBomb::getColliders() {

	return mColliders;

}

//=============================================================================
bool CBomb::OnExplode() {

    Dead = true;

	return true;

}

//=============================================================================
bool CBomb::DropBomb() {

    return true;

}

int CBomb::BombGetX() {

    return Xb;
}

int CBomb::BombGetY() {

    return Yb;
}

int CBomb::EnemyGetX() {

    return this->Xb;
}

int CBomb::EnemyGetY() {

    return this->Yb;
}
