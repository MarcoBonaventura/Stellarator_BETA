#ifndef _CBULLETENEMY_H
   #define _CBULLETENEMY_H


#include "CEntity.h"
#include "CParticle_XPL.h"


class CBulletEnemy :public CEntity {

        //int p1, p2, deltaX, deltaY;

        CParticle_XPL *bulletExplosion;

		float   Xbe, Ybe;
        int     i, j, r, max_index;
		int		ordBullet, horizon;
        int		selectCollider;
		int 	_rect_RGB_R, _rect_RGB_G, _rect_RGB_B, _rect_alpha;
        bool    _render_rect;

        SDL_Point final_rect;

        int coeffx;         //coefficiente "a" di x
        int coeffy;         //coefficiente "b" di y
        int termnoto;       //termine noto "c"

        static const int MaxRow = 2000;
		float vet[MaxRow][2];

		double degree;
		//SDL_Point	bulletPIVOT;

		int AnimState;


    public:

		CBulletEnemy(int x1, int y1, float vettore[][2], char* soundFX, eFlag F);
        ~CBulletEnemy();

        int     W2, H2;
        int     speed_inc;
        double  degree_inc;

    public:

        bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnInit();

        void OnLoop();

        void OnMove();

		void OnAnimate();

        void OnRender();

        void PathLine();

        void OnCleanup();

        void EntityDEL();

        bool OnCollision(CEntity *Entity);

        void CollisionLoop();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        bool Fire();

		float BulletGetX();

		float BulletGetY();

		void SetRenderRect(bool rend, int RGBR, int RGBG, int RGBB, int alpha);

};




#endif
