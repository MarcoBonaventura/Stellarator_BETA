//==============================================================================
#define _CRT_SECURE_NO_DEPRECATE

#include "CEntity.h"
#include "CGenerator.h"
#include "Stringify.h"
#include "CArea.h"

#include "Define.h"

#include "CAppStateGame.h"

#include <iostream>
#include <algorithm>
#include <functional>

#define Maximum(a, b) ((a > b) ? a : b)
#define Minimum(a, b) ((a < b) ? a : b)

#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

int WWIDTH;
int WHEIGHT;

//==============================================================================
std::vector<CEntity*> CEntity::EntityList;
std::map<int, CEntity*> CEntity::EntityMap;
std::map<int, CEntity*> CEntity::TargetEnemyMap;

int CEntity::current_ID = 0;
int CEntity::counter_BRO = 0;


int CEntity::Xp = 0;
int CEntity::Yp = 0;

//==============================================================================
CEntity::CEntity() {

    ID = current_ID++;

    if(this->Type == ENTITY_SIZE_SSX) BRO = counter_BRO++;

    X  = Y  =   0;
    X1 = Y1 =   0;
    X2 = Y2 =   0;
    Xe = Ye =   0;
    Xb = Yb =   0;


    ib = 0;
    kb = 0;

    //this->Width  = 128;
    //this->Height = 128;

    PlayerScore = 0;

    AnimState   = 7;

    counter     = 0;

    MoveLeft  = false;
    MoveRight = false;
    MoveUp    = false;
    MoveDown  = false;

    boom      = false;
    Dead      = false;

    SpeedX = 0;
    SpeedY = 0;

    AccelX = 0;
    AccelY = 0;

    MaxSpeedX = 4;
    MaxSpeedY = 3;


    Col_X = 0;
    Col_Y = 0;

    Col_Width  = 20;
    Col_Height = 5;

    Window = CAppStateGame::GetInstance()->GetWindow();

    entityRenderer = CAppStateGame::GetInstance()->GetRenderer();


}

//==============================================================================
CEntity::~CEntity() {

    //if (entityRenderer) SDL_DestroyRenderer(entityRenderer);

}


//==============================================================================
bool CEntity::OnLoad(char *File, int Width, int Height, int MaxFrames) {


	this->Width = Width;
	this->Height = Height;


	//Anim_Control.MaxFrames = MaxFrames;

    return true;

}

bool CEntity::OnLoad(char *File, int Width, int Height) {


	this->Width = Width;
	this->Height = Height;


	//Anim_Control.MaxFrames = MaxFrames;

    return true;

}

bool CEntity::OnLoad(char *File, int RGBalpha) {


    return true;

}

bool CEntity::OnLoad(char *File) {


    return true;

}


//=====ON LOOPING ENTITY=======================================================
void CEntity::OnLoop() {

    SDL_Log("Entity loop");

    /*
    //Anim_Control.OnAnimate();

    //Player not Moving
    if(MoveLeft == false && MoveRight == false && MoveUp == false && MoveDown == false)
    {
        StopMove();
    }

    //We're Moving
    if(MoveLeft)    { AccelX = -0.5;    }
    if(MoveRight)   { AccelX = 0.5;     }
    if(MoveUp)      { AccelY = -0.5;    }
    if(MoveDown)    { AccelY = 0.5;     }


    SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
    SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();


    if(SpeedX > MaxSpeedX)  SpeedX =  MaxSpeedX;
    if(SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
    if(SpeedY > MaxSpeedY)  SpeedY =  MaxSpeedY;
    if(SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;


    OnAnimate();

    OnMove(SpeedX, SpeedY);

    Xp = X;
    Yp = Y;

    //EntityDEL();

    counter++;
     */

}


