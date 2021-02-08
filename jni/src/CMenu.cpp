#include "CApp.h"
#include "CMenu.h"
#include "Stringify.h"
#include "TextureBank.h"
#include "CSoundBank.h"

#include "CCamera.h"

#include "CAppStateIntro.h"
#include "CAppStateTrans.h"
#include "CAppStateGamePause.h"
#include "CAppStateGame.h"

#include <stdio.h>
#include <stdlib.h>

#include <android/log.h>

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


bool CMenu::displayMenu = true;

float SCREEN_W_RATIO;
float SCREEN_H_RATIO;


// CMENU CODE


void CMenu::triggerMenu()
{
	displayMenu = !displayMenu;
}

void CMenu::showMenu(bool on_off)
{
	displayMenu = on_off;
}

bool CMenu::getShowMenu()
{
	return displayMenu;
}

void CMenu::Draw()
{
	this->onRender();
}

SDL_Rect CMenu::getBounds()
{
	SDL_Rect	MenuRect;
	MenuRect.x = this->x;
	MenuRect.y = this->y;
	MenuRect.w = this->w;
	MenuRect.h = this->h;

	return MenuRect;
}

// PANEL CODE

void Panel::init()
{
	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
	SDL_SetRenderDrawColor(buttonRenderer, 0x00, 0x00, 0xFF, 0xFF);

	panelTexture = "panelTEST";

	X1 = (WWIDTH / 100) * 10;
	X2 = (WWIDTH / 100) * 90;
	Y1 = (WHEIGHT / 100) * 25;
	Y2 = (WHEIGHT / 100) * 90;

	
}

void Panel::init2() {

}

int Panel::GetX1()
{
	return X1;
}

int Panel::GetY1()
{
	return Y1;
}
int Panel::getWidth()
{
	return WWIDTH - X1 * 2;
}

int Panel::getHeight()
{
	return Y2 - Y1;
}

void Panel::showPanel(bool on_off)
{
	displayPanel = on_off;
}

bool Panel::getShowPanel()
{
	return displayPanel;
}

void Panel::onLoop()
{
	
}

void Panel::handleEvent(SDL_Event* e)
{
	SDL_Log("Panel::handleEvent()");
}

void Panel::onClick()
{
	
}

void Panel::onRender()
{
	if (buttonRenderer)
	{
		//SDL_Log("Panel onRender()\n");
		TextureBank::Get(panelTexture)->Render(X1, Y1, W, H, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}
}



void Panel::onDelete()
{
	delete this;
}


// BUTTON CODE

Button::Button() 
{
	buttonID = 0;
}

Button::~Button()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "default Button destructor", "");
}

void Button::init()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "new Default Button created", "");
	Panel::init();
	
	w = Panel::getWidth() / 4;
	h = w / 1,75;
	x = (Panel::GetX1() + buttonID * w) + (padding * buttonID);
	y = Panel::GetY1();

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

	SDL_SetRenderDrawColor(buttonRenderer, 0x00, 0x00, 0x00, 0xFF);

	buttonTexture = "";
	currentSprite = BUTTON_SPRITE_OUT;

	CApp::Logger.OnLog(__FILE__, __LINE__, "button texture", buttonTexture);
	CApp::Logger.OnLog(__FILE__, __LINE__, "button id", Stringify::Int(buttonID));
	CApp::Logger.OnLog(__FILE__, __LINE__, "button x", Stringify::Int(x));
	CApp::Logger.OnLog(__FILE__, __LINE__, "button y", Stringify::Int(y));
	CApp::Logger.OnLog(__FILE__, __LINE__, "button w", Stringify::Int(w));
	CApp::Logger.OnLog(__FILE__, __LINE__, "button h", Stringify::Int(h));
}

void Button::init2() {}

int Button::getX()
{
	return x;
}

int Button::getY()
{
	return y;
}

int Button::getH()
{
	return h;
}

int Button::getW()
{
	return w;
}


void Button::showButton(bool on_off)
{
	displayButton = on_off;
}

bool Button::getShowButton()
{
	return displayButton;
}

void Button::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = 300 * currentSprite;
	ya = thisButton.y;
	ha = thisButton.h;
	wa = thisButton.w;

}

void Button::onRender()
{
	if (buttonRenderer)
	{
		//CApp::Logger.OnLog(__FILE__, __LINE__, "renderer default Button", "");
		SDL_Log("Button onRender()\n");
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, 0, 300, 150, 255);
		//TextureBank::Get(buttonTexture)->Render(x, y, w, h, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}
	
}


// BUTTON ACTION & CONTROLLER FUNCTION 

void Button::onClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-on event", "");

	
	
}

void Button::offClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-out event", "");

	CAppStateGamePause::isRunning = true;
	CAppStateGamePause::onPause = false;
}

void Button::onMouseOver()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse over event", "");
}

//*** Mobile Device Gesture ***
void Button::onTouchDown()
{
	//CApp::Logger.OnLog(__FILE__, __LINE__, "mouse touch Down event", "");
	SDL_Log("BUTTON: On Touch Down Event\n");
}

void Button::onTouchUp()
{
	//CApp::Logger.OnLog(__FILE__, __LINE__, "mouse touch Up event", "");
	SDL_Log("BUTTON: On Touch Up Event\n");
}

void Button::onTouchMove()
{
	//CApp::Logger.OnLog(__FILE__, __LINE__, "mouse touch Move event", "");
	SDL_Log("BUTTON: On Touch Move Event\n");
}

SDL_Rect Button::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void Button::handleEvent(SDL_Event* e)
{

	SDL_Log("BUTTON::handleEvent()");

	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			SDL_Log("Button UNtouched\n");
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			SDL_Log("Button touched\n");
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				this->onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				this->onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				this->onTouchUp();
				break;
			}
		}
	}


}

void Button::ForceFeedbackPushButton()
{
    if (SDL_HapticRumblePlay(mouseHaptic, 0.07, 30) != 0)
    {
        SDL_Log("Warning: Unable to play rumble! %s", SDL_GetError());
    }

}

void Button::onDelete()
{
	delete this;
}




// BACKGROUND

Background::Background()
{
	buttonID = 0;
	menuID = MAIN;

	SDL_Log("background()");

    buttonTexture = "BackgroundShips2XXL";

	return_ships.w = 313;
	return_ships.h = 285;
	return_ships.x = 0;
	return_ships.y = WHEIGHT - return_ships.h;

	return_switch = true;
    displayButton = false;

	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	w = WWIDTH;
	h = WHEIGHT;
	x = 0;
	y = 0;
	wa = 835;
	ha = 1600;

    xa = ya = 0;

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();


	SDL_Log("background initialization completed");
    SDL_Log("() >> w: %d - h: %d - wa: %d - ha: %d", w, h, wa, ha);


}



Background::~Background()
{
	SDL_Log("~background()");
}

void Background::init()
{

	return_menu.w = 235;
	return_menu.h = 214;
	return_menu.x = 0;
	return_menu.y = WHEIGHT - return_menu.h;


	return_switch = false;


	buttonTexture = "WindowSmartphoneXXXL";

    SDL_Log("displayButton? %d", displayButton);
    if (displayButton) currentSprite = BUTTON_SPRITE_OUT;
    else if (!displayButton) currentSprite = BUTTON_SPRITE_DOWN;
    SDL_Log("currentSprite: %d", currentSprite);

    w = WWIDTH;
    h = WHEIGHT;
    x = 0;
    y = 0;
	wa = 835;
	ha = 1600;

    SDL_Log("init() >> w: %d - h: %d - wa: %d - ha: %d", w, h, wa, ha);

}


void Background::init2() {

    buttonTexture = "WindowPaused";

    currentSprite = BUTTON_SPRITE_OUT;


}

/*
void Background::init3()
{


    buttonTexture = "DebriefingWindow";


}
*/

void Background::showButton(bool on_off)
{
	displayButton = on_off;
}

bool Background::getShowButton()
{
	return displayButton;
}

void Background::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();


    //if (return_switch) xa = wa * currentSprite;
    xa = wa * currentSprite;
	//ya = thisButton.y;
	//ha = thisButton.h;
	//wa = thisButton.w;


}

