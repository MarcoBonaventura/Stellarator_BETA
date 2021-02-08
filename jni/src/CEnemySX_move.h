#ifndef _CENEMYSX_MOVE_H_
    #define _CENEMYSX_MOVE_H_

#include "CEntity.h"
#include "CEnemySX.h"
#include "CBulletEnemy.h"
#include "CMedal.h"

class CEnemySX_move: public CEnemySX {

        int     xBoom, yBoom, X2, animFrame;
        int     AnimState, temp_ct;
        static  int shoted, X1, Y1;

        float   alpha, ray, slowDown;

        char*   bullet_file;

        static const int MaxRow = 2000;
        float pathLine[MaxRow][2];

        int ENTmoving;
        int r;

        SDL_Surface*    surf_rect;
        SDL_Rect    *ret;

        CBulletEnemy        *BullEnemy;
        CBulletEnemy_S      *BulletSSX;

        CMedal* 			MedalHonor;



    public:


        CEnemySX_move(int Xe, int Ye, eMove moving);
        ~CEnemySX_move();



        bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnInit();

        void OnLoop() override;

        void OnMove();

        void OnAnimate() override;

        void OnRender() override;

        void OnFire();

        bool canFIRE();

        bool booleanFIRE();

        void OnCleanup();

        void EntityDEL();

        void OnDeleteEnemy();

        bool OnCollision(CEntity *Entity);

        void CollisionLoop();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        int EnemyGetX();
        int EnemyGetY();

        int GetEntityMoving();


};

#endif
