#include "CParticle_Smooky.h"
#include "CAppStateGame.h"
#include "CBomb.h"

#include <cstring>



CParticle_Smooky::CParticle_Smooky(int X, int Y, int W, int H, eFlag  flag, int A) {

    this->X = X;
    this->Y = Y;
    X2 = 0;
    Y2 = 0;

    W2 = W;
    H2 = H;

    this->Flags = flag;
    switch (Flags) {

        case ENTITY_FLAG_NONE:
            Width = W2 * OVERALL_RATIO;
            Height = H2 * OVERALL_RATIO;
            break;

        case ENTITY_FLAG_BOSS:
            Width = W2 * OVERALL_ENEMY_RATIO;
            Height = H2 * OVERALL_ENEMY_RATIO;
            break;
    }

    alpha_smog = A;

    grey = 150;
    smooky_R = {x, y, Width, Height};

    Type = ENTITY_TYPE_PARTICLE;

}

void CParticle_Smooky::OnInit() {



}



//=============================================================================
void CParticle_Smooky::OnLoop() {

	switch (Flags) {

		case ENTITY_FLAG_NONE:

			if (alpha_smog == 0) {
				Dead = true;
			} else {
				alpha_smog -= 15;
			}

			break;

		case ENTITY_FLAG_BOSS:

			if (alpha_smog == 0) {
				Dead = true;
			} else {
				alpha_smog -= 3;
			}

			Y -= 5;

			break;
	}


	/*
	if (grey >= 0) {
		grey -= 5;
	}
	*/

}


void CParticle_Smooky::OnMove() {




}


void CParticle_Smooky::OnAnimate() {




}


//=============================================================================
void CParticle_Smooky::OnRender() {



	if (entityRenderer)
	{
        //SDL_SetRenderDrawColor(entityRenderer, grey, grey, grey, alpha_smog);
        //SDL_RenderFillRect(entityRenderer, &smooky_R);
		TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, X2, Y2, W2, H2, alpha_smog);
	}
	else
	{
		SDL_Log("particle Smoke render error: %s", SDL_GetError());
	}

}






//=============================================================================
bool CParticle_Smooky::IsExpired() {

	if (alpha_smog == 0)
	{
		Dead = true;
		return true;
	}

    return false;
	
}



void CParticle_Smooky::EntityDEL() {

    CEntity::EntityDEL();


}


