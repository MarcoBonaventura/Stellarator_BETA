#define _CRT_SECURE_NO_DEPRECATE

#include "CApp.h"
#include "CShield.h"

#include <sstream>
#include <string.h>
#include <cstdlib>

using namespace std;

//=============================================================================
CShield::CShield(int X, int Y) {

    this->Xs = X;
    this->Ys = Y;

    this->Type = ENTITY_TYPE_PLAYER;
    this->Size = ENTITY_SIZE_SX;

    this->Dead      = false;
    this->Expired   = false;

    this->countLoop   = 0;
    this->counter     = 1;

    frameShield = "IMG/PROTOTIPI/shield/png/shield_";
    file_ext    = ".png";

    /** Player fire sound effect */
    //CSoundBank::SoundControl.Play(soundFX);

    CApp::Logger.OnLog( __FILE__, __LINE__, "Shield enabled!", "");

}

//=============================================================================
CShield::~CShield() {


    CApp::Logger.OnLog( __FILE__, __LINE__, "delete CShield()", "");


}



//=============================================================================
bool CShield::OnLoad(char *File, int Width, int Height, int MaxFrames) {


    if(CEntity::OnLoad(File, width, height) == false) {

        CApp::Logger.OnLog( __FILE__, __LINE__, "error loading bmp shield_n file", "");
        return false;
    }

    //CSurface::Transparent(Surf_Entity, 255, 0, 255);

    return true;

}

//=============================================================================
void CShield::OnLoop() {

    CApp::Logger.OnLog( __FILE__, __LINE__, "CShield::OnLoop()", "");

    Xs = CEntity::GetX() -66;
    Ys = CEntity::GetY() -68;

    if(countLoop %2 == 0)
    {
        stringstream strs;
        strs << counter;

        string temp_string = strs.str();
        char const* counter_char = temp_string.c_str();

        strcpy(buffer, frameShield);
        strcat(buffer, counter_char);
        strcat(buffer, ".png");

        OnLoad(buffer, 256, 256, NULL);
        std::cout<<"buffer: "<<buffer<<std::endl;
        if (counter < 15)
        {
            counter++;
        }
        else
        {
            counter = 1;
        }
    }



    IsExpired();


    countLoop++;




}

//=============================================================================
void CShield::OnMove() {



}

//=============================================================================
void CShield::OnRender() {

    X = Xs;
    Y = Ys;
    //CSurface::OnDraw(Surf_Display, Surf_Entity, X, Y, Width, Height);
    CApp::Logger.OnLog( __FILE__, __LINE__, "CShield::OnRender()", "");

}


//=============================================================================
bool CShield::IsExpired() {


    if (countLoop > 1500)
    {
        Dead = true;
        Expired = true;
        std::cout<<"Boss animation expl EXPIRED - *pX2: "<<*pX2<<" *pY2: "<<*pY2<<std::endl;
        CApp::Logger.OnLog( __FILE__, __LINE__, "CShield::IsExpired()", "");
		return true;
    }
	else
	{
		return false;
	}

}


//=============================================================================
void CShield::CollisionLoop() {

    for (Uint32 i=0; i<CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i])
        {
            CApp::Logger.OnLog( __FILE__, __LINE__, "CShield OnLoop EntityList = NULL", "");
            continue;
        }
        CEntity::CheckCollision(CEntity::EntityList[i]);
    }

}

//=============================================================================
bool CShield::OnCollision(CEntity *Entity) {

    CApp::Logger.OnLog( __FILE__, __LINE__, "CShield OnCollision()", "");


    if (Entity->Size == ENTITY_SIZE_BOSS || Entity->Flags == ENTITY_FLAG_ENEMY_F)
    {
        switch (rand() % 9)
        {
            case 0: anim_filename = "IMG/explosion/sx/explSX_01.png"; break;
            case 1: anim_filename = "IMG/explosion/sx/explSX_02.png"; break;
            case 2: anim_filename = "IMG/explosion/sx/explSX_03.png"; break;
            case 3: anim_filename = "IMG/explosion/sx/explSX_04.png"; break;
            case 4: anim_filename = "IMG/explosion/sx/explSX_05.png"; break;
            case 5: anim_filename = "IMG/explosion/sx/explSX_06.png"; break;
            case 6: anim_filename = "IMG/explosion/sx/explSX_07.png"; break;
            case 7: anim_filename = "IMG/explosion/sx/explSX_08.png"; break;
            case 8: anim_filename = "IMG/explosion/sx/explSX_09.png"; break;
            case 9: anim_filename = "IMG/explosion/sx/explSX_10.png"; break;
        }

        int XB = BulletGetX() -20;
        int YB = BulletGetY() -20;

        

        CParticle_XPL *bulletExplosion = new CParticle_XPL(XB, YB, NONE, EXPLOSION, "boom_01");
        if(bulletExplosion->OnLoad(anim_filename, 64, 64, NULL) == false)
        {
            CApp::Logger.OnLog( __FILE__, __LINE__, "Error loading image explosion.png", "");
        }

        CApp::Logger.OnLog( __FILE__, __LINE__, "TRY new CShield", "");
        CEntity::EntityList.push_back(bulletExplosion);
        CApp::Logger.OnLog( __FILE__, __LINE__, "new CShield allocated", "");
       


    }

    std::cout<<"CShield::OnCollision()\n";
    //OnCleanup();
    //OnDeleteBullet();
    //CEntity::OnCollision(Entity);
    //EntityDEL();
    CApp::Logger.OnLog( __FILE__, __LINE__, "end CShield Collision()", "");


    return true;

}


void CShield::shiftColliders() {

    //The row offset
    int r = 0;

    //Go through the dot's collision boxes
    for (Uint32 set=0; set<mColliders.size(); ++set)
    {
        //Center the collision box
        mColliders[set].x = mPosX + (Width - mColliders[set].w) /2;

        //Set the collision box at its row offset
        mColliders[set].y = mPosY + r;

        //Move the row offset down the height of the collision box
        r += mColliders[set].h;
    }

}

std::vector<SDL_Rect>& CShield::getColliders() {

	return mColliders;

}


//=============================================================================
void CShield::OnCleanup() {

    CApp::Logger.OnLog( __FILE__, __LINE__, "CShield::OnCleanup()", "");


 }



void CShield::EntityDEL() {


   
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead == true)
        {
            
            /*(*it)->OnCleanup();*/
            delete *it;
            it = CEntity::EntityList.erase(it);
            CApp::Logger.OnLog( __FILE__, __LINE__, "Entity CShield deleted", "");
          
        }
        else
        {
            it++;
        }
    }
    std::cout<<"EntityListSize CShield after iterator: "<<CEntity::EntityList.size()<<"\n";
    //CApp::Logger.OnLog( __FILE__, __LINE__, "outside Entity CShield vector iterator ", "");
   



}




int CShield::BulletGetX() {

    return this->Xb;
}

int CShield::BulletGetY() {

    return this->Yb;
}
