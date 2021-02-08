#ifndef CASTEROID_H_INCLUDED
#define CASTEROID_H_INCLUDED

#include "CEnemySX.h"



#endif // CASTEROID_H_INCLUDED


class CAsteroid: public CEnemySX {

        int     xBoom, yBoom;
        int     AnimState;
        int     width, height;
        int     countLoop;

    public:
        CAsteroid();
        CAsteroid(int X, int Y);
        ~CAsteroid();



        virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnMove();

        virtual void OnAnimate();

        virtual void OnRender();

        virtual void OnCleanup();

        virtual void EntityDEL();

        void OnDeleteEnemy();

        bool OnCollision(CEntity *Entity);

        virtual void CollisionLoop();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        int EnemyGetX();

        int EnemyGetY();

};
