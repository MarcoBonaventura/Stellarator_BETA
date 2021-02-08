//==============================================================================
/*
	Texture Bank class for loading multiple textures

	3/18/2014
    SDLTutorials.com
    Tim Jones
*/
//==============================================================================
#ifndef __TEXTUREBANK_H__
	#define __TEXTUREBANK_H__

#include <map>
#include <string>
#include <vector>

#include "Texture.h"

struct SLoader{

	int x;
	int y;
	int w;
	int h;
	int x2;
	int y2;
	int w2;
	int h2;
	int alpha;

};

struct SBar {

	int x;
	int y;
	int w;
	int h;
	int x2;
	int y2;
	int w2;
	int h2;
	float perc;

};



class TextureBank {

private:

    static std::map<std::string, Texture*> TexList;

    static SDL_Renderer *Renderer;
    static SDL_Window *Window;


    static int LoaderW, LoaderH, LoaderBarW, LoaderBarH;
    static std::string entityLoader;
    static std::string entityBar;

    static int tempFactor;
    static int tempFactor2;

	static SDL_Surface*    PrimarySurface;

    static SLoader  LoaderInfo;
    static SBar 	BarInfo;

public:


		static bool OnInit();

		static void Cleanup();

    private:

        static void AddTexture(SDL_Renderer* Renderer, std::string ID, std::string Filename);

	public:

		static Texture* Get(std::string ID);

		static TextureBank* GetInstance();

		static void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);

		static void RenderLoaderBar(int x, int y, int w, int h, int x2, int y2, int w2, int h2, float Percent);
		static void RenderLoaderBKG(int x, int y, int w, int h, int x2, int y2, int w2, int h2, int alpha);
        static void RenderPreLoader(SLoader L, SBar B);
        static void RenderPostLoader();
        static SLoader 	GetLoader();
		static SBar		GetBar();

};

#endif
