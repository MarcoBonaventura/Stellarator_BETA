#include "CParticle_XPL.h"

#include <random>


CParticle_XPL::CParticle_XPL(int x, int y, eMove z, Effect_type E, char* soundFX) {

    xBoom   = x;
    yBoom   = y;
    Xf = xBoomF = x +32;
    Yf = yBoomF = y +32;

    index = 0;

    X = x;
    Y = y;
    X2 = Y2 = 0;
    iY = kX   = 0;
    Z = z;
    motion_xpl = z;
    wf = hf = 5;
    Xf2 = Yf2 = 0;

    this->effect = E;
    this->Dead = false;
    Expired = false;

    Type = ENTITY_TYPE_PARTICLE;
    Flags = ENTITY_FLAG_MAPONLY;
    Size = ENTITY_SIZE_PP;

    grey = 150;
    //alpha = 45;
	ray = 5;

    const double start  = 30;
    const double stop   = 60;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(start, std::nextafter(stop, DBL_MAX));

    alpha1 = alpha2 = dist(mt);
    SDL_Log("alpha1/2 %1.2f %1.2f", alpha1, alpha2);

    alphaChannel = 255;
    MaxSpeedX = 2 * OVERALL_SPEED_RATIO;
    MaxSpeedY = 2 * OVERALL_SPEED_RATIO;

    counter = 0;

    /*
    Surf_Flare = NULL;
    for(int v = 0; v < 10; v++)
    {
        flareArray.push_back(Surf_Flare);
    }
    */

    //OnLoad(anim_filename, 64, 64, NULL);

    /** Smart Explosion for smart enemies */
    CSoundBank::SoundControl.Play2(soundFX);

    //SDL_Log("new xpl() ID: %d", this->ID);


}

CParticle_XPL::~CParticle_XPL() {

    //if (Surf_Flare)  SDL_FreeSurface(Surf_Flare);


}

void CParticle_XPL::OnInit() {


    switch (this->effect) {

        case FLARES_BIG:

            for (int i = 0; i < MAX_FLARES_BIG; i++)
            {
                flares_big[i].x = X + this->Width / 2;
                flares_big[i].y = Y + this->Height / 2;
                flares_big[i].w = 15;
                flares_big[i].h = 15;
            }

            break;

        case FLARES_SMALL:

            for (int i = 0; i < MAX_FLARES_SMALL; i++)
            {
                flares_small[i].x = X + this->Width / 2;
                flares_small[i].y = Y + this->Height / 2;
                flares_small[i].w = 15;
                flares_small[i].h = 15;
            }

            break;


        default:


            break;
    }



}

//=============================================================================
bool CParticle_XPL::OnLoad(char *File, int Width, int Height, int MaxFrames) {

    if(!CEntity::OnLoad(File, Width, Height, MaxFrames)) {

        return false;
    }

        /*
        switch (rand() % 3)
        {
            case 0: flare_file = "IMG/explosion/flare_yellow_anim_5x.bmp";
            break;

            case 1: flare_file = "IMG/explosion/flare_red_anim_5x.bmp";
            break;

            case 2: flare_file = "IMG/explosion/flare_green_anim_5x.bmp";
            break;

            case 3: flare_file = "IMG/explosion/flare_blue_anim_5x.bmp";
            break;
        }

        for (int a=0; a<10; a++)
        {
            //flareArray[a] = CSurface::OnLoad("IMG/explosion/flare_yellow_5x.bmp", NULL);
            //flareArray[a] = Texture::OnLoad(flare_file, NULL);
            Texture::Transparent(flareArray[a], 255, 0, 255);
        }

        */
    return true;


}





//=============================================================================
void CParticle_XPL::OnCleanup() {



    CEntity::OnCleanup();

}


//=============================================================================
void CParticle_XPL::OnLoop() {


    switch (this->effect) {

        case EXPLOSION:
            if (iY < 8) {
                if (kX < 8) {
                    X2 = W2 * kX;
                } else if (kX == 8) {
                    kX = 0;
                    iY++;
                    //X2 += H2;
                    X2 = 0;
                    Y2 = H2 * iY;
                }

            }
            kX++;

            if (iY >= 8) {
                this->Dead = true;
                //SDL_Log("xpls ID %d finished", this->ID);
            }

            break;

        case FLARES_BIG:

            if (counter > 50) this->Dead = true;

            break;


        case FLARES_SMALL:

            if (alphaChannel <= 0) this->Dead = true;

            break;

    }

    OnMove();

    /*
    if (ray > 20)
    {

        if (alphaChannel > 0) alphaChannel -= 15;
        std::cout<<"alphaChannel: "<<alphaChannel<<std::endl;
    }
    */

    if (grey >= 0) {
        grey -= 5;
    }

    if(this->counter %5 == 0) {
        alphaChannel -= 10;
        Xf2++;
    }
    if (alphaChannel < 0) alphaChannel = 0;

    //std::cout<<"horizon: "<<horizon<<" Player Y+400: "<<CPlayer::PlayerStat.PlayerGetY()<<"\n";

    //alpha = 2;
    ray += 2;
    counter++;

}