void Background::onRender()
{
	if (buttonRenderer)
	{
		//TextureBank::Get(buttonTexture)->Render(0, 0, w, h, 0, 0, WHEIGHT, WWIDTH, 255);
		TextureBank::Get(buttonTexture)->Render(x, y, WWIDTH, WHEIGHT, xa, ya, wa, ha, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void Background::onClick()
{
	
}

void Background::offClick()
{
	
}

void Background::onMouseOver()
{
	
}

//*** Mobile Device Gesture ***
void Background::onTouchDown()
{
    SDL_Log("onTouchDown return_switch: %d", return_switch);
	if(return_switch)
	{
		if (tX >= return_ships.x &&
			tX <= return_ships.x + return_ships.w &&
			tY >= return_ships.y &&
			tY <= return_ships.y + return_ships.h) {
			ForceFeedbackPushButton();
			currentSprite = BUTTON_SPRITE_HOVER;
		}
	}

}

void Background::onTouchUp()
{
    SDL_Log("onTouchUp return_switch: %d", return_switch);
	if(return_switch)
	{
        if (tX >= return_ships.x &&
            tX <= return_ships.x + return_ships.w &&
            tY >= return_ships.y &&
            tY <= return_ships.y + return_ships.h)
        {
            currentSprite = BUTTON_SPRITE_OUT;
            CAppStateGamePause::GetInstance()->menuTrans = true;
            SDL_Delay(200);
            CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::BACK);
        }
    }

}

void Background::onTouchMove()
{

}

SDL_Rect Background::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void Background::handleEvent(SDL_Event* e)
{

    if(return_switch)
    {
        if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION) {

            tX = e->tfinger.x * WWIDTH;
            tY = e->tfinger.y * WHEIGHT;

            bool hover = true;
            SDL_Rect thisButton;
            //thisButton = getBounds();
            thisButton = return_ships;
            if (tX < thisButton.x) {
                hover = false;
            } else if (tX > thisButton.x + thisButton.w) {
                hover = false;
            }
            if (tY < thisButton.y) {
                hover = false;
            } else if (tY > thisButton.y + thisButton.h) {
                hover = false;
            }

            if (!hover) {
                currentSprite = BUTTON_SPRITE_OUT;
            } else {
                switch (e->type) {
                    case SDL_FINGERMOTION:
                        currentSprite = BUTTON_SPRITE_HOVER;
                        onTouchMove();
                        break;
                    case SDL_FINGERDOWN:
                        currentSprite = BUTTON_SPRITE_DOWN;
                        onTouchDown();
                        break;
                    case SDL_FINGERUP:
                        currentSprite = BUTTON_SPRITE_OUT;
                        onTouchUp();
                        break;
                }
            }
        }
    }

}


void Background::onDelete()
{
	delete this;
}


// BACKGROUND2

Background2::Background2()
{
    buttonID = 0;
    menuID = MAIN;

    SDL_Log("background2()");

    //buttonTexture = "BackgroundShips";
    buttonTexture = "Window_GameOver";

    Panel::init();

    currentSprite = BUTTON_SPRITE_OUT;

    w = WWIDTH;
    h = WHEIGHT;
    x = 0;
    y = 0;
    xa = ya = 0;
    wa = 835;
    ha = 1600;

	return_switch = true;
    displayButton = true;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

    SDL_Log("background initialization completed");



}


Background2::~Background2()
{
    SDL_Log("~background2()");
}

void Background2::init()
{

	return_menu.w = 235;
	return_menu.h = 214;
    return_menu.x = 0;
    return_menu.y = WHEIGHT - return_menu.h;


    return_switch = true;
    displayButton = true;

    buttonTexture = "WindowSmartphoneXXXL";

    SDL_Log("displayButton? %d", displayButton);
    SDL_Log("return_switch: %d", return_switch);
    currentSprite = BUTTON_SPRITE_OUT;
    //else if (!displayButton) currentSprite = BUTTON_SPRITE_DOWN;
    SDL_Log("currentSprite: %d", currentSprite);

    w = WWIDTH;
    h = WHEIGHT;
    x = 0;
    y = 0;
    wa = 835;
    ha = 1600;

    SDL_Log("init() >> w: %d - h: %d - wa: %d - ha: %d", w, h, wa, ha);
}


void Background2::init2()
{
	wa = 835;
	ha = 1600;
    currentSprite = BUTTON_SPRITE_OUT;
    buttonTexture = "Window_debrief";

}

/*
void Background::init3()
{


    buttonTexture = "DebriefingWindow";


}
*/

void Background2::showButton(bool on_off)
{
    displayButton = on_off;
}

bool Background2::getShowButton()
{
    return displayButton;
}

void Background2::onLoop()
{
    SDL_Rect thisButton;
    thisButton = getBounds();


    xa = wa * currentSprite;
    //ya = thisButton.y;
    //ha = thisButton.h;
    //wa = thisButton.w;


}

void Background2::onRender()
{
    if (buttonRenderer)
    {
        //TextureBank::Get(buttonTexture)->Render(0, 0, w, h, 0, 0, WHEIGHT, WWIDTH, 255);
        TextureBank::Get(buttonTexture)->Render(x, y, WWIDTH, WHEIGHT, xa, ya, wa, ha, 255);
    }
    else
    {
        CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void Background2::onClick()
{

}

void Background2::offClick()
{

}

void Background2::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Background2::onTouchDown()
{

    SDL_Log("onTouchDown return_switch: %d", return_switch);
    if(return_switch)
    {
        if (tX >= return_menu.x &&
            tX <= return_menu.x + return_menu.w &&
            tY >= return_menu.y &&
            tY <= return_menu.y + return_menu.h) {
            ForceFeedbackPushButton();
            currentSprite = BUTTON_SPRITE_HOVER;
        }
        else
        {
            currentSprite = BUTTON_SPRITE_OUT;
        }
    }

}

void Background2::onTouchUp()
{

    SDL_Log("onTouchUp return_switch: %d", return_switch);
    if(return_switch)
    {
        if (tX >= return_menu.x &&
            tX <= return_menu.x + return_menu.w &&
            tY >= return_menu.y &&
            tY <= return_menu.y + return_menu.h)
        {
            currentSprite = BUTTON_SPRITE_OUT;
            CAppStateGamePause::GetInstance()->menuTrans = true;
            SDL_Delay(200);
            CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::BACK);
        }
        else
        {

        }
    }

}

void Background2::onTouchMove()
{

}

SDL_Rect Background2::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void Background2::handleEvent(SDL_Event* e)
{

    if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
    {

        tX = e->tfinger.x * WWIDTH;
        tY = e->tfinger.y * WHEIGHT;

        bool hover = true;
        SDL_Rect thisButton;
        //thisButton = getBounds();
        thisButton = return_menu;

        if (tX < thisButton.x)
        {
            hover = false;
        }
        else if (tX > thisButton.x + thisButton.w)
        {
            hover = false;
        }
        if (tY < thisButton.y)
        {
            hover = false;
        }
        else if (tY > thisButton.y + thisButton.h)
        {
            hover = false;
        }

        if (!hover)
        {
            currentSprite = BUTTON_SPRITE_OUT;
        }
        else
        {
            switch (e->type)
            {
                case SDL_FINGERMOTION:
                    currentSprite = BUTTON_SPRITE_HOVER;
                    onTouchMove();
                    break;
                case SDL_FINGERDOWN:
                    currentSprite = BUTTON_SPRITE_DOWN;
                    onTouchDown();
                    break;
                case SDL_FINGERUP:
                    currentSprite = BUTTON_SPRITE_OUT;
                    onTouchUp();
                    break;
            }
        }
    }

}


void Background2::onDelete()
{
    delete this;
}



// HANGAR


float Hangar::Xhangar = 0;
float Hangar::Yhangar = 0;
float Hangar::XcHangar = 0;
float Hangar::YcHangar = 0;
float Hangar::MoveX = 0;

float   Hangar::breakpointA = 0;
float   Hangar::breakpointB = 0;
float   Hangar::breakpointC = 0;
float   Hangar::breakpointX = 0;
float   Hangar::Xoffset = 0;

bool  Hangar::scrolling = false;

Hangar::Hangar()
{
    buttonID = 0;
	menuID = MAIN;

	SDL_Log("Hangar()");
}

Hangar::~Hangar()
{
	SDL_Log("~Hangar()");
}

void Hangar::init()
{
	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	ha = 1920;

    this->w = WWIDTH *4;
    this->h = WHEIGHT;
	this->x = 0;
    this->y = 0;

    this->buttonTexture = "Hangar_bg";

	ship_thumb = WWIDTH * 0.75;
	padding = (WWIDTH - ship_thumb) /2;

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

    XcHangar = YcHangar = 0;
    tXhangar = tYhangar = 0;

    float tempW = ((WWIDTH -ship_thumb) /2);
    breakpointA = 0;
    breakpointB = -(WWIDTH);
    breakpointC = -(WWIDTH *2);
    breakpointX = -(WWIDTH *3);

    //SDL_Log("breakpointB: %d", breakpointB);
    //SDL_Log("breakpointC: %d", breakpointC);
    //SDL_Log("breakpointX: %d", breakpointX);

    MoveX = 0;
    MAXspeed = 30;
    SpeedX = 0;
    Accel = 0.25;
    scrolling = false;

    up = down = move = false;

	SDL_Log("Hangar initialization completed");
	SDL_Log("BreakPointB: %1.2f",breakpointB);
    SDL_Log("BreakPointC: %1.2f",breakpointC);
    SDL_Log("BreakPointX: %1.2f",breakpointX);

}


void Hangar::init2() {}

void Hangar::showButton(bool on_off)
{
	displayButton = on_off;
}

bool Hangar::getShowButton()
{
	return displayButton;
}

void Hangar::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

    if (scrolling)
    {
        if (Xhangar <= 0 && Xhangar >= -w + WWIDTH)
        {
            if (MoveX > 0)
            {
                if (Xhangar < breakpointA && Xhangar > breakpointA -200)
                {
                    MoveX += Accel;
                    Xhangar = breakpointA;
                    scrolling = false;
                    SDL_Log("breakPointB: %1.2f", Xhangar);
                    goto jump;
                }
                else if (Xhangar < breakpointB && Xhangar > breakpointB -200)
                {
                    MoveX += Accel;
                    Xhangar = breakpointB;
                    scrolling = false;
                    SDL_Log("breakPointB: %1.2f", Xhangar);
                    goto jump;
                }
                else if (Xhangar < breakpointC && Xhangar > breakpointC -200)
                {
                    MoveX += Accel;
                    Xhangar = breakpointC;
                    scrolling = false;
                    SDL_Log("breakPointC: %1.2f", Xhangar);
                    goto jump;
                }
                else if (Xhangar < breakpointX && Xhangar > -w + WWIDTH -200)
                {
                    MoveX += Accel;
                    Xhangar = breakpointX;
                    scrolling = false;
                    SDL_Log("breakPointX: %1.2f", Xhangar);
                    goto jump;
                }


                MoveX -= Accel;

            }
            if (MoveX < 0)
            {
                if (Xhangar < breakpointA +200 && Xhangar > breakpointA)
                {
                    MoveX += Accel;
                    Xhangar = breakpointA;
                    scrolling = false;
                    SDL_Log("breakPointB: %1.2f", Xhangar);
                    goto jump;
                }

                else if (Xhangar < breakpointB +200 && Xhangar > breakpointB)
                {
                    MoveX += Accel;
                    Xhangar = breakpointB;
                    scrolling = false;
                    SDL_Log("breakPointB: %1.2f", Xhangar);
                    goto jump;
                }
                else if (Xhangar < breakpointC +200 && Xhangar > breakpointC)
                {
                    MoveX += Accel;
                    Xhangar = breakpointC;
                    scrolling = false;
                    SDL_Log("breakPointC: %1.2f", Xhangar);
                    goto jump;
                }
                else if (Xhangar < breakpointX +200 && Xhangar > -w + WWIDTH)
                {
                    MoveX += Accel;
                    Xhangar = breakpointX;
                    scrolling = false;
                    SDL_Log("breakPointX: %1.2f", Xhangar);
                    goto jump;
                }

            }
            //if (MoveX > MAXspeed) MoveX = MAXspeed;
            //if (MoveX < -MAXspeed) MoveX = -MAXspeed;



            Xhangar += MoveX;
            //SDL_Log("tXhangar: %1.5f - X: %1.2f - MoveX: %1.2f", tXhangar, Xhangar, MoveX);
        } else if (Xhangar > 0)
        {
            //SDL_Log("X > 0: %1.2f - MoveX: %1.2f set MoveX >> 0", Xhangar, MoveX);
            Xhangar = 0;
            MoveX = 0;
            scrolling = false;
        } else if (Xhangar < -w + WWIDTH)
        {
            Xhangar = -w + WWIDTH;
            //XcHangar = Xhangar;
            scrolling = false;
        }
    }

    jump:

    if(MoveX >= 0 && MoveX < Accel) scrolling = false;
    else if(MoveX > -Accel && MoveX <= 0) scrolling = false;

    if (Xhangar <= 0 && Xhangar >= -w + WWIDTH)
    {
        XcHangar = Xhangar;
    }

    YcHangar = tYhangar;
    SDL_Log("Loop X: %1.2f", XcHangar);
    CCamera::CameraControl.OnMove(XcHangar, 0);

}

void Hangar::onMove(float MoveX, float prevX) {

}

void Hangar::AddOffset(int offset) {

    scrolling = false;
    MoveX = 0;
    XcHangar = offset;
    CCamera::CameraControl.OnMove(XcHangar, 0);

}

void Hangar::onRender()
{
	if (buttonRenderer)
	{
        TextureBank::Get(buttonTexture)->Render(XcHangar, 0, w +390, h, 0, 0, w, ha, 255);
	}
	else
	{
		//CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void Hangar::onClick()
{

}

void Hangar::offClick()
{

}

void Hangar::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Hangar::onTouchDown()
{
	SDL_Log("touch down");
    //CCamera::CameraControl.OnMove(0, 0);

    down = true;
    scrolling = false;
    MoveX = 0;
	
}

void Hangar::onTouchUp()
{

	SDL_Log("touch up");
    up = true;
    if(down) {
        scrolling = false;
        MoveX = 0;
    }

}

void Hangar::onTouchMove()
{

    //SDL_Log("touch moving");
    CCamera::CameraControl.TargetMode = TARGET_MODE_EXPLORER;

    if (Xhangar <= 0 && Xhangar >= -w + WWIDTH)
    {
        scrolling = true;
        down = false;
        up = false;
        move = true;

        tXhangar = x * WWIDTH;

        if (tXhangar == 0) MoveX = 0;
        else MoveX = tXhangar;
        //SDL_Log("OnMove - X: %1.2f - MoveX: %1.2f", Xhangar, MoveX);
    }
    else if (Xhangar > 0)
    {
        Xhangar = 0;
        MoveX = 0;
        scrolling = false;
    } else if (Xhangar < -w + WWIDTH)
    {
        Xhangar = -w + WWIDTH;
        MoveX = 0;
        scrolling = false;
    }
    SDL_Log("Xhangar: %1.2f", Xhangar);
    SDL_Log("MoveX: %1.2f", MoveX);



    /*
    if (CCamera::CameraControl.GetY() <= 0 && CCamera::CameraControl.GetY() >= -3200 + WHEIGHT)	Yc = CCamera::CameraControl.GetY();
    else if (CCamera::CameraControl.GetY() > 0) CCamera::CameraControl.Y = 0;
    else if (CCamera::CameraControl.GetY() < -3200 + WHEIGHT) CCamera::CameraControl.Y = -3200 + WHEIGHT;
	*/



}




SDL_Rect Hangar::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = x;
	buttonRect.y = y;
	buttonRect.w = w;
	buttonRect.h = h;

	return buttonRect;
}

void Hangar::handleEvent(SDL_Event* e)
{



    switch (e->type)
    {
        case SDL_FINGERMOTION:

            x = e->tfinger.dx;
            y = e->tfinger.dy;
            onTouchMove();
            break;

        case SDL_FINGERDOWN:

            onTouchDown();
            break;

        case SDL_FINGERUP:

            onTouchUp();
            break;
    }



    //SDL_Log("dx: %1.3f - dy: %1.3f", e->tfinger.dx, e->tfinger.dy);
    //SDL_Log("scrollX: %1.5f", x);

}


void Hangar::onDelete()
{
	delete this;
}




// EXPLORER

//Explorer Explorer::Instance;
float Explorer::X1 = 0;
float Explorer::Y1 = 0;
float Explorer::Xc = 0;
float Explorer::Yc = 0;
float Explorer::MoveX = 0;

int Explorer::Waa   = 0;
int Explorer::Haa   = 0;

bool Explorer::scrolling = false;

Explorer::Explorer()
{
	buttonID = 0;
	menuID = MAIN;
	
	

	SDL_Log("explorer()");
}

Explorer::~Explorer()
{
	SDL_Log("~explorer()");
	
}

void Explorer::init()
{
	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

    MoveX = 0;
    MAXspeed = 30;
    SpeedX = 0;
    Accel = 0.25;
    scrolling = false;

    up = down = move = false;
	
	/*
	Level0.w = 265;
	Level0.h = 265;
	Level0.x = 250;
	Level0.y = 250;
    */

	//this->w = WWIDTH *1.5;
	//this->h = WHEIGHT; // 1500
	this->w = 4000;
	this->h = WHEIGHT;
	this->x = 0;
	this->y = 0;
	wa = 4000;
	ha = 2000;

	Waa = w;
	Haa = h;

	//SDL_Log("explr x: %d   y:%d", this->x, this->y);

	buttonTexture = "Galaxy_final";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

	this->tXm = this->tYm = 0;
}

void Explorer::init2() {}

void Explorer::showButton(bool on_off)
{
	displayButton = on_off;
}

bool Explorer::getShowButton()
{
	return displayButton;
}

void Explorer::onLoop()
{

	SDL_Rect thisButton;
	thisButton = getBounds();

    if (scrolling)
    {
        if (Xc <= 0 && Xc >= (-w + WWIDTH))
        {
            if (MoveX > 0) MoveX -= Accel;
            if (MoveX < 0) MoveX += Accel;
            //if (MoveX > MAXspeed) MoveX = MAXspeed;
            //if (MoveX < -MAXspeed) MoveX = -MAXspeed;

            Xc += MoveX;
        } else if (Xc > 0)
        {
            Xc = 0;
            MoveX = 0;
            scrolling = false;
        } else if (Xc < (-w + WWIDTH))
        {
            Xc = -w + WWIDTH;
            //this->X1 = this->Xc;
            scrolling = false;
        }
    }

    if (MoveX >= 0 && MoveX < Accel) scrolling = false;
    else if (MoveX > -Accel && MoveX <= 0) scrolling = false;

    if (Xc <= 0 && Xc >= (-w + WWIDTH))
    {
        X1 = Xc;
    }

    //SDL_Log("Xc: %1.2f", X1);
    Yc = Y1 = 0;
    CCamera::CameraControl.OnMove(X1, 0);

}

void Explorer::onRender()
{
	if (buttonRenderer)
	{
		//SDL_Log("Explorer onRender()");
        //SDL_Log("X1: %1.2f", X1);
		TextureBank::Get(buttonTexture)->Render(X1, 0, w, h, 0, 0, wa, ha, 255);
	}
	else
	{
		SDL_Log("Explorer bad renderer");
		//CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void Explorer::onClick()
{

}

void Explorer::offClick()
{

}

void Explorer::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Explorer::onTouchDown()
{
	/*
	if (!CAppStateIntro::GetInstance()->GetMothershipComplete())
	{
		if (tXt >= Level0.x &&
			tXt <= Level0.x + Level0.w &&
			tYt >= Level0.y &&
			tYt <= Level0.y + Level0.h)
		{
			SDL_Log("SDL_Rect Level0 touchedUP");
			//CAppStateGamePause::isRunning = true;
			CAppStateGamePause::onPause = false;
			CAppStateGamePause::menuTrans = true;
			CCamera::CameraControl.TargetMode = TARGET_MODE_NORMAL;
			CAppStateGamePause::setActiveMenu(CAppStateGamePause::NEWGAME);
		}
	}
    */

    //SDL_Log(" touch down Xc: %1.2f", X1);
    //CCamera::CameraControl.OnMove(0, 0);

    down = true;
    scrolling = false;
    MoveX = 0;
	
}

void Explorer::onTouchUp()
{
	
	up = true;
    if(down) {
        scrolling = false;
        MoveX = 0;
    }
	

}

void Explorer::onTouchMove()
{
    CCamera::CameraControl.TargetMode = TARGET_MODE_EXPLORER;

    if (Xc <= 0 && Xc >= -w + WWIDTH)
    {
        scrolling = true;
        down = false;
        up = false;
        move = true;

        tXm = x * WWIDTH;

        if (tXm == 0) MoveX = 0;
        else MoveX = tXm;
    }
    else if (Xc > 0)
    {
        Xc = 0;
        MoveX = 0;
        scrolling = false;
    } else if (Xc < (-w + WWIDTH))
    {
        Xc = -w + WWIDTH;
        MoveX = 0;
        scrolling = false;
    }


}

SDL_Rect Explorer::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void Explorer::handleEvent(SDL_Event* e)
{
	/*
	this->x1 = e->tfinger.x;
	this->y1 = e->tfinger.y;
	this->x = e->tfinger.dx;
	this->y = e->tfinger.dy;
    */
    //SDL_Log("dx: %1.5f - dy: %1.5f", e->tfinger.dx, e->tfinger.dy);
    //SDL_Log("x: %d - y: %d", this->x, this->y);

	switch (e->type)
	{
        case SDL_FINGERMOTION:

            x = e->tfinger.dx;
            tYm = e->tfinger.dy;
            this->onTouchMove();
            break;

        case SDL_FINGERDOWN:

            this->onTouchDown();
            break;

        case SDL_FINGERUP:

            this->onTouchUp();
            break;
	}
	


}

int Explorer::getWa() {

    return Waa;

}
int Explorer::getHa () {

    return  Haa;

}


void Explorer::onDelete()
{
	delete this;
}

/*
Explorer* Explorer::GetInstance() {

	return &Instance;

}
*/


// BUTTON PLAY CODE

ButtonPlay::ButtonPlay()
{
	buttonID = 0;
	menuID = PLAY;

	buttonTexture = "Play";
	displayButton = false;

	w = WWIDTH * 0.4;
	h = w / 1.7;

	SDL_Log("button PLAY constructor");
}

ButtonPlay::~ButtonPlay()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "Button Play Destructor", "");
}

void ButtonPlay::init()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "new Button Play created", "");
	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	/*
	w = Panel::getWidth() / 3;
	h = w / 2;
	x = (Panel::GetX1() + buttonID * w) + (padding * buttonID);
	y = Panel::GetY1();
	*/


	x = (WWIDTH - this->w) /2;
	y = WHEIGHT * 0.22;
    //y = Panel::GetY1() + (padding * buttonID);



	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}


void ButtonPlay::init2() {


	//x = (WWIDTH - this->w) /2 + w/2;
	//y = WHEIGHT* 0.80;

	x = (WWIDTH / 2) - (w / 2);
	y = WHEIGHT * 0.65;

	displayButton = true;


}

void ButtonPlay::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonPlay::getShowButton()
{
	return displayButton;
}

void ButtonPlay::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = thisButton.x;
	ya = 223 * currentSprite;;
	ha = thisButton.h;
	wa = thisButton.w;
}

void ButtonPlay::onRender()
{
	if (buttonRenderer)
	{
		//SDL_Log("Button Play onRender()\n");
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, 645, 223, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonPlay::onClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-on event", "");
	
}

void ButtonPlay::offClick()
{
	/*
	CAppStateGamePause::isRunning = true;
	CAppStateGamePause::onPause = false;
	CAppStateGamePause::menuTrans = true;
	*/
}

void ButtonPlay::onMouseOver()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse over event", "");
}

//*** Mobile Device Gesture ***
void ButtonPlay::onTouchDown()
{

	if (SDL_HapticRumblePlay(mouseHaptic, 0.20, 80) != 0)
	{
		SDL_Log("Warning: Unable to play rumble! %s", SDL_GetError());
	}


    currentSprite = BUTTON_SPRITE_HOVER;
    ForceFeedbackPushButton();



	/*
	CAppStateGamePause::isRunning = true;
	CAppStateGamePause::onPause = false;
	CAppStateGamePause::menuTrans = true;
	*/

}

void ButtonPlay::onTouchUp()
{

	if (displayButton)
	{
		currentSprite = BUTTON_SPRITE_OUT;
		CAppStateGamePause::GetInstance()->menuTrans = true;
		CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::MISSION);
	}
	else
	{
		currentSprite = BUTTON_SPRITE_OUT;
        CAppStateGamePause::menuTrans = true;
        CAppStateGamePause::setActiveMenu(CAppStateGamePause::PLAY);
    }

}

void ButtonPlay::onTouchMove()
{
	
}

SDL_Rect ButtonPlay::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonPlay::handleEvent(SDL_Event* e)
{

	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;
		
		//LOGD("Button Play tfinger.x: %1.4f", e->tfinger.x);
		//LOGD("Button Play tfinger.y: %1.4f", e->tfinger.y);
		//LOGD("Button Play tX: %d", tX);
		//LOGD("Button Play tY: %d", tY);
		

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			//SDL_Log("Button Play UNtouched\n");
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			//SDL_Log("Button Play touched\n");
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				this->onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				this->onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				this->onTouchUp();
				break;
			}
		}
	}


}



void ButtonPlay::onDelete()
{
	delete this;
}




// BUTTON NEXT CODE

ButtonNext::ButtonNext()
{
	buttonID = 0;
	menuID = MAIN;

    currentSprite = BUTTON_SPRITE_OUT;

	SDL_Log("button NEXT constructor");

}

ButtonNext::~ButtonNext()
{

}

void ButtonNext::init()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "new Button Next created", "");
	Panel::init();

	wa = 645;
	ha = 223;
    w = WWIDTH * 0.45;
    h = w * 0.40;

    x = (WWIDTH - this->w) /2;
    y = WHEIGHT * 0.40;

	buttonTexture = "Restart";
	displayButton = true;

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

    SDL_SetRenderDrawColor(buttonRenderer, 0x00, 0x00, 0x00, 0xFF);

}


void ButtonNext::init2() {

    Panel::init();

    buttonTexture = "Back_xs";
    displayButton = false;

    wa = 313;
    ha = 285;
    w = WWIDTH * 0.3;
    h = w / 1.1;
    //x = (WWIDTH - this->w) /2 - (w/2);
    x = (WWIDTH / 2) - (w / 2);
    y = WHEIGHT * 0.50;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

    SDL_SetRenderDrawColor(buttonRenderer, 0x00, 0x00, 0x00, 0xFF);


}

void ButtonNext::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonNext::getShowButton()
{
	return displayButton;
}

void ButtonNext::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = thisButton.x;
	ya = ha * currentSprite;
	//ha = thisButton.h;
	//wa = thisButton.w;
}

void ButtonNext::onRender()
{
	if (buttonRenderer)
	{
		//SDL_Log("Button Play onRender()\n");
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, wa, ha, 255);
	}
	else
	{

	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonNext::onClick()
{

}

void ButtonNext::offClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-out event", "");
/*
	CAppStateGamePause::isRunning = true;
	CAppStateGamePause::onPause = false;
	CAppStateGamePause::menuTrans = true;
*/
}

void ButtonNext::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void ButtonNext::onTouchDown()
{

    ForceFeedbackPushButton();
    currentSprite = BUTTON_SPRITE_HOVER;

	//SDL_Log("ButtonPLAY: On Touch Down Event");


}

