#ifndef _CPARTICLE_PlayerXPL_H_
    #define _CPARTICLE_PlayerXPL_H_

#include "CParticles.h"
#include "CApp.h"


class CParticle_PlayerXPL : public CParticles {

        int xBoom, yBoom;
        int X2b, Y2b, iY, kX;

        int yVelocity;


    public:

        CParticle_PlayerXPL(int x, int y, char* soundFX, eFlag F);
        ~CParticle_PlayerXPL();

        //int width = 32;
        //int height = 32;

        virtual bool OnLoad(char *File, int Width, int Height, int MaxFrames);

        virtual void OnRender();

        virtual void OnLoop();

        virtual void OnCleanup();

        bool IsExpired();

        void OnMove();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        void EntityDEL();


};


#endif
