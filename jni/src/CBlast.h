#ifndef _CBlast_H
   #define _CBlast_H


#include "CEntity.h"



class CBlast :public CEntity {

    char    *anim_filename;


    public:

        CBlast(int X, int Y, int soundFX);
        ~CBlast();

        float kAcc;

    public:

        bool OnLoad(char *File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnMove();

        void OnRender();

        void OnCleanup();

        void EntityDEL();

        bool OnCollision(CEntity* Entity);

        void CollisionLoop();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        bool OnExplode();

        int BlastGetX();

        int BlastGetY();

};




#endif
