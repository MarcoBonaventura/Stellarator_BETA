#ifndef _CENEMYSX_H_
    #define _CENEMYSX_H_

#include "CEntity.h"
#include "CBulletEnemy_S.h"
#include "CParticle_Smoke.h"
#include "CMedal.h"


class CEnemySX: public CEntity {

        int     xBoom, yBoom;
        int     AnimState, ENTmoving;

        SDL_Renderer*   myRenderer;

		//CParticle_Smoke* ENGINE;
		CMedal*			MedalHonor;

		SDL_Rect    *ret;

    public:

        CEnemySX();
        CEnemySX(int Xe, int Ye);
        ~CEnemySX();

        //static int TEXTURE_WIDTH;
		//static int TEXTURE_HEIGHT;

        int		r;


        virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnInit();

        void OnLoop();

        void OnMove();

		void OnFire();

		void Engine();

        virtual void OnAnimate();

        virtual void OnRender();

        virtual void OnCleanup();

        virtual void EntityDEL();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        void OnDeleteEnemy();

        bool OnCollision(CEntity *Entity);

        virtual void CollisionLoop();

        int EnemyGetX();
		int EnemyGetY();

		int EnemyGetMoving();


};

#endif
