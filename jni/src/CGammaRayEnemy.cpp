#include "CApp.h"
#include "CGammaRayEnemy.h"
#include "CMedal.h"

#include <cstdlib>


bool CGammaRayEnemy::LaserAlive = true;


//=============================================================================
CGammaRayEnemy::CGammaRayEnemy(int X, int Y, int Z, std::string soundFX) {

	SDL_Log("enemyCGammaRay creation");

    this->X = X;
    this->Y = Y;
    EnemyOffset.x = this->X;
    EnemyOffset.y = this->Y;

    enemy_ID = Z;
	animstate = 0;
	counter = 0;

	Type = ENTITY_TYPE_BULLET_E;
	Dead = false;

    degreeUP = true;
    degreeDOWN = false;
    degree = 0;

    pivot = &Laser_pivot;

    LaserAlive = true;

	/** Player fire sound effect */
	//CSoundBank::SoundControl.Play2(soundFX);
	//CSoundBank::SoundControl.PlayOGG("test2.ogg");
}

//=============================================================================
CGammaRayEnemy::~CGammaRayEnemy() {



}


void CGammaRayEnemy::OnInit() {

	SDL_Log("enemyCGammaRay OnInit()");

	mColliders.resize(1);

	mVelX = 0;
	mVelY = 0;

	switch (Size)
    {
        case ENTITY_SIZE_SSX:
            mColliders[0].w = Width / 2;
            mColliders[0].h = WHEIGHT;
            entityTexture = "EnemyLaserBlue";
            break;

        case ENTITY_SIZE_SX:
            /*
            mColliders[0].w = Width / 2;
            mColliders[0].h = WHEIGHT;
            */
            entityTexture = "EnemyLaserGreen";  // EnemyLaser.png

            break;

        case ENTITY_SIZE_NONE:
            mColliders[0].w = Width / 2;
            mColliders[0].h = WHEIGHT;
            entityTexture = "EnemyLaserGreen";  // EnemyLaser.png
            break;
    }

	shiftColliders();

	SDL_Log("gammaray/laser initiated");

}



//=============================================================================
bool CGammaRayEnemy::OnLoad(char *File, int Width, int Height, int MaxFrames) {

	if (CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
		return false;
	}

	return true;

}

//=============================================================================
void CGammaRayEnemy::OnLoop() {

    /*
    if (CEntity::EntityMap.find(enemy_ID) == CEntity::EntityMap.end())
    {
        SDL_Log("Map not found");
	}
    */
    if (CEntity::TargetEnemyMap.find(enemy_ID) == CEntity::TargetEnemyMap.end())
    {
        Dead = true;
    }
    else if(CEntity::GetEntity(this->enemy_ID)->Dead)
    {
        SDL_Log("EnemyGammaRay Dead");
        this->Dead = true;
    }
    else
    {
        OnMove();
        shiftColliders();
        CollisionLoop();

        //this->Height = WHEIGHT - CEntity::GetEntity(this->enemy_ID)->EnemyGetY() + this->EnemyOffset.y;

    }

    switch (Size)
    {
        case ENTITY_SIZE_SSX:
            animstate = 0;
            /*
            if (counter % 1 == 0) {
                if (animstate < 27) animstate++;
                else animstate = 0;

            }
            */
            if(counter > 100)
            {
                //if (counter % 105 == 0) {
                    CEntity::GetEntity(enemy_ID)->laser_time = (long)SDL_GetTicks();
                    SDL_Log("Laser_time: %d", CEntity::GetEntity(enemy_ID)->laser_time);
                    LaserAlive = false;
                    Dead = true;
                //}
            }
            break;

        case ENTITY_SIZE_SX:

            animstate = 0;
            break;

        case ENTITY_SIZE_NONE:
            if(counter > 100)
            {
                if (this->counter % 105 == 0) {
                    CEntity::GetEntity(enemy_ID)->laser_time = (long)SDL_GetTicks();
                    SDL_Log("Laser_time: %d", CEntity::GetEntity(enemy_ID)->laser_time);
                    LaserAlive = false;
                    Dead = true;
                }
            }
            animstate = 0;
            break;
    }




    counter++;


}

//=============================================================================
void CGammaRayEnemy::OnMove() {

    if (CEntity::EntityMap.find(enemy_ID) == CEntity::EntityMap.end()) {
        SDL_Log("Map not found");
        Dead = true;
    }

    std::map<int, CEntity *>::iterator it;
    it = CEntity::EntityMap.find(this->enemy_ID);


    switch (Size)
    {
        case ENTITY_SIZE_SSX: {

            if (it != CEntity::EntityMap.end() || CEntity::GetEntity(enemy_ID) != NULL) {
                if (!Dead) {
                    //SDL_Log("gammarayenemy onmove");
                    X = CEntity::GetEntity(enemy_ID)->EnemyGetX() + EnemyOffset.x;
                    Y = CEntity::GetEntity(enemy_ID)->EnemyGetY() + EnemyOffset.y;
                }
            }

            degree = 0;
        }
            break;

        case ENTITY_SIZE_SX: {

            if (it != CEntity::EntityMap.end() || CEntity::GetEntity(enemy_ID) != NULL) {
                if (!Dead) {
                    //SDL_Log("gammarayenemy onmove");
                    X = CEntity::GetEntity(enemy_ID)->EnemyGetX() + 142 * OVERALL_ENEMY_RATIO;
                    Y = CEntity::GetEntity(enemy_ID)->EnemyGetY() + 247 * OVERALL_ENEMY_RATIO;
                    //Laser_pivot.x = CEntity::GetEntity(this->enemy_ID)->Width / 2;
                    Laser_pivot.x = 0;
                    Laser_pivot.y = 0;
                }
            }

            if (degree == 30) {
                degreeDOWN = true;
                degreeUP = false;
            } else if (degree == -30) {
                degreeDOWN = false;
                degreeUP = true;
            }

            if (counter % 2 == 0) {
                if (degreeUP) degree += 0.5;
                if (degreeDOWN) degree -= 0.5;
            }

        }
            break;

        case ENTITY_SIZE_NONE: {
            X = CEntity::GetEntity(enemy_ID)->EnemyGetX() + 142 * OVERALL_ENEMY_RATIO;
            Y = CEntity::GetEntity(enemy_ID)->EnemyGetY() + 247 * OVERALL_ENEMY_RATIO;
            //Laser_pivot.x = 0;
            //Laser_pivot.y = 0;

        }
            break;
    }



	


}

