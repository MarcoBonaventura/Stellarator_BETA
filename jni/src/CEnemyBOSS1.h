#ifndef _CENEMYBOSS1_H_
    #define _CENEMYBOSS1_H_

#define _CRT_SECURE_NO_DEPRECATE

#include "CPopup.h"
#include "CEntity.h"
#include "CBulletEnemy.h"
#include "CBulletBOSS1.h"
#include "CParticle_BossXPL.h"
#include "CParticle_Smoke.h"
#include "CMedal.h"


class CEnemyBOSS1 :public CEntity {

	char *muzzle;


	SDL_Point	circuitBoss[4] = {};
    //CParticle_BossXPL *BossExplosion;


    int LimitX_dx;
    int LimitX_sx;
    int Offset;
    int path, now, speed;
    bool intro;

    SDL_Point posA;
    SDL_Point posB;
    SDL_Point posC;

    static const int MaxRow = 1000;
    //int **pathLine = new int*[MaxRow];

    //static const int MAX_FLARES = 20;
    double alpha, alpha_inc;
    const double alphaINIT = 3.6;
    const double alphaSTOP = 5.8;

    float forward;

    int timeToMove, timeToFire;

    int playerX, ply_w;

    //pathline variables for enemyBullet
    float px1;       //ascissa x1 del punto p1
    float px2;       //ascissa x2 del punto p2
    float py1;       //ordinata y1 del punto p1
    float py2;       //ordinata y2 del punto p2
    float px1b, py1b;

    int cx1, cx2;
    int cy1, cy2;


    float DeltaX;           //delta px2 - px1
    float DeltaY;           //delta py2 - py1

    float m;                //coefficiente angolare
    float q;                //ordinata all'origine (intercetta)

    bool CanFire();
    int shooted;

    static const Uint32 rows = 4;
    char* filename[rows];
    //char* filename[rows] = {"Bubble1", "Bubble2", "Bubble3", "Bubble4", "Bubble5"};

    int j;
    int bx, by;

    public:

        CPopup              *popup;
        CMedal              *MedalBoss;
        CParticle_BossXPL   *BossExpl;
        CBulletEnemy        *BullEnemyBoss;
        CBulletEnemy		*BullEnemyBoss2;
        CBulletBOSS1        *BullEnemyBossCaga;
        CBulletBOSS1        *BullEnemyBossCaga2;

        bool pos_A, pos_B, pos_C;

        float pathLine[MaxRow][2];
        float pathLine2[MaxRow][2];
        float escapeLine[MaxRow][2];

        int indexX, indexY;
        int W2, H2;

		static int countPopup;

        static int DeadTime;
		static int damage;
        static bool BossIsAlive;
		static bool	CannonSxIsAlive;

        static int Xen;
        static int Yen;

        static int getXen();
        static int getYen();

		//Uint32 callback1(Uint32 interval, void* param);
		//Uint32 callback2(Uint32 interval, void* param);
		//Uint32 callback3(Uint32 interval, void* param);






        CEnemyBOSS1(int x, int y, BossPath move);
        ~CEnemyBOSS1();

        bool OnLoad(char* File, int Width, int Height);

        void OnInit();

        void OnLoop();

        void OnMove();

        void OnEscape(SDL_Point escape);
        void OnVanish();

        void OnAnimate();

        void OnFire();
        void OnFire2();

        void OnCaga();
        void OnCaga2();

        void IA();

        void OnRender();

        static void OnRenderStamina(SDL_Surface *Surf_Display);

        void OnCleanup();

        void EntityDEL();

        bool OnCollision(CEntity *Entity);

        void CollisionLoop();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        int EnemyGetX();

        int EnemyGetY();

        void BossPopup(int j);

};

#endif
