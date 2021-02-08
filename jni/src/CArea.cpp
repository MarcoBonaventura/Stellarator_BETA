//=============================================================================

#define _CRT_SECURE_NO_WARNINGS
#include "CArea.h"
#include "CApp.h"
#include "Stringify.h"

#include <iostream>
#include <cstdio>
#include <algorithm>

#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

//=============================================================================
CArea CArea::AreaControl;

char CArea::TilesetFile[255] = {};
int CArea::AreaSize = 0;
std::string CArea::strTile = "";

//=============================================================================
CArea::CArea() {

    AreaSize = 0;

}

void CArea::setEnviroments(std::string c, int a) {

	strTile = c;
	AreaSize = a;

	LOGD("CArea strTile: %s", c.c_str());
	LOGD("CArea AreaSize: %d", AreaSize);
	
}



//=============================================================================
bool CArea::OnLoad() {

	OnCleanup();

	for (int Y = 0; Y<2; Y++)
	{
		CMap tempMap;
		if (tempMap.OnLoad() == false)
		{
			//CApp::Logger.OnLog(__FILE__, __LINE__, "CArea:OnLoad error step3", "");
			SDL_Log("CArea::OnLoad error");
			return false;
		}
		MapList.push_back(tempMap);
		//CApp::Logger.OnLog(__FILE__, __LINE__, "MapList item", "");
		SDL_Log("MapList item");
	}

	return true;

}



//=============================================================================
bool CArea::OnLoad(char* File) {

    OnCleanup();

    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL)
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "CArea:OnLoad error step1", "");
        return false;
    }



    fscanf(FileHandle, "%s\n", TilesetFile);
    CApp::Logger.OnLog( __FILE__, __LINE__, "tilesetFile", Stringify::Char(TilesetFile));


    fscanf(FileHandle, "%d\n", &AreaSize);
    CApp::Logger.OnLog( __FILE__, __LINE__, "AreaSize", Stringify::Int(AreaSize));

	fclose(FileHandle);

	/*
    for(int Y=0; Y<61; Y++)
    {
        char MapFile[255];

        fscanf(FileHandle, "%s ", MapFile);

        CMap tempMap;
        if(tempMap.OnLoad(MapFile) == false)
        {
			fclose(FileHandle);
            //CApp::Logger.OnLog( __FILE__, __LINE__, "CArea:OnLoad error step3", "");
            return false;
        }
        //tempMap.Surf_Tileset = Surf_Tileset;
        MapList.push_back(tempMap);
        //CApp::Logger.OnLog( __FILE__, __LINE__, "MapList item", "");
    }
	fclose(FileHandle);
	*/

	for (int Y = 0; Y<2; Y++)
	{
		

		CMap tempMap;
		if (tempMap.OnLoad() == false)
		{
			CApp::Logger.OnLog( __FILE__, __LINE__, "CArea:OnLoad error step3", "");
			return false;
		}
		MapList.push_back(tempMap);
		CApp::Logger.OnLog( __FILE__, __LINE__, "MapList item", "");
	}
	
	
    return true;


}


//=============================================================================
void CArea::OnGenerateMap() {

	SDL_Log("generate Gal");

	AreaSize = 1;

	for (int Y = 0; Y<1; Y++)
	{
		CMap tempMap;
		tempMap.OnLoad();
		std::vector<CMap>::iterator it;
		it = MapList.begin();
		MapList.insert(it, tempMap);
	}
	
}

//-----------------------------------------------------------------------------
void CArea::OnRender(int CameraX, int CameraY) {

    //int MapWidth  = MAP_WIDTH  * TILE_SIZE;
    
	//int MapHeight = MAP_HEIGHT * TILE_SIZE;

	int mH = MapHeight * TILE_SIZE;

    int FirstID = 0;
        FirstID = FirstID + ((-CameraY / mH) * AreaSize);

    for (int i = 0; i < 2; i++)
    {
        //Uint32 ID = FirstID + ((i / 2) * AreaSize) + (i % 2);
		Uint32 ID = i;

		if (ID < 0 || ID >= MapList.size())
		{
			continue;
		}
        //int X = ((ID % AreaSize) * MapWidth) + CameraX;

        int Y = ((ID / AreaSize) * mH) + CameraY;
		
        //CApp::Logger.OnLog( __FILE__, __LINE__, "CArea::OnRender()", "");
		//CApp::Logger.OnLog(__FILE__, __LINE__, "MapList ID:", Stringify::Int(ID));
		//CApp::Logger.OnLog( __FILE__, __LINE__, "MapList size:", Stringify::Int(MapList.size()));
		//CApp::Logger.OnLog(__FILE__, __LINE__, "MapList Y:", Stringify::Int(Y));
        MapList[ID].OnRender(0, Y);
		
		

		if (Y % WHEIGHT == 0)
		{
			if (Y == 1)
			{
				//OnGenerateMap();
			}
			if (Y > 0 )
			{
				CApp::Logger.OnLog(__FILE__, __LINE__, "clear AREA MAP", Stringify::Int(Y));
				
				SDL_Log("clear Area Gal");
				MapList.pop_back();
				OnGenerateMap();
				
				//std::swap_ranges(MapList.begin(), MapList.begin(), MapList.end());
				//std::swap(MapList.begin(), MapList.end());
				CCamera::CameraControl.ResetY();

			}
		}
	}
	
}

//-----------------------------------------------------------------------------
void CArea::OnCleanup() {
	
	MapList.clear();
	
}

//=============================================================================
CMap *CArea::GetMap(int X, int Y) {

	Uint32 MapWidth  = MAP_WIDTH * TILE_SIZE;
	Uint32 MapHeight = MAP_HEIGHT * TILE_SIZE;
	Uint32 ID = X / MapWidth;
    ID = ID + ((Y / MapHeight) * AreaSize);

    if(ID < 0 || ID >= MapList.size()) { return NULL; }

    return &MapList[ID];

}

//-----------------------------------------------------------------------------
CTile *CArea::GetTile(int X, int Y) {

	int MapWidth  = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

	CMap* Map = GetMap(X, Y);

	if(Map == NULL) return NULL;

	X = X % MapWidth;
	Y = Y % MapHeight;

    return Map->GetTile(X, Y);
	
}