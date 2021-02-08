#include "CParticle_Smoke.h"
#include "CAppStateGame.h"
#include "CBomb.h"

#include <cstring>



CParticle_Smoke::CParticle_Smoke(char* fileL, char* fileH, int width, int height, int SourceW, int SourceH, SDL_Point engOffset, int moving, int rocketID) {



	counter = 0;
    X2 = 0;
    Y2 = 0;

    X = engOffset.x;
    Y = engOffset.y;

	stringLow = fileL;
	stringHigh = fileH;

	particleTexture = fileL;
	Width = width;
	Height = height;
    alphaSmoke = 255;

    this->SourceW = SourceW;
    this->SourceH = SourceH;

	engineOffset = engOffset;
    move = moving;
    Xp = engOffset.x;
    Yp = engOffset.y;

    alpha_smog = 255;
    this->rocket_ID = rocketID;

    Type = ENTITY_TYPE_PARTICLE;
    Flags = ENTITY_FLAG_NONE;

    //float tempx = CPlayer::PlayerStat.PlayerGetX();
    //float tempy = CPlayer::PlayerStat.PlayerGetY();
    //SDL_Log(" SMOKE temp x: %f1.2 - temp y: %f1.2", tempx, tempy);

    //SDL_Log("Particle_Smoke %d", this->ID);
    //SDL_Log("muzzle");

}

void CParticle_Smoke::OnInit() {



}

//=============================================================================
bool CParticle_Smoke::OnLoad(char *File, int Width, int Height) {

    if(CEntity::OnLoad(File, Width, Height) == false) {

        return false;
    }

    return true;
}


//=============================================================================
void CParticle_Smoke::OnLoop() {

	switch(move)
    {
        case 0:

            X = CPlayer::PlayerGetXp() + engineOffset.x;
            Y = CPlayer::PlayerGetYp() + engineOffset.y;

            OnAnimate();
            if(stringLow == "OrangeBlast__anim_ply")
            {
                if (counter > 4)
                {
                    counter = 0;
                    Dead = true;
                }
            }
            if(stringLow == "BlueCircle__anim")
            {
                if (counter > 3)
                {
                    counter = 0;
                    Dead = true;
                }
            }


            break;

        case 1:



            if (Y < 0) Dead = true;

            break;

        case 2:

            if(CEntity::GetEntity(rocket_ID) == NULL)
            {
                //SDL_Log("Rocket ply Dead");
                Dead = true;
            }

            //SDL_Log("smog loop %d", rocket_ID);
            if(alpha_smog > 0) {
                alpha_smog -= 5;
                //SDL_Log("smog ID %d - alpha %d", this->ID, this->alpha_smog);

            }
            else if (alpha_smog <= 0) {
                Dead = true;
            }

            break;

        case 3:

            Dead = true;

            break;

        case 4:

            X = CEnemyBOSS1::getXen() + engineOffset.x;
            Y = CEnemyBOSS1::getYen() + engineOffset.y;

            OnAnimate();
            if (counter > 4)
            {
                counter = 0;
                Dead = true;
            }

            break;

        case 5:

            OnAnimate();
            if (counter > 4) {
                counter = 0;
                Dead = true;
            }

            break;

        case 10:
            if(CEntity::GetEntity(rocket_ID)->Dead)
            {
                Dead = true;
            } else {
                OnAnimate();
                if (counter > 4) {
                    counter = 0;
                }
            }



            break;

    }


    //this->x = CPlayer::PlayerGetXp();
    //this->y = CPlayer::PlayerGetYp();



	/*
	if(this->stringLow == "EngineRED_anim_high")
	{
		if (this->counter > 7)
		{
			this->counter = 0;
        }
    }
	*/

	OnMove();


	counter++;


}


void CParticle_Smoke::OnMove() {


    switch(move)
    {
        case 0:
            break;

        case 1:
            //this->y = CBomb::BombGetY() + CBomb::Height;
            break;

        case 2:

            Y -= 2;
            //SDL_Log("smog move %d", rocket_ID);
            //this->x = CEntity::GetEntity(this->rocket_ID)->EnemyGetX();
            //this->y = CEntity::GetEntity(this->rocket_ID)->EnemyGetY() + 67;
            //SDL_Log("smog x %d - smog y %d", x, y);
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

    }

}


void CParticle_Smoke::OnAnimate() {

    switch(move)
    {
        case 0:
            X2 = SourceW * counter;
            Y2 = 0;

            break;

        case 1:
            X2 = SourceW * counter;
            Y2 = 0;

            break;

        case 2:

            //SDL_Log("smog animate %d", rocket_ID);

            X2 = 0;
            Y2 = 0;

            break;

        case 3:
            break;

        case 4:
            X2 = SourceW * counter;
            Y2 = 0;
            break;

        case 5:
            X2 = SourceW * counter;
            Y2 = 0;
            break;


        default:
            X2 = SourceW * counter;
            Y2 = 0;
            break;

    }


}


//=============================================================================
void CParticle_Smoke::OnRender() {

    //this->X = Xp;
    //this->Y = Yp;

    //this->Width * this->counter

	if (entityRenderer)
	{
		TextureBank::Get(this->particleTexture)->Render(X, Y, Width, Height, X2, Y2, SourceW, SourceH, alpha_smog);
		//SDL_Log("rendering PlayerSmoke: %s - width: %d - x: %d - counter: %d", this->particleTexture.c_str(), this->Width, this->X2, this->counter);
	}
	else
	{
		//SDL_Log("PlayerSmoke render error: %s", SDL_GetError());
	}

}


//=============================================================================
void CParticle_Smoke::OnCleanup() {

    CEntity::OnCleanup();

}





//=============================================================================
bool CParticle_Smoke::IsExpired() {

	if (alphaSmoke <= 0)
	{
		Dead = true;
		return true;
	}

    return false;
	
}


void CParticle_Smoke::shiftColliders() {

    

}

std::vector<SDL_Rect>& CParticle_Smoke::getColliders() {

	return this->mColliders;

}

void CParticle_Smoke::EntityDEL() {

    CEntity::EntityDEL();

    /*
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead)
        {
            delete *it;
            it = CEntity::EntityList.erase(it);
        }
        else
        {
            it++;
        }
    }
    */

}


