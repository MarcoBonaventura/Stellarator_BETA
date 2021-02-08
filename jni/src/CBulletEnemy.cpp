#include "CApp.h"
#include "CBulletEnemy.h"
#include "Stringify.h"

#include <cstdlib>


//=============================================================================
CBulletEnemy::CBulletEnemy(int x1, int y1, float vettore[][2], char* soundFX, eFlag F) {

    X = x1;
    Y = y1;

	AnimState = 0;
	degree = 0;
	speed_inc = 2;

	_render_rect = false;
	_rect_RGB_R = _rect_RGB_G = _rect_RGB_B = 255;
	_rect_alpha = 255;

    Dead = false;
    Type = ENTITY_TYPE_BULLET_E;
    selectCollider = F;
    Flags = F;
    Size = ENTITY_SIZE_BB;
    degree_inc = 5;

    i = j = 0;
    for (int z = 0; z < MaxRow; z++)
    {
        if (vettore[z][1] <= WHEIGHT) {
            vet[z][0] = vettore[z][0];
            vet[z][1] = vettore[z][1];
            max_index = z;
            //SDL_Log("ID: %d vet[%d][0] = %1.3f - vet[%d][1] = %1.3f",ID, z, vet[z][0], z, vet[z][1]);
        } else {
            SDL_Log("enemy bullet vector[%d][0] = %1.3f - vector[%d][1] = %1.3f", z, vet[z][0], z, vet[z][1]);
            break;
        }
    }

    /* Player fire sound effect */
    CSoundBank::SoundControl.Play2(soundFX);

    SDL_Log("Enemy bullet fired!");

}

//=============================================================================
CBulletEnemy::~CBulletEnemy() {
	
    //CApp::Logger.OnLog( __FILE__, __LINE__, "delete CBulletEnemy()", "");
	
}

void CBulletEnemy::OnInit() {

    mVelX = 0;
    mVelY = 0;

    switch(selectCollider)
    {
        case ENTITY_FLAG_ENEMY_M:
            mColliders.resize(1);
            mColliders[0].w = 21;
            mColliders[0].h = 56;
        break;

        case ENTITY_FLAG_ENEMY_F:
            mColliders.resize(1);
            mColliders[0].w = 30;
            mColliders[0].h = 30;
        break;

        case ENTITY_FLAG_BOSS:
            mColliders.resize(1);
            mColliders[0].w = Width;
            mColliders[0].h = Height;
        break;

        default:
            mColliders.resize(1);
            mColliders[0].w = 32;
            mColliders[0].h = 9;
        break;
    }

    for (int set = 0; set < mColliders.size(); ++set)
    {
        mColliders[set].w = mColliders[set].w * OVERALL_ENEMY_RATIO;
        mColliders[set].h = mColliders[set].h * OVERALL_ENEMY_RATIO;
    }

	shiftColliders();


}


void CBulletEnemy::shiftColliders() {

    switch (selectCollider)
    {
        case ENTITY_FLAG_ENEMY_S:
            r = 0;
            break;

        case ENTITY_FLAG_ENEMY_M:
            r = 12 * OVERALL_ENEMY_RATIO;
            break;

        case ENTITY_FLAG_ENEMY_F:
            r = 10 * OVERALL_ENEMY_RATIO;
            break;

        case ENTITY_FLAG_BOSS:
            r = 0;
            break;

        default:
            r = 0;
            break;
    }

    //Go through the dot's collision boxes
    for (int set=0; set<mColliders.size(); ++set)
    {
        //Center the collision box
        mColliders[set].x = BulletGetX() + (Width - mColliders[set].w) /2;

        //Set the collision box at its row offset
        mColliders[set].y = BulletGetY() + r;

        //Move the row offset down the height of the collision box
        r += mColliders[set].h;
    }

}



//=============================================================================
void CBulletEnemy::PathLine() {


    //q = -px1*(DeltaY/DeltaX)+py1;

    //std::cout<<"m= "<<m<<" q= "<<q<<std::endl;

}

//=============================================================================
bool CBulletEnemy::OnLoad(char *File, int Width, int Height, int MaxFrames) {

    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }

    return true;

}

