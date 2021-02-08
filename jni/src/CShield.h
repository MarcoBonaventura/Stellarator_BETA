#ifndef _CSHIELD_H
   #define _CSHIELD_H


#include "CEntity.h"
#include "CPlayer.h"



class CShield :public CEntity {


        char*   frameShield;
        char* file_ext;
        char buffer[255];

        int counter, countLoop;
        int Xs, Ys, X2, Y2;

        const int width  = 256;
        const int height = 256;

        bool Expired;

    public:

        CShield(int X, int Y);
        ~CShield();

    public:

        bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnMove();

        void OnRender();

        bool IsExpired();

        void OnCleanup();

        void EntityDEL();

        bool OnCollision(CEntity *Entity);

        void CollisionLoop();

        std::vector<SDL_Rect>& getColliders();
        void shiftColliders();

        int BulletGetX();

        int BulletGetY();

};




#endif
