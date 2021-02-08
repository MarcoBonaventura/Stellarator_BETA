//=============================================================================
#define _CRT_SECURE_NO_DEPRECATE

#include "CMap.h"
#include "CGalaxy.h"
#include "CArea.h"
#include "CApp.h"
#include "TextureBank.h"
#include "Stringify.h"
#include "Define.h"

#include <iostream>
#include <cstdio>

#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

int MapWidth;
int MapHeight;

//=============================================================================
CMap::CMap() {

	
}


//=============================================================================
bool CMap::OnLoad() {

	TileList.clear();

	//CApp::Logger.OnLog(__FILE__, __LINE__, "step0", "new area map tile");
	for (int Y = 0; Y < MapHeight; Y++)
	{
		//CApp::Logger.OnLog(__FILE__, __LINE__, "tiling Y", Stringify::Int(Y));
		for (int X = 0; X < MapWidth; X++)
		{
			CTile tempTile;

			/*
			if (X == MapWidth - 1) continue;
			*/
			if (Y == 0)
			{
				if (X == 0)
				{
					tempTile.TileID = 0;
					tempTile.TypeID = 1;
					//CApp::Logger.OnLog(__FILE__, __LINE__, "step2A X", Stringify::Int(X));
					//CApp::Logger.OnLog(__FILE__, __LINE__, "step2A TileID", Stringify::Int(tempTile.TileID));
					TileList.push_back(tempTile);
					continue;
				}
				else if (X > 0)
				{
					do
					{
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step2A", "random tile");
						//if (X == MapWidth - 1) break;
						tempTile.TileID = rand() % 5;
						tempTile.TypeID = 1;
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step2B X", Stringify::Int(X));
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step2B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList[X - 1].TileID);
				}
			}
			else if (Y > 0)
			{
				if (X == 0)
				{
					do
					{
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step3A", "random tile");
						tempTile.TileID = rand() % 5;
						tempTile.TypeID = 1;
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step3B X", Stringify::Int(X));
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step3B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList[TileList.size() - MapWidth].TileID);
					TileList.push_back(tempTile);
					continue;
				}
				else if (X > 0)
				{
					do
					{
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step4A", "random tile");
						tempTile.TileID = rand() % 5;
						tempTile.TypeID = 1;
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step4B X", Stringify::Int(X));
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step4B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList[X - 1].TileID || tempTile.TileID == TileList[TileList.size() - MapWidth].TileID);
				}
			}

			//CApp::Logger.OnLog(__FILE__, __LINE__, "step5", "pushback tile");
			TileList.push_back(tempTile);

		}

		//CApp::Logger.OnLog(__FILE__, __LINE__, "step5", "new row tile");

	}

	return true;
}




//=============================================================================
/*
bool CMap::OnLoad(char* File) {

    TileList.clear();


	//******************
    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL) {
        return false;
    }

	
    for(int Y=0; Y < MapHeight; Y++)
    {
        for(int X=0; X < MapWidth; X++)
        {
            CTile tempTile;

            fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

            TileList.push_back(tempTile);
        }
        fscanf(FileHandle, "\n");
    }
	fclose(FileHandle);
	*//////////////////////////


/*
	//CApp::Logger.OnLog(__FILE__, __LINE__, "step0", "new area map tile");
	for (int Y = 0; Y < MapHeight; Y++)
	{
		//CApp::Logger.OnLog(__FILE__, __LINE__, "tiling Y", Stringify::Int(Y));
		for (int X = 0; X < MapWidth; X++)
		{
			CTile tempTile;

			if (Y == 0)
			{
				if (X == 0)
				{
					tempTile.TileID = 0;
					tempTile.TypeID = 1;
					//CApp::Logger.OnLog(__FILE__, __LINE__, "step2A X", Stringify::Int(X));
					//CApp::Logger.OnLog(__FILE__, __LINE__, "step2A TileID", Stringify::Int(tempTile.TileID));
					TileList.push_back(tempTile);
					continue;
				}
				else if (X > 0)
				{
					do
					{
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step2A", "random tile");
						//if (X == MapWidth - 1) break;
						tempTile.TileID = rand() % 5;
						tempTile.TypeID = 1;
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step2B X", Stringify::Int(X));
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step2B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList[X - 1].TileID);
				}
			}
			else if (Y > 0)
			{
				if (X == 0)
				{
					do
					{
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step3A", "random tile");
						tempTile.TileID = rand () % 5;
						tempTile.TypeID = 1;
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step3B X", Stringify::Int(X));
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step3B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList[TileList.size() - MapWidth].TileID);
					TileList.push_back(tempTile);
					continue;
				}
				else if (X > 0)
				{
					do
					{
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step4A", "random tile");
						tempTile.TileID = rand() % 5;
						tempTile.TypeID = 1;
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step4B X", Stringify::Int(X));
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step4B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList[X - 1].TileID || tempTile.TileID == TileList[TileList.size() - MapWidth].TileID);
				}
			}
			
			//CApp::Logger.OnLog(__FILE__, __LINE__, "step5", "pushback tile");
			TileList.push_back(tempTile);
			
		}

		//CApp::Logger.OnLog(__FILE__, __LINE__, "step5", "new row tile");

	}

    return true;
}
*/


