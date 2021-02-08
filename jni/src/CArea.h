//=============================================================================
#ifndef _CAREA_H_
    #define _CAREA_H_

#include "CMap.h"

//=============================================================================
class CArea {

		SDL_Surface*	Surf_Tileset;
		

    public:

        static CArea        AreaControl;

        std::vector<CMap>   MapList;
        static int          AreaSize;
        static char         TilesetFile[255];
		static std::string	strTile;
    
        CArea();

		bool	OnLoad();
        bool    OnLoad(char* File);

		void	OnGenerateMap();

        void    OnRender(int CameraX, int CameraY);

        void    OnCleanup();

        CMap*	GetMap(int X, int Y);

		CTile*	GetTile(int X, int Y);

		static	void setEnviroments(std::string c, int a);

};

//=============================================================================

#endif