void ButtonNext::onTouchUp()
{

    if (displayButton) {
        currentSprite = BUTTON_SPRITE_OUT;
        CAppStateGamePause::isRunning = true;
        CAppStateGamePause::onPause = false;
        CAppStateGame::GetInstance()->onReset = true;
        CAppStateGamePause::GetInstance()->OnRestore();
    } else {
        currentSprite = BUTTON_SPRITE_OUT;
        CAppStateGamePause::isRunning = true;
        CAppStateGamePause::onPause = true;
        CAppStateGamePause::menuTrans = true;
        CAppStateGame::GetInstance()->onReset = true;
        CAppStateGamePause::setActiveMenu(CAppStateGamePause::MAIN);
    }
}

void ButtonNext::onTouchMove()
{

}

SDL_Rect ButtonNext::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonNext::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		//LOGD("Button Play tfinger.x: %1.4f", e->tfinger.x);
		//LOGD("Button Play tfinger.y: %1.4f", e->tfinger.y);
		//LOGD("Button Play tX: %d", tX);
		//LOGD("Button Play tY: %d", tY);


		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			//SDL_Log("Button Play UNtouched\n");
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			//SDL_Log("Button Play touched\n");
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				this->onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				this->onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				this->onTouchUp();
				break;
			}
		}
	}


}



void ButtonNext::onDelete()
{
	delete this;
}





// BUTTON RESUME CODE

ButtonResume::ButtonResume()
{
	buttonID = 0;
	menuID = EXIT;
    Panel::init();

    currentSprite = BUTTON_SPRITE_OUT;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

    SDL_SetRenderDrawColor(buttonRenderer, 0x00, 0x00, 0x00, 0xFF);


    w = WWIDTH * 0.45;
    h = w * 0.40;



	SDL_Log("button RESUME constructor");

}

ButtonResume::~ButtonResume()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "Button Resume Destructor", "");
}

void ButtonResume::init()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "new Button Resume created", "");

	wa = 645;
    ha = 223;
	x = (WWIDTH - this->w) /2;
	y = WHEIGHT * 0.28;

	SDL_Log("w: %d h: %d x: %d y: %d", w, h, x, y);

	buttonTexture = "Resume";



}

void ButtonResume::init2() {

	/*
    x = (WWIDTH - this->w) /2;
    y = WHEIGHT * 0.53;
    SDL_Log("w: %d h: %d x: %d y: %d", w, h, x, y);
    buttonTexture = "Play";
	*/

	wa = 317;
	ha = 285;
	w = WWIDTH * 0.3;
	h = w / 1.1;
	//x = (WWIDTH - this->w) /2 - (w/2);
	x = (WWIDTH / 2) - (w / 2);
	y = WHEIGHT * 0.50;



	//SDL_Log("Return button x: %d - y: %d", x, y);

	buttonTexture = "Back_xs";

}

void ButtonResume::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonResume::getShowButton()
{
	return displayButton;
}

void ButtonResume::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = thisButton.x;
	ya = ha * currentSprite;
	//ha = thisButton.h;
	//wa = thisButton.w;
}

void ButtonResume::onRender()
{
	if (buttonRenderer)
	{
		//SDL_Log("Button Play onRender()\n");
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, wa, ha, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

	SDL_SetRenderDrawColor(buttonRenderer, 0x00, 0x00, 0x00, 0xFF);

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonResume::onClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-on event", "");

}

void ButtonResume::offClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-out event", "");

	CAppStateGamePause::isRunning = true;
	CAppStateGamePause::onPause = false;
	CAppStateGamePause::GetInstance()->OnRestore();
	
	//CAppStateGamePause::menuTrans = true;

}

void ButtonResume::onMouseOver()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse over event", "");
}

//*** Mobile Device Gesture ***
void ButtonResume::onTouchDown()
{
	ForceFeedbackPushButton();
	currentSprite = BUTTON_SPRITE_HOVER;
	//SDL_Log("ButtonRESUME: On Touch Down Event");



}

void ButtonResume::onTouchUp()
{
	currentSprite = BUTTON_SPRITE_OUT;
	CAppStateGamePause::isRunning = true;
	CAppStateGamePause::onPause = false;
	CAppStateGamePause::GetInstance()->OnRestore();

}

void ButtonResume::onTouchMove()
{

}

SDL_Rect ButtonResume::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonResume::handleEvent(SDL_Event* e)
{

	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		//LOGD("Button Play tfinger.x: %1.4f", e->tfinger.x);
		//LOGD("Button Play tfinger.y: %1.4f", e->tfinger.y);
		//LOGD("Button Play tX: %d", tX);
		//LOGD("Button Play tY: %d", tY);


		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			//SDL_Log("Button Play UNtouched\n");
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			//SDL_Log("Button Play touched\n");
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				this->onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				this->onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				this->onTouchUp();
				break;
			}
		}
	}


}



void ButtonResume::onDelete()
{
	delete this;
}





// BUTTON DEBRIEF CODE

ButtonDebrief::ButtonDebrief()
{
	buttonID = 0;
	//menuID = EXIT;

	SDL_Log("button DEBRIEF constructor");

}

ButtonDebrief::~ButtonDebrief()
{

}

void ButtonDebrief::init()
{
	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	x = 340;
    y = 880;
    w = 835;
    h = 1600;

    starSX.x = 330 * SCREEN_W_RATIO;
	starSX.y = 875 * SCREEN_H_RATIO;
    SDL_Log("starSX.x %d - starSX.y %d", starSX.x, starSX.y);

    starM1.x = 330 * SCREEN_W_RATIO;
    starM1.y = 730 * SCREEN_H_RATIO;
    SDL_Log("starM1.x %d - starM1.y %d", starM1.x, starM1.y);

    starMM.x = 330 * SCREEN_W_RATIO;
    starMM.y = 590 * SCREEN_H_RATIO;
    SDL_Log("starMM.x %d - starMM.y %d", starMM.x, starMM.y);

    starBB.x = 330 * SCREEN_W_RATIO;
    starBB.y = 450 * SCREEN_H_RATIO;
    SDL_Log("starBB.x %d - starBB.y %d", starBB.x, starBB.y);

    //buttonTexture = "";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

	SDL_SetRenderDrawColor(buttonRenderer, 0x00, 0x00, 0x00, 0xFF);

}

void ButtonDebrief::init2() {}

void ButtonDebrief::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonDebrief::getShowButton()
{
	return displayButton;
}

void ButtonDebrief::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	/*
	xa = thisButton.x;
	ya = 223 * currentSprite;
	ha = thisButton.h;
	wa = thisButton.w;
	 */
}

void ButtonDebrief::onRender()
{
	if (buttonRenderer)
	{
		//SDL_Log("Button Play onRender()\n");
		//TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, 0, wa, ha, 255);
		CPlayerStat::PlayerStat.OnRender(starSX.x, starSX.y, 385, 90, CPlayer::starSX *100, Surface_bonus);
        CPlayerStat::PlayerStat.OnRender(starMM.x, starMM.y, 385, 90, CPlayer::starMM *100, Surface_bonus);
        CPlayerStat::PlayerStat.OnRender(starM1.x, starM1.y, 385, 90, CPlayer::starM1 *100, Surface_bonus);
        CPlayerStat::PlayerStat.OnRender(starBB.x, starBB.y, 385, 90, CPlayer::starBB *100, Surface_bonus);
    }
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

	SDL_SetRenderDrawColor(buttonRenderer, 0xFF, 0x00, 0x00, 0xFF);

}


// BUTTON ACTION & CONTROLLER FUNCTION

void ButtonDebrief::onClick()
{

}

void ButtonDebrief::offClick()
{


}

void ButtonDebrief::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void ButtonDebrief::onTouchDown()
{

	/*
	ForceFeedbackPushButton();
	currentSprite = BUTTON_SPRITE_HOVER;
	*/

}

void ButtonDebrief::onTouchUp()
{
	/*
	currentSprite = BUTTON_SPRITE_OUT;
	CAppStateGamePause::isRunning = true;
	CAppStateGamePause::onPause = false;
	CAppStateGamePause::GetInstance()->OnRestore();
	*/
}

void ButtonDebrief::onTouchMove()
{

}

SDL_Rect ButtonDebrief::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonDebrief::handleEvent(SDL_Event* e)
{

	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		//LOGD("Button Play tfinger.x: %1.4f", e->tfinger.x);
		//LOGD("Button Play tfinger.y: %1.4f", e->tfinger.y);
		//LOGD("Button Play tX: %d", tX);
		//LOGD("Button Play tY: %d", tY);


		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			//SDL_Log("Button Play UNtouched\n");
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			//SDL_Log("Button Play touched\n");
			switch (e->type)
			{
				case SDL_FINGERMOTION:
					currentSprite = BUTTON_SPRITE_HOVER;
					this->onTouchMove();
					break;
				case SDL_FINGERDOWN:
					currentSprite = BUTTON_SPRITE_DOWN;
					this->onTouchDown();
					break;
				case SDL_FINGERUP:
					currentSprite = BUTTON_SPRITE_OUT;
					this->onTouchUp();
					break;
			}
		}
	}


}



void ButtonDebrief::onDelete()
{
	delete this;
}











// BUTTON SHIP CODE

ButtonShip::ButtonShip()
{
	buttonID = 1;
	menuID = SHIP;
}

ButtonShip::~ButtonShip()
{
	//CApp::Logger.OnLog(__FILE__, __LINE__, "Button Ship Destructor", "");
}

void ButtonShip::init()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "new Button Ship created", "");
	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	/*
	w = Panel::getWidth() / 3; 
	h = w / 2;
	//x = (Panel::GetX1() + buttonID * w) + (padding * buttonID);
	x = Panel::GetX1();
	y = (Panel::GetY1() + buttonID * h) + (padding * buttonID);
	*/

    w = WWIDTH * 0.4;
    h = w / 1.7;
	x = (WWIDTH - this->w) /2;
    y = WHEIGHT * 0.38;
	//y = Panel::GetY1() + (padding * buttonID) + ( h * buttonID);


	buttonTexture = "Hangar";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void ButtonShip::init2() {}

void ButtonShip::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonShip::getShowButton()
{
	return displayButton;
}

void ButtonShip::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = thisButton.x;
	ya = 223 * currentSprite;
	ha = thisButton.h;
	wa = thisButton.w;
}

void ButtonShip::onRender()
{
	if (buttonRenderer)
	{
		//SDL_Log("Button Option onRender()\n");
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, 645, 223, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonShip::onClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-on event", "");
}

void ButtonShip::offClick()
{
	
}

void ButtonShip::onMouseOver()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse over event", "");
}

//*** Mobile Device Gesture ***
void ButtonShip::onTouchDown()
{

	ForceFeedbackPushButton();

	//CAppStateGamePause::onPause = false;
	currentSprite = BUTTON_SPRITE_HOVER;


	SDL_Log("Ship Menu selected");

}

void ButtonShip::onTouchUp()
{

	currentSprite = BUTTON_SPRITE_OUT;
	CAppStateGamePause::setActiveMenu(CAppStateGamePause::SHIP);
	CAppStateGamePause::menuTrans = true;

}

void ButtonShip::onTouchMove()
{

}

SDL_Rect ButtonShip::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonShip::handleEvent(SDL_Event* e)
{

	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			//SDL_Log("Button Ship UNtouched\n");
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			//SDL_Log("Button Ship touched\n");
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				this->onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				this->onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				this->onTouchUp();
				break;
			}
		}
	}


}



void ButtonShip::onDelete()
{
	delete this;
}





// BUTTON OPTION CODE

ButtonOpt::ButtonOpt()
{
	buttonID = 2;
	menuID = OPTION;
}

ButtonOpt::~ButtonOpt()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "Button Option Destructor", "");
}

void ButtonOpt::init()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "new Button Option created", "");
	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	/*
	w = Panel::getWidth() / 3;
	h = w / 2;
	//x = (Panel::GetX1() + buttonID * w) + (padding * buttonID);
	x = Panel::GetX1();
	y = (Panel::GetY1() + buttonID * h) + (padding * buttonID);
	*/

    w = WWIDTH * 0.3;
    h = w / 1.1;
	x = (WWIDTH - this->w) /2;
	y = WHEIGHT * 0.54;

	buttonTexture = "Options";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void ButtonOpt::init2() {}

void ButtonOpt::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonOpt::getShowButton()
{
	return displayButton;
}

void ButtonOpt::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = thisButton.x;
	ya = 286 * currentSprite;
	ha = thisButton.h;
	wa = thisButton.w;
}

void ButtonOpt::onRender()
{
	if (buttonRenderer)
	{
		//SDL_Log("Button Option onRender()\n");
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, 313, 286, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonOpt::onClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-on event", "");
}

void ButtonOpt::offClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-out event", "");
	CAppStateGamePause::setActiveMenu(CAppStateGamePause::OPTION);
	CAppStateGamePause::menuTrans = true;
	
}

void ButtonOpt::onMouseOver()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse over event", "");
}

//*** Mobile Device Gesture ***
void ButtonOpt::onTouchDown()
{

	ForceFeedbackPushButton();

	currentSprite = BUTTON_SPRITE_HOVER;

	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse touch Down event", "");
	

}

void ButtonOpt::onTouchUp()
{

	currentSprite = BUTTON_SPRITE_OUT;
	CAppStateGamePause::setActiveMenu(CAppStateGamePause::OPTION);
	CAppStateGamePause::menuTrans = true;

}

void ButtonOpt::onTouchMove()
{
	
}

SDL_Rect ButtonOpt::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonOpt::handleEvent(SDL_Event* e)
{

	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			//SDL_Log("Button Option UNtouched\n");
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			SDL_Log("Button Option touched\n");
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				this->onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				this->onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				this->onTouchUp();
				break;
			}
		}
	}


}



void ButtonOpt::onDelete()
{
	delete this;
}


// BUTTON EXIT CODE

ButtonExit::ButtonExit()
{
	buttonID = 3;
}

ButtonExit::~ButtonExit()
{

}

void ButtonExit::init()
{
	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;
	exitGame = true;

	/*
	w = Panel::getWidth() / 3; 
	h = w / 2;
	//x = (Panel::GetX1() + buttonID * w) + (padding * buttonID);
	x = Panel::GetX1();
	y = (Panel::GetY1() + buttonID * h) + (padding * buttonID);
	*/

	w = WWIDTH * 0.3;
	h = w / 1.1;
	x = (WWIDTH - this->w) /2;
	y = WHEIGHT * 0.72;
    //y = Panel::GetY1() + (padding * buttonID) + ( h * buttonID);

	buttonTexture = "Exit";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void ButtonExit::init2()
{

	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	exitGame = false;

	/*
	w = Panel::getWidth() / 3;
	h = w / 2;
	//x = (Panel::GetX1() + buttonID * w) + (padding * buttonID);
	x = Panel::GetX1();
	y = (Panel::GetY1() + buttonID * h) + (padding * buttonID);
	*/

	w = WWIDTH * 0.3;
	h = w / 1.1;
	x = (WWIDTH - this->w) /2;
	y = WHEIGHT * 0.53;
	//y = Panel::GetY1() + (padding * buttonID) + ( h * buttonID);

	buttonTexture = "Exit";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();


}

void ButtonExit::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonExit::getShowButton()
{
	return displayButton;
}

void ButtonExit::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = thisButton.x;
	ya = 285 * currentSprite;
	ha = thisButton.h;
	wa = thisButton.w;
}

void ButtonExit::onRender()
{
	if (buttonRenderer)
	{
		//SDL_Log("Button Exit onRender()\n");
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, 313, 285, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonExit::onClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-on event", "");
	
}

void ButtonExit::offClick()
{
	CAppStateGamePause::isRunning = true;
	CAppStateGamePause::menuTrans = true;
	CAppStateGame::GetInstance()->onReset = true;
	CAppStateGame::GetInstance()->OnDeactivate();
	CAppStateGamePause::setActiveMenu(CAppStateGamePause::MAIN);

}

void ButtonExit::onMouseOver()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse over event", "");
}

//*** Mobile Device Gesture ***
void ButtonExit::onTouchDown()
{

	ForceFeedbackPushButton();

	currentSprite = BUTTON_SPRITE_HOVER;


}

void ButtonExit::onTouchUp()
{
	currentSprite = BUTTON_SPRITE_OUT;

    if (!exitGame)
    {
        CAppStateGamePause::isRunning = true;
        CAppStateGamePause::menuTrans = true;
        CAppStateGame::GetInstance()->onReset = true;
        CAppStateGame::GetInstance()->OnDeactivate();
        CAppStateGamePause::setActiveMenu(CAppStateGamePause::MAIN);
    }
    else
    {
        CAppStateGamePause::isRunning = true;
        CAppStateGamePause::menuTrans = true;
        CAppStateGamePause::setActiveMenu(CAppStateGamePause::EXIT);
    }
}

void ButtonExit::onTouchMove()
{
	
}

SDL_Rect ButtonExit::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonExit::handleEvent(SDL_Event* e)
{

	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			//SDL_Log("Button Exit UNtouched\n");
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			SDL_Log("Button Exit touched\n");
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				this->onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				this->onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				this->onTouchUp();
				break;
			}
		}
	}


}

void ButtonExit::onDelete()
{
	delete this;
}



// BUTTON RETURN CODE

ButtonReturn::ButtonReturn()
{
	SDL_Log("Return()");
}

ButtonReturn::~ButtonReturn()
{
	SDL_Log("~Return()");
}

void ButtonReturn::init()
{

	/// for Hangar menu & LevelCompleted
	buttonID = 2;

	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

    w = WWIDTH * 0.3;
    h = w / 1.1;
    //x = (WWIDTH - this->w) /2 - (w/2);
	x = (WWIDTH / 2) - (w / 2);
	y = WHEIGHT * 0.50;



	//SDL_Log("Return button x: %d - y: %d", x, y);

	buttonTexture = "Back_xs";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void ButtonReturn::init2()
{

	/// for Explorer menu
	buttonID = 3;

	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	w = WWIDTH * 0.25;
	h = w / 1.05;
	x = (WWIDTH - this->w) * 0.1;
	//x = WWIDTH * 0.66;
    y = WHEIGHT * 0.83;

	//SDL_Log("Return button x: %d - y: %d", x, y);

	buttonTexture = "Back_xs";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}


void ButtonReturn::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonReturn::getShowButton()
{
	return displayButton;
}

void ButtonReturn::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = thisButton.x;
	ya = w * currentSprite;
	ha = thisButton.h;
	wa = thisButton.w;
}

