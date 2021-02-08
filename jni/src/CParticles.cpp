#include "CParticles.h"
#include "CPlayer.h"
#include "CApp.h"


//CParticles  CParticles::ParticlesEngine;

CParticles::CParticles() {

    Flags = ENTITY_FLAG_MAPONLY;

    Expired = false;


}


//=============================================================================
bool CParticles::OnLoad(char *File, int Width, int Height) {

    if(CEntity::OnLoad(File, Width, Height) == false) {

        return false;
    }

    return true;


}


//=============================================================================
void CParticles::OnRender() {

    //CEntity::OnRender();

}



//=============================================================================
void CParticles::OnLoop() {


}


//=============================================================================
void CParticles::OnMove() {


}

//=============================================================================
bool CParticles::IsExpired() {

	return true;

}

int CParticles::particleGetX() {

    return Xp;

}


int CParticles::particleGetY() {

    return Yp;

}


void CParticles::shiftColliders() {



}

std::vector<SDL_Rect>& CParticles::getColliders() {

	return mColliders;

}


//=============================================================================
void CParticles::OnDeleteParticle() {

    //CApp::Logger.OnLog( __FILE__, __LINE__, "particle deleted", "");
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead == true)
        {
            (*it)->OnCleanup();
            delete (*it);
            it = CEntity::EntityList.erase(it);
            std::cout<<"particle DELETED!\n";
            //std::cout<<"EntityList after particle DEL: "<<EntityList.size()<<"\n";
            /*
            char TempC[255];
            int Temp = CEntity::EntityList.size();
            int n = sprintf(TempC, "%d", Temp);
            CApp::Logger.OnLog( __FILE__, __LINE__, "EntityLIST size after iterator CBULLET", TempC);
            */
        }
        else
        {
            it++;
        }
    }


}


//=============================================================================
void CParticles::OnCleanup() {

    CEntity::OnCleanup();

}



//=============================================================================
CParticles::~CParticles() {

}
