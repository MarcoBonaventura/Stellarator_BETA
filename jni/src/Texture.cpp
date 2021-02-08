//==============================================================================
#include <iostream>
#include <string>
#include "CApp.h"
#include "Texture.h"
#include "Stringify.h"
//#include "zzip.h"

//==============================================================================
Texture::Texture() {

}

//==============================================================================
SDL_Surface* Texture::OnLoad(char* File) {

	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Dest = NULL;

    //LOAD .PNG AND .JPEG image files
	if((Surf_Temp = IMG_Load(File)) == NULL) {
		return NULL;
	}

//	Surf_Dest = SDL_DisplayFormatAlpha(Surf_Temp);
	SDL_FreeSurface(Surf_Temp);

	return Surf_Dest;


}


//==============================================================================
SDL_Surface* Texture::OnLoad(char* File, int RGBalpha) {

	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Dest = NULL;

    //LOAD ONLY .BMP image files!!!
	if((Surf_Temp = SDL_LoadBMP(File)) != NULL)
    {
//        Surf_Dest = SDL_DisplayFormat(Surf_Temp);
        SDL_FreeSurface(Surf_Temp);

        return Surf_Dest;
	}
	else
        return NULL;




}





//==============================================================================
bool Texture::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {

	if(Surf_Dest == NULL || Surf_Src == NULL)
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "Csurface::OnDraw ERROR!", "");
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);


	return true;

}

//==============================================================================
bool Texture::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int W, int H) {

	if(Surf_Dest == NULL || Surf_Src == NULL)
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "Csurface::OnDraw ERROR!", "");
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;

	SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

	return true;
}



//------------------------------------------------------------------------------
bool Texture::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H) {

	if(Surf_Dest == NULL || Surf_Src == NULL)
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "Csurface::OnDraw ERROR!", "");
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

	return true;
}

//-----RENDER ENEMY-------------------------------------------------------------
bool Texture::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int Xe, int Ye, int X2, int Y2, int W, int H, int zero) {

	if(Surf_Dest == NULL || Surf_Src == NULL)
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "Csurface::OnDraw Enemy ERROR!", "");
		return false;
	}

	SDL_Rect DestR;

	DestR.x = Xe;
	DestR.y = Ye;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

	return true;
}

//-----RENDER BULLET-------------------------------------------------------------
bool Texture::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int Xb, int Yb, int X2, int Y2, int W, int H, float zerob) {

	if(Surf_Dest == NULL || Surf_Src == NULL)
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "Texture::OnDraw general entities ERROR!", "");
		return false;
	}

	SDL_Rect DestR;

	DestR.x = Xb;
	DestR.y = Yb;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

	return true;
}




//------------------------------------------------------------------------------
bool Texture::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B) {

	if(Surf_Dest == NULL)
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "CANNOT apply transparent property", "");
		return false;
	}

//	SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));

	return true;

}


Texture::~Texture() {

    if (SDLTexture)
    {
        SDL_DestroyTexture(SDLTexture);
        SDLTexture = NULL;
    }

}


//==============================================================================
//*****NEW SDL2 FEATURES*****
//==============================================================================
bool Texture::OnLoad(SDL_Renderer* Renderer, std::string Filename) {

	if(Renderer == NULL)
    {
		CApp::Logger.OnLog( __FILE__, __LINE__, "bad SDL RENDER passed", SDL_GetError());
		return false;
	}

	this->Renderer = Renderer;
	this->Filename = Filename;

	SDL_Surface* TempSurface = IMG_Load(Filename.c_str());
	if(TempSurface == NULL)
    {
		//Log("Unable to load image : %s : %s", Filename.c_str(), IMG_GetError());
		CApp::Logger.OnLog( __FILE__, __LINE__, "unable to load image", SDL_GetError());
		SDL_Log("unable to load Texture %s\n", SDL_GetError());
		return false;
	}

    // Convert SDL surface to a texture
	if((SDLTexture = SDL_CreateTextureFromSurface(Renderer, TempSurface)) == NULL)
    {
		//Log("Unable to create SDL Texture : %s : %s", Filename.c_str(), IMG_GetError());
		CApp::Logger.OnLog( __FILE__, __LINE__, "unable to create SDL TEXTURE from SURFACE", SDL_GetError());
		return false;
	}

	SDL_SetTextureBlendMode(SDLTexture, SDL_BLENDMODE_BLEND);

    fmt = TempSurface->format;
    bpp = TempSurface->format->BytesPerPixel;
    ptc = TempSurface->pitch;

    pxl = TempSurface->pixels;

    // Grab dimensions
	SDL_QueryTexture(SDLTexture, NULL, NULL, &Width, &Height);

	//Log("Texture Dimensions: %s : %d %d", Filename.c_str(), Width, Height);

	SDL_FreeSurface(TempSurface);

    CApp::Logger.OnLog( __FILE__, __LINE__, "Texture loaded", Filename);
	return true;

}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y) {


	Render(X, Y, Width, Height, 255);

}


