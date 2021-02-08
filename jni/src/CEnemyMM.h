#ifndef _CENEMYMM_H_
    #define _CENEMYMM_H_

#include "CEntity.h"
#include "CBulletEnemy.h"
#include "CBulletEnemy_S.h"
#include "CParticle_PlayerXPL.h"
#include "CMedal.h"
#include "CGammaRayEnemy.h"


class CEnemyMM :public CEntity {


        int LimitX_dx;
        int LimitX_sx;
        int Offset;
        int shoted;

        //pathline variables for enemyBullet
        float px1;       //ascissa x1 del punto p1
        float px2;       //ascissa x2 del punto p2
        float py1;       //ordinata y1 del punto p1
        float py2;       //ordinata y2 del punto p2

        float DeltaX;           //delta px2 - px1
        float DeltaY;           //delta py2 - py1

        float m;                //coefficiente angolare
        float q;                //ordinata all'origine (intercetta)

        float MaxSpeed;
        float slowDown;

        bool CanFire();
        bool LaserON, pos_C, pos_A;
        double forward;
        float alpha_inc, alpha_offset;


    public:

        CBulletEnemy            *BullEnemy;
        CBulletEnemy_S          *BullEnemyStd;
        CParticle_PlayerXPL*    PlayerExplosion;
        CMedal*					MedalHonor;
        CGammaRayEnemy*         Laser;
        //int pathLine[2][1000];
        //int *prtPathLine[2]:
        //*prtPathLine = pathLine[0];
        static const int MaxRow = 2000;
        //int **pathLine = new int*[MaxRow];
        float pathLine[MaxRow][2];
        int indexX, indexY;

        int selected;

        CEnemyMM(int Xe, int Ye, eMove moving);
        ~CEnemyMM();

        bool OnLoad(char* File, int Width, int Height);

        void OnInit();

        void OnLoop();

        void OnMove();

		void OnAnimate();

        void OnFire();

        void OnLaser();

        void OnRender();

        void OnCleanup();

        void EntityDEL();

        bool OnCollision(CEntity *Entity);

        void CollisionLoop();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        int EnemyGetX();

        int EnemyGetY();

};

#endif
