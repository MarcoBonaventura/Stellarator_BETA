#ifndef _CPARTICLE_BOSSXPL_H_
    #define _CPARTICLE_BOSSXPL_H_

#include "CParticles.h"
#include "CApp.h"



class CParticle_BossXPL : public CParticles {

        int xBoom, yBoom;
        int X2b, Y2b, i, k;

        const int width = 32;
        const int height = 32;

        char* frameXPL;
        char* finaleFrameXPL;
        char* file_ext;
        char buffer[255];

        int counter, countLoop;


    public:

        CParticle_BossXPL(int x, int y, char* soundFX);
        ~CParticle_BossXPL();

        virtual bool OnLoad(char *File, int Width, int Height, int MaxFrames);

        virtual void OnRender();

        virtual void OnLoop();

        virtual void OnCleanup();

        bool IsExpired();

        void OnMove();

        void EntityDEL();




};


#endif