void ButtonReturn::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, 313, 285, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonReturn::onClick()
{

}

void ButtonReturn::offClick()
{
	CAppStateGamePause::GetInstance()->menuTrans = true;
	CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::BACK);
}

void ButtonReturn::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void ButtonReturn::onTouchDown()
{

	ForceFeedbackPushButton();

	currentSprite = BUTTON_SPRITE_HOVER;

}

void ButtonReturn::onTouchUp()
{

	currentSprite = BUTTON_SPRITE_OUT;
	CAppStateGamePause::GetInstance()->menuTrans = true;
	CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::BACK);


}

void ButtonReturn::onTouchMove()
{
	
}

SDL_Rect ButtonReturn::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonReturn::handleEvent(SDL_Event* e)
{

	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonReturn::onDelete()
{
	delete this;
}



// BUTTON VIDEO CODE

ButtonVideo::ButtonVideo()
{
	buttonID = 0;
	menuID = VIDEO;
}

ButtonVideo::~ButtonVideo()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "Button Video Destructor", "");
}

void ButtonVideo::init()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "new Button Video created", "");
	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	w = WWIDTH * 0.45;
	h = w * 0.40;
	x = (WWIDTH - this->w) /2;
    y = Panel::GetY1() + (padding * buttonID);


	buttonTexture = "Video";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void ButtonVideo::init2() {}

void ButtonVideo::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonVideo::getShowButton()
{
	return displayButton;
}

void ButtonVideo::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = thisButton.x;
	ya = 223 * currentSprite;
	ha = thisButton.h;
	wa = thisButton.w;
}

void ButtonVideo::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, 645, 223, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonVideo::onClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-on event", "");

}

void ButtonVideo::offClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-out event", "");
	CAppStateGamePause::menuTrans = true;
	CAppStateGamePause::setActiveMenu(CAppStateGamePause::VIDEO);
}

void ButtonVideo::onMouseOver()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse over event", "");
}

//*** Mobile Device Gesture ***
void ButtonVideo::onTouchDown()
{

	ForceFeedbackPushButton();
	currentSprite = BUTTON_SPRITE_HOVER;


}

void ButtonVideo::onTouchUp()
{

	currentSprite = BUTTON_SPRITE_OUT;
	CAppStateGamePause::menuTrans = true;
	CAppStateGamePause::setActiveMenu(CAppStateGamePause::VIDEO);

}

void ButtonVideo::onTouchMove()
{
	
}

SDL_Rect ButtonVideo::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonVideo::handleEvent(SDL_Event* e)
{

	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonVideo::onDelete()
{
	delete this;
}




// BUTTON SOUND CODE

ButtonSound::ButtonSound()
{
	buttonID = 1;
	menuID = SOUND;
}

ButtonSound::~ButtonSound()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "Button Sound Destructor", "");
}

void ButtonSound::init()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "new Button Sound created", "");
	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	w = WWIDTH * 0.45;
	h = w * 0.40;
	x = (WWIDTH - this->w) /2;
	y = Panel::GetY1() + (padding * buttonID) + ( h * buttonID);

	buttonTexture = "Sound";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void ButtonSound::init2() {}

void ButtonSound::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonSound::getShowButton()
{
	return displayButton;
}

void ButtonSound::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = thisButton.x;
	ya = 223 * currentSprite;
	ha = thisButton.h;
	wa = thisButton.w;
}

void ButtonSound::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, 645, 223, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonSound::onClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-on event", "");

}

void ButtonSound::offClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-out event", "");

	CAppStateGamePause::menuTrans = true;
	CAppStateGamePause::setActiveMenu(CAppStateGamePause::SOUND);

}

void ButtonSound::onMouseOver()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse over event", "");
}

//*** Mobile Device Gesture ***
void ButtonSound::onTouchDown()
{

	ForceFeedbackPushButton();
	currentSprite = BUTTON_SPRITE_HOVER;

}

void ButtonSound::onTouchUp()
{

	currentSprite = BUTTON_SPRITE_OUT;
	CAppStateGamePause::menuTrans = true;
	CAppStateGamePause::setActiveMenu(CAppStateGamePause::SOUND);
	
}

void ButtonSound::onTouchMove()
{
	
}

SDL_Rect ButtonSound::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonSound::handleEvent(SDL_Event* e)
{

	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonSound::onDelete()
{
	delete this;
}




// BUTTON VOLUME SX

ButtonVolumeSX::ButtonVolumeSX()
{
	buttonID = 1;
}

ButtonVolumeSX::~ButtonVolumeSX()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "Button Sound Destructor", "");
}

void ButtonVolumeSX::init()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "new Button Sound created", "");
	Panel::init();

	w = Panel::getWidth() / 20;
	h = Panel::getHeight() / 20;
	x = Panel::GetX1() + (padding);
	y = Panel::GetY1() + (h * 2);

	buttonTexture = "soundbar_sxTOT";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void ButtonVolumeSX::init2() {}

void ButtonVolumeSX::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonVolumeSX::getShowButton()
{
	return displayButton;
}

void ButtonVolumeSX::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = 300 * currentSprite;
	ya = thisButton.y;
	ha = thisButton.h;
	wa = thisButton.w;
}

void ButtonVolumeSX::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, 0, 300, 150, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonVolumeSX::onClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-on event", "");

}

void ButtonVolumeSX::offClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-out event", "");
	
	//CAppStateGamePause::menuTrans = true;
	SDL_Rect wRECT = SoundBar::getBounds();
	if (wRECT.w > 0 && CAppStateGame::volumeTuning > 0)
	{

		SoundBar::setBounds(wRECT.x, wRECT.y, wRECT.h, wRECT.w - SoundBar::getWratio());
		CAppStateGame::volumeTuning--;
		CApp::Logger.OnLog(__FILE__, __LINE__, "volumeTuning", Stringify::Int(CAppStateGame::volumeTuning));
	}
	i++;
}

void ButtonVolumeSX::onMouseOver()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse over event", "");
}

//*** Mobile Device Gesture ***
void ButtonVolumeSX::onTouchDown()
{

	ForceFeedbackPushButton();

	SDL_Rect wRECT = SoundBar::getBounds();
	if (wRECT.w > 0 && CAppStateGame::volumeTuning > 0)
	{

		SoundBar::setBounds(wRECT.x, wRECT.y, wRECT.h, wRECT.w - SoundBar::getWratio());
		CAppStateGame::volumeTuning--;
	}
	i++;
}

void ButtonVolumeSX::onTouchUp()
{
	
}

void ButtonVolumeSX::onTouchMove()
{
	
}

SDL_Rect ButtonVolumeSX::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonVolumeSX::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonVolumeSX::onDelete()
{
	delete this;
}



// BUTTON VOLUME DX

ButtonVolumeDX::ButtonVolumeDX()
{
	buttonID = 1;
}

ButtonVolumeDX::~ButtonVolumeDX()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "Button Sound Destructor", "");
}

void ButtonVolumeDX::init()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "new Button Sound created", "");
	Panel::init();

	w = Panel::getWidth() / 20;
	h = Panel::getHeight() / 20;
	x = (Panel::GetX1() + (padding)) + (Panel::getWidth() / 20) + (((Panel::getWidth() / 20) * 7));
	y = Panel::GetY1() + (h * 2);

	buttonTexture = "soundbar_dxTOT";

	
	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void ButtonVolumeDX::init2() {}

void ButtonVolumeDX::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonVolumeDX::getShowButton()
{
	return displayButton;
}

void ButtonVolumeDX::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = 300 * currentSprite;
	ya = thisButton.y;
	ha = thisButton.h;
	wa = thisButton.w;
}

void ButtonVolumeDX::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, 0, 300, 150, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonVolumeDX::onClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-on event", "");

}

void ButtonVolumeDX::offClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse click-out event", "");

	SDL_Rect wRECT = SoundBar::getBounds();
	
	if (CAppStateGame::volumeTuning < 14)
	{

		SoundBar::setBounds(wRECT.x, wRECT.y, wRECT.h, wRECT.w + SoundBar::getWratio());
		CAppStateGame::volumeTuning++;
		CApp::Logger.OnLog(__FILE__, __LINE__, "volumeTuning", Stringify::Int(CAppStateGame::volumeTuning));
	}
	
}

void ButtonVolumeDX::onMouseOver()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse over event", "");
}

//*** Mobile Device Gesture ***
void ButtonVolumeDX::onTouchDown()
{

	ForceFeedbackPushButton();

	SDL_Rect wRECT = SoundBar::getBounds();

	if (CAppStateGame::volumeTuning < 14)
	{

		SoundBar::setBounds(wRECT.x, wRECT.y, wRECT.h, wRECT.w + SoundBar::getWratio());
		CAppStateGame::volumeTuning++;
	}
}

void ButtonVolumeDX::onTouchUp()
{
	
}

void ButtonVolumeDX::onTouchMove()
{
	
}

SDL_Rect ButtonVolumeDX::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonVolumeDX::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonVolumeDX::onDelete()
{
	delete this;
}


// SOUND BAR CODE

SDL_Rect SoundBar::theBar = { 0, 0, 0, 0 };
int SoundBar::wRatio = 0;

SoundBar::SoundBar()
{
	buttonID = 1;
}

SoundBar::~SoundBar()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "soundbar Destructor", "");
}

void SoundBar::init()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "new soundbar created", "");
	Panel::init();

	
	theBar.w = ((Panel::getWidth() / 20) * CAppStateGame::volumeTuning) / 2;
	theBar.h = Panel::getHeight() / 20;
	theBar.x = Panel::GetX1() + Panel::getWidth() / 15;
	theBar.y = Panel::GetY1() + (theBar.h * 2);

	wRatio = (((Panel::getWidth() / 20) * 7) / 2) /7;
	
	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
	theSurf = SDL_GetWindowSurface(buttonWindow);
	theTexture = SDL_CreateTextureFromSurface(buttonRenderer, theSurf);

}

void SoundBar::init2() {}

void SoundBar::onLoop()
{
	
}

void SoundBar::onRender()
{
	/*
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, 0, 300, 150, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}
	*/
	
	//SDL_SetRenderDrawColor(buttonRenderer, 0x00, 0x00, 0xff, 0xff);
	SDL_RenderCopy(buttonRenderer, theTexture, NULL, &theBar);
	

}

void SoundBar::setBounds(int x, int y, int h, int w)
{
	theBar.x = x;
	theBar.y = y;
	theBar.h = h;
	theBar.w = w;
}

SDL_Rect SoundBar::getBounds()
{
	return theBar;
}


int SoundBar::getWratio()
{
	return wRatio;
}

void SoundBar::onDelete()
{
	delete this;
}



/**** LEVELS SELECTOR ****/

// BUTTON LEVELs CODE

ButtonLevel0::ButtonLevel0()
{
	SDL_Log("Level0()");
	buttonID = 0;

	LevelON = false;
}

ButtonLevel0::~ButtonLevel0()
{
	SDL_Log("~Level0()");
}

void ButtonLevel0::init()
{
	this->buttonID = 0;

	this->currentSprite = BUTTON_SPRITE_OUT;
	CCamera::CameraControl.TargetMode = TARGET_MODE_EXPLORER;

	this->w = 150;
	this->h = 175;
	this->x = 0;
	this->y = 0;

	if (CAppStateIntro::GetInstance()->GetMothershipComplete())
	{
		buttonTexture = "TAG_level_available";
		LevelON = true;
	}
	else
	{
		buttonTexture = "TAG_level_locked";
	}
	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

  
void ButtonLevel0::init2()
{
	this->buttonID = 0;

	this->currentSprite = BUTTON_SPRITE_OUT;

	this->w = 125;
	this->h = 146;
	this->x = 420;
	this->y = 90;

	//SDL_Log("Return button x: %d - y: %d", x, y);

	this->buttonTexture = "TAG_level_locked";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}


void ButtonLevel0::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonLevel0::getShowButton()
{
	return displayButton;
}

void ButtonLevel0::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	this->x = 600 + Explorer::X1;
	this->y = 1500 + Explorer::Y1;

	//SDL_Log("tag x %d y %d", x, y);

	this->xa = wa * currentSprite;
	this->ya = 0;
	this->ha = thisButton.h;
	this->wa = thisButton.w;
}

void ButtonLevel0::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
	}
	else
	{
		SDL_Log("bad renderer Level0 tag");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonLevel0::onClick()
{
	
}

void ButtonLevel0::offClick()
{
	

}

void ButtonLevel0::onMouseOver()
{
	
}

//*** Mobile Device Gesture ***
void ButtonLevel0::onTouchDown()
{

    if (SDL_HapticRumblePlay(mouseHaptic, 0.20, 80) != 0)
    {
        SDL_Log("Warning: Unable to play rumble! %s", SDL_GetError());
    }

	ForceFeedbackPushButton();

	if (this->LevelON)
	{
        SDL_Delay(300);
		SDL_Log("selected mission0");
		CAppStateGame::GetInstance()->currentMission = 0;
		CAppStateGamePause::onPause = false;
		CAppStateGamePause::menuTrans = true;
		CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::MISSION);
	}
}

void ButtonLevel0::onTouchUp()
{

}

void ButtonLevel0::onTouchMove()
{

}

SDL_Rect ButtonLevel0::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonLevel0::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonLevel0::onDelete()
{
	delete this;
}




ButtonLevel1::ButtonLevel1()
{
	SDL_Log("Level1()");

    this->buttonID = 0;


    CCamera::CameraControl.TargetMode = TARGET_MODE_EXPLORER;

    xa = 0;
    ya = 0;
    ha = 385;
    wa = 330;

    if (WHEIGHT < 1300) {
        w = wa * 0.35;
        h = ha * 0.35;

        offset.x = Explorer::getWa() * 0.07;
        offset.y = Explorer::getHa() * 0.18;
    }
    else if (WHEIGHT >= 1300 && WHEIGHT <= 2000) {
        w = wa * 0.50;
        h = ha * 0.50;

        offset.x = Explorer::getWa() * 0.10;
        offset.y = Explorer::getHa() * 0.18;
    }
    else if (WHEIGHT > 2000) {
        w = wa * 0.80;
        h = ha * 0.80;

        offset.x = Explorer::getWa() * 0.15;
        offset.y = Explorer::getHa() * 0.18;
    }




    buttonTexture = "stage_1";

    this->LevelON = true;

    this->buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    this->buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();


}

ButtonLevel1::~ButtonLevel1()
{
	SDL_Log("~Level1()");
}

void ButtonLevel1::init()
{
    SDL_Log("Level1 avail");

    currentSprite = BUTTON_SPRITE_OUT;
}

void ButtonLevel1::init2()
{

    currentSprite = BUTTON_SPRITE_UP;

}


void ButtonLevel1::showButton(bool on_off)
{
	this->displayButton = on_off;
}

bool ButtonLevel1::getShowButton()
{
	return displayButton;
}

void ButtonLevel1::onLoop()
{

    if (!CAppStateIntro::GetInstance()->stage_complete[1]) currentSprite = BUTTON_SPRITE_OUT;
    else currentSprite = BUTTON_SPRITE_UP;

    SDL_Rect thisButton;
    thisButton = getBounds();

	xa = wa * currentSprite;
	ya = 0;

	x = offset.x + Explorer::X1;
	y = offset.y + Explorer::Y1;

	//SDL_Log("currentSprite: %d - xa: %d - wa: %d", currentSprite, xa, wa);

}

void ButtonLevel1::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}
}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonLevel1::onClick()
{
	
}

void ButtonLevel1::offClick()
{
	
}

void ButtonLevel1::onMouseOver()
{
	
}

//*** Mobile Device Gesture ***
void ButtonLevel1::onTouchDown()
{
	ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;

	if (this->LevelON)
	{
        SDL_Delay(300);
        SDL_Log("selected mission1");
		CAppStateGame::GetInstance()->currentMission = 1;
		CAppStateGamePause::onPause = false;
		CAppStateGamePause::menuTrans = true;
		CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::MISSION);
	}
}

void ButtonLevel1::onTouchUp()
{

    currentSprite = BUTTON_SPRITE_OUT;

}

void ButtonLevel1::onTouchMove()
{
	
}

