#ifndef _CBOMB_H
   #define _CBOMB_H


#include "CEntity.h"
#include "CPlayer.h"
#include "CBlast.h"


class CBomb : public CEntity {

    char    *anim_filename;
    bool    expired;
    int     alpha;

    char*			MuzzleSX;
    char*			MuzzleDX;
    SDL_Point		engOffset;



    public:

        CBomb(int X, int Y, int soundFX);
        ~CBomb();

        float kAcc;

    public:

         int W2, H2, X2, Y2;

         void OnInit();

         bool OnLoad(char* File, int Width, int Height, int MaxFrames);

         void OnLoop();

         void OnMove();

         void OnRender();

         void Smog();

         void OnCleanup();

         void EntityDEL();

         bool OnCollision(CEntity *Entity);

         void CollisionLoop();

         void shiftColliders();

         std::vector<SDL_Rect>& getColliders();

         bool DropBomb();

         bool OnExplode();

         int BombGetX();

         int BombGetY();

        int EnemyGetX();

        int EnemyGetY();

};




#endif