//==============================================================================
void CEntity::OnMove(float MoveX, float MoveY) {

    /*

	if (MoveX == 0 && MoveY == 0) return;



	if (X > 10 && X < WWIDTH - 128)          {	X = MoveX; }
	else if (X <= 10 && MoveX > 0)			 {	X = MoveX; }
	else if (X >= WWIDTH - 128 && MoveX < 0) {	X = MoveX; }



	if (Y > WHEIGHT / 2 && Y < WHEIGHT - 128)   Y = MoveY;
	else if (Y <= WHEIGHT / 2 && MoveY > 0)		Y = MoveY;
	else if (Y >= 630 && MoveY <0)				Y = MoveY;

    */

	/***** ANALOGIC PILOT MODE *****
	if (X > 10 && X < WWIDTH - 128)          { X += MoveX; }
	else if (X <= 10 && MoveX > 0)			 { X += MoveX; }
	else if (X >= WWIDTH - 128 && MoveX < 0) { X += MoveX; }



	if (Y > WHEIGHT / 2 && Y < WHEIGHT - 128)         Y += MoveY;
	else if (Y <= WHEIGHT / 2 && MoveY > 0) Y += MoveY;
	else if (Y >= 630 && MoveY <0)  Y += MoveY;
	*/

}

void CEntity::StopMove() {

	if (SpeedX > 0) { AccelX = -1; }
	if (SpeedX < 0) { AccelX = 1; }

	if (SpeedY > 0) { AccelY = -1; }
	if (SpeedY < 0) { AccelY = 1; }

	if (SpeedX < 2.0f && SpeedX > -1.0f)
	{
		AccelX = 0;
		SpeedX = 0;
	}
	if (SpeedY < 2.0f && SpeedY > -1.0f)
	{
		AccelY = 0;
		SpeedY = 0;
	}


}

void CEntity::StopMoveX() {

	if (SpeedX > 0) { AccelX = -1; }
	if (SpeedX < 0) { AccelX = 1; }

	if (SpeedX < 2.0f && SpeedX > -1.0f)
	{
		AccelX = 0;
		SpeedX = 0;
	}

}

void CEntity::StopMoveY() {


	if (SpeedY > 0) { AccelY = -1; }
	if (SpeedY < 0) { AccelY = 1; }

	if (SpeedY < 2.0f && SpeedY > -1.0f)
	{
		AccelY = 0;
		SpeedY = 0;
	}


}

void CEntity::OnRender() {


}

void CEntity::OnCleanup() {


}


//==============================================================================
void CEntity::OnAnimate() {

    if (counter %3 == 0)
    {


        if(MoveLeft)
        {
            if (AnimState > 0)
            {
                AnimState--;
            }
        }
        else if (MoveLeft == false)
        {
            if (AnimState < 7)
            {
                AnimState++;
            }
        }


        if(MoveRight)
        {
            if (AnimState < 12)
            {
                AnimState++;
            }
        }
        else if (MoveRight == false)
        {
            if (AnimState > 7)
            {
                AnimState--;
            }
        }

    }




    //Anim_Control.OnAnimate();


}

bool CEntity::OnCollision(CEntity *Entity) {

    return true;

}




//=====GET BOUNDS==============================================================
SDL_Rect CEntity::GetBounds() {

    //std::cout<<"GetBounds()\n";

    SDL_Rect bounds;
    bounds.x = (Sint16)(X);
    bounds.y = (Sint16)(Y);
    bounds.w = (Sint16)(Width);
    bounds.h = (Sint16)(Height);

    return bounds;

}


//=====NORMALIZED BOUNDS=======================================================
SDL_Rect CEntity::NormalizeBounds(const SDL_Rect& rect) {

    //std::cout<<"NormalizeBounds()\n";

    SDL_Rect normalized;

    normalized.x = rect.x - (Sint16)X + Width;
    normalized.y = rect.y - (Sint16)Y;
    normalized.w = rect.w;
    normalized.h = rect.h;

    return normalized;


}


//=====INTERSECTION============================================================
SDL_Rect CEntity::Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB) {

    int x1 = Maximum(boundsA.x, boundsB.x);
    int y1 = Maximum(boundsA.y, boundsB.y);

    int x2 = Minimum(boundsA.x + boundsA.w, boundsB.x + boundsB.w);
    int y2 = Minimum(boundsA.y + boundsA.h, boundsB.y + boundsB.h);

    int width   = x2 - x1;
    int height  = y2 - y1;

    if (width > 0 && height > 0)
    {
        SDL_Rect intersect = {x1, y1, width, height};
        return intersect;
    }
    else
    {
        SDL_Rect intersect = {0, 0, 0, 0};
        return intersect;
    }



}


