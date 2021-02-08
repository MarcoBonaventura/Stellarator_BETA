#include "CPopup.h"
#include "CApp.h"
#include "CEnemyBOSS1.h"

#include "CAppStateGame.h"


//int CEnemyBOSS1::damage = 100;

CPopup CPopup::Instance;
bool CPopup::show = false;

/*
CPopup::CPopup(int x, int y) {

	CApp::Logger.OnLog(__FILE__, __LINE__, "new POPUP!", "");

	Xp = x;
	Yp = y;
	
	Dead = false;
	
}
*/

CPopup::CPopup() {

	CApp::Logger.OnLog(__FILE__, __LINE__, "new POPUP!", "");
	
}

CPopup::~CPopup() {

	CApp::Logger.OnLog(__FILE__, __LINE__, "delete POPUP!", "");
	
	
}


//-----------------------------------------------------------------------------
bool CPopup::OnLoad() {

	Width = 150;
	Height = 100;
	Type = ENTITY_TYPE_PARTICLE;
	Size = ENTITY_SIZE_PP;
	Flags = ENTITY_FLAG_MAPONLY;
	
	Window = CAppStateGame::GetInstance()->GetWindow();

	popupRenderer = CAppStateGame::GetInstance()->GetRenderer();

	if (Window != NULL && popupRenderer != NULL) { return true; }

	return false;

}

void CPopup::OnLoop() {

    //OnMove();
	Xp = CEnemyBOSS1::getXen() + 310;
	Yp = CEnemyBOSS1::getYen();
	
	if (CEnemyBOSS1::damage == 75 ||
		CEnemyBOSS1::damage == 55 ||
		CEnemyBOSS1::damage == 25 ||
		CEnemyBOSS1::damage == 1)
	{
		//this->Dead = true;
		//CEnemyBOSS1::countPopup--;
		show = false;
		entityTexture = "";
	}

    if (CEnemyBOSS1::BossIsAlive == false)
        Dead = true;

	

}

void CPopup::OnMove() {

    Xp = CEnemyBOSS1::getXen() +310;
    Yp = CEnemyBOSS1::getYen();

    
}

void CPopup::OnRender() {

    X = Xp;
    Y = Yp;

	if (show)
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "render POPUP!", "");
		if (popupRenderer)
		{
			TextureBank::Get(entityTexture)->Render(X, Y, Width, Height, 255);
		}
		else
		{
			CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
		}
	}

	

}


void CPopup::OnCleanup() {

    CApp::Logger.OnLog( __FILE__, __LINE__, "CPopup::OnCleanup()", "");

}

void CPopup::EntityDEL() {

    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead == true)
        {
            (*it)->OnCleanup();
            delete *it;
            it = CEntity::EntityList.erase(it);

            /*
            for (int i=0; i<MaxRow; i++)
            {
                delete [] vet[i];
            }
            delete [] vet;
            */

            CApp::Logger.OnLog( __FILE__, __LINE__, "Entity CPopup deleted", "");
		}
        else
        {
            it++;
        }
    }
    //CApp::Logger.OnLog( __FILE__, __LINE__, "outside Entity CBullet vector iterator ", "");
    


}


