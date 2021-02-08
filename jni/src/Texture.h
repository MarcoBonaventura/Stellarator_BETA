//==============================================================================
// Surface functions
//==============================================================================
#ifndef _TEXTURE_H_
    #define _TEXTURE_H_

#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//==============================================================================
class Texture {

    int alpha;
    Uint32 *myPixels;

	public:

		Texture();
		~Texture();

        std::string Filename;

		int Width = 0;
		int Height = 0;

		SDL_Renderer* Renderer = NULL;
		SDL_Texture* SDLTexture = NULL;
		SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

		void*   pxl;

        SDL_PixelFormat*    fmt;

        int     bpp;
        int     ptc;

	public:

		static SDL_Surface* OnLoad(char* File);

		static SDL_Surface* OnLoad(char* File, int RGBalpha);

		static bool OnDraw(SDL_Surface* Surf_Entity, SDL_Surface* Surf_Src, int X, int Y);

		static bool OnDraw(SDL_Surface* Surf_Entity, SDL_Surface* Surf_Src, int X, int Y, int W, int H);

		static bool OnDraw(SDL_Surface* Surf_Entity, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);

		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int Xe, int Ye, int X2, int Y2, int W, int H, int zero);

		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int Xb, int Yb, int X2, int Y2, int W, int H, float zerob);

		static bool Transparent(SDL_Surface* Surf_Entity, int R, int G, int B);


        //----------------------------
        //SDL2 NEW IMPROVED FUNCTIONS!
		bool OnLoad(SDL_Renderer* Renderer, std::string Filename);

		void Render(int X, int Y);

		void Render(int X, int Y, int Width, int Height,  int X2, int Y2, int W2, int H2, float perc);

		void RenderFlip(int X, int Y, int Width, int Height,  int X2, int Y2, int W2, int H2, float perc);

		void Render(int X, int Y, int Width, int Height, int alpha);

		void Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight, int alpha);

		void Render(int X, int Y, int Width, int Height, int X2, int Y2, int SWidth, int SHeight, double degrees, SDL_Point *pivot, int alpha);



		int GetWidth();

		int GetHeight();


};

//==============================================================================

#endif
