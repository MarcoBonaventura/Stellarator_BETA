#ifndef _CPARTICLE_SMOKE_H_
    #define _CPARTICLE_SMOKE_H_

#include "CParticles.h"
#include "CApp.h"
#include "CEntity.h"
//#include "CPlayer.h"





class CParticle_Smoke : public CParticles {

    private:

        //CParticle_Smoke *Engine;
        int width, height, SourceW, SourceH, X2, Y2, move, alpha_smog;
        int rocket_ID;
        char* stringLow;
        char* stringHigh;
        float x, y;
        SDL_Point   engineOffset;

		
    public:

        CParticle_Smoke(char* fileL, char* fileH, int width, int height, int SourceW, int SourceH, SDL_Point engOffset, int moving, int rocketID);

        bool OnLoad(char *File, int Width, int Height);

		void OnInit();

        void OnRender();

        void OnLoop();

        void OnMove();

        void OnAnimate();

        void OnCleanup();

        bool IsExpired();

        void shiftColliders();

        void EntityDEL();

        std::vector<SDL_Rect>& getColliders();


};


#endif
