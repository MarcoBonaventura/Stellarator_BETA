//==============================================================================
#ifndef _CMAP_H_
    #define _CMAP_H_

#include <SDL.h>
#include <vector>
#include <deque>


#include "CTile.h"
#include "Texture.h"

//==============================================================================
class CMap {

		std::vector<CTile>      TileList;
		std::vector<CTile>      TileList2;
		int ttX, ttY;
		
	public:

		CMap();

		bool OnLoad();
		//bool OnLoad(char* File);
		
		bool OnLoadGal();
		//bool OnLoadGal(char* File);

		//void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);
		//void OnRenderGal(SDL_Surface* Surf_Display, int MapX, int MapY);

		void OnRender(int MapX, int MapY);
		void OnRenderGal(int MapX, int MapY);

        CTile*	GetTile(int X, int Y);
        CTile*	GetTileGal(int X, int Y);

};

//==============================================================================

#endif