//=============================================================================
void CBulletEnemy::OnLoop() {

    OnMove();
    shiftColliders();
	CollisionLoop();


	if (BulletGetY() > WHEIGHT || BulletGetX() > WWIDTH || BulletGetX() < 0 || BulletGetY() > WHEIGHT)
    {
		//SDL_Log("dead bullet x: %d y: %d", BulletGetX(), BulletGetY());
		Dead = true;
    }

    switch (Flags) {

	    case ENTITY_FLAG_ENEMY_M:
	        degree += 4;
	        break;

	    case ENTITY_FLAG_ENEMY_M2:
            degree += 4;
            break;

        case ENTITY_FLAG_BOSS:
	        degree += degree_inc;
	        break;

	    default:
	        degree += 4;
	        break;
	}


}

//=============================================================================
void CBulletEnemy::OnMove() {


	//------------


    switch (Flags) {
	    case ENTITY_FLAG_ENEMY_F:
            if (i <=  MaxRow) {
                X = vet[i][0];
                Y = vet[i][1];
            }
	        i += 2;

	        break;
	    case ENTITY_FLAG_ENEMY_M:
            if (i <=  MaxRow) {

                if (i <=  MaxRow) {
                    X = vet[i][0];
                    Y = vet[i][1];
                }
            }
	        i += 1;
	        break;

	    case ENTITY_FLAG_BOSS:
            if (i <=  max_index) {
                X = vet[i][0];
                Y = vet[i][1];
            } else {
                Dead = true;
            }
            i += speed_inc;

	         break;

        default:
            if (i <=  MaxRow) {
                    X = vet[i][0];
                    Y = vet[i][1];
            }
            i += 1;
            break;
	}

    OnAnimate();
    
}

void CBulletEnemy::OnAnimate() {

	if (AnimState < 14) AnimState++;
	else AnimState = 0;

}

//=============================================================================
void CBulletEnemy::OnRender() {

    if (entityRenderer)
    {
		TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, W2 * AnimState, 0, W2, H2, degree, NULL, 255);
		if (_render_rect) {
            SDL_SetRenderDrawBlendMode(entityRenderer, SDL_BLENDMODE_BLEND);
		    SDL_SetRenderDrawColor(entityRenderer, _rect_RGB_R, _rect_RGB_G, _rect_RGB_B, _rect_alpha);
            SDL_RenderDrawLine(entityRenderer, X + Width / 2, Y + Height / 2, (int)vet[max_index][0], (int)vet[max_index][1]);
            //SDL_Log("final_rect X: %d - Y: %d", (int)vet[max_index][0], (int)vet[max_index][1]);
		}
    }
    else
    {
        SDL_Log("BulletEnemy OnRender() BAD RENDERER! %s", SDL_GetError());
    }

}


//=============================================================================
void CBulletEnemy::OnCleanup() {


 }




void CBulletEnemy::EntityDEL() {


    CEntity::EntityDEL();

    /*
   
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead == true)
        {
           
            (*it)->OnCleanup();
            delete *it;
            it = CEntity::EntityList.erase(it);
            /*
            for (int i=0; i<MaxRow; i++)
            {
                delete [] vet[i];
            }
            delete [] vet;
            */
    /*
        }
        else
        {
            it++;
        }
    }

    */

}


//=============================================================================
void CBulletEnemy::CollisionLoop() {

    for (int i=0; i<CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i])
        {
            continue;
        }
        CEntity::CheckCollision(CEntity::EntityList[i]);
    }


}


//=============================================================================
bool CBulletEnemy::OnCollision(CEntity *Entity) {

    Dead = true;

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
    }

    int XB = BulletGetX() + Width / 2;
    int YB = BulletGetY() + Height / 2;

   

    bulletExplosion = new CParticle_XPL(XB, YB, NONE, EXPLOSION, "boom_02");

    bulletExplosion->particleTexture = anim_filename;
    bulletExplosion->W2 = 64;
    bulletExplosion->H2 = 64;
    bulletExplosion->Width  = bulletExplosion->W2 * OVERALL_RATIO;
    bulletExplosion->Height = bulletExplosion->H2 * OVERALL_RATIO;

    CEntity::EntityList.push_back(bulletExplosion);

    return true;

}



std::vector<SDL_Rect>& CBulletEnemy::getColliders() {

	return mColliders;

}

//=============================================================================
bool CBulletEnemy::Fire() {

    return true;

}

float CBulletEnemy::BulletGetX() {

    return this->X;
}

float CBulletEnemy::BulletGetY() {

    return this->Y;
}

void CBulletEnemy::SetRenderRect(bool rend, int RGBR, int RGBG, int RGBB, int alpha) {

    _render_rect = rend;
    _rect_RGB_R = RGBR;
    _rect_RGB_G = RGBG;
    _rect_RGB_B = RGBB;
    _rect_alpha = alpha;

}