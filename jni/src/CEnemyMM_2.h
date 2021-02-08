#ifndef _CENEMYMM_2_H_
    #define _CENEMYMM_2_H_

#include "CEntity.h"
#include "CBulletEnemy_S.h"
#include "CMedal.h"
#include "CParticles.h"


class CEnemyMM_2 : public CEntity {

    public:

        CBulletEnemy_S        *BullEnemy;
        CMedal              	*MedalHonor;
        //int pathLine[2][1000];
        //int *prtPathLine[2]:
        //*prtPathLine = pathLine[0];
        static const int MaxRow = 2000;
        //int **pathLine = new int*[MaxRow];
		float pathLine[MaxRow][2];
        int indexX, indexY;
		int offsetY;
        bool fireSX;
        bool fireDX;

        SDL_Rect    ret[10];


    private:

        int LimitX_dx;
        int LimitX_sx;
        int Offset;
        int shoted;

        // fattore di accelerazione
        float kAcc;
		float slowDown;

        //pathline variables for enemyBullet
		float px1;       //ascissa x1 del punto p1
		float px2;       //ascissa x2 del punto p2
		float py1;       //ordinata y1 del punto p1
		float py2;       //ordinata y2 del punto p2

        float DeltaX;           //delta px2 - px1
        float DeltaY;           //delta py2 - py1

        float m;                //coefficiente angolare
        float q;                //ordinata all'origine (intercetta)



		int reset_kAcc();

		char*			MuzzleSX;
		char*			MuzzleDX;



    public:

        CEnemyMM_2(int X, int Y);
        ~CEnemyMM_2();


        bool OnLoad(char* File, int Width, int Height);

        void OnInit();

        void OnLoop();

        void OnMove();

		void OnAnimate();

        bool CanFire();

		void OnFire();

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
