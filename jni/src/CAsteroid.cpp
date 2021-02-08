#include "CAsteroid.h"
#include "CApp.h"


CAsteroid::CAsteroid(int X, int Y) {

    this->Xe = X;
    this->Ye = Y;
    this->Y2 = 0;

    boom = false;
    this->Dead = false;

    this->AnimState = 0;
    width   = 128;
    height  = 128;


    this->Type  = ENTITY_TYPE_GENERIC;
    this->Size  = ENTITY_SIZE_SX;
    this->Flags = ENTITY_FLAG_ENEMY_S;



}

CAsteroid::~CAsteroid() {


    CApp::Logger.OnLog( __FILE__, __LINE__, "delete CAsteroid()", "");


}


bool CAsteroid::OnLoad(char* File, int Width, int Height, int MaxFrames) {

    CEnemySX::OnLoad(File, Width, Height, MaxFrames);

	return true;

}


void CAsteroid::OnLoop() {

    OnMove();

    if (EnemyGetY() > WHEIGHT) Dead = true;


    if (AnimState > 29) AnimState = 0;

    countLoop++;

}

void CAsteroid::OnAnimate() {



}


void CAsteroid::OnMove() {


    Ye += 1;
    if (countLoop %7 == 0) AnimState++;


}


void CAsteroid::OnRender() {

    X = Xe;
    Y = Ye;

    //Texture::OnDraw(Surf_Display, Surf_Entity, X, Y, AnimState * Width, Y2, Width, Height);

}



void CAsteroid::OnCleanup() {

    CEnemySX::OnCleanup();

}


//=============================================================================
void CAsteroid::CollisionLoop() {

    CEnemySX::CollisionLoop();


}

void CAsteroid::shiftColliders() {

    //The row offset
    int r = 0;

    //Go through the dot's collision boxes
	for (Uint32 set = 0; set<mColliders.size(); ++set)
    {
        //Center the collision box
        mColliders[set].x = mPosX + (Width - mColliders[set].w) /2;

        //Set the collision box at its row offset
        mColliders[set].y = mPosY + r;

        //Move the row offset down the height of the collision box
        r += mColliders[set].h;
    }

}

std::vector<SDL_Rect>& CAsteroid::getColliders() {

	return mColliders;

}


bool CAsteroid::OnCollision(CEntity *Entity) {

    if (this != NULL)
    {
        if (EnemyGetY() >1)
        {
            //std::cout<<"EnemySx OnCollision() X: "<<X<<" - Y: "<<Y<<std::endl;
            //Dead = true;

            //CApp::Logger.OnLog( __FILE__, __LINE__, "CAsteroid::OnCollision()", "");
            //std::cout<<"EnemySX collision"<<std::endl;

            //CApp::Logger.OnLog( __FILE__, __LINE__, "PlayerScore +100", "");
            //CPlayer::PlayerStat.PlayerScore += 100;

            //CApp::Logger.OnLog( __FILE__, __LINE__, "PlayerScore updated", "");
            //CPlayerStat::PlayerStat.OnUpdate();

            switch (rand() % 9)
            {
                case 0: anim_filename = "IMG/explosion/sx/explSX_01.png"; break;
                case 1: anim_filename = "IMG/explosion/sx/explSX_02.png"; break;
                case 2: anim_filename = "IMG/explosion/sx/explSX_03.png"; break;
                case 3: anim_filename = "IMG/explosion/sx/explSX_04.png"; break;
                case 4: anim_filename = "IMG/explosion/sx/explSX_05.png"; break;
                case 5: anim_filename = "IMG/explosion/sx/explSX_06.png"; break;
                case 6: anim_filename = "IMG/explosion/sx/explSX_07.png"; break;
                case 7: anim_filename = "IMG/explosion/sx/explSX_08.png"; break;
                case 8: anim_filename = "IMG/explosion/sx/explSX_09.png"; break;
                case 9: anim_filename = "IMG/explosion/sx/explSX_10.png"; break;
            }

            int XB = EnemyGetX();
            int YB = EnemyGetY();

            

                CParticle_XPL *Explosion = new CParticle_XPL(XB, YB, ASTEROID, EXPLOSION, "boom_01");
                if(Explosion->OnLoad(anim_filename, 64, 64, NULL) == false)
                {
                    CApp::Logger.OnLog( __FILE__, __LINE__, "Error loading image explosion.png", "");
                }

                CApp::Logger.OnLog( __FILE__, __LINE__, "TRY new CParticle_XPL()", "");
                CEntity::EntityList.push_back(Explosion);
                CApp::Logger.OnLog( __FILE__, __LINE__, "new CParticle_XPL() allocated", "");
           

            CApp::Logger.OnLog( __FILE__, __LINE__, "CAsteroid Dead = true", "");

            //CEntity::OnCollision(Entity);
            //EntityDEL();
            CApp::Logger.OnLog( __FILE__, __LINE__, "end CAsteroid Collision()", "");
            return true;
        }
    }
    else
    {
        return false;
    }

	return true;

}




void CAsteroid::OnDeleteEnemy() {



}


void CAsteroid::EntityDEL() {


    CEnemySX::EntityDEL();

}



int CAsteroid::EnemyGetX() {

    return this->Xe;
}

int CAsteroid::EnemyGetY() {

    return this->Ye;
}
