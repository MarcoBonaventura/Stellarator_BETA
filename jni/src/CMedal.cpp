#include "CMedal.h"
#include "CPlayerStat.h"
#include "CShield.h"
#include "CFPS.h"
#include "CAppStateIntro.h"


#include <cmath>
#include <cstdlib>
//#include <random>

int CPlayer::fireMODE = 0;
SDL_Renderer* CMedal::Renderer = NULL;

CMedal::CMedal(float x, float y, float h, float r, char* soundFX, eFlag F, eMove moving) {

    Type = ENTITY_TYPE_MEDAL;
    Size = ENTITY_SIZE_MEDAL;

	this->Xm = x;
	this->Ym = y;

    x2 = y2 = 0;
    w2 = h2 = 199;

    medalHonor = h;
	medalMove = moving;
    selectCollider = F;
	this->Flags = F;

    k = 3 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(10)));
		
    X2 = 0;
    //X2 = 0;


    //Xm += rand() % 100;
    //Ym += rand() % 40;

	//MAXalpha = 10;
    alpha   = 0.1;
    ray     = r;
    //ray     = rand() % 75 + 35;
    x1      = Xm;
    y1      = Ym;

    j = 0;

    counter = 0;
    soundBeep = soundFX;
	
	
	/*** moving zig-zag ***/
	this->offset = x;
	this->kAcc = 0.03;
	this->MaxSpeedX = 1.5;
	this->MaxSpeedY = rand() % 1 + 1;
	this->SpeedX = 0;
	this->SpeedY = 0;
	this->AccelX = 0.1;
	this->MoveX = rand() % 1 + 1;
	MoveRight = true;
	MoveLeft = false;

	//SDL_Log("Medal offset: %d", offset);





    if (Flags == ENTITY_FLAG_BOSS)
    {
        if(x <= WWIDTH * 0.3 || x >= WWIDTH * 0.70)
        {
            OnMove3(cp, POINTS_COUNT, curve, Flags);
        }
        else
        {
            OnMove3(POINTS_COUNT);
        }
    }
    else
    {
        OnMove3(POINTS_COUNT);
    }

    SDL_Log("entity Medal ID: %d", this->ID);

}



CMedal::~CMedal() {

}


//=============================================================================
bool CMedal::OnLoad(char* File) {

    if(CEntity::OnLoad(File) == false) {
        return false;

    }

    return true;


}

void CMedal::OnInit() {

    mVelX = 0;
    mVelY = 0;


    switch (selectCollider)
    {
		case ENTITY_FLAG_ENEMY_S:
			mColliders.resize(1);
			mColliders[0].w = 75;
			mColliders[0].h = 70;
			break;

		case ENTITY_FLAG_ENEMY_M:
			mColliders.resize(1);
			mColliders[0].w = 75;
			mColliders[0].h = 70;
			break;

        case ENTITY_FLAG_ENEMY_M1:
            mColliders.resize(1);
            mColliders[0].w = 75;
            mColliders[0].h = 70;
        break;

		case ENTITY_FLAG_ENEMY_M2:
			mColliders.resize(1);
			mColliders[0].w = 75;
			mColliders[0].h = 70;
			break;

        case ENTITY_FLAG_BOSS:
            mColliders.resize(1);
            mColliders[0].w = 177;
            mColliders[0].h = 135;
        break;

        case ENTITY_FLAG_NONE:
            mColliders.resize(1);
            mColliders[0].w = 130;
            mColliders[0].h = 130;
            break;
    }

    for (int set = 0; set < mColliders.size(); ++set)
    {
        mColliders[set].w = mColliders[set].w * OVERALL_RATIO;
        mColliders[set].h = mColliders[set].h * OVERALL_RATIO;
    }

	//Initialize colliders relative to position
	shiftColliders();



    Renderer = CAppStateIntro::GetInstance()->GetRenderer();

    if(!Renderer)
    {
        SDL_Log("bad Renderer in CMedal %s", SDL_GetError());
        exit(0);
    }

    SDL_Log("Medal X %1.3f Y %1.3f", Xm, Ym);


}