void CParticle_XPL::OnMove() {

    switch (this->motion_xpl) {

        case MOVE_DX:
            xBoom += MaxSpeedX;
            X = xBoom;
            Y = yBoom;
            break;

        case MOVE_SX:
            xBoom -= MaxSpeedX;
            X = xBoom;
            Y = yBoom;
            break;

        case ESCAPE_DX:
            xBoom += MaxSpeedX;
            X = xBoom;
            Y = yBoom;
            break;

        case ESCAPE_SX:
            xBoom -= MaxSpeedX;
            X = xBoom;
            Y = yBoom;
            break;

        case MOVE_DOWN:
            yBoom += 3;
            break;

        case NONE:

            break;

        default:

            break;
    }


    //r +=2;

    //ray += 0.5;


    switch (this->effect) {

        case FLARES_BIG:

            for (int i = 0; i < MAX_FLARES_BIG; i++)
            {
                flares_big[i].x += (cos((alpha2 * PIG) / 180));
                flares_big[i].y += (sin((alpha2 * PIG) / 180));
                alpha2 += 360 / MAX_FLARES_BIG;
            }

            break;

        case FLARES_SMALL: {

            //SDL_Log("flares_small origin x: %d - y: %d", flares_small[0].x, flares_small[0].y);
            for (int i = 1; i < MAX_FLARES_SMALL + 1; i++) {

                double temp_cosX = (cos((alpha2 * PIG) / 180));
                double temp_sinY = (sin((alpha2 * PIG) / 180));
                flares_small[i - 1].x += std::round(temp_cosX);
                flares_small[i - 1].y += std::round(temp_sinY);
                //SDL_Log("alpha: %1.3f - cosX: %1.2f - cosY %1.2f", alpha, temp_cosX, temp_sinY);
                //SDL_Log("SDL_Rect.x: %d - SDL_Rect.y: %d", flares_small[i - 1].x, flares_small[i - 1].y);
                alpha2 += 360.0 / MAX_FLARES_SMALL;
            }
        }
            break;


        default:


            break;

    }





    if (alpha2 >= 360) {
        //SDL_Log("set alpha = 0");
        alpha2 = alpha1;
    }


}


//=============================================================================
void CParticle_XPL::OnRender() {


    //X2 = *pX2;
    //Y2 = *pY2;


    if (entityRenderer) {

        switch (effect) {

            case EXPLOSION: {

                //CSurface::OnDraw(Surf_Display, Surf_Entity, X, Y, X2, Y2, Width, Height, 0);
                TextureBank::Get(particleTexture)->Render(this->X, this->Y, this->Width,
                                                          this->Height,
                                                          X2, Y2, W2, H2, 255);


                for (index = 0; index < MAX_FLARES_BIG; index++) {
                    SDL_SetRenderDrawColor(entityRenderer, index * 255, index * 25, 0, 0xFF);

                    //SDL_RenderFillRect(entityRenderer, stars[i]);

                }


            }
                break;

            case FLARES_BIG: {

                for (index = 0; index < MAX_FLARES_BIG; index++) {
                    SDL_SetRenderDrawColor(entityRenderer, index * 255, index * 25, 0, alphaChannel);
                    SDL_RenderFillRect(entityRenderer, &flares_big[index]);

                    //SDL_RenderFillRect(entityRenderer, stars[i]);

                }
            }
                break;

            case FLARES_SMALL: {
                for (index = 1; index < MAX_FLARES_SMALL + 1; index++) {
                    if (flares_small != NULL)
                    {
                        SDL_SetRenderDrawColor(entityRenderer, 80, 80, 80, alphaChannel);
                        SDL_SetRenderDrawBlendMode(entityRenderer, SDL_BLENDMODE_BLEND);
                        SDL_RenderFillRect(entityRenderer, &flares_small[index - 1]);
                        //SDL_Log("XPL RENDER X: %d - Y: %d - W: %d - H: %d", flares_small[index].x, flares_small[index].y, flares_small[index].w, flares_small[index].h);
                    }
                }
            }
                break;

            default:
                SDL_Log("warning: XPL render default!");
                break;
        }
    }
    else
    {
        SDL_Log("ParticleXPL Bad Renderer! %s", SDL_GetError());
    }



}


//=============================================================================
bool CParticle_XPL::IsExpired() {

    /*
    if (*pX2 >= 480 && *pY2 >= 480)
    {
        Dead = true;
        Expired = true;
        //std::cout<<"EXPIRED - *pX2: "<<*pX2<<" *pY2: "<<*pY2<<std::endl;
        //CApp::Logger.OnLog( __FILE__, __LINE__, "CParticle_XPL::IsExpired()", "");
        //EntityDEL();

        for(std::vector<SDL_Surface*>::iterator it = flareArray.begin(); it!= flareArray.end(); it++)
        {
            delete *it;
        }
        flareArray.clear();

        /*
        for (int exp=0; exp<13; exp++)
        {
            delete [] flareArray[exp];
        }

        //delete [] flareArray;
        *//*
        return true;

    }
    */

    return false;





}


void CParticle_XPL::shiftColliders() {

    //The row offset
    int r = 0;

    //Go through the dot's collision boxes
    for (int set=0; set<mColliders.size(); ++set)
    {
        //Center the collision box
        mColliders[set].x = mPosX + (Width - mColliders[set].w) /2;

        //Set the collision box at its row offset
        mColliders[set].y = mPosY + r;

        //Move the row offset down the height of the collision box
        r += mColliders[set].h;
    }

}

std::vector<SDL_Rect>& CParticle_XPL::getColliders() {

	return mColliders;

}



//=============================================================================
void CParticle_XPL::EntityDEL() {

    CEntity::EntityDEL();

    /*
    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead)
        {
            delete (*it);
            it = CEntity::EntityList.erase(it);

        }
        else
        {
            it++;
        }
    }
    */

}