SDL_Rect ButtonLevel1::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonLevel1::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		this->tX = e->tfinger.x * WWIDTH;
		this->tY = e->tfinger.y * WHEIGHT;
		this->tXm = e->tfinger.dx * WWIDTH;
		this->tYm = e->tfinger.dy * WHEIGHT;
		
		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (this->tX < thisButton.x)
		{
			hover = false;
		}
		else if (this->tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (this->tY < thisButton.y)
		{
			hover = false;
		}
		else if (this->tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				//currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				//currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				//currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonLevel1::onDelete()
{
	delete this;
}



ButtonLevel2::ButtonLevel2()
{
	SDL_Log("Level2()");
	buttonID = 2;
    Panel::init();

    xa = 0;
    ya = 0;
    ha = 385;
    wa = 330;

    if (WHEIGHT < 1300) {
        w = wa * 0.35;
        h = ha * 0.35;

        offset.x = Explorer::getWa() * 0.85;
        offset.y = Explorer::getHa() * 0.20;
    }
    else if (WHEIGHT >= 1300 && WHEIGHT <= 2000) {
        w = wa * 0.50;
        h = ha * 0.50;

        offset.x = Explorer::getWa() * 0.85;
        offset.y = Explorer::getHa() * 0.20;
    }
    else if (WHEIGHT > 2000) {
        w = wa * 0.80;
        h = ha * 0.80;

        offset.x = Explorer::getWa() * 0.85;
        offset.y = Explorer::getHa() * 0.20;
    }

    buttonTexture = "stage_2";
    this->LevelON = true;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
}

ButtonLevel2::~ButtonLevel2()
{
	SDL_Log("~Level2()");
}

void ButtonLevel2::init()
{
    currentSprite = BUTTON_SPRITE_OUT;
}

void ButtonLevel2::init2()
{
    currentSprite = BUTTON_SPRITE_UP;
}


void ButtonLevel2::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonLevel2::getShowButton()
{
	return displayButton;
}

void ButtonLevel2::onLoop()
{

    if (!CAppStateIntro::GetInstance()->stage_complete[2]) currentSprite = BUTTON_SPRITE_OUT;
    else currentSprite = BUTTON_SPRITE_UP;

    this->xa = wa * currentSprite;
    this->ya = 0;


    this->x = offset.x + Explorer::X1;
    this->y = offset.y + Explorer::Y1;

    SDL_Rect thisButton;
    thisButton = getBounds();
}

void ButtonLevel2::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonLevel2::onClick()
{
	
}

void ButtonLevel2::offClick()
{
	
}

void ButtonLevel2::onMouseOver()
{
	
}

//*** Mobile Device Gesture ***
void ButtonLevel2::onTouchDown()
{
	ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;

	if (this->LevelON)
	{
        SDL_Delay(300);
		SDL_Log("selected mission2");
		CAppStateGame::GetInstance()->currentMission = 2;
		CAppStateGamePause::GetInstance()->onPause = false;
		CAppStateGamePause::GetInstance()->menuTrans = true;
		CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::MISSION);
	}
}

void ButtonLevel2::onTouchUp()
{

    currentSprite = BUTTON_SPRITE_OUT;

}

void ButtonLevel2::onTouchMove()
{

}

SDL_Rect ButtonLevel2::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonLevel2::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				//currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				//currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				//currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonLevel2::onDelete()
{
	delete this;
}



ButtonLevel3::ButtonLevel3()
{
	SDL_Log("Level3()");
	buttonID = 2;

    Panel::init();

    xa = 0;
    ya = 0;
    ha = 385;
    wa = 330;

    if (WHEIGHT < 1300) {
        w = wa * 0.35;
        h = ha * 0.35;

        offset.x = Explorer::getWa() * 0.75;
        offset.y = Explorer::getHa() * 0.55;
    }
    else if (WHEIGHT >= 1300 && WHEIGHT <= 2000) {
        w = wa * 0.50;
        h = ha * 0.50;

        offset.x = Explorer::getWa() * 0.75;
        offset.y = Explorer::getHa() * 0.55;
    }
    else if (WHEIGHT > 2000) {
        w = wa * 0.80;
        h = ha * 0.80;

        offset.x = Explorer::getWa() * 0.75;
        offset.y = Explorer::getHa() * 0.55;
    }


    if (CAppStateIntro::GetInstance()->GetMothershipComplete())
    {
        buttonTexture = "stage_3";
        this->LevelON = true;
    }
    else
    {
        SDL_Log("mm tag red");
        buttonTexture = "TAG_level_locked";
    }
    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

ButtonLevel3::~ButtonLevel3()
{
	SDL_Log("~Level3()");
}

void ButtonLevel3::init()
{
    currentSprite = BUTTON_SPRITE_OUT;
}

void ButtonLevel3::init2()
{
    currentSprite = BUTTON_SPRITE_UP;
}


void ButtonLevel3::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonLevel3::getShowButton()
{
	return displayButton;
}

void ButtonLevel3::onLoop()
{
    if (!CAppStateIntro::GetInstance()->stage_complete[3]) currentSprite = BUTTON_SPRITE_OUT;
    else currentSprite = BUTTON_SPRITE_UP;

    this->xa = wa * currentSprite;
    this->ya = 0;

    this->x = offset.x + Explorer::X1;
    this->y = offset.y + Explorer::Y1;

    SDL_Rect thisButton;
    thisButton = getBounds();
}

void ButtonLevel3::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonLevel3::onClick()
{
	
}

void ButtonLevel3::offClick()
{
	
}

void ButtonLevel3::onMouseOver()
{
	
}

//*** Mobile Device Gesture ***
void ButtonLevel3::onTouchDown()
{

	ForceFeedbackPushButton();

	currentSprite = BUTTON_SPRITE_HOVER;

	if (this->LevelON)
	{
        SDL_Delay(300);
		SDL_Log("selected mission3");
		CAppStateGame::GetInstance()->currentMission = 3;
		CAppStateGamePause::GetInstance()->onPause = false;
		CAppStateGamePause::GetInstance()->menuTrans = true;
		CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->MISSION);
	}
}

void ButtonLevel3::onTouchUp()
{

    currentSprite = BUTTON_SPRITE_OUT;

}

void ButtonLevel3::onTouchMove()
{

}

SDL_Rect ButtonLevel3::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonLevel3::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				//currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				//currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				//currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonLevel3::onDelete()
{
	delete this;
}



ButtonLevel4::ButtonLevel4()
{
	SDL_Log("Level4()");
	buttonID = 2;

    Panel::init();

    xa = 0;
    ya = 0;
    ha = 385;
    wa = 330;

    if (WHEIGHT < 1300) {
        w = wa * 0.35;
        h = ha * 0.35;

        offset.x = Explorer::getWa() * 0.20;
        offset.y = Explorer::getHa() * 0.73;
    }
    else if (WHEIGHT >= 1300 && WHEIGHT <= 2000) {
        w = wa * 0.50;
        h = ha * 0.50;

        offset.x = Explorer::getWa() * 0.20;
        offset.y = Explorer::getHa() * 0.73;
    }
    else if (WHEIGHT > 2000) {
        w = wa * 0.80;
        h = ha * 0.80;

        offset.x = Explorer::getWa() * 0.20;
        offset.y = Explorer::getHa() * 0.73;
    }

    if (CAppStateIntro::GetInstance()->GetMothershipComplete())
    {
        buttonTexture = "stage_4";
        this->LevelON = true;
    }
    else
    {
        SDL_Log("mm tag red");
        buttonTexture = "TAG_level_locked";
    }

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

ButtonLevel4::~ButtonLevel4()
{
	SDL_Log("~Level4()");
}

void ButtonLevel4::init()
{
    currentSprite = BUTTON_SPRITE_OUT;
}

void ButtonLevel4::init2()
{
    currentSprite = BUTTON_SPRITE_UP;
}


void ButtonLevel4::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonLevel4::getShowButton()
{
	return displayButton;
}

void ButtonLevel4::onLoop()
{
    if (!CAppStateIntro::GetInstance()->stage_complete[4]) currentSprite = BUTTON_SPRITE_OUT;
    else currentSprite = BUTTON_SPRITE_UP;

    this->xa = wa * currentSprite;
    this->ya = 0;

    this->x = offset.x + Explorer::X1;
    this->y = offset.y + Explorer::Y1;

    SDL_Rect thisButton;
    thisButton = getBounds();
}

void ButtonLevel4::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonLevel4::onClick()
{
	
}

void ButtonLevel4::offClick()
{
	
}

void ButtonLevel4::onMouseOver()
{
	
}

//*** Mobile Device Gesture ***
void ButtonLevel4::onTouchDown()
{
	ForceFeedbackPushButton();

	currentSprite = BUTTON_SPRITE_HOVER;

	if (this->LevelON)
	{
        SDL_Delay(300);
		SDL_Log("selected mission4");
		CAppStateGame::GetInstance()->currentMission = 4;
		CAppStateGamePause::GetInstance()->onPause = false;
		CAppStateGamePause::GetInstance()->menuTrans = true;
		CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->MISSION);
	}
}

void ButtonLevel4::onTouchUp()
{

    currentSprite = BUTTON_SPRITE_OUT;

}

void ButtonLevel4::onTouchMove()
{

}

SDL_Rect ButtonLevel4::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonLevel4::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				//currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				//currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				//currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonLevel4::onDelete()
{
	delete this;
}



// FINAL LEVEL!

ButtonLevelX::ButtonLevelX()
{
	SDL_Log("LevelX()");

    Panel::init();

    this->buttonID = 666;

    xa = 0;
    ya = 0;
    ha = 385;
    wa = 330;

    if (WHEIGHT < 1300) {
        w = wa * 0.35;
        h = ha * 0.35;

        offset.x = (Explorer::getWa() / 2) - (w / 2);
        offset.y = (Explorer::getHa() / 2) - (h / 2);
    }
    else if (WHEIGHT >= 1300 && WHEIGHT <= 2000) {
        w = wa * 0.50;
        h = ha * 0.50;

        offset.x = (Explorer::getWa() / 2) - (w / 2);
        offset.y = (Explorer::getHa() / 2) - (h / 2);
    }
    else if (WHEIGHT > 2000) {
        w = wa * 0.80;
        h = ha * 0.80;

        offset.x = (Explorer::getWa() / 2) - (w / 2);
        offset.y = (Explorer::getHa() / 2) - (h / 2);
    }

    this->buttonTexture = "stage_final";


    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

ButtonLevelX::~ButtonLevelX()
{
	SDL_Log("~LevelX()");
}

void ButtonLevelX::init()
{
    SDL_Log("Final Level avail");
    LevelON = true;
    currentSprite = BUTTON_SPRITE_OUT;
}

void ButtonLevelX::init2()
{
    LevelON = false;
    SDL_Log("Final level denied");
    currentSprite = BUTTON_SPRITE_DOWN;
}


void ButtonLevelX::showButton(bool on_off)
{
	displayButton = on_off;
}

bool ButtonLevelX::getShowButton()
{
	return displayButton;
}

void ButtonLevelX::onLoop()
{

    if(CAppStateIntro::GetInstance()->GetFinalMission()) currentSprite = BUTTON_SPRITE_OUT;
    else currentSprite = BUTTON_SPRITE_DOWN;

    SDL_Rect thisButton;
    thisButton = getBounds();

    xa = wa * currentSprite;
    ya = 0;

    x = offset.x + Explorer::X1;
    y = offset.y + Explorer::Y1;


}

void ButtonLevelX::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void ButtonLevelX::onClick()
{
	

}

void ButtonLevelX::offClick()
{
	

}

void ButtonLevelX::onMouseOver()
{
	
}

//*** Mobile Device Gesture ***
void ButtonLevelX::onTouchDown()
{
	ForceFeedbackPushButton();

	currentSprite = BUTTON_SPRITE_HOVER;

	if (LevelON)
	{
        SDL_Delay(300);
		SDL_Log("let's play Final Mission!");
		CAppStateGame::GetInstance()->currentMission = 666;
		CAppStateGamePause::GetInstance()->onPause = false;
		CAppStateGamePause::GetInstance()->menuTrans = true;
		CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->NEWGAME);
	}
}

void ButtonLevelX::onTouchUp()
{
	currentSprite = BUTTON_SPRITE_OUT;
}

void ButtonLevelX::onTouchMove()
{

}

SDL_Rect ButtonLevelX::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void ButtonLevelX::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			//currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				//currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				//currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				//currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonLevelX::onDelete()
{
	delete this;
}


// Button Mission Levels

int	 Mission0::missionID = 0;
bool Mission0::LevelON = false;

Mission0::Mission0()
{


    //buttonID = 2;

    wa = 306;
    ha = 401;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
        x = (WWIDTH / 2) - w - (w / 2);
        y = (WHEIGHT / 2) - (h / 2) - h;
    }
    else if (WHEIGHT > 1300 && WHEIGHT <= 2000) {
        w = wa * 0.82;
        h = ha * 0.82;
        x = (WWIDTH / 2) - w - (w / 2) - padding / 2;
        y = (WHEIGHT / 2) - (h / 2) - h - padding / 2;
    }
    else if (WHEIGHT > 2000) {
        w = wa;
        h = ha;
        x = (WWIDTH / 2) - w - (w / 2) - padding;
        y = (WHEIGHT / 2) - (h / 2) - h - padding;
    }



    xa = 0;
    ya = 0;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

    buttonTexture = "Level_1";

}

Mission0::~Mission0()
{
    SDL_Log("~Mission0()");
}

void Mission0::init()
{

    currentSprite = BUTTON_SPRITE_OUT;

}

void Mission0::init2()
{
    currentSprite = BUTTON_SPRITE_DOWN;

}


void Mission0::showButton(bool on_off)
{
    displayButton = on_off;
}

bool Mission0::getShowButton()
{
    return displayButton;
}

void Mission0::onLoop()
{
    SDL_Rect thisButton;
    thisButton = getBounds();


    xa = wa * currentSprite;
    ya = 0;
    //ha = thisButton.h;
    //wa = thisButton.w;
}

void Mission0::onRender()
{
    if (buttonRenderer)
    {
        TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
    }
    else
    {
        SDL_Log("bad renderer Level0 tag");
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void Mission0::onClick()
{

}

void Mission0::offClick()
{


}

void Mission0::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Mission0::onTouchDown()
{

    ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;

}

void Mission0::onTouchUp()
{


    //SDL_Delay(500);




    currentSprite = BUTTON_SPRITE_OUT;
    SDL_Log("let's play mission %d", missionID);
    CAppStateGame::GetInstance()->currentLevel = missionID;
    CAppStateGamePause::GetInstance()->onPause = false;
    CAppStateGamePause::GetInstance()->menuTrans = true;

    CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->NEWGAME);


}

void Mission0::onTouchMove()
{


    currentSprite = BUTTON_SPRITE_HOVER;


}

SDL_Rect Mission0::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void Mission0::handleEvent(SDL_Event* e)
{

    //SDL_Log("Mission0::handleEvent()");

    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][missionID]) {

        if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION) {
            int tX, tY;
            tX = e->tfinger.x * WWIDTH;
            tY = e->tfinger.y * WHEIGHT;

            bool hover = true;
            SDL_Rect thisButton;
            thisButton = getBounds();
            if (tX < thisButton.x) {
                hover = false;
            } else if (tX > thisButton.x + thisButton.w) {
                hover = false;
            }
            if (tY < thisButton.y) {
                hover = false;
            } else if (tY > thisButton.y + thisButton.h) {
                hover = false;
            }

            if (!hover) {
                currentSprite = BUTTON_SPRITE_OUT;
            } else {
                switch (e->type) {
                    case SDL_FINGERMOTION:

                        onTouchMove();
                        break;

                    case SDL_FINGERDOWN:

                        onTouchDown();
                        break;

                    case SDL_FINGERUP:

                        onTouchUp();
                        break;
                }
            }
        }
    }

}

void Mission0::onDelete()
{
    delete this;
}

// Button Mission Levels

int	 Mission1::missionID = 1;
bool Mission1::LevelON = false;

Mission1::Mission1()
{
    SDL_Log("Mission1()");

    buttonID = 2;

	wa = 306;
	ha = 401;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
        x = (WWIDTH / 2) - (w / 2);
        y = (WHEIGHT / 2) - (h / 2) - h;
    }
    else if (WHEIGHT > 1300 && WHEIGHT <= 2000) {
        w = wa * 0.82;
        h = ha * 0.82;
        x = (WWIDTH / 2) - (w / 2);
        y = (WHEIGHT / 2) - (h / 2) - h - padding / 2;
    }
    else if (WHEIGHT > 2000) {
        w = wa;
        h = ha;
        x = (WWIDTH / 2) - (w / 2);
        y = (WHEIGHT / 2) - (h / 2) - h - padding;
    }

	xa = 0;
    ya = 0;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

    buttonTexture = "Level_2";

}

Mission1::~Mission1()
{
    SDL_Log("~Mission1()");
}

void Mission1::init()
{

    currentSprite = BUTTON_SPRITE_OUT;

}

void Mission1::init2()
{

    currentSprite = BUTTON_SPRITE_DOWN;

}


void Mission1::showButton(bool on_off)
{
    displayButton = on_off;
}

bool Mission1::getShowButton()
{
    return displayButton;
}

void Mission1::onLoop()
{
    SDL_Rect thisButton;
    thisButton = getBounds();


    xa = wa * currentSprite;
    ya = 0;
    //ha = thisButton.h;
    //wa = thisButton.w;
}

void Mission1::onRender()
{
    if (buttonRenderer)
    {
        TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
    }
    else
    {
        SDL_Log("bad renderer Level0 tag");
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void Mission1::onClick()
{

}

void Mission1::offClick()
{


}

void Mission1::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Mission1::onTouchDown()
{

    currentSprite = BUTTON_SPRITE_HOVER;


}

void Mission1::onTouchUp()
{


    currentSprite = BUTTON_SPRITE_OUT;
	SDL_Log("let's play mission %d", missionID);
    CAppStateGame::GetInstance()->currentLevel = missionID;
    CAppStateGamePause::GetInstance()->onPause = false;
    CAppStateGamePause::GetInstance()->menuTrans = true;
    CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->NEWGAME);



}

void Mission1::onTouchMove()
{

    currentSprite = BUTTON_SPRITE_HOVER;


}

SDL_Rect Mission1::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void Mission1::handleEvent(SDL_Event* e)
{

    //SDL_Log("Mission1::handleEvent()");

    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][missionID])
    {

        if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
        {
            int tX, tY;
            tX = e->tfinger.x * WWIDTH;
            tY = e->tfinger.y * WHEIGHT;

            bool hover = true;
            SDL_Rect thisButton;
            thisButton = getBounds();
            if (tX < thisButton.x)
            {
                hover = false;
            }
            else if (tX > thisButton.x + thisButton.w)
            {
                hover = false;
            }
            if (tY < thisButton.y)
            {
                hover = false;
            }
            else if (tY > thisButton.y + thisButton.h)
            {
                hover = false;
            }

            if (!hover)
            {
                currentSprite = BUTTON_SPRITE_OUT;
            }
            else
            {
                switch (e->type)
                {
                    case SDL_FINGERMOTION:
                        //currentSprite = BUTTON_SPRITE_HOVER;
                        onTouchMove();
                        break;
                    case SDL_FINGERDOWN:
                        //currentSprite = BUTTON_SPRITE_DOWN;
                        onTouchDown();
                        break;
                    case SDL_FINGERUP:
                        //currentSprite = BUTTON_SPRITE_OUT;
                        onTouchUp();
                        break;
                }
            }
        }
    }

}

void Mission1::onDelete()
{
    delete this;
}

// Button Mission Levels

int	 Mission2::missionID = 2;
bool Mission2::LevelON = false;