void CMedal::shiftColliders() {

    switch (selectCollider)
    {
        case ENTITY_FLAG_ENEMY_S:
            r = 14 * OVERALL_RATIO;
            break;

        case ENTITY_FLAG_ENEMY_M:
            r = 14;
            break;

        case ENTITY_FLAG_ENEMY_M1:
            r = 14;
            break;

        case ENTITY_FLAG_ENEMY_M2:
            r = 0;
            break;

        case ENTITY_FLAG_BOSS:
            r = 8 * OVERALL_RATIO;
            break;

        case ENTITY_FLAG_NONE:
            r = 5 * OVERALL_RATIO;
    }

    for (int set = 0; set < mColliders.size(); ++set)
    {
        mColliders[set].x = MedalGetX() + (Width - mColliders[set].w) / 2;

        mColliders[set].y = MedalGetY() + r;

        ret.h = mColliders[set].h;
        ret.w = mColliders[set].w;
        ret.x = mColliders[set].x;
        ret.y = mColliders[set].y;

        r += mColliders[set].h;
    }

}


//=============================================================================
void CMedal::OnMove() {

	


	/*** Bezier moving ***/ 

	//this->MoveX += AccelX * CFPS::FPSControl.GetSpeedFactor();
	//Ym += Accel * CFPS::FPSControl.GetSpeedFactor();


	if (this->MoveX > this->MaxSpeedX)		this->MoveX = this->MaxSpeedX;
	if (this->MoveX < -(this->MaxSpeedX))	this->MoveX = -(this->MaxSpeedX);
	//if (this->MoveY > this->MaxSpeedY)		this->MoveY = this->MaxSpeedY;
	//if (this->MoveY < -(this->MaxSpeedY))	this->MoveY = -(this->MaxSpeedY);

	//SDL_Log("MoveX + Acc: %1.3f", this->MoveX);
	//SDL_Log("CMedal Xm: %1.3f", Xm);
	//if (MedalGetX() > 5 && PlayerGetX() < WWIDTH - CPlayer::Width)	{ X += Xm; }
	//else if (MedalGetX() <= 5 && Xm > 0)							{ X += Xm; }
	//else if (MedalGetX() >= WWIDTH - CPlayer::Width && Xm < 0)		{ X += Xm; }

	
	//this->Xm += this->MoveX;
	//Y += MoveY;

	

	if (this->Xm > (offset + 150))   
	{
		if (MoveX > 0)
		{
			MoveX -= kAcc;
			kAcc += 0.02;
			//SDL_Log("MoveX > offset: %1.3f - kAcc: %1.2f", (this->MoveX), kAcc);
		}
		else
		{
			this->MoveLeft = true; this->MoveRight = false;
			//SDL_Log("MoveLeft = true");
			kAcc = 0;
			offset += (Xm - (offset + 150)) + 20;
			MoveX = 0;
			//SDL_Log("new offset: %d", offset);
		}
	}
	else if (this->Xm < (offset - 150))    
	{ 
		if (MoveX > 0)
		{
			MoveX -= kAcc;
			kAcc += 0.02;
			//SDL_Log("MoveX < offset: %1.3f - kAcc: %1.2f", this->MoveX, kAcc);
		}
		else
		{
			this->MoveLeft = false; this->MoveRight = true;
			//SDL_Log("MoveRight = true");
			kAcc = 0;
			offset +=  ((offset - 150) - Xm) - 40;
			MoveX = 0;
			//SDL_Log("new offset: %d", offset);
		}
	}
	else
	{
		MoveX += AccelX * CFPS::FPSControl.GetSpeedFactor();
		//SDL_Log("MoveX SpeedUp!");
	}

	this->MoveDown = true;
	this->MoveUp = false;

	if (this->MoveLeft)   { this->Xm += -(this->MoveX);  }
	if (this->MoveRight)  { this->Xm += this->MoveX;  }
	if (this->MoveDown)	{ this->Ym += 2; }
	


}


//=============================================================================
void CMedal::OnMove2() {

	/*** Logaritmic moving ***/

	//if (alpha > MAXalpha) alpha = MAXalpha;

	if (counter %2 == 0)
	{
		Ym =    y1+ray*sin(alpha);
		Xm =    x1+ray*cos(alpha);

		//std::cout<<"raggio: "<<ray<<" - alpha: "<<alpha<<" - Xm: "<<Xm<<" - Ym: "<<Ym<<std::endl;

		if (ray < WWIDTH / 5) ray+= 0.5;
		alpha += 0.025;

		//float temp_y1 = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2))) + 1;
		y1 += 2;
	}

}


