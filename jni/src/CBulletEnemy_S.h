#ifndef _CBULLETENEMY_S_H
   #define _CBULLETENEMY_S_H


#include "CEntity.h"


class CBulletEnemy_S : public CEntity {

        int     Xbe, Ybe, gBullet, speedBullet;
        int     i, j, r;
		int		AnimState;


    public:

		CBulletEnemy_S(int x1, int y1, float speed, float g, char* soundFX, eFlag F);
        ~CBulletEnemy_S();

        bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnInit();

        void OnLoop();

        void OnMove();

		void OnAnimate();

        void OnRender();

        void OnCleanup();

        void EntityDEL();

        bool OnCollision(CEntity *Entity);

        void CollisionLoop();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        bool Fire();

        int BulletGetX();

        int BulletGetY();

        int selectCollider;

};




#endif