Mission2::Mission2()
{
    SDL_Log("Mission2()");
    buttonID = 2;

    buttonTexture = "Level_3";

	wa = 306;
	ha = 401;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
        x = (WWIDTH / 2) + (w / 2);
        y = (WHEIGHT / 2) - (h / 2) - h;
    }
    else if (WHEIGHT > 1300 && WHEIGHT <= 2000) {
        w = wa * 0.82;
        h = ha * 0.82;
        x = (WWIDTH / 2) + (w / 2) + padding / 2;
        y = (WHEIGHT / 2) - (h / 2) - h - padding / 2;
    }
    else if (WHEIGHT > 2000) {
        w = wa;
        h = ha;
        x = (WWIDTH / 2) + (w / 2) + padding;
        y = (WHEIGHT / 2) - (h / 2) - h - padding;
    }

    xa = 0;
    ya = 0;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
}

Mission2::~Mission2()
{
    SDL_Log("~Mission2()");
}

void Mission2::init()
{
    currentSprite = BUTTON_SPRITE_OUT;
}

void Mission2::init2()
{
    currentSprite = BUTTON_SPRITE_DOWN;
}


void Mission2::showButton(bool on_off)
{
    displayButton = on_off;
}

bool Mission2::getShowButton()
{
    return displayButton;
}

void Mission2::onLoop()
{
    SDL_Rect thisButton;
    thisButton = getBounds();


    xa = wa * currentSprite;
    ya = 0;
    //ha = thisButton.h;
    //wa = thisButton.w;
}

void Mission2::onRender()
{
    if (buttonRenderer)
    {
        TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
    }
    else
    {
        SDL_Log("bad renderer Level0 tag");
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void Mission2::onClick()
{

}

void Mission2::offClick()
{


}

void Mission2::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Mission2::onTouchDown()
{
    ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;

}

void Mission2::onTouchUp()
{


    currentSprite = BUTTON_SPRITE_OUT;
	//CAppStateGame::GetInstance()->Call_Interstitial();
    SDL_Log("let's play mission %d", missionID);
    CAppStateGame::GetInstance()->currentLevel = missionID;
    CAppStateGamePause::GetInstance()->onPause = false;
    CAppStateGamePause::GetInstance()->menuTrans = true;
    CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->NEWGAME);

}

void Mission2::onTouchMove()
{


    currentSprite = BUTTON_SPRITE_HOVER;

}

SDL_Rect Mission2::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void Mission2::handleEvent(SDL_Event* e)
{

    //SDL_Log("Mission2::handleEvent()");

    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][missionID]) {

        if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION) {
            int tX, tY;
            tX = e->tfinger.x * WWIDTH;
            tY = e->tfinger.y * WHEIGHT;

            bool hover = true;
            SDL_Rect thisButton;
            thisButton = getBounds();
            if (tX < thisButton.x) {
                hover = false;
            } else if (tX > thisButton.x + thisButton.w) {
                hover = false;
            }
            if (tY < thisButton.y) {
                hover = false;
            } else if (tY > thisButton.y + thisButton.h) {
                hover = false;
            }

            if (!hover) {
                currentSprite = BUTTON_SPRITE_OUT;
            } else {
                switch (e->type) {
                    case SDL_FINGERMOTION:
                        //currentSprite = BUTTON_SPRITE_HOVER;
                        onTouchMove();
                        break;
                    case SDL_FINGERDOWN:
                        //currentSprite = BUTTON_SPRITE_DOWN;
                        onTouchDown();
                        break;
                    case SDL_FINGERUP:
                        //currentSprite = BUTTON_SPRITE_OUT;
                        onTouchUp();
                        break;
                }
            }
        }
    }

}

void Mission2::onDelete()
{
    delete this;
}

// Button Mission Levels

int	 Mission3::missionID = 3;
bool Mission3::LevelON = false;

Mission3::Mission3()
{
    SDL_Log("Mission3()");
    buttonID = 2;

    buttonTexture = "Level_4";

	wa = 306;
	ha = 401;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
        x = (WWIDTH / 2) - (w / 2) - w;
        y = (WHEIGHT / 2) - (h / 2);
    }
    else if (WHEIGHT > 1300 && WHEIGHT <= 2000) {
        w = wa * 0.82;
        h = ha * 0.82;
        x = (WWIDTH / 2) - (w / 2) - w - padding / 2;
        y = (WHEIGHT / 2) - (h / 2);
    }
    else if (WHEIGHT > 2000) {
        w = wa;
        h = ha;
        x = (WWIDTH / 2) - (w / 2) - w - padding;
        y = (WHEIGHT / 2) - (h / 2);
    }

    xa = 0;
    ya = 0;

    //y = (WHEIGHT * 0.25) + h * 0;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
}

Mission3::~Mission3()
{
    SDL_Log("~Mission3()");
}

void Mission3::init()
{
    currentSprite = BUTTON_SPRITE_OUT;
}

void Mission3::init2()
{
    currentSprite = BUTTON_SPRITE_DOWN;
}


void Mission3::showButton(bool on_off)
{
    displayButton = on_off;
}

bool Mission3::getShowButton()
{
    return displayButton;
}

void Mission3::onLoop()
{
    SDL_Rect thisButton;
    thisButton = getBounds();


    xa = wa * currentSprite;
    ya = 0;
    //ha = thisButton.h;
    //wa = thisButton.w;
}

void Mission3::onRender()
{
    if (buttonRenderer)
    {
        TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
    }
    else
    {
        SDL_Log("bad renderer Level0 tag");
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void Mission3::onClick()
{

}

void Mission3::offClick()
{


}

void Mission3::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Mission3::onTouchDown()
{

    ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;



}

void Mission3::onTouchUp()
{


    currentSprite = BUTTON_SPRITE_OUT;
	SDL_Log("let's play mission %d", missionID);
    CAppStateGame::GetInstance()->currentLevel = missionID;
    CAppStateGamePause::GetInstance()->onPause = false;
    CAppStateGamePause::GetInstance()->menuTrans = true;
    CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->NEWGAME);

}

void Mission3::onTouchMove()
{
    currentSprite = BUTTON_SPRITE_HOVER;

}

SDL_Rect Mission3::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void Mission3::handleEvent(SDL_Event* e)
{

    //SDL_Log("Mission3::handleEvent()");

    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][missionID]) {

        if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION) {
            int tX, tY;
            tX = e->tfinger.x * WWIDTH;
            tY = e->tfinger.y * WHEIGHT;

            bool hover = true;
            SDL_Rect thisButton;
            thisButton = getBounds();
            if (tX < thisButton.x) {
                hover = false;
            } else if (tX > thisButton.x + thisButton.w) {
                hover = false;
            }
            if (tY < thisButton.y) {
                hover = false;
            } else if (tY > thisButton.y + thisButton.h) {
                hover = false;
            }

            if (!hover) {
                currentSprite = BUTTON_SPRITE_OUT;
            } else {
                switch (e->type) {
                    case SDL_FINGERMOTION:

                        onTouchMove();
                        break;

                    case SDL_FINGERDOWN:

                        onTouchDown();
                        break;

                    case SDL_FINGERUP:

                        onTouchUp();
                        break;
                }
            }
        }
    }

}

void Mission3::onDelete()
{
    delete this;
}

// Button Mission Levels

int	 Mission4::missionID = 4;
bool Mission4::LevelON = false;

Mission4::Mission4()
{
    SDL_Log("Mission4()");
    buttonID = 2;

    buttonTexture = "Level_5";

	wa = 306;
	ha = 401;

	if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
        x = (WWIDTH / 2) - (w / 2);
        y = (WHEIGHT / 2) - (h / 2);
    }
    else if (WHEIGHT > 1300 && WHEIGHT <= 2000) {
        w = wa * 0.82;
        h = ha * 0.82;
        x = (WWIDTH / 2) - (w / 2);
        y = (WHEIGHT / 2) - (h / 2);
    }
    else if (WHEIGHT > 2000) {
        w = wa;
        h = ha;
        x = (WWIDTH / 2) - (w / 2);
        y = (WHEIGHT / 2) - (h / 2);
    }

    xa = 0;
    ya = 0;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
}

Mission4::~Mission4()
{
    SDL_Log("~Mission4()");
}

void Mission4::init()
{
    currentSprite = BUTTON_SPRITE_OUT;
}

void Mission4::init2()
{
    currentSprite = BUTTON_SPRITE_DOWN;
}


void Mission4::showButton(bool on_off)
{
    displayButton = on_off;
}

bool Mission4::getShowButton()
{
    return displayButton;
}

void Mission4::onLoop()
{
    SDL_Rect thisButton;
    thisButton = getBounds();


    xa = wa * currentSprite;
    ya = 0;
    //ha = thisButton.h;
    //wa = thisButton.w;
}

void Mission4::onRender()
{
    if (buttonRenderer)
    {
        TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
    }
    else
    {
        SDL_Log("bad renderer Level4 tag");
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void Mission4::onClick()
{

}

void Mission4::offClick()
{


}

void Mission4::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Mission4::onTouchDown()
{

    ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;

}

void Mission4::onTouchUp()
{


    currentSprite = BUTTON_SPRITE_OUT;
	SDL_Log("let's play mission %d", missionID);
    CAppStateGame::GetInstance()->currentLevel = missionID;
    CAppStateGamePause::GetInstance()->onPause = false;
    CAppStateGamePause::GetInstance()->menuTrans = true;
    CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->NEWGAME);

}

void Mission4::onTouchMove()
{


    currentSprite = BUTTON_SPRITE_HOVER;

}

SDL_Rect Mission4::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void Mission4::handleEvent(SDL_Event* e)
{

    //SDL_Log("Mission4::handleEvent()");

    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][missionID]) {

        if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION) {
            int tX, tY;
            tX = e->tfinger.x * WWIDTH;
            tY = e->tfinger.y * WHEIGHT;

            bool hover = true;
            SDL_Rect thisButton;
            thisButton = getBounds();
            if (tX < thisButton.x) {
                hover = false;
            } else if (tX > thisButton.x + thisButton.w) {
                hover = false;
            }
            if (tY < thisButton.y) {
                hover = false;
            } else if (tY > thisButton.y + thisButton.h) {
                hover = false;
            }

            if (!hover) {
                currentSprite = BUTTON_SPRITE_OUT;
            } else {
                switch (e->type) {
                    case SDL_FINGERMOTION:
                        //currentSprite = BUTTON_SPRITE_HOVER;
                        onTouchMove();
                        break;
                    case SDL_FINGERDOWN:
                        //currentSprite = BUTTON_SPRITE_DOWN;
                        onTouchDown();
                        break;
                    case SDL_FINGERUP:
                        //currentSprite = BUTTON_SPRITE_OUT;
                        onTouchUp();
                        break;
                }
            }
        }
    }

}

void Mission4::onDelete()
{
    delete this;
}


// Button Mission Levels

int	 Mission5::missionID = 5;
bool Mission5::LevelON = false;

Mission5::Mission5()
{
    SDL_Log("Mission5()");
    buttonID = 2;

    buttonTexture = "Level_6";

	wa = 306;
	ha = 401;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
        x = (WWIDTH / 2) + (w / 2);
        y = (WHEIGHT / 2) - (h / 2);
    }
    else if (WHEIGHT > 1300 && WHEIGHT <= 2000) {
        w = wa * 0.82;
        h = ha * 0.82;
        x = (WWIDTH / 2) + (w / 2) + padding / 2;
        y = (WHEIGHT / 2) - (h / 2);
    }
    else if (WHEIGHT > 2000) {
        w = wa;
        h = ha;
        x = (WWIDTH / 2) + (w / 2) + padding;
        y = (WHEIGHT / 2) - (h / 2);
    }

	xa = 0;
    ya = 0;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
}

Mission5::~Mission5()
{
    SDL_Log("~Mission5()");
}

void Mission5::init()
{
    currentSprite = BUTTON_SPRITE_OUT;
}

void Mission5::init2()
{
    currentSprite = BUTTON_SPRITE_DOWN;
}


void Mission5::showButton(bool on_off)
{
    displayButton = on_off;
}

bool Mission5::getShowButton()
{
    return displayButton;
}

void Mission5::onLoop()
{
    SDL_Rect thisButton;
    thisButton = getBounds();


    xa = wa * currentSprite;
    ya = 0;
    //ha = thisButton.h;
    //wa = thisButton.w;
}

void Mission5::onRender()
{
    if (buttonRenderer)
    {
        TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
    }
    else
    {
        SDL_Log("bad renderer Level6 tag");
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void Mission5::onClick()
{

}

void Mission5::offClick()
{


}

void Mission5::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Mission5::onTouchDown()
{

    ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;

}

void Mission5::onTouchUp()
{


    currentSprite = BUTTON_SPRITE_OUT;
    SDL_Log("let's play mission %d", missionID);
    CAppStateGame::GetInstance()->currentLevel = missionID;
    CAppStateGamePause::GetInstance()->onPause = false;
    CAppStateGamePause::GetInstance()->menuTrans = true;
    CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->NEWGAME);

}

void Mission5::onTouchMove()
{


    currentSprite = BUTTON_SPRITE_HOVER;

}

SDL_Rect Mission5::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void Mission5::handleEvent(SDL_Event* e)
{

    //SDL_Log("Mission5::handleEvent()");

    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][missionID]) {

        if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION) {
            int tX, tY;
            tX = e->tfinger.x * WWIDTH;
            tY = e->tfinger.y * WHEIGHT;

            bool hover = true;
            SDL_Rect thisButton;
            thisButton = getBounds();
            if (tX < thisButton.x) {
                hover = false;
            } else if (tX > thisButton.x + thisButton.w) {
                hover = false;
            }
            if (tY < thisButton.y) {
                hover = false;
            } else if (tY > thisButton.y + thisButton.h) {
                hover = false;
            }

            if (!hover) {
                currentSprite = BUTTON_SPRITE_OUT;
            } else {
                switch (e->type) {
                    case SDL_FINGERMOTION:
                        //currentSprite = BUTTON_SPRITE_HOVER;
                        onTouchMove();
                        break;
                    case SDL_FINGERDOWN:
                        //currentSprite = BUTTON_SPRITE_DOWN;
                        onTouchDown();
                        break;
                    case SDL_FINGERUP:
                        //currentSprite = BUTTON_SPRITE_OUT;
                        onTouchUp();
                        break;
                }
            }
        }
    }

}

void Mission5::onDelete()
{
    delete this;
}




// Button Mission Levels

int	 Mission6::missionID = 6;
bool Mission6::LevelON = false;

Mission6::Mission6()
{
    SDL_Log("Mission6()");
    buttonID = 2;

    buttonTexture = "Level_7";

    wa = 306;
    ha = 401;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
        x = (WWIDTH / 2) - (w / 2) - w;
        y = (WHEIGHT / 2) + (h / 2);
    }
    else if (WHEIGHT > 1300 && WHEIGHT <= 2000) {
        w = wa * 0.82;
        h = ha * 0.82;
        x = (WWIDTH / 2) - (w / 2) - w - padding / 2;
        y = (WHEIGHT / 2) + (h / 2) + padding / 2;
    }
    else if (WHEIGHT > 2000) {
        w = wa;
        h = ha;
        x = (WWIDTH / 2) - (w / 2) - w - padding;
        y = (WHEIGHT / 2) + (h / 2) + padding;
    }

    xa = 0;
    ya = 0;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
}

Mission6::~Mission6()
{
    SDL_Log("~Mission6()");
}

void Mission6::init()
{
    currentSprite = BUTTON_SPRITE_OUT;
}

void Mission6::init2()
{
    currentSprite = BUTTON_SPRITE_DOWN;
}


void Mission6::showButton(bool on_off)
{
    displayButton = on_off;
}

bool Mission6::getShowButton()
{
    return displayButton;
}

void Mission6::onLoop()
{
    SDL_Rect thisButton;
    thisButton = getBounds();


    xa = wa * currentSprite;
    ya = 0;
    //ha = thisButton.h;
    //wa = thisButton.w;
}

void Mission6::onRender()
{
    if (buttonRenderer)
    {
        TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
    }
    else
    {
        SDL_Log("bad renderer Level7 tag");
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void Mission6::onClick()
{

}

void Mission6::offClick()
{


}

void Mission6::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Mission6::onTouchDown()
{

    ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;

}

void Mission6::onTouchUp()
{


    currentSprite = BUTTON_SPRITE_OUT;
	SDL_Log("let's play mission %d", missionID);
    CAppStateGame::GetInstance()->currentLevel = missionID;
    CAppStateGamePause::GetInstance()->onPause = false;
    CAppStateGamePause::GetInstance()->menuTrans = true;
    CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->NEWGAME);

}

void Mission6::onTouchMove()
{


    currentSprite = BUTTON_SPRITE_HOVER;

}

SDL_Rect Mission6::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void Mission6::handleEvent(SDL_Event* e)
{

    //SDL_Log("Mission7::handleEvent()");

    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][missionID]) {

        if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION) {
            int tX, tY;
            tX = e->tfinger.x * WWIDTH;
            tY = e->tfinger.y * WHEIGHT;

            bool hover = true;
            SDL_Rect thisButton;
            thisButton = getBounds();
            if (tX < thisButton.x) {
                hover = false;
            } else if (tX > thisButton.x + thisButton.w) {
                hover = false;
            }
            if (tY < thisButton.y) {
                hover = false;
            } else if (tY > thisButton.y + thisButton.h) {
                hover = false;
            }

            if (!hover) {
                currentSprite = BUTTON_SPRITE_OUT;
            } else {
                switch (e->type) {
                    case SDL_FINGERMOTION:
                        //currentSprite = BUTTON_SPRITE_HOVER;
                        onTouchMove();
                        break;
                    case SDL_FINGERDOWN:
                        //currentSprite = BUTTON_SPRITE_DOWN;
                        onTouchDown();
                        break;
                    case SDL_FINGERUP:
                        //currentSprite = BUTTON_SPRITE_OUT;
                        onTouchUp();
                        break;
                }
            }
        }
    }

}

void Mission6::onDelete()
{
    delete this;
}