void CMedal::OnMove3() {

    if (j < POINTS_COUNT) {
        Xm = curve[j].x;
        Ym = curve[j].y;
    }

    j++;

}

void CMedal::OnMove3(int numberOfPoints) {

	//SDL_Log("computing Medal vect");
	cp[0].x = Xm;
	cp[0].y = Ym;

	//SDL_Log("cp[0].x=%1.2f - cp[0].y=%1.2f", cp[0].x, cp[0].y);

	// STEP1
	if (cp[0].x >= WWIDTH / 2)
	{
		cp[1].x = cp[0].x - WWIDTH * 0.3f;
		cp[2].x = cp[1].x + WWIDTH * 0.6f;
		cp[3].x = cp[0].x - WWIDTH * 0.3f;
	}
	else if (cp[0].x < WWIDTH / 2) 
	{ 
		cp[1].x = cp[0].x + WWIDTH * 0.3f;
		cp[2].x = cp[1].x - WWIDTH * 0.6f;
		cp[3].x = cp[2].x + WWIDTH * 0.3f;
	}
	cp[1].y = cp[0].y + 300;
	cp[2].y = cp[1].y;
	cp[3].y = WHEIGHT + 100;


	//SDL_Log("cp[1].x= %1.2f - cp[1].y= %1.2f", cp[1].x, cp[1].y);
	//SDL_Log("cp[2].x= %1.2f - cp[2].y= %1.2f", cp[2].x, cp[2].y);
	//SDL_Log("cp[3].x= %1.2f - cp[3].y= %1.2f", cp[3].x, cp[3].y);



	float dt;
	int   i;

	dt = 1.0 / (numberOfPoints - 1);

	for (i = 0; i < numberOfPoints; i++)
	{
		//SDL_Log("OnMove3 i: %d", i);

		curve[i] = PointOnCubicBezier(cp, i*dt, this->k);
        points[i].x = (int)curve[i].x;
        points[i].y = (int)curve[i].y;
 	}

	//SDL_Log("Medal curve populated");

}


void CMedal::OnMove3(Point2D cp[4], int numberOfPoints, Point2D curve[POINTS_COUNT], int Flags)
{

    //SDL_Log("return Medal coords");
    cp[0].x = MedalGetX();
    cp[0].y = MedalGetY();

    //SDL_Log("cp[0].x=%1.2f - cp[0].y=%1.2f", cp[0].x, cp[0].y);

    // STEP1
    if (cp[0].x >= WWIDTH / 2)
    {
        cp[1].x = cp[0].x - 300;
        cp[2].x = cp[1].x + 500;
        cp[3].x = cp[0].x - 1200;
    }
    else if (cp[0].x < WWIDTH / 2)
    {
        cp[1].x = cp[0].x + 300;
        cp[2].x = cp[1].x - 300;
        cp[3].x = cp[2].x + 1200;
    }
    cp[1].y = cp[0].y + 300;
    cp[2].y = cp[1].y;
    cp[3].y = cp[2].y + 1200;

    /*
    SDL_Log("cp[1].x=%1.2f - cp[1].y=%1.2f", cp[1].x, cp[1].y);
    SDL_Log("cp[2].x=%1.2f - cp[2].y=%1.2f", cp[2].x, cp[2].y);
    SDL_Log("cp[3].x=%1.2f - cp[3].y=%1.2f", cp[3].x, cp[3].y);
    */


    float dt;
    int   i;

    dt = 1.0 / (numberOfPoints - 1);

    for (i = 0; i < numberOfPoints; i++)
    {
        //SDL_Log("OnMove3 i: %d", i);

        curve[i] = PointOnCubicBezier(cp, i*dt, this->k);
        points[i].x = (int)curve[i].x;
        points[i].y = (int)curve[i].y;
    }

    //SDL_Log("Medal curve populated");

}


//=============================================================================
void CMedal::OnLoop() {

	switch (medalMove)
	{
        case BEZIER:
                OnMove3();
            break;

        case LOGARITMIC:
                OnMove2();
            break;
        case BEZIER_BOSS:
                OnMove3();
            break;

	}

	
	shiftColliders();

    CollisionLoop();

    if (MedalGetX() < 0 || MedalGetX() > WWIDTH || MedalGetY() > WHEIGHT) Dead = true;

    counter++;

}



