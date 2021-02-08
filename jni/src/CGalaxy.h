//=============================================================================
#ifndef _CGALAXY_H_
    #define _CGALAXY_H_

#include "CMap.h"

//=============================================================================
class CGalaxy {
    
	SDL_Surface*			Surf_Tileset;

	public:
        
		static CGalaxy		GalaxyControl;
		std::vector<CMap>   GalList;
        static int	        AreaSize;
		static char			TilesetFile[255];
		static std::string	strTile;

        CGalaxy();

		bool	OnLoad();
		bool    OnLoad(char* File);

		void	OnGenerateMap();

        void    OnRender(int X, int Y);

        void    OnCleanup();

        CMap*	GetMap(int X, int Y);

		CTile*	GetTileGal(int X, int Y);

		static	void setEnviroments(std::string c, int a);
};

//=============================================================================

#endif