// Button Mission Levels

int	 Mission7::missionID = 7;
bool Mission7::LevelON = false;

Mission7::Mission7()
{
    SDL_Log("Mission7()");
    buttonID = 2;

    buttonTexture = "Level_8";

    wa = 306;
    ha = 401;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
        x = (WWIDTH /2) - (w / 2);
        y = (WHEIGHT / 2) + (h / 2);
    }
    else if (WHEIGHT > 1300 && WHEIGHT <= 2000) {
        w = wa * 0.82;
        h = ha * 0.82;
        x = (WWIDTH /2) - (w / 2);
        y = (WHEIGHT / 2) + (h / 2) + padding / 2;
    }
    else if (WHEIGHT > 2000) {
        w = wa;
        h = ha;
        x = (WWIDTH /2) - (w / 2);
        y = (WHEIGHT / 2) + (h / 2) + padding;
    }

    xa = 0;
    ya = 0;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
}

Mission7::~Mission7()
{
    SDL_Log("~Mission7()");
}

void Mission7::init()
{
    currentSprite = BUTTON_SPRITE_OUT;
}

void Mission7::init2()
{
    currentSprite = BUTTON_SPRITE_DOWN;
}


void Mission7::showButton(bool on_off)
{
    displayButton = on_off;
}

bool Mission7::getShowButton()
{
    return displayButton;
}

void Mission7::onLoop()
{
    SDL_Rect thisButton;
    thisButton = getBounds();


    xa = wa * currentSprite;
    ya = 0;
    //ha = thisButton.h;
    //wa = thisButton.w;
}

void Mission7::onRender()
{
    if (buttonRenderer)
    {
        TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
    }
    else
    {
        SDL_Log("bad renderer Level8 tag");
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void Mission7::onClick()
{

}

void Mission7::offClick()
{


}

void Mission7::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Mission7::onTouchDown()
{

    ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;

}

void Mission7::onTouchUp()
{


    currentSprite = BUTTON_SPRITE_OUT;
	SDL_Log("let's play mission %d", missionID);
    CAppStateGame::GetInstance()->currentLevel = missionID;
    CAppStateGamePause::GetInstance()->onPause = false;
    CAppStateGamePause::GetInstance()->menuTrans = true;
    CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->NEWGAME);

}

void Mission7::onTouchMove()
{


    currentSprite = BUTTON_SPRITE_HOVER;

}

SDL_Rect Mission7::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void Mission7::handleEvent(SDL_Event* e)
{

    //SDL_Log("Mission4::handleEvent()");

    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][missionID]) {

        if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION) {
            int tX, tY;
            tX = e->tfinger.x * WWIDTH;
            tY = e->tfinger.y * WHEIGHT;

            bool hover = true;
            SDL_Rect thisButton;
            thisButton = getBounds();
            if (tX < thisButton.x) {
                hover = false;
            } else if (tX > thisButton.x + thisButton.w) {
                hover = false;
            }
            if (tY < thisButton.y) {
                hover = false;
            } else if (tY > thisButton.y + thisButton.h) {
                hover = false;
            }

            if (!hover) {
                currentSprite = BUTTON_SPRITE_OUT;
            } else {
                switch (e->type) {
                    case SDL_FINGERMOTION:
                        //currentSprite = BUTTON_SPRITE_HOVER;
                        onTouchMove();
                        break;
                    case SDL_FINGERDOWN:
                        //currentSprite = BUTTON_SPRITE_DOWN;
                        onTouchDown();
                        break;
                    case SDL_FINGERUP:
                        //currentSprite = BUTTON_SPRITE_OUT;
                        onTouchUp();
                        break;
                }
            }
        }
    }

}

void Mission7::onDelete()
{
    delete this;
}


// Button Mission Levels

int	 Mission8::missionID = 8;
bool Mission8::LevelON = false;

Mission8::Mission8()
{
    SDL_Log("Mission8()");
    buttonID = 2;

    buttonTexture = "Level_9";

    wa = 306;
    ha = 401;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
        x = (WWIDTH /2) + (w / 2);
        y = (WHEIGHT / 2) + (h / 2);
    }
    else if (WHEIGHT > 1300 && WHEIGHT <= 2000) {
        w = wa * 0.82;
        h = ha * 0.82;
        x = (WWIDTH /2) + (w / 2) + padding / 2;
        y = (WHEIGHT / 2) + (h / 2) + padding / 2;
    }
    else if (WHEIGHT > 2000) {
        w = wa;
        h = ha;
        x = (WWIDTH /2) + (w / 2) + padding;
        y = (WHEIGHT / 2) + (h / 2) + padding;
    }

    xa = 0;
    ya = 0;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
}

Mission8::~Mission8()
{
    SDL_Log("~Mission8()");
}

void Mission8::init()
{
    currentSprite = BUTTON_SPRITE_OUT;
}

void Mission8::init2()
{
    currentSprite = BUTTON_SPRITE_DOWN;
}


void Mission8::showButton(bool on_off)
{
    displayButton = on_off;
}

bool Mission8::getShowButton()
{
    return displayButton;
}

void Mission8::onLoop()
{
    SDL_Rect thisButton;
    thisButton = getBounds();


    xa = wa * currentSprite;
    ya = 0;
    //ha = thisButton.h;
    //wa = thisButton.w;
}

void Mission8::onRender()
{
    if (buttonRenderer)
    {
        TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
    }
    else
    {
        SDL_Log("bad renderer Level9 tag");
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void Mission8::onClick()
{

}

void Mission8::offClick()
{


}

void Mission8::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Mission8::onTouchDown()
{

    ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;

}

void Mission8::onTouchUp()
{


    currentSprite = BUTTON_SPRITE_OUT;
	SDL_Log("let's play mission %d", missionID);
    CAppStateGame::GetInstance()->currentLevel = missionID;
    CAppStateGamePause::GetInstance()->onPause = false;
    CAppStateGamePause::GetInstance()->menuTrans = true;
    CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->NEWGAME);

}

void Mission8::onTouchMove()
{


    currentSprite = BUTTON_SPRITE_HOVER;

}

SDL_Rect Mission8::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void Mission8::handleEvent(SDL_Event* e)
{

    //SDL_Log("Mission4::handleEvent()");

    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][missionID]) {

        if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION) {
            int tX, tY;
            tX = e->tfinger.x * WWIDTH;
            tY = e->tfinger.y * WHEIGHT;

            bool hover = true;
            SDL_Rect thisButton;
            thisButton = getBounds();
            if (tX < thisButton.x) {
                hover = false;
            } else if (tX > thisButton.x + thisButton.w) {
                hover = false;
            }
            if (tY < thisButton.y) {
                hover = false;
            } else if (tY > thisButton.y + thisButton.h) {
                hover = false;
            }

            if (!hover) {
                currentSprite = BUTTON_SPRITE_OUT;
            } else {
                switch (e->type) {
                    case SDL_FINGERMOTION:
                        //currentSprite = BUTTON_SPRITE_HOVER;
                        onTouchMove();
                        break;
                    case SDL_FINGERDOWN:
                        //currentSprite = BUTTON_SPRITE_DOWN;
                        onTouchDown();
                        break;
                    case SDL_FINGERUP:
                        //currentSprite = BUTTON_SPRITE_OUT;
                        onTouchUp();
                        break;
                }
            }
        }
    }

}

void Mission8::onDelete()
{
    delete this;
}


// Button Mission Levels

int	 Mission9::missionID = 9;
bool Mission9::LevelON = false;

Mission9::Mission9()
{
    SDL_Log("Mission9()");
    buttonID = 2;

    buttonTexture = "Level_10";

    wa = 306;
    ha = 401;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
        x = (WWIDTH /2) - (w / 2);
        y = (WHEIGHT / 2) + (h / 2) + h;
    }
    else if (WHEIGHT > 1300 && WHEIGHT <= 2000) {
        w = wa * 0.82;
        h = ha * 0.82;
        x = (WWIDTH /2) - (w / 2);
        y = (WHEIGHT / 2) + (h / 2) + h + padding / 2;
    }
    else if (WHEIGHT > 2000) {
        w = wa;
        h = ha;
        x = (WWIDTH /2) - (w / 2);
        y = (WHEIGHT / 2) + (h / 2) + h + padding * 2;
    }

    xa = 0;
    ya = 0;

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
}

Mission9::~Mission9()
{
    SDL_Log("~Mission9()");
}

void Mission9::init()
{
    currentSprite = BUTTON_SPRITE_OUT;
}

void Mission9::init2()
{
    currentSprite = BUTTON_SPRITE_DOWN;
}


void Mission9::showButton(bool on_off)
{
    displayButton = on_off;
}

bool Mission9::getShowButton()
{
    return displayButton;
}

void Mission9::onLoop()
{
    SDL_Rect thisButton;
    thisButton = getBounds();


    xa = wa * currentSprite;
    ya = 0;
    //ha = thisButton.h;
    //wa = thisButton.w;
}

void Mission9::onRender()
{
    if (buttonRenderer)
    {
        TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, ya, wa, ha, 255);
    }
    else
    {
        SDL_Log("bad renderer Level10 tag");
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void Mission9::onClick()
{

}

void Mission9::offClick()
{


}

void Mission9::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void Mission9::onTouchDown()
{

    ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;

}

void Mission9::onTouchUp()
{


    currentSprite = BUTTON_SPRITE_OUT;
	SDL_Log("let's play mission %d", missionID);
    CAppStateGame::GetInstance()->currentLevel = missionID;
    CAppStateGamePause::GetInstance()->onPause = false;
    CAppStateGamePause::GetInstance()->menuTrans = true;
    CAppStateGamePause::GetInstance()->setActiveMenu(CAppStateGamePause::GetInstance()->NEWGAME);

}

void Mission9::onTouchMove()
{


    currentSprite = BUTTON_SPRITE_HOVER;

}

SDL_Rect Mission9::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void Mission9::handleEvent(SDL_Event* e)
{

    //SDL_Log("Mission4::handleEvent()");

    if (CAppStateIntro::GetInstance()->level_gained[CAppStateGame::currentMission][missionID]) {

        if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION) {
            int tX, tY;
            tX = e->tfinger.x * WWIDTH;
            tY = e->tfinger.y * WHEIGHT;

            bool hover = true;
            SDL_Rect thisButton;
            thisButton = getBounds();
            if (tX < thisButton.x) {
                hover = false;
            } else if (tX > thisButton.x + thisButton.w) {
                hover = false;
            }
            if (tY < thisButton.y) {
                hover = false;
            } else if (tY > thisButton.y + thisButton.h) {
                hover = false;
            }

            if (!hover) {
                currentSprite = BUTTON_SPRITE_OUT;
            } else {
                switch (e->type) {
                    case SDL_FINGERMOTION:
                        //currentSprite = BUTTON_SPRITE_HOVER;
                        onTouchMove();
                        break;
                    case SDL_FINGERDOWN:
                        //currentSprite = BUTTON_SPRITE_DOWN;
                        onTouchDown();
                        break;
                    case SDL_FINGERUP:
                        //currentSprite = BUTTON_SPRITE_OUT;
                        onTouchUp();
                        break;
                }
            }
        }
    }

}

void Mission9::onDelete()
{
    delete this;
}





// BUTTON SPACESHIP PLAYER SELECTORS

// SHIP A

GetShipA::GetShipA()
{
	SDL_Log("GetShipA()");
	buttonID = 0;
}

GetShipA::~GetShipA()
{
	SDL_Log("~GetShipA()");
}

void GetShipA::init()
{
	Panel::init();

    xa = 0;
    ya = 0;
    wa = 785;
    ha = 573;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
    }
    else if (WHEIGHT >= 1300 && WHEIGHT <= 2000) {
        w = wa;
        h = ha;
    }
    else if (WHEIGHT > 2000) {
        w = wa * 1.2;
        h = ha * 1.2;
    }

	x = (WWIDTH - w) / 2;
	y = (WHEIGHT - h) / 2;


	//SDL_Log("GetShipA x: %d - y: %d", x, y);

	buttonTexture = "HangarRed";

	if (CAppStateIntro::GetInstance()->MySpaceship[0] == true)
	{
		this->currentSprite = BUTTON_SPRITE_OUT;
	}
	else if (CAppStateIntro::GetInstance()->GetPlayerShip() == 1)
	{
		this->currentSprite = BUTTON_SPRITE_HOVER;
	}
	else
	{
		this->currentSprite = BUTTON_SPRITE_OUT;
		SDL_Log("spaceshipA not available");
	}
	/*
	if (CAppStateIntro::GetInstance()->GetFinalMission())
	{
		buttonTexture = "ShipBackgroundSelectorA";
	}
	else
	{
		buttonTexture = "ShipBackgroundSelectorA";
	}
	*/
	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void GetShipA::init2()
{
    /*
	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	w = Panel::getWidth();
	h = w / 2;
	x = WWIDTH * 0.70;
	y = WHEIGHT * 0.85;


	buttonTexture = "ShipBackgroundSelectorA";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();
    */

}


void GetShipA::showButton(bool on_off)
{
	displayButton = on_off;
}

bool GetShipA::getShowButton()
{
	return displayButton;
}

void GetShipA::onLoop()
{
	if (CAppStateIntro::GetInstance()->MySpaceship[0] == true)
	{
		if (CAppStateIntro::GetInstance()->GetPlayerShip() == 1)
		{
			this->currentSprite = BUTTON_SPRITE_HOVER;
		}
		else
		{
			this->currentSprite = BUTTON_SPRITE_OUT;
		}
	}

	SDL_Rect thisButton;
	thisButton = getBounds();

    x = Hangar::XcHangar + (WWIDTH -w) /2;

	//xa = thisButton.x;
	ya = ha * this->currentSprite;
	//ha = thisButton.h;
	//wa = thisButton.w;
}

void GetShipA::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, wa, ha, 255);
	}
	else
	{
		SDL_Log("bad renderer GetShipA");
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void GetShipA::onClick()
{


}

void GetShipA::offClick()
{


}

void GetShipA::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void GetShipA::onTouchDown()
{
	ForceFeedbackPushButton();

    currentSprite = BUTTON_SPRITE_HOVER;

	SDL_Log("spaceshipA sprite %d", this->currentSprite);

	Hangar::scrolling = false;
    Hangar::MoveX = 0;
    CCamera::CameraControl.OnMove(Hangar::breakpointA, 0);
    //Hangar::Xhangar = Hangar::breakpointA;
	
}

void GetShipA::onTouchUp()
{

    if (CAppStateIntro::GetInstance()->MySpaceship[0] == true)
    {
        CAppStateIntro::GetInstance()->SetPlayerShip(1);
        SDL_Log("Spaceship A selected");
    }

}

void GetShipA::onTouchMove()
{

}

SDL_Rect GetShipA::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void GetShipA::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			//currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				//currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				//currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				//currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void GetShipA::onDelete()
{
	delete this;
}


// SHIP B
GetShipB::GetShipB()
{
	SDL_Log("GetShipB()");
	buttonID = 1;
}

GetShipB::~GetShipB()
{
	SDL_Log("~GetShipB()");
}

void GetShipB::init()
{
	Panel::init();

    xa = 0;
    ya = 0;
    wa = 785;
    ha = 573;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
    }
    else if (WHEIGHT >= 1300 && WHEIGHT <= 2000) {
        w = wa;
        h = ha;
    }
    else if (WHEIGHT > 2000) {
        w = wa * 1.2;
        h = ha * 1.2;
    }

    //x = ((WWIDTH -w) /2) +w +(w /2);
    x = Hangar::XcHangar + ((WWIDTH -w) /2) +WWIDTH;
    y = (WHEIGHT -h) /2;

	buttonTexture = "HangarBlue";

	if (CAppStateIntro::GetInstance()->MySpaceship[1] == true)
	{
		this->currentSprite = BUTTON_SPRITE_OUT;
	}
	else if (CAppStateIntro::GetInstance()->GetPlayerShip() == 2)
	{
		this->currentSprite = BUTTON_SPRITE_HOVER;
	}
	else
	{
		this->currentSprite = BUTTON_SPRITE_OUT;
		SDL_Log("spaceshipB not available");
	}

	/*
	if (CAppStateIntro::GetInstance()->GetFinalMission())
	{
	buttonTexture = "ShipBackgroundSelectorA";
	}
	else
	{
	buttonTexture = "ShipBackgroundSelectorA";
	}
	*/
	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void GetShipB::init2()
{
	

}


void GetShipB::showButton(bool on_off)
{
	displayButton = on_off;
}

bool GetShipB::getShowButton()
{
	return displayButton;
}

void GetShipB::onLoop()
{
	if (CAppStateIntro::GetInstance()->MySpaceship[1] == true)
	{
		if (CAppStateIntro::GetInstance()->GetPlayerShip() == 2)
		{
			this->currentSprite = BUTTON_SPRITE_HOVER;
		}
		else
		{
			this->currentSprite = BUTTON_SPRITE_OUT;
		}
	}

	SDL_Rect thisButton;
	thisButton = getBounds();

    //x = Hangar::XcHangar + ((WWIDTH -w) /2) +w + (w /2);
    x = Hangar::XcHangar + ((WWIDTH -w) /2) +WWIDTH;

	//xa = thisButton.x;
    ya = ha * this->currentSprite;
	//ha = thisButton.h;
	//wa = thisButton.w;
}

void GetShipB::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, wa, ha, 255);
	}
	else
	{
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void GetShipB::onClick()
{


}

void GetShipB::offClick()
{


}

void GetShipB::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void GetShipB::onTouchDown()
{
	ForceFeedbackPushButton();

    this->currentSprite = BUTTON_SPRITE_HOVER;

	SDL_Log("spaceshipB sprite %d", this->currentSprite);
    /*
    Hangar::scrolling = false;
    Hangar::MoveX = 0;
    CCamera::CameraControl.OnMove(Hangar::breakpointB, 0);
    Hangar::XcHangar = Hangar::breakpointB;
    */



}

void GetShipB::onTouchUp()
{

    if (CAppStateIntro::GetInstance()->MySpaceship[1] == true)
    {
        CAppStateIntro::GetInstance()->SetPlayerShip(2);

        //Hangar::AddOffset(Hangar::breakpointB);

        SDL_Log("Spaceship B selected");
    }


}

void GetShipB::onTouchMove()
{

}

SDL_Rect GetShipB::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void GetShipB::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			//currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				//currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				//currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				//currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void GetShipB::onDelete()
{
	delete this;
}


// SHIP C
GetShipC::GetShipC()
{
	SDL_Log("GetShipC()");
	buttonID = 2;
}

GetShipC::~GetShipC()
{
	SDL_Log("~GetShipC()");
}

void GetShipC::init()
{
	Panel::init();

    xa = 0;
    ya = 0;
    wa = 785;
    ha = 573;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
    }
    else if (WHEIGHT >= 1300 && WHEIGHT <= 2000) {
        w = wa;
        h = ha;
    }
    else if (WHEIGHT > 2000) {
        w = wa * 1.2;
        h = ha * 1.2;
    }

    //x = ((WWIDTH -w) /2) +w *2 + w;
    x = Hangar::XcHangar + ((WWIDTH -w) /2) +WWIDTH*2;
    y = (WHEIGHT -h) /2;

	buttonTexture = "HangarGreen";

	if (CAppStateIntro::GetInstance()->MySpaceship[2] == true)
	{
		this->currentSprite = BUTTON_SPRITE_OUT;
	}
	else if (CAppStateIntro::GetInstance()->GetPlayerShip() == 3)
	{
		this->currentSprite = BUTTON_SPRITE_HOVER;
	}
	else
	{
		this->currentSprite = BUTTON_SPRITE_OUT;
		SDL_Log("spaceshipC not available");
	}

	/*
	if (CAppStateIntro::GetInstance()->GetFinalMission())
	{
	buttonTexture = "ShipBackgroundSelectorA";
	}
	else
	{
	buttonTexture = "ShipBackgroundSelectorA";
	}
	*/
	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void GetShipC::init2()
{
	Panel::init();

	currentSprite = BUTTON_SPRITE_OUT;

	w = Panel::getWidth() / 3;
	h = w / 2;
	x = WWIDTH * 0.70;
	y = WHEIGHT * 0.85;


	buttonTexture = "ShipBackgroundSelectorC";

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}


void GetShipC::showButton(bool on_off)
{
	displayButton = on_off;
}

bool GetShipC::getShowButton()
{
	return displayButton;
}

void GetShipC::onLoop()
{
	if (CAppStateIntro::GetInstance()->MySpaceship[2] == true)
	{
		if (CAppStateIntro::GetInstance()->GetPlayerShip() == 3)
		{
			this->currentSprite = BUTTON_SPRITE_HOVER;
		}
		else
		{
			this->currentSprite = BUTTON_SPRITE_OUT;
		}
	}

	SDL_Rect thisButton;
	thisButton = getBounds();

    x = Hangar::XcHangar + ((WWIDTH -w) /2) +WWIDTH*2;


	//xa = thisButton.x;
    ya = ha * this->currentSprite;
	//ha = thisButton.h;
	//wa = thisButton.w;
}

void GetShipC::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, wa, ha, 255);
	}
	else
	{
	}

}


