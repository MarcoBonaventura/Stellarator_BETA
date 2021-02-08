#ifndef _CBULLETBOSS1_H
   #define _CBULLETBOSS1_H


#include "CEntity.h"
#include "CParticle_XPL.h"


class CBulletBOSS1 :public CEntity {

        int      Xbe, Ybe;

        int      i, j, selectCollider;

        double degree;

        CParticle_XPL *bulletExplosion;

    public:

        CBulletBOSS1(int x1, int y1, char* soundFX, eFlag F);
        ~CBulletBOSS1();

    public:

        bool     isAlive;

        bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnInit();

        void OnLoop();

        void OnMove();

        void OnRender();

        void PathLine();

        void OnCleanup();

        void EntityDEL();

        bool OnCollision(CEntity *Entity);

		void CollisionLoop();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        bool Fire();

        int BulletGetX();

        int BulletGetY();

};




#endif
