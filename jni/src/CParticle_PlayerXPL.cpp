#include "CParticle_PlayerXPL.h"



CParticle_PlayerXPL::CParticle_PlayerXPL(int x, int y, char* soundFX, eFlag F) {


    X = x;
    Y = y;
    X2 = Y2 = 0;
    iY = kX = 0;

    yVelocity = F;

    Type = ENTITY_TYPE_PARTICLE;
    Flags = ENTITY_FLAG_MAPONLY;
    Dead = false;
    Expired = false;

    CSoundBank::SoundControl.Play2(soundFX);

    SDL_Log("Particle Player XPL");

}

CParticle_PlayerXPL::~CParticle_PlayerXPL() {

}


//=============================================================================
bool CParticle_PlayerXPL::OnLoad(char *File, int Width, int Height, int MaxFrames) {

    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {

        CApp::Logger.OnLog( __FILE__, __LINE__, "error loading png file ", "");
        return false;
    }

    return true;
}


//=============================================================================
void CParticle_PlayerXPL::OnRender() {

    if (entityRenderer)
    {
        //SDL_Log("xpl render X2 %d - Y2 %d", X2, Y2);
        TextureBank::Get(particleTexture)->Render(this->X, this->Y, this->Width, this->Height, X2, Y2, W2, H2, 255);
    }
    else
    {
        SDL_Log("Particle_PLY::OnRender() BAD RENDERER! %s", SDL_GetError());
    }

}


//=============================================================================
void CParticle_PlayerXPL::OnCleanup() {



    CEntity::OnCleanup();

}


//=============================================================================
void CParticle_PlayerXPL::OnLoop() {

    if (iY < 8)
    {
        if (kX < 8)
        {
            X2 = W2 * kX;
        }
        else if (kX == 8)
        {
            kX = 0;
            iY++;
            //X2 += H2;
            X2 = 0;
            Y2 = H2 * iY;
        }

    }
    kX++;

    if (iY >= 8) {
        Dead = true;
        Expired = true;
    }

    OnMove();


}

void CParticle_PlayerXPL::OnMove() {

    switch(yVelocity)
    {
        case ENTITY_FLAG_ENEMY_M:
            Y += 2;
        break;

        case ENTITY_FLAG_ENEMY_F:
            //yBoom = yBoom;
        break;

        case ENTITY_FLAG_PLAYER:
        break;

        default:
            Y += 2;
        break;
    }



}


//=============================================================================
bool CParticle_PlayerXPL::IsExpired() {


    if (iY >= 8)
    {
        Dead = true;
        Expired = true;
    	return true;
    }
	else
	{
		return false;
	}

}


void CParticle_PlayerXPL::shiftColliders() {

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

std::vector<SDL_Rect>& CParticle_PlayerXPL::getColliders() {

	return mColliders;

}


//=============================================================================
void CParticle_PlayerXPL::EntityDEL() {

    CEntity::EntityDEL();

    /*
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead)
        {
            delete *it;
            it = CEntity::EntityList.erase(it);

        }
        else
        {
            it++;
        }
    }
    */

}