// BUTTON ACTION & CONTROLLER FUNCTION 

void GetShipC::onClick()
{


}

void GetShipC::offClick()
{


}

void GetShipC::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void GetShipC::onTouchDown()
{
	ForceFeedbackPushButton();

    this->currentSprite = BUTTON_SPRITE_HOVER;

	SDL_Log("spaceshipC sprite %d", this->currentSprite);

    //Hangar::scrolling = false;
    //Hangar::MoveX = 0;
    CCamera::CameraControl.OnMove(Hangar::breakpointC, 0);
    Hangar::XcHangar = Hangar::breakpointC;

}

void GetShipC::onTouchUp()
{

    if (CAppStateIntro::GetInstance()->MySpaceship[2] == true)
    {
        CAppStateIntro::GetInstance()->SetPlayerShip(3);

        SDL_Log("Spaceship C selected");
    }

}

void GetShipC::onTouchMove()
{

}

SDL_Rect GetShipC::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = this->x;
	buttonRect.y = this->y;
	buttonRect.w = this->w;
	buttonRect.h = this->h;

	return buttonRect;
}

void GetShipC::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			//currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				//currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				//currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				//currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void GetShipC::onDelete()
{
	delete this;
}




// SHIP X
GetShipX::GetShipX()
{
    SDL_Log("GetShipX()");
    buttonID = 2;
}

GetShipX::~GetShipX()
{
    SDL_Log("~GetShipX()");
}

void GetShipX::init()
{
    Panel::init();

    xa = 0;
    ya = 0;
    wa = 785;
    ha = 573;

    if (WHEIGHT < 1300) {
        w = wa * 0.60;
        h = ha * 0.60;
    }
    else if (WHEIGHT >= 1300 && WHEIGHT <= 2000) {
        w = wa;
        h = ha;
    }
    else if (WHEIGHT > 2000) {
        w = wa * 1.2;
        h = ha * 1.2;
    }

    //x = Hangar::XcHangar + ((WWIDTH -w) /2) +w*3 + (w /2) + w;
    x = Hangar::XcHangar + ((WWIDTH -w) /2) +WWIDTH*3;
    y = (WHEIGHT -h) /2;

    buttonTexture = "HangarYellowAvail";

    if (CAppStateIntro::GetInstance()->MySpaceship[3] == true)
    {
        this->currentSprite = BUTTON_SPRITE_OUT;
    }
    else if (CAppStateIntro::GetInstance()->GetPlayerShip() == 3)
    {
        this->currentSprite = BUTTON_SPRITE_HOVER;
    }
    else
    {
        this->currentSprite = BUTTON_SPRITE_OUT;
        SDL_Log("spaceshipC not available");
    }

    /*
    if (CAppStateIntro::GetInstance()->GetFinalMission())
    {
    buttonTexture = "ShipBackgroundSelectorA";
    }
    else
    {
    buttonTexture = "ShipBackgroundSelectorA";
    }
    */
    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}

void GetShipX::init2()
{
    Panel::init();

    currentSprite = BUTTON_SPRITE_OUT;

    w = 785;
    h = 573;
    x = Hangar::XcHangar + ((WWIDTH -w) /2) +WWIDTH*3;
    y = (WHEIGHT -h) /2;

    xa = 0;
    ya = 0;
    wa = 785;
    ha = 573;


    buttonTexture = "HangarYellowLocked";

    buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
    buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

}


void GetShipX::showButton(bool on_off)
{
    displayButton = on_off;
}

bool GetShipX::getShowButton()
{
    return displayButton;
}

void GetShipX::onLoop()
{
    if (CAppStateIntro::GetInstance()->MySpaceship[3] == true)
    {
        if (CAppStateIntro::GetInstance()->GetPlayerShip() == 4)
        {
            this->currentSprite = BUTTON_SPRITE_HOVER;
        }
        else
        {
            this->currentSprite = BUTTON_SPRITE_OUT;
        }
    }

    SDL_Rect thisButton;
    thisButton = getBounds();

    x = Hangar::XcHangar + ((WWIDTH -w) /2) +WWIDTH*3;


    //xa = thisButton.x;
    ya = ha * this->currentSprite;
    //ha = thisButton.h;
    //wa = thisButton.w;
}

void GetShipX::onRender()
{
    if (buttonRenderer)
    {
        TextureBank::Get(buttonTexture)->Render(x, y, w, h, 0, ya, wa, ha, 255);
    }
    else
    {
    }

}


// BUTTON ACTION & CONTROLLER FUNCTION

void GetShipX::onClick()
{


}

void GetShipX::offClick()
{


}

void GetShipX::onMouseOver()
{

}

//*** Mobile Device Gesture ***
void GetShipX::onTouchDown()
{
    ForceFeedbackPushButton();

    if (CAppStateIntro::GetInstance()->MySpaceship[3] == true)
    {
        this->currentSprite = BUTTON_SPRITE_HOVER;
    }
    SDL_Log("spaceshipC sprite %d", this->currentSprite);

    Hangar::scrolling = false;
    Hangar::MoveX = 0;
    CCamera::CameraControl.OnMove(Hangar::breakpointX, 0);
    Hangar::XcHangar = Hangar::breakpointX;

}

void GetShipX::onTouchUp()
{

    if (CAppStateIntro::GetInstance()->MySpaceship[3] == true)
    {
        CAppStateIntro::GetInstance()->SetPlayerShip(4);

        SDL_Log("Spaceship C selected");
    }

}

void GetShipX::onTouchMove()
{

}

SDL_Rect GetShipX::getBounds()
{
    SDL_Rect	buttonRect;
    buttonRect.x = this->x;
    buttonRect.y = this->y;
    buttonRect.w = this->w;
    buttonRect.h = this->h;

    return buttonRect;
}

void GetShipX::handleEvent(SDL_Event* e)
{
    if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
    {
        int tX, tY;
        tX = e->tfinger.x * WWIDTH;
        tY = e->tfinger.y * WHEIGHT;

        bool hover = true;
        SDL_Rect thisButton;
        thisButton = getBounds();
        if (tX < thisButton.x)
        {
            hover = false;
        }
        else if (tX > thisButton.x + thisButton.w)
        {
            hover = false;
        }
        if (tY < thisButton.y)
        {
            hover = false;
        }
        else if (tY > thisButton.y + thisButton.h)
        {
            hover = false;
        }

        if (!hover)
        {
            //currentSprite = BUTTON_SPRITE_OUT;
        }
        else
        {
            switch (e->type)
            {
                case SDL_FINGERMOTION:
                    //currentSprite = BUTTON_SPRITE_HOVER;
                    onTouchMove();
                    break;
                case SDL_FINGERDOWN:
                    //currentSprite = BUTTON_SPRITE_DOWN;
                    onTouchDown();
                    break;
                case SDL_FINGERUP:
                    //currentSprite = BUTTON_SPRITE_OUT;
                    onTouchUp();
                    break;
            }
        }
    }


}

void GetShipX::onDelete()
{
    delete this;
}










// BUTTON TEST CODE
ButtonTEST::ButtonTEST()
{
	
}

ButtonTEST::~ButtonTEST()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "ButtonTEST destructor", "");
}

void ButtonTEST::init()
{
	Panel::init();

	buttonID = 2;
	w = Panel::getWidth() / 10;
	h = w / 3;
	x = Panel::GetX1() + buttonID * w;
	y = Panel::GetY1();

	buttonWindow = CAppStateIntro::GetInstance()->GetWindow();
	buttonRenderer = CAppStateIntro::GetInstance()->GetRenderer();

	currentSprite = BUTTON_SPRITE_OUT;

	CApp::Logger.OnLog(__FILE__, __LINE__, "buttonTEST texture", buttonTexture);
	CApp::Logger.OnLog(__FILE__, __LINE__, "buttonTEST id", Stringify::Int(buttonID));
	CApp::Logger.OnLog(__FILE__, __LINE__, "buttonTEST x", Stringify::Int(x));
	CApp::Logger.OnLog(__FILE__, __LINE__, "buttonTEST y", Stringify::Int(y));
	CApp::Logger.OnLog(__FILE__, __LINE__, "buttonTEST w", Stringify::Int(w));
	CApp::Logger.OnLog(__FILE__, __LINE__, "buttonTEST h", Stringify::Int(h));

}

void ButtonTEST::init2() {}

void ButtonTEST::onLoop()
{
	SDL_Rect thisButton;
	thisButton = getBounds();

	xa = 300 * currentSprite;
	ya = thisButton.y;
	ha = thisButton.h;
	wa = thisButton.w;
}

void ButtonTEST::onRender()
{
	if (buttonRenderer)
	{
		TextureBank::Get(buttonTexture)->Render(x, y, w, h, xa, 0, 300, 150, 255);
		//TextureBank::Get(buttonTexture)->Render(x, y, w, h, 255);
	}
	else
	{
		CApp::Logger.OnLog(__FILE__, __LINE__, "bad Renderer", "");
	}
}

SDL_Rect ButtonTEST::getBounds()
{
	SDL_Rect	buttonRect;
	buttonRect.x = getX();
	buttonRect.y = getY();
	buttonRect.w = getW();
	buttonRect.h = getH();

	return buttonRect;
}

void ButtonTEST::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP || e->type == SDL_FINGERMOTION)
	{
		int tX, tY;
		tX = e->tfinger.x * WWIDTH;
		tY = e->tfinger.y * WHEIGHT;

		bool hover = true;
		SDL_Rect thisButton;
		thisButton = getBounds();
		if (tX < thisButton.x)
		{
			hover = false;
		}
		else if (tX > thisButton.x + thisButton.w)
		{
			hover = false;
		}
		if (tY < thisButton.y)
		{
			hover = false;
		}
		else if (tY > thisButton.y + thisButton.h)
		{
			hover = false;
		}

		if (!hover)
		{
			currentSprite = BUTTON_SPRITE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_FINGERMOTION:
				currentSprite = BUTTON_SPRITE_HOVER;
				onTouchMove();
				break;
			case SDL_FINGERDOWN:
				currentSprite = BUTTON_SPRITE_DOWN;
				onTouchDown();
				break;
			case SDL_FINGERUP:
				currentSprite = BUTTON_SPRITE_OUT;
				onTouchUp();
				break;
			}
		}
	}


}

void ButtonTEST::onMouseOver()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "button TEST mouse over event", "");
}

void ButtonTEST::onClick()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "Button TEST mouse over event", "");
	
}

void ButtonTEST::offClick()
{
	CAppStateGamePause::GetInstance()->isRunning = true;
}

//*** Mobile Device Gesture ***
void ButtonTEST::onTouchDown()
{
	ForceFeedbackPushButton();
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse touch Down event", "");
}

void ButtonTEST::onTouchUp()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse touch Up event", "");
}

void ButtonTEST::onTouchMove()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "mouse touch Move event", "");
}

int ButtonTEST::getX()
{
	return x;
}

int ButtonTEST::getY()
{
	return y;
}

int ButtonTEST::getH()
{
	return h;
}

int ButtonTEST::getW()
{
	return w;
}

void ButtonTEST::onDelete()
{
	delete this;
}



// ***** MENU FACTORY CODE *****

CMenuFactory::CMenuFactory()
{
	CApp::Logger.OnLog(__FILE__, __LINE__, "add buttons to Panel", "");

	set("background", &Background::Create);		// background anchor to main panel
    set("background2", &Background2::Create);		// background anchor to main panel
	set("hangar", &Hangar::Create);				// hangar anchor to main panel
	set("explorer", &Explorer::Create);			// explorer anchor to main panel
	set("ship", &ButtonShip::Create);			// button ship anchor to main panel
	set("option", &ButtonOpt::Create);			// button option anchor to main panel
	set("play", &ButtonPlay::Create);			// button play anchor to main Panel
	set("next", &ButtonNext::Create);			// button next anchor to main Panel
	set("resume", &ButtonResume::Create);		// button resume anchor to main Panel
	set("debrief", &ButtonDebrief::Create);		// button debfrie anchor to main Panel
	set("exit", &ButtonExit::Create);			// button exit anchor to main panel
	set("video", &ButtonVideo::Create);			// button video anchor to main panel
	set("sound", &ButtonSound::Create);			// button sound anchor to main panel
	set("return", &ButtonReturn::Create);		// button exit anchor to main panel

	set("volumesx", &ButtonVolumeSX::Create);	// Volume loud-low selector
	set("volumedx", &ButtonVolumeDX::Create);	// Volume loud-up selector
	set("soundbar", &SoundBar::Create);			// soundbar volume index

	set("level0", &ButtonLevel0::Create);		// button level0 anchor to main panel
	set("level1", &ButtonLevel1::Create);		// button level1 anchor to main panel
	set("level2", &ButtonLevel2::Create);		// button level2 anchor to main panel
	set("level3", &ButtonLevel3::Create);		// button level3 anchor to main panel
	set("level4", &ButtonLevel4::Create);		// button level4 anchor to main panel
	set("levelX", &ButtonLevelX::Create);		// button levelX anchor to main panel

	set("mission0", &Mission0::Create);			// button mission anchor to main panel
	set("mission1", &Mission1::Create);			// button mission anchor to main panel
	set("mission2", &Mission2::Create);			// button mission anchor to main panel
	set("mission3", &Mission3::Create);			// button mission anchor to main panel
	set("mission4", &Mission4::Create);			// button mission anchor to main panel
    set("mission5", &Mission5::Create);			// button mission anchor to main panel
    set("mission6", &Mission6::Create);			// button mission anchor to main panel
    set("mission7", &Mission7::Create);			// button mission anchor to main panel
    set("mission8", &Mission8::Create);			// button mission anchor to main panel
    set("mission9", &Mission9::Create);			// button mission anchor to main panel

	set("shipA", &GetShipA::Create);			// button shipA anchor to main panel
	set("shipB", &GetShipB::Create);			// button shipB anchor to main panel
	set("shipC", &GetShipC::Create);			// button shipC anchor to main panel
    set("shipX", &GetShipX::Create);			// button shipX anchor to main panel

	set("menuID", &Button::Create);				// the ID menu
	//set("TEST", &ButtonTEST::Create);			// TEST BUTTON
	
	set("panel", &Panel::Create);

	CApp::Logger.OnLog(__FILE__, __LINE__, "m_FactoryMap size: ", Stringify::Int(m_FactoryMap.size()));

	
};

CMenuFactory::~CMenuFactory()
{
	m_FactoryMap.clear();
}

CMenu *CMenuFactory::CreateMenu(std::string b_name)
{
	FactoryMap::iterator it = m_FactoryMap.find(b_name);
	if (it != m_FactoryMap.end())
	{
		return it->second();
	}

	return NULL;
}

void CMenuFactory::set(const std::string b_name, CMenu::CreateMenuFn pfnCreate)
{
	m_FactoryMap[b_name] = pfnCreate;
}




CMenuFactory *CMenuFactory::getFactory()
{
	static CMenuFactory instance;
	return &instance;
}