//=====CHECK COLLISION=========================================================
/*
bool CEntity::CheckCollision(CEntity *Entity) {


    if ( this->Type != Entity->Type &&
         this != NULL   &&
         this != false  &&
         Entity != NULL &&
         Entity->Dead == false &&
         Entity->Flags ^ ENTITY_FLAG_MAPONLY )
    {

        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_BOSS)	  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_BOSS)	  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;

        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_BOSS)      goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MyBOMB)    goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_PLAYER)    goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;

        if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_PLAYER)	  goto jump;
        if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;

        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_MyBOMB)    goto jump;
        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;

        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_BOSS)      goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        SDL_Rect collisionRect = Intersection(this->GetBounds(), Entity->GetBounds());

        SDL_Rect normalA = this->NormalizeBounds(collisionRect);
        SDL_Rect normalB = Entity->NormalizeBounds(collisionRect);

        for(int y=0; y<collisionRect.h; y++)
        {
            for(int x=0; x<collisionRect.w; x++)
            {
                if(GetAlphaXY(this, normalA.x + x, normalA.y + y) && GetAlphaXY(Entity, normalB.x + x, normalB.y + y))
                {
                    CEntityCol EntityCol;

                    EntityCol.EntityA = this;
                    EntityCol.EntityB = Entity;

                    CEntityCol::EntityColList.push_back(EntityCol);

                    return true;

                }

            }

        }





    }

    jump:

    return false;

}



//=====GET ALPHA X-Y===========================================================
bool CEntity::GetAlphaXY(CEntity *Entity, int x, int y) {

    int bpp = TextureBank::Get(entityTexture)->bpp;

    Uint8 *p = (Uint8*)TextureBank::Get(entityTexture)->pxl + y * TextureBank::Get(entityTexture)->ptc + x * bpp;

    Uint32 pixelColor;

    switch(bpp)
    {
        case(1):
            pixelColor = *p;
            break;

        case(2):
            pixelColor = *(Uint16*)p;
            break;

        case(3):
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                pixelColor = p[0] << 16 | p[1] << 8 | p[2];
            else
                pixelColor = p[0] | p[1] << 8 | p[2] << 16;
            break;

        case(4):
            pixelColor = *(Uint32*)p;
            break;
    }

    Uint8 red, green, blue, alpha;

    SDL_PixelFormat* format = TextureBank::Get(entityTexture)->fmt;

    SDL_GetRGBA(pixelColor, format, &red, &green, &blue, &alpha);

    return alpha > 128;




}
*/