//=============================================================================
bool CMap::OnLoadGal() {

	TileList2.clear();

	//CApp::Logger.OnLog(__FILE__, __LINE__, "step0", "new area map tile");
	for (int Y = 0; Y < MapHeight; Y++)
	{
		//CApp::Logger.OnLog(__FILE__, __LINE__, "tiling Y", Stringify::Int(Y));
		for (int X = 0; X < MapWidth; X++)
		{
			CTile tempTile;

			/*
			if (X == MapWidth - 1) continue;
			*/
			if (Y == 0)
			{
				if (X == 0)
				{
					tempTile.TileID = 0;
					tempTile.TypeID = 1;
					//CApp::Logger.OnLog(__FILE__, __LINE__, "step2A X", Stringify::Int(X));
					//CApp::Logger.OnLog(__FILE__, __LINE__, "step2A TileID", Stringify::Int(tempTile.TileID));
					TileList2.push_back(tempTile);
					continue;
				}
				else if (X > 0)
				{
					do
					{
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step2A", "random tile");
						//if (X == MapWidth - 1) break;
						tempTile.TileID = rand() % 5;
						tempTile.TypeID = 1;
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step2B X", Stringify::Int(X));
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step2B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList2[X - 1].TileID);
				}
			}
			else if (Y > 0)
			{
				if (X == 0)
				{
					do
					{
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step3A", "random tile");
						tempTile.TileID = rand() % 5;
						tempTile.TypeID = 1;
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step3B X", Stringify::Int(X));
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step3B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList2[TileList2.size() - MapWidth].TileID);
					TileList2.push_back(tempTile);
					continue;
				}
				else if (X > 0)
				{
					do
					{
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step4A", "random tile");
						tempTile.TileID = rand() % 5;
						tempTile.TypeID = 1;
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step4B X", Stringify::Int(X));
						//CApp::Logger.OnLog(__FILE__, __LINE__, "step4B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList2[X - 1].TileID || tempTile.TileID == TileList2[TileList2.size() - MapWidth].TileID);
				}
			}

			//CApp::Logger.OnLog(__FILE__, __LINE__, "step5", "pushback tile");
			TileList2.push_back(tempTile);

		}

		//CApp::Logger.OnLog(__FILE__, __LINE__, "step5", "new row tile");

	}




	return true;
}



//=============================================================================
/*
bool CMap::OnLoadGal(char* File) {

	TileList2.clear();

	FILE* FileHandle = fopen(File, "r");

	if (FileHandle == NULL)
	{
		std::cout << "CMap::OnLoadGal STEP error" << std::endl;
		return false;
	}


	for (int Y = 0; Y < MapHeight; Y++)
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "tiling Y", Stringify::Int(Y));
		for (int X = 0; X < MapWidth; X++)
		{
			CTile tempTile;

			if (Y == 0)
			{
				if (X == 0)
				{
					tempTile.TileID = 0;
					tempTile.TypeID = 1;
					CApp::Logger.OnLog(__FILE__, __LINE__, "step2A X", Stringify::Int(X));
					CApp::Logger.OnLog(__FILE__, __LINE__, "step2A TileID", Stringify::Int(tempTile.TileID));
					TileList2.push_back(tempTile);
					continue;
				}
				else if (X > 0)
				{
					do
					{
						CApp::Logger.OnLog(__FILE__, __LINE__, "step2A", "random tile");
						//if (X == MapWidth - 1) break;
						tempTile.TileID = rand() % 5;
						tempTile.TypeID = 1;
						CApp::Logger.OnLog(__FILE__, __LINE__, "step2B X", Stringify::Int(X));
						CApp::Logger.OnLog(__FILE__, __LINE__, "step2B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList2[X - 1].TileID);
				}
			}
			else if (Y > 0)
			{
				if (X == 0)
				{
					do
					{
						CApp::Logger.OnLog(__FILE__, __LINE__, "step3A", "random tile");
						tempTile.TileID = rand() % 5;
						tempTile.TypeID = 1;
						CApp::Logger.OnLog(__FILE__, __LINE__, "step3B X", Stringify::Int(X));
						CApp::Logger.OnLog(__FILE__, __LINE__, "step3B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList2[TileList2.size() - MapWidth].TileID);
					TileList2.push_back(tempTile);
					continue;
				}
				else if (X > 0)
				{
					do
					{
						CApp::Logger.OnLog(__FILE__, __LINE__, "step4A", "random tile");
						tempTile.TileID = rand() % 5;
						tempTile.TypeID = 1;
						CApp::Logger.OnLog(__FILE__, __LINE__, "step4B X", Stringify::Int(X));
						CApp::Logger.OnLog(__FILE__, __LINE__, "step4B TileID", Stringify::Int(tempTile.TileID));
					} while (tempTile.TileID == TileList2[X - 1].TileID || tempTile.TileID == TileList2[TileList2.size() - MapWidth].TileID);
				}
			}

			CApp::Logger.OnLog(__FILE__, __LINE__, "step5", "pushback tile");
			TileList2.push_back(tempTile);

		}

		CApp::Logger.OnLog(__FILE__, __LINE__, "step5", "new row tile");

	}


	return true;
}
*/




//-----------------------------------------------------------------------------
void CMap::OnRender(int MapX, int MapY) {

	//if(Surf_Tileset == NULL) return;

	//int TilesetWidth  = Surf_Tileset->w / TILE_SIZE;
	//int TilesetHeight = Surf_Tileset->h / TILE_SIZE;

	//int TilesetWidth  = 2048 / TILE_SIZE;
    //int TilesetHeight = 256 / TILE_SIZE;

	
	int TilesetWidth = (WWIDTH * 2) / TILE_SIZE;
	int TilesetHeight = (WHEIGHT / 3) / TILE_SIZE;

	int ID = 0;

	for(int Y=0; Y < MapHeight; Y++)
    {
		for(int X=0; X < MapWidth; X++)
		{
			if(TileList[ID].TypeID == TILE_TYPE_NONE)
			{
				ID++;
				SDL_Log("TILE_TYPE_NONE Map event occured");
				continue;
			}

			//int tX = MapX + (X * TILE_SIZE);
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);

			int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
			//int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;
			int TilesetY = 0;

			//Texture::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			//std::string mapTexture = CArea::AreaControl.strTile;
			std::string mapTexture = "Tile_bg_256x256_NEAR";
			
			//CApp::Logger.OnLog( __FILE__, __LINE__, "CMap::OnRender()", mapTexture);
			//LOGD("mapTexture: %s", mapTexture.c_str());
			TextureBank::Get(mapTexture)->Render(tX, tY, TILE_SIZE, TILE_SIZE, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE, 255);

			

			ID++;
		}
	}
}


