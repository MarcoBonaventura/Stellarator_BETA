#ifndef _CBULLETSMART_H
   #define _CBULLETSMART_H


#include "CEntity.h"
#include "CParticle_XPL.h"
#include "CParticle_Smooky.h"

#define PI 3.14159265
#define POINTS_COUNT 1000

typedef struct
{
	float x;
	float y;
}
Point4D;

class CBulletSmart :public CEntity {

        SDL_Point points[POINTS_COUNT] = {};
		static SDL_Renderer* Renderer;

		Point4D cp[4];
		Point4D curve[POINTS_COUNT];

		SDL_Rect    ret;

		int     Xbe, Ybe;
        int     i, j, r, ii;
		int		ordBullet, horizon;
        int		selectCollider;

        int DELTA_enemy_X, DELTA_enemy_Y, temp_x, temp_y;

        int coeffx;         //coefficiente "a" di x
        int coeffy;         //coefficiente "b" di y
        int termnoto;       //termine noto "c"

		// variabili per calcolo traiettoria
		float px1;       //ascissa x1 del punto p1
		float px2;       //ascissa x2 del punto p2
		float py1;       //ordinata y1 del punto p1
		float py2;       //ordinata y2 del punto p2
		float k;

		int cx1;
		int cy1;

		float temp_xbe, temp_ybe;

		float DeltaX;           //delta px2 - px1
		float DeltaY;           //delta py2 - py1

		float m;                //coefficiente angolare
		float q;                //ordinata all'origine (intercetta)
		float kAcc;				//coefficiente accelerazione
		double degrees;         //inclinazione retta in radianti


		int 	enemyMOVE;
		int 	accX, accY;

        static const int MaxRow = 2000;
		float 	vet[MaxRow][2];
		double  vetG[MaxRow][1];

		int AnimState;



    public:

		enum RocketMove
		{
			DESTROY         = 1,
			SEEKandDESTROY  = 2
		};

		static int      rocketMOVE;

		CBulletSmart(int x1, int y1, float vettore[][2], double degrees[][1], int targetID, char* soundFX, eFlag F);
		~CBulletSmart();

		int lockID, W2, H2;

    public:

        bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnInit();

        void OnLoop();

        void OnMove();

		void OnAnimate();

        void OnRender();

        void PathLine(Point4D cp[4], int numberOfPoints, Point4D curve[POINTS_COUNT]);
        void PathLine(int numberOfPoints);

        void OnCleanup();

        void EntityDEL();

        bool OnCollision(CEntity *Entity);

        void CollisionLoop();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        bool Fire();

		int BulletGetX();

		int BulletGetY();

		Point4D PointOnCubicBezier(Point4D cp[4], float t, float k);

};




#endif
