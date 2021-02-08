#ifndef _CPARTICLES_H_
    #define _CPARTICLES_H_

#include <string>
#include "CEntity.h"


class CParticles : public CEntity {

    private:

		CParticles *Engine;
		
    public:



        CParticles();
        virtual ~CParticles();

        //static  CParticles  ParticlesEngine;

        std::string particleTexture;

        int 	Width, Height;
		int 	Xp, Yp;

		int		alphaSmoke;
		int		counter;

		int 	effect;

        bool Expired;

        bool IsExpired();

        virtual void OnRender();

        virtual bool OnLoad(char *File, int Width, int Height);

        virtual void OnLoop();

        virtual void OnCleanup();

        virtual void shiftColliders();

        virtual std::vector<SDL_Rect>& getColliders();

        void OnDeleteParticle();

        void OnMove();

        int particleGetX();

        int particleGetY();


};


#endif
