#ifndef _CBULLET_H
   #define _CBULLET_H


#include "CEntity.h"
#include "CPlayer.h"
#include "CParticle_XPL.h"



class CBullet : public CEntity {

    int zOffset, r;
    SDL_Rect    ret;


    public:

         CBullet(int X, int Y, int Z, int W, int H, std::string soundFX);
         ~CBullet();

         int W2, H2;



    public:

        bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnInit();

        void OnLoop();

        void OnMove();

        void OnRender();

        void OnCleanup();

        void EntityDEL();

        bool OnCollision(CEntity *Entity);

        void CollisionLoop();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        bool Fire();

        int BulletGetX();

        int BulletGetY();

};




#endif