void CEntity::CheckCollision(CEntity *Entity) {

    //CApp::Logger.OnLog( __FILE__, __LINE__, "CheckCollision STEP1", "");
	//SDL_Log("Entity CheckCollision()");

    if ( this != Entity &&
         this->Dead ==  false  &&
         Entity->Dead == false &&
         Entity->Flags ^ ENTITY_FLAG_MAPONLY )
    {
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
		if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_BOSS)	  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_BOSS)	  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;

        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_BOSS)      goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
		if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MyBOMB)    goto jump;
		if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_PLAYER)    goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;

		if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
		if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
		if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_PLAYER)	  goto jump;
        if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
		
		if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_MyBOMB)    goto jump;
        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
		if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;

        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_BOSS)      goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
		if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_BOSS)      goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;
		
        SDL_Rect collisionRect = Intersection(this->GetBounds(), Entity->GetBounds());

        if(collisionRect.w > 0 && collisionRect.h > 0)
        {
            //The sides of the rectangles
            int leftA, leftB;
            int rightA, rightB;
            int topA, topB;
            int bottomA, bottomB;

            //SDL_Rect RectA = mColliders;
            std::vector<SDL_Rect> RectA = this->getColliders();

            //SDL_Rect RectB = EntityRect;
            std::vector<SDL_Rect> RectB = Entity->getColliders();

            //Go through the A boxes
			for (Uint32 Abox = 0; Abox < RectA.size(); Abox++)
            {

                //Calculate the sides of rect A
                leftA   = RectA[Abox].x;
                rightA  = RectA[Abox].x + RectA[Abox].w;
                topA    = RectA[Abox].y;
                bottomA = RectA[Abox].y + RectA[Abox].h;

                // Go through the B boxes
				for (Uint32 Bbox = 0; Bbox < RectB.size(); Bbox++)
                {
                    //Calculate the sides of rect B
                    leftB = RectB[Bbox].x;
                    rightB = RectB[Bbox].x + RectB[Bbox].w;
                    topB = RectB[Bbox].y;
                    bottomB = RectB[Bbox].y + RectB[Bbox].h;

                    //If no sides from A are outside of B
                    if(!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
                    {
						// collision is detected
                        CEntityCol EntityCol;

                        EntityCol.EntityA = this;
                        EntityCol.EntityB = Entity;

                        /** just for debug
                        char TempA[255];
                        int Temp1 = EntityCol.EntityA->Type;
                        int n1 = sprintf(TempA, "%d", Temp1);
                        //SDL_Log("EntityA.x: %d",EntityCol.EntityA->X);
                        //SDL_Log("EntityA.y: %d",EntityCol.EntityA->Y);

                        char TempB[255];
                        int Temp2 = EntityCol.EntityB->Type;
                        int n2 = sprintf(TempB, "%d", Temp2);
                        //SDL_Log("EntityB.x: %d",EntityCol.EntityB->X);
                        //SDL_Log("EntityB.y: %d",EntityCol.EntityB->Y);

                        //SDL_Log("EntityColEnd");

                        TempA[255];
                        Temp1 = EntityCol.EntityA->Size;
                        n1 = sprintf(TempA, "%d", Temp1);

                        TempB[255];
                        Temp2 = EntityCol.EntityB->Size;
                        n2 = sprintf(TempB, "%d", Temp2);
                        */

                        CEntityCol::EntityColList.push_back(EntityCol);

                        break;
                    }
                }
            }
        }
    }

    jump:

    return;


}

void CEntity::CollisionLoop() {

    //LEAVE BLANK!!!!

}

void CEntity::shiftColliders() {

	//LEAVE BLANK!!!!

}


std::vector<SDL_Rect>& CEntity::getColliders() {

    return mColliders;

}

//-----------------------------------------------------------------------------
bool CEntity::Jump() {

    //std::cout << "collision detected!\n";
    //Entity->Dead = true;
    return true;

}


//-----------------------------------------------------------------------------
void CEntity::ScoreInc() {

}

bool CEntity::Crash() {

    CApp::Logger.OnLog( __FILE__, __LINE__, "CEntity::Crash()", "");
    //CEntityCol Player;
    //Player.EntityA->Dead = true;
    //PlayerHealth += -15;


    return true;
}


void CEntity::OnFire() {

}

bool CEntity::canFIRE() {}

bool CEntity::booleanFIRE() {}

void CEntity::IA() {

}

int CEntity::GetX() {

    return Xp;

}

int CEntity::GetY() {

    return Yp;

}

int CEntity::EnemyGetX() {}
int CEntity::EnemyGetY() {}

float CEntity::PlayerGetX() {}
float CEntity::PlayerGetY() {}

int CEntity::GetEntityMoving() {}


CEntity* CEntity::GetEntity(int temp_ID) {

    if (EntityMap.find(temp_ID) == EntityMap.end())
    {
        SDL_Log("Map not found");
        return 0;
    }

    return EntityMap[temp_ID];


}


//-----------------------------------------------------------------------------
void CEntity::EntityDEL() {

    int temp_ID;

    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead)
        {
            temp_ID = (*it)->ID;
            if (!CEntity::TargetEnemyMap.empty())
            {
                std::map<int, CEntity*>::iterator iter;
                if(CEntity::TargetEnemyMap.find(this->ID) != CEntity::TargetEnemyMap.end())
                {
                    //SDL_Log("entityDEL() ID %d erased from map", this->ID);
                    iter = CEntity::TargetEnemyMap.find(this->ID);
                    CEntity::TargetEnemyMap.erase(iter);
                }
            }


            SDL_Log("delete Entity ID: %d",(*it)->ID);
            (*it)->OnCleanup();
            delete *it;
            (it) = CEntity::EntityList.erase(it);
        }
        else
        {
            it++;
        }
    }


	

}

//OLD==========================================================================
void CEntity::OnDelete() {


}
