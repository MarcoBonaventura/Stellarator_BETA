#define _CRT_SECURE_NO_DEPRECATE

#include "CParticle_BossXPL.h"

#include <sstream>
#include <string.h>

#include "Stringify.h"

#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

using namespace std;

CParticle_BossXPL::CParticle_BossXPL(int x, int y, char* soundFX) {



    xBoom = x;
    yBoom = y;

    X2 = Y2 = 0;
    i = k = 0;

    frameXPL    = "explosion_";
    //file_ext    = ".png";

    counter = 10001;
    countLoop = 0;

    finaleFrameXPL = "10001";

    Expired = false;

    //CSoundBank::SoundControl.Play2(soundFX);

	//LOGD("Boss Explosion()\n");

}

CParticle_BossXPL::~CParticle_BossXPL() {



}


//=============================================================================
bool CParticle_BossXPL::OnLoad(char *File, int Width, int Height, int MaxFrames) {

    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {

        CApp::Logger.OnLog( __FILE__, __LINE__, "error loading png file", "");
        return false;
    }

    return true;
}


//=============================================================================
void CParticle_BossXPL::OnRender() {

    X = xBoom;
    Y = yBoom;

    X2 = *pX2;
    Y2 = *pY2;


    //std::cout<<"OnRenderExplosion\n";
                //std::cout<<"X2b: "<<X2b<<" Y2b: "<<Y2b<<std::endl;
    //CEntity::OnRender(Surf_Display);
    //std::cout<<"xBoom: "<<X<<" yBoom: "<<Y<<std::endl;
    //CSurface::OnDraw(Surf_Display, Surf_Entity, X, Y, X2, Y2, Width, Height, 0);

    //CSurface::OnDraw(Surf_Display, Surf_Entity, X, Y, X2b, Y2b, width, height);
    //CApp::Logger.OnLog( __FILE__, __LINE__, "CParticle_XPL::OnRender()", "");

    if (entityRenderer)
    {
        TextureBank::Get(particleTexture)->Render(this->X, this->Y, this->Width, this->Height, X2, Y2, this->Width, this->Height, 255);
    }
    else
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "bad Renderer", "");
    }



}


//=============================================================================
void CParticle_BossXPL::OnCleanup() {

    CEntity::OnCleanup();

}


//=============================================================================
void CParticle_BossXPL::OnLoop() {

    if(countLoop %4 == 0)
    {
        stringstream strs;
        strs << counter;
		//LOGD("Boss Explosion strs: %s", strs.c_str());


        string temp_string = strs.str();
        char const* counter_char = temp_string.c_str();

        strcpy(buffer, frameXPL);
        strcat(buffer, counter_char);

		//LOGD("Boss Explosion buffer: %s", buffer);

        particleTexture = Stringify::Char(buffer);
		//LOGD("Boss Explosion step2");
        //OnLoad(buffer, 320, 240, NULL);
        counter++;
    }


    IsExpired();
    countLoop++;

}

void CParticle_BossXPL::OnMove() {

    yBoom += 2;

}


//=============================================================================
bool CParticle_BossXPL::IsExpired() {


    if (counter > 10090)
    {
		LOGD("Boss dead");
        Dead = true;
        Expired = true;
        CApp::Logger.OnLog( __FILE__, __LINE__, "CParticle_BossXPL::IsExpired()", "");
		return true;
    }
	else
	{
		return false;
	}

}



//=============================================================================
void CParticle_BossXPL::EntityDEL() {

   
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead)
        {
            SDL_Log("delete Particle BOSS");
            delete *it;
            it = CEntity::EntityList.erase(it);
        }
        else
        {
            it++;
        }
    }
  

}
