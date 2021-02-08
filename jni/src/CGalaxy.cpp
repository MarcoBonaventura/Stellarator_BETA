//=============================================================================

#define _CRT_SECURE_NO_DEPRECATE

#include "CGalaxy.h"
#include "CApp.h"
#include "Texture.h"

#include "Stringify.h"

#include <iostream>
#include <cstdio>

#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

//=============================================================================
CGalaxy CGalaxy::GalaxyControl;

char CGalaxy::TilesetFile[255] = {};
int CGalaxy::AreaSize = 0;
std::string CGalaxy::strTile = "";

//=============================================================================
CGalaxy::CGalaxy() {

    

}

void CGalaxy::setEnviroments(std::string c, int a) {

	strTile = c;
	AreaSize = a;
	
	LOGD("CGalaxy strTile: %s", c.c_str());
	LOGD("CGalaxy AreaSize: %d", AreaSize);

}


//=============================================================================
bool CGalaxy::OnLoad() {

	OnCleanup();
	
	for (int Y = 0; Y<2; Y++)
	{
		CMap tempMap2;
		if (tempMap2.OnLoadGal() == false)
		{
			SDL_Log("CGalaxy step3 error\n");
			return false;
		}
		GalList.push_back(tempMap2);
		SDL_Log("CGalaxy created\n");
	}

	//OnGenerateMap();

	return true;

}


//=============================================================================
bool CGalaxy::OnLoad(char* File) {

    OnCleanup();

	
    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL)
    {
        CApp::Logger.OnLog(__FILE__,__LINE__,"CGalaxy step1 error","");
		SDL_Log("CGalaxy step1 error\n");
        return false;
    }

	

    fscanf(FileHandle, "%s\n", TilesetFile);
	CApp::Logger.OnLog(__FILE__, __LINE__, "tilesetFile", Stringify::Char(TilesetFile));

    fscanf(FileHandle, "%d\n", &AreaSize);
	CApp::Logger.OnLog(__FILE__, __LINE__, "AreaSize", Stringify::Int(AreaSize));

	fclose(FileHandle);
	


    for (int Y=0; Y<2; Y++)
    {
        //char MapFile[255];

        //fscanf(FileHandle, "%s ", MapFile);

        CMap tempMap2;
        if(tempMap2.OnLoadGal() == false)
        {
            fclose(FileHandle);

            CApp::Logger.OnLog(__FILE__,__LINE__,"CGalaxy step3 error","");
            return false;
        }
        //tempMap2.Surf_Tileset = Surf_Tileset;
        //std::cout << "tempMap: "<<tempMap.Surf_Tileset<<"\n";
        GalList.push_back(tempMap2);
    }
	
    return true;
	
}



//----------------------------------------------------------------------------
void CGalaxy::OnGenerateMap() {

	//AreaSize = 1;
	SDL_Log("generate Map");

	for (int Y = 0; Y<1; Y++)
	{
		CMap tempMap2;
		tempMap2.OnLoadGal();
		std::vector<CMap>::iterator it;
		it = GalList.begin();
		GalList.insert(it, tempMap2);
	}

}


//-----------------------------------------------------------------------------
void CGalaxy::OnRender(int CameraX, int CameraY) {

    //int MapWidth  = GAL_WIDTH  * TILEGAL_WSIZE;
    //int MapHeight = GAL_HEIGHT * TILEGAL_HSIZE;

	//MapWidth = WWIDTH  / TILEGAL_WSIZE;
	//MapHeight = WHEIGHT / TILEGAL_HSIZE;

	int mH = MapHeight * TILE_SIZE;

    int FirstID = 0;
    FirstID = FirstID + ((-CameraY / mH) * AreaSize);

	for (int i = 0; i < 2; i++)
	{
		//Uint32 ID = FirstID + ((i / 2) * AreaSize) + (i % 2);
		Uint32 ID = i;

		if (ID < 0 || ID >= GalList.size())
		{
			SDL_Log("ID mismatching");
			continue;
		}
		//int X = ((ID % AreaSize) * MapWidth) + CameraX;

		int Y = ((ID / AreaSize) * mH) + CameraY;

		//SDL_Log("CGalaxy Y: %d", Y);

		//CApp::Logger.OnLog( __FILE__, __LINE__, "CArea::OnRender()", "");
		//CApp::Logger.OnLog(__FILE__, __LINE__, "MapList ID:", Stringify::Int(ID));
		//CApp::Logger.OnLog( __FILE__, __LINE__, "MapList size:", Stringify::Int(GalList.size()));
		//CApp::Logger.OnLog(__FILE__, __LINE__, "MapList Y:", Stringify::Int(Y));
		//SDL_Log("CGalaxy OnRender()\n");
		GalList[ID].OnRenderGal(0, Y);



		if (Y % WHEIGHT == 0)
		{
			if (Y == 1)
			{
				//OnGenerateMap();
			}
			if (Y > 0)
			{
				SDL_Log("clear Area map");
				GalList.pop_back();
				OnGenerateMap();

				//std::swap_ranges(MapList.begin(), MapList.begin(), MapList.end());
				//std::swap(MapList.begin(), MapList.end());
				CCamera::CameraControl.ResetYg();

			}
		}

	}

}

//-----------------------------------------------------------------------------
void CGalaxy::OnCleanup() {

	if(Surf_Tileset)
    {
        SDL_FreeSurface(Surf_Tileset);
    }

	GalList.clear();

}

//=============================================================================
CMap *CGalaxy::GetMap(int X, int Y) {

	//MapWidth = WWIDTH / TILEGAL_WSIZE;
	//MapHeight = WHEIGHT / TILEGAL_HSIZE; 
	
	Uint32 ID = X / MapWidth;
    ID = ID + ((Y / MapHeight) * AreaSize);

    if(ID < 0 || ID >= GalList.size()) { return NULL; }

    return &GalList[ID];

}

//-----------------------------------------------------------------------------
CTile *CGalaxy::GetTileGal(int X, int Y) {

	//int MapWidth = WWIDTH / TILEGAL_WSIZE;
	//int MapHeight = WHEIGHT / TILEGAL_HSIZE;

	CMap* Map = GetMap(X, Y);

	if(Map == NULL) return NULL;

	X = X % MapWidth;
	Y = Y % MapHeight;

    return Map->GetTileGal(X, Y);

}

//=============================================================================
