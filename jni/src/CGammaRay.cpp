#include "CApp.h"
#include "CGammaRay.h"
#include "CMedal.h"
#include "CPlayer.h"
#include "CAppStateGame.h"
#include "CEnemyBOSS1.h"

#include <cstdlib>

bool CGammaRay::collision = false;

//=============================================================================
CGammaRay::CGammaRay(int X, int Y, int w_off, int Z, std::string soundFX) {

	SDL_Log("CGammaRay creation");

    this->X = X;
    this->Y = Y;
    this->PlayerOffset.x = this->X;
    this->PlayerOffset.y = this->Y;
    this->Type = ENTITY_TYPE_GAMMARAY;
    this->Size = ENTITY_SIZE_PB;
    this->Flags = ENTITY_FLAG_GAMMARAY;
    this->Dead = false;
    this->collision = false;
    this->zOffset = Z;
    wOffset = w_off;




	/** Player fire sound effect */
	//CSoundBank::SoundControl.Play2(soundFX);
	//CSoundBank::SoundControl.PlayOGG("test2.ogg");
}

//=============================================================================
CGammaRay::~CGammaRay() {


}


void CGammaRay::OnInit() {

	SDL_Log("CGammaRay OnInit()");

	mColliders.resize(1);

	mVelX = 0;
	mVelY = 0;

	mColliders[0].w = Width;
	mColliders[0].h = WHEIGHT;

	shiftColliders();

	SDL_Log("gammaray initiated");

}



//=============================================================================
bool CGammaRay::OnLoad(char *File, int Width, int Height, int MaxFrames) {

	if (!CEntity::OnLoad(File, Width, Height, MaxFrames)) {
		return false;
	}

	return true;

}

//=============================================================================
void CGammaRay::OnLoop() {

    if(CAppStateGame::nextState) this->Dead = true;
    if(!CEnemyBOSS1::BossIsAlive) this->Dead = true;


	//CollisionLoop();

    if(CEntityCol::EntityColList.empty()) {
        Y = 0;
        collision = false;
    }

    OnMove();

}

//=============================================================================
void CGammaRay::OnMove() {

	if (CEntity::EntityMap.find(0) != CEntity::EntityMap.end()) {
		Height = (CPlayer::PlayerGetYp() + 40) - Y;
		//this->Xg = CPlayer::PlayerGetXp() + 207 * OVERALL_RATIO;
		X = CPlayer::PlayerGetXp() + wOffset;
		//X = CPlayer::GetPlayerX() + wOffset;
	}
	shiftColliders();

}

//=============================================================================
void CGammaRay::OnRender() {

	//SDL_Log("CGammaRay Rendering X: %1.3f - Y: %1.3f", Xg, Yg);

	if (entityRenderer)
	{
		TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, 0, 0, W2, H2, 255);
		//SDL_Log("CGammaRay Rendering");
	}
	else
	{
		SDL_Log("bad CGammaRay Renderer, error %s", SDL_GetError());
	}


}


//=============================================================================
void CGammaRay::CollisionLoop() {

	//CApp::Logger.OnLog( __FILE__, __LINE__, "CGammaRay::CollisionLoop()", "");

	for (int i = 0; i<CEntity::EntityList.size(); i++)
	{
		if (!CEntity::EntityList[i])
		{
            continue;
		}

		//if(this != CEntity::EntityList[i])
		CEntity::CheckCollision(CEntity::EntityList[i]);
	}


}

//=============================================================================
bool CGammaRay::OnCollision(CEntity *Entity) {

	if (Entity->Type == ENTITY_TYPE_ENEMY || Entity->Type == ENTITY_TYPE_BOSS)
    {
		Y = Entity->EnemyGetY() + (Entity->Height / 2);
		Height = (CPlayer::PlayerGetYp() + 40) - Y;
        collision = true;
        SDL_Log("Centity->Y %d", Entity->EnemyGetY());


		SDL_Point offset;
		offset.x = GammaRayGetX() - 10;
		offset.y = GammaRayGetY() - 10;

		char* str1 = "gammaray_light";
		char* str2 = "gammaray_light";

		CParticle_Smoke* smookey = new CParticle_Smoke(str1, str2, 50, 50, 100, 100, offset, 3, this->ID);

		CEntity::EntityList.push_back(smookey);

        return true;
    }



	/*

	if (Entity->Size == ENTITY_SIZE_BOSS || Entity->Flags == ENTITY_FLAG_ENEMY_F || Entity->Flags == ENTITY_FLAG_ENEMY_M)
	{
		switch (rand() % 9)
		{
		case 0: anim_filename = "explSX_01"; break;
		case 1: anim_filename = "explSX_02"; break;
		case 2: anim_filename = "explSX_03"; break;
		case 3: anim_filename = "explSX_04"; break;
		case 4: anim_filename = "explSX_05"; break;
		case 5: anim_filename = "explSX_06"; break;
		case 6: anim_filename = "explSX_07"; break;
		case 7: anim_filename = "explSX_08"; break;
		case 8: anim_filename = "explSX_09"; break;
		case 9: anim_filename = "explSX_10"; break;
		default:anim_filename = "explSX_01"; break;
		}

		int XB = GammaRayGetX() - 20;
		int YB = GammaRayGetY() - 20;



		CParticle_XPL* bulletExplosion = new CParticle_XPL(XB, YB, 0, "boom_02");

		bulletExplosion->particleTexture = anim_filename;
		bulletExplosion->Width = 64;
		bulletExplosion->Height = 64;
		bulletExplosion->Expired = false;
		bulletExplosion->Dead = false;
		bulletExplosion->Type = ENTITY_TYPE_PARTICLE;
		bulletExplosion->Flags = ENTITY_FLAG_MAPONLY;
		bulletExplosion->Size = ENTITY_SIZE_PP;

		CApp::Logger.OnLog(__FILE__, __LINE__, "TRY new EnemyBullet CParticle_XPL()", "");
		CEntity::EntityList.push_back(bulletExplosion);



	}

	
	*/


}

void CGammaRay::shiftColliders() {

	//The row offset
	int r = 0;

	//Go through the dot's collision boxes

	//Center the collision box
	mColliders[0].x = GammaRayGetX() + (Width - mColliders[0].w) / 2;

	//Set the collision box at its row offset
	mColliders[0].y = GammaRayGetY() + r;

	//Move the row offset down the height of the collision box
	//r += mColliders[0].h;


}


std::vector<SDL_Rect>& CGammaRay::getColliders() {

	return mColliders;

}


//=============================================================================
bool CGammaRay::Fire() {

	return true;

}


//=============================================================================
void CGammaRay::OnCleanup() {

	CApp::Logger.OnLog(__FILE__, __LINE__, "CGammaRay::OnCleanup()", "");


}



void CGammaRay::EntityDEL() {

	//CEntity::EntityDEL();



	for (std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
	{
		if (!(*it)) continue;
		if ((*it)->Dead)
		{

			(*it)->OnCleanup();
			delete (*it);
			(it) = CEntity::EntityList.erase(it);
		}
		else
		{
			it++;
		}
	}
	std::cout << "EntityListSize CGammaRay after iterator: " << CEntity::EntityList.size() << "\n";



}




float CGammaRay::GammaRayGetX() {

	return this->X;
}

float CGammaRay::GammaRayGetY() {

	return this->Y;
}



