#ifndef _CPARTICLE_SMOOKY_H_
    #define _CPARTICLE_SMOOKY_H_

#include "CParticles.h"
#include "CParticle_Smoke.h"
#include "CApp.h"
#include "CEntity.h"
//#include "CPlayer.h"





class CParticle_Smooky : public CParticles {

    private:

        int x, y, width, height, alpha_smog;
        Uint8 grey;
        SDL_Rect smooky_R;

		
    public:

        CParticle_Smooky(int X, int Y, int W, int H, eFlag flag, int A);

        //bool OnLoad(char *File, int Width, int Height);

		void OnInit();

        void OnRender();

        void OnLoop();

        void OnMove();

        void OnAnimate();

        //void OnCleanup();

        bool IsExpired();

        //void shiftColliders();

        void EntityDEL();

        //std::vector<SDL_Rect>& getColliders();


};


#endif