//=============================================================================
void CMedal::OnRender() {

	this->X = this->Xm;
	this->Y = this->Ym;

    if (entityRenderer)
    {
        TextureBank::Get(entityTexture)->Render(this->X, this->Y, this->Width, this->Height, x2, y2, w2, h2, 255);

        //SDL_SetRenderDrawColor(entityRenderer, 0xFF, 0xFF, 0x00, 0xFF);
        //SDL_RenderFillRect(entityRenderer, &ret);

    }
    else
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "bad Renderer", "");
    }
    //RenderDot(MedalGetX(), MedalGetY(), 5, 5, dotColor);
   	/* just for debug Bezier Curves */
    //SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawLines(Renderer, points, POINTS_COUNT);
}





//=============================================================================
void CMedal::OnCleanup() {

    //CEntity::OnCleanup();

}




//=============================================================================
void CMedal::CollisionLoop() {

    for (int i=0; i<CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i])
        {
            CApp::Logger.OnLog( __FILE__, __LINE__, "CMedal EntityList = NULL", "");
            continue;
        }
        CEntity::CheckCollision(CEntity::EntityList[i]);
    }


}



//=============================================================================
bool CMedal::OnCollision(CEntity *Entity) {

    Dead = true;

    CSoundBank::SoundControl.Play2(soundBeep);

    CPlayer::PlayerStat.playerHonor += medalHonor;

    /*
    if (medalHonor == 0)
    {
        CShield *myShield = new CShield(CPlayer::PlayerStat.PlayerGetX(), CPlayer::PlayerStat.PlayerGetY());
        CEntity::EntityList.push_back(myShield);
    }
    else if (medalHonor == 10)
    {
        CPlayer::PlayerStat.fireMODE = FIRE_TRIPLE;
    }
    */

    return true;



}





std::vector<SDL_Rect>& CMedal::getColliders() {

	return mColliders;

}


//=============================================================================
float CMedal::MedalGetX() {

    return this->Xm;

}


//=============================================================================
float CMedal::MedalGetY() {

    return this->Ym;

}


//=============================================================================
void CMedal::EntityDEL() {

    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead)
        {
            (*it)->OnCleanup();
            delete *it;
            it = CEntity::EntityList.erase(it);
            SDL_Log("medal deleted");
        }
        else
        {
            it++;
        }
    }




}


/*
float CMedal::GetRandom() {

	static std::default_random_engine e;
	static std::uniform_real_distribution<> dis(1, 2); // rage 0 - 1
	return dis(e);
		
}
*/

Point2D CMedal::PointOnCubicBezier(Point2D cp[4], float t, float k)
{
	float   ax, bx, cx;
	float   ay, by, cy;
	float   tSquared, tCubed;
	Point2D result;

	/* calcolo dei coefficienti del polinomio */

	cx = k * (cp[1].x - cp[0].x);
	bx = k * (cp[2].x - cp[1].x) - cx;
	ax = cp[3].x - cp[0].x - cx - bx;

	cy = k * (cp[1].y - cp[0].y);
	by = k * (cp[2].y - cp[1].y) - cy;
	ay = cp[3].y - cp[0].y - cy - by;

	/* calcolo del punto della curva in relazione a t */

	tSquared = t * t;
	tCubed = tSquared * t;

	result.x = (ax * tCubed) + (bx * tSquared) + (cx * t) + cp[0].x;
	result.y = (ay * tCubed) + (by * tSquared) + (cy * t) + cp[0].y;

	//SDL_Log("Medal PointOnCubicBezier()");

	return result;

}

void CMedal::RenderDot(float x, float y, int w, int h, SDL_Color dotColor) {


    //SDL_Log("RenderDot");




    if (Renderer)
    {
        //SDL_Color red;
        //SDL_GetRenderDrawColor(Renderer, &red.r, &red.g, &red.g, &red.a);
        SDL_Rect DOTrect = { (int)x, (int)y, w, h };
        SDL_SetRenderDrawColor(Renderer, dotColor.r, dotColor.g, dotColor.b, dotColor.a);
        SDL_RenderFillRect(Renderer, &DOTrect);
        SDL_RenderPresent(Renderer);
    }
    else
    {
        SDL_Log("Bad Renderer %s", SDL_GetError());
    }


}