//=============================================================================
void CGammaRayEnemy::OnRender() {

	//SDL_Log("CGammaRay Rendering");

	if (entityRenderer)
	{
		TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, W2 * animstate, 0, W2, H2, degree, pivot, 255);
        //SDL_SetRenderDrawColor(entityRenderer, 0xFF, 0x00, 0xFF, 0xFF);
        //SDL_RenderFillRect(entityRenderer, &ret);
	}
	else
	{
		//SDL_Log("bad CGammaRay Renderer, error %s", SDL_GetError());
	}


}


//=============================================================================
void CGammaRayEnemy::CollisionLoop() {

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
bool CGammaRayEnemy::OnCollision(CEntity *Entity) {

	//SDL_Log("GammaRay BLASTED!!");


    if (Entity->Type == ENTITY_TYPE_PLAYER)

    {
        switch (rand() % 9) {
            case 0:
                anim_filename = "explSX_01";
                break;
            case 1:
                anim_filename = "explSX_02";
                break;
            case 2:
                anim_filename = "explSX_03";
                break;
            case 3:
                anim_filename = "explSX_04";
                break;
            case 4:
                anim_filename = "explSX_05";
                break;
            case 5:
                anim_filename = "explSX_06";
                break;
            case 6:
                anim_filename = "explSX_07";
                break;
            case 7:
                anim_filename = "explSX_08";
                break;
            case 8:
                anim_filename = "explSX_09";
                break;
            case 9:
                anim_filename = "explSX_10";
                break;
            default:
                anim_filename = "explSX_01";
                break;
        }

        int XB = GammaRayGetX() + this->Width / 2;
        int YB = (int)Entity->PlayerGetY() + (Entity->Height /2);



        CParticle_XPL *bulletExplosion = new CParticle_XPL(XB, YB, NONE, EXPLOSION, "boom_02");

        bulletExplosion->particleTexture = anim_filename;
        bulletExplosion->Width = 64;
        bulletExplosion->Height = 64;
        bulletExplosion->Expired = false;
        bulletExplosion->Dead = false;
        bulletExplosion->Type = ENTITY_TYPE_PARTICLE;
        bulletExplosion->Flags = ENTITY_FLAG_MAPONLY;
        bulletExplosion->Size = ENTITY_SIZE_PP;

        CEntity::EntityList.push_back(bulletExplosion);

        SDL_Log("Laser Enemy hit the target!");

    }


	
	//Dead = true;

	return true;

}

void CGammaRayEnemy::shiftColliders() {

	//The row offset
	int r = 0;

	//Go through the dot's collision boxes

	//Center the collision box
	mColliders[0].x = GammaRayGetX() + (Width - mColliders[0].w) / 2;

	//Set the collision box at its row offset
	mColliders[0].y = GammaRayGetY() + r;

    ret.h = mColliders[0].h;
    ret.w = mColliders[0].w;
    ret.x = mColliders[0].x;
    ret.y = mColliders[0].y;

	//Move the row offset down the height of the collision box
	//r += mColliders[0].h;


}


std::vector<SDL_Rect>& CGammaRayEnemy::getColliders() {

	return mColliders;

}


//=============================================================================
bool CGammaRayEnemy::Fire() {

	return true;

}


//=============================================================================
void CGammaRayEnemy::OnCleanup() {

	CApp::Logger.OnLog(__FILE__, __LINE__, "CGammaRay::OnCleanup()", "");


}



void CGammaRayEnemy::EntityDEL() {

	//CEntity::EntityDEL();



	for (std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
	{
		if (!(*it)) continue;
		if ((*it)->Dead == true)
		{
            SDL_Log("GammaRayEnemy onDelete");
			(*it)->OnCleanup();
			delete (*it);
			(it) = CEntity::EntityList.erase(it);
		}
		else
		{
			it++;
		}
	}
	//std::cout << "EntityListSize CGammaRay after iterator: " << CEntity::EntityList.size() << "\n";
	//CApp::Logger.OnLog( __FILE__, __LINE__, "outside Entity CBullet vector iterator ", "");



}




int CGammaRayEnemy::GammaRayGetX() {

	return this->X;
}

int CGammaRayEnemy::GammaRayGetY() {

	return this->Y;
}

bool CGammaRayEnemy::GetLaserOnOff() {

    return LaserAlive;


}



