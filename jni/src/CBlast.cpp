#include "CBlast.h"
#include "CApp.h"



//=============================================================================
CBlast::CBlast(int X, int Y, int soundFX) {

    this->Xb = X;
    this->Yb = Y;

    this->X2 = 0;

    Type = ENTITY_TYPE_MyBULLET;
    Size = ENTITY_SIZE_BOMB;

    Dead = false;


    counter = 0;

    /** Player fire sound effect */
    //CSoundBank::SoundControl.Play(soundFX);

}

//=============================================================================
CBlast::~CBlast() {


    CApp::Logger.OnLog( __FILE__, __LINE__, "delete CBlast()", "");


}



//=============================================================================
bool CBlast::OnLoad(char *File, int Width, int Height, int MaxFrames) {

    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        CApp::Logger.OnLog( __FILE__, __LINE__, "errore loading CBlast image file...", "");
        return false;
    }

    //CSurface::Transparent(Surf_Entity, 255, 0, 255);

    return true;

}

//=============================================================================
void CBlast::OnLoop() {


    //OnMove();
    if (counter %6 == 0) this->X2 += 134;

    if (counter >= 73) Dead = true;

    counter++;

}

//=============================================================================
void CBlast::OnMove() {



}

//=============================================================================
void CBlast::OnRender() {

    X = Xb;
    Y = Yb;
    //Texture::Texture(Surf_Display, Surf_Entity, X, Y, this->X2, 0, 134, 134);

}

//=============================================================================
void CBlast::OnCleanup() {

    CApp::Logger.OnLog( __FILE__, __LINE__, "CBlast::OnCleanup()", "");


 }



void CBlast::EntityDEL() {


    
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead == true)
        {
           
            /*(*it)->OnCleanup();*/
            delete *it;
            it = CEntity::EntityList.erase(it);
            CApp::Logger.OnLog( __FILE__, __LINE__, "Entity CBlast deleted", "");
           
        }
        else
        {
            it++;
        }
    }
    //CApp::Logger.OnLog( __FILE__, __LINE__, "outside Entity CBullet vector iterator ", "");
   



}

//=============================================================================
bool CBlast::OnCollision(CEntity *Entity) {


    CApp::Logger.OnLog( __FILE__, __LINE__, "CBlast OnCollision()", "");
    //Dead = true;





    CApp::Logger.OnLog( __FILE__, __LINE__, "end CBlast Collision()", "");


    return true;

}


//=============================================================================
void CBlast::CollisionLoop() {

	for (Uint32 i = 0; i<CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i])
        {
            CApp::Logger.OnLog( __FILE__, __LINE__, "CBlast EntityList = NULL", "");
            continue;
        }
        CEntity::CheckCollision(CEntity::EntityList[i]);
    }


}

void CBlast::shiftColliders() {

    //The row offset
    int r = 0;

    //Go through the dot's collision boxes
	for (Uint32 set = 0; set<mColliders.size(); ++set)
    {
        //Center the collision box
        mColliders[set].x = mPosX + (Width - mColliders[set].w) /2;

        //Set the collision box at its row offset
        mColliders[set].y = mPosY + r;

        //Move the row offset down the height of the collision box
        r += mColliders[set].h;
    }

}


std::vector<SDL_Rect>& CBlast::getColliders() {

	return mColliders;

}

//=============================================================================
bool CBlast::OnExplode() {

    Dead = true;

	return true;

}



int CBlast::BlastGetX() {

    return this->Xb;
}

int CBlast::BlastGetY() {

    return this->Yb;
}