//------------------------------------------------------------------------------
void Texture::Render(int X, int Y, int Width, int Height, int X2, int Y2, int W2, int H2, float perc) {


    perc = perc > 1.f ? 1.f : perc < 0.f ? 0.f : perc;
    int pW = (int)((float)Width * perc);

    //SDL_Log("Texture() >> x1: %d - y1: %d - w1: %d - h1: %d - x2: %d - y2: %d - w2: %d - h2: %d - perc: %f1.2", X, Y, pW, Height, X2, Y2, W2, H2, perc);

    SDL_Rect Destination = {X, Y, pW, Height};
	SDL_Rect Source = {X2, Y2, W2, H2};

    if (Renderer != NULL && SDLTexture != NULL)
        SDL_RenderCopy(Renderer, SDLTexture, &Source, &Destination);



}


//------------------------------------------------------------------------------
void Texture::RenderFlip(int X, int Y, int Width, int Height, int X2, int Y2, int W2, int H2, float perc) {


	perc = perc > 1.f ? 1.f : perc < 0.f ? 0.f : perc;
	int pW = (int)((float)Width * perc);

	//SDL_Log("Texture() >> x1: %d - y1: %d - w1: %d - h1: %d - x2: %d - y2: %d - w2: %d - h2: %d - perc: %f1.2", X, Y, pW, Height, X2, Y2, W2, H2, perc);

    int Xtemp = X - pW;
    //pW = X - Xtemp;

	SDL_Rect Destination = {Xtemp, Y, pW, Height};
	SDL_Rect Source = {X2, Y2, W2, H2};

	if (Renderer != NULL && SDLTexture != NULL)
		SDL_RenderCopy(Renderer, SDLTexture, &Source, &Destination);

		//SDL_RenderCopyEx(Renderer, SDLTexture, &Source, &Destination, NULL, NULL, flip);

}



//------------------------------------------------------------------------------
void Texture::Render(int X, int Y, int Width, int Height, int alpha) {

	SDL_Rect Destination = {X, Y, Width, Height};

	
		SDL_SetTextureAlphaMod(SDLTexture, alpha);
	
	//SDL_UpdateTexture(SDLTexture, NULL, , 640 * sizeof (Uint32));

	if (Renderer != NULL && SDLTexture != NULL)
		SDL_RenderCopy(Renderer, SDLTexture, NULL, &Destination);



}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight, int alpha) {

	SDL_Rect Source = {SX, SY, SWidth, SHeight};
	SDL_Rect Destination = {X, Y, Width, Height};

	SDL_SetTextureAlphaMod(SDLTexture, alpha);

    //SDL_UpdateTexture(SDLTexture, NULL, myPixels, 640 * sizeof (Uint32));

	if ((SDL_RenderCopy(Renderer, SDLTexture, &Source, &Destination)) < 0)
        SDL_Log("failed rendering texture - ", SDL_GetError());

}


//-----------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Texture::Render(int X, int Y, int Width, int Height, int X2, int Y2, int SWidth, int SHeight, double degrees, SDL_Point *pivot, int alpha) {

	SDL_Rect Source = {X2, Y2, SWidth, SHeight};
	SDL_Rect Destination = {X, Y, Width, Height};

	SDL_SetTextureAlphaMod(SDLTexture, alpha);

    //SDL_UpdateTexture(SDLTexture, NULL, myPixels, 640 * sizeof (Uint32));

	if ((SDL_RenderCopyEx(Renderer, SDLTexture, &Source, &Destination, degrees, pivot, SDL_FLIP_NONE)) < 0)
        CApp::Logger.OnLog( __FILE__, __LINE__, "render texture failed", "");


}

//------------------------------------------------------------------------------
int Texture::GetWidth()  { return Width;  }

int Texture::GetHeight() { return Height; }

//==============================================================================
