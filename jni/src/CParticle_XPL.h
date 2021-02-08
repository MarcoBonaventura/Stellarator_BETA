#ifndef _CPARTICLE_XPL_H_
    #define _CPARTICLE_XPL_H_

#include "CParticles.h"
#include "CApp.h"
#include <cmath>

#define PIG 3.14159265

struct newFlares {

    float   x;
    float   y;
    int     w;
    int     h;
};


class CParticle_XPL : public CParticles {

        int xBoom, yBoom, xBoomF, yBoomF;
        int X2b, Y2b, iY, kX, Z, Xf, Yf, Xf2, Yf2, wf, hf, index;
        Uint8   grey;

        eMove motion_xpl;

        float   alphaChannel, ray;
        double  alpha1, alpha2;

        static const int MAX_FLARES_BIG = 16;
        static const int MAX_FLARES_SMALL = 4;

        SDL_Rect    flares_big[MAX_FLARES_BIG];

        SDL_Rect    flares_small[MAX_FLARES_SMALL];


    public:

        CParticle_XPL(int x, int y, eMove z, Effect_type E, char* soundFX);

        ~CParticle_XPL();

        bool Expired;

        virtual bool OnLoad(char *File, int Width, int Height, int MaxFrames);

        virtual void OnRender();

        virtual void OnLoop();

        virtual void OnCleanup();

        bool IsExpired();

        void OnMove();

        void OnInit();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        void EntityDEL();


};


#endif