//-----------------------------------------------------------------------------
void CMap::OnRenderGal(int MapX, int MapY) {

	//int TilesetWidth  = Surf_Tileset->w / TILEGAL_WSIZE;
	//int TilesetHeight = Surf_Tileset->h / TILEGAL_HSIZE;

	int TilesetWidth	= (WWIDTH * 2) / TILEGAL_WSIZE;
	int TilesetHeight	= (WHEIGHT / 3) / TILEGAL_HSIZE;

	int ID = 0;

	for(int Y=0; Y < MapHeight; Y++)
    {
		for(int X=0; X < MapWidth; X++)
		{
			if(TileList2[ID].TypeID == TILE_TYPE_NONE)
			{
				ID++;
				SDL_Log("TILE_TYPE_NONE Gal event occured");
				continue;
			}

			int tX = MapX + (X * TILEGAL_WSIZE);
			int tY = MapY + (Y * TILEGAL_HSIZE);

			int TilesetX = (TileList2[ID].TileID % TilesetWidth) * TILEGAL_WSIZE;
			//int TilesetY = (TileList2[ID].TileID / TilesetWidth) * TILEGAL_HSIZE;
			int TilesetY = 1;

			//std::string galTexture = CGalaxy::GalaxyControl.strTile;
			std::string galTexture = "Tile_bg_256x256_DEEP";
			//Texture::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILEGAL_WSIZE, TILEGAL_HSIZE);
			//LOGD("CMap galTexture: %s", galTexture.c_str());
			
			TextureBank::Get(galTexture)->Render(tX, tY, TILEGAL_WSIZE, TILEGAL_HSIZE, TilesetX, TilesetY, TILEGAL_WSIZE, TILEGAL_HSIZE, 255);
			ID++;
		}
	}
}


//=============================================================================
CTile* CMap::GetTile(int X, int Y) {

    Uint32 ID = 0;

    ID = X / TILE_SIZE;
    ID = ID + (MapWidth * (Y / TILE_SIZE));

    if(ID < 0 || ID >= TileList.size()) 
	{
		SDL_Log("TileList = NULL");
    	return NULL;
    }

    return &TileList[ID];


}


//=============================================================================
CTile* CMap::GetTileGal(int X, int Y) {

    Uint32 ID = 0;

    ID = X / TILEGAL_WSIZE;
    ID = ID + (MapWidth * (Y / TILEGAL_HSIZE));

    if(ID < 0 || ID >= TileList2.size()) 
	{ 
		SDL_Log("TileList2 = NULL");
		return NULL; 
	}

    return &TileList2[ID];


}


