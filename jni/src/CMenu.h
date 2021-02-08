/*******************************************************************************/
/*** Graphic User Interface - designed for videogames - by Marco Bonaventura ***/
/*** 2015 - All Rights Reserved! ***********************************************/
/*******************************************************************************/

#ifndef _CMENU_H_
	#define _CMENU_H_

#include "CApp.h"
#include "CAnimation.h"

#include "Stringify.h"
#include "Define.h"
#include <map>

class CMenu 
{
	static bool displayMenu;
	int			x, y, w, h;
	bool		LevelON;

public:
	void triggerMenu();
	void showMenu(bool on_off);
	bool getShowMenu();
	
	virtual void init() = 0;
	virtual void init2() = 0;
    //void init3();
	virtual void onLoop() = 0;
	virtual void handleEvent(SDL_Event* e) = 0;
	virtual void onRender() = 0;
	virtual void onDelete() = 0;

	virtual void onClick() = 0;
	void Draw();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();

	void SetXY(int xx, int yy) { x = xx; y = yy; }

	typedef CMenu* (*CreateMenuFn)(void);

	std::string buttonTexture;
	int buttonID;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;
			
	
	int	 missionID;
    bool displayButton;
	

};

class Panel : public CMenu
{
	int X1, Y1, X2, Y2, W, H;
	bool displayPanel;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;
	
	std::string		panelTexture;	

public:
		

	void init();
	void init2();
	int getWidth();
	int getHeight();
	int GetX1();
	int GetY1();
		

	void showPanel(bool on_off);
	bool getShowPanel();
    bool displayButton;
	
	void onLoop();
	void handleEvent(SDL_Event* e);
	void onRender();
	void onDelete();

	void onClick();
	
	static CMenu* Create() 
	{	
		return new Panel(); 
	}

	friend class Button;
	friend class ButtonPlay;
	friend class ButtonExit;

};

// Class DEFAULT button
class Button : public Panel
{
	int x, y, w, h;
	int xa, ya, wa, ha;

	

public:
	
	Button();
 	Button(int bID);
	~Button();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;
    bool displayButton;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;
	int padding = 50;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { x = xx; y = yy; }
	
	void onDelete();
	

	static CMenu* Create() 
	{ 
		return new Button(); 
	}

	void ForceFeedbackPushButton();
	

};




// Class BACKGROUND

class Background : public Button
{
	int x, y, w, h;
	int tX, tY;
	int xa, ya, wa, ha;
	int buttonID = 0;


	bool	return_switch;
	SDL_Rect return_menu;
	SDL_Rect return_ships;


	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	Background();
    //Background(std::string bck_str);
	~Background();



	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;
    std::string buttonTexture;
	bool displayButton;

	/*
	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;
	*/

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
    //void init3();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;


	void onDelete();


	static CMenu* Create()
	{
		return new Background();
	}

};


class Background2 : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
    int tX, tY;
	int buttonID = 0;
	bool displayButton;

	bool	return_switch;
	SDL_Rect return_bck;


	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	Background2();
	~Background2();

	static bool switch_surface;

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;
	std::string buttonTexture;

    SDL_Rect return_menu;
    SDL_Rect return_ships;

	/*
	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;
	*/

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	//void init3();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;


	void onDelete();


	static CMenu* Create()
	{
		return new Background2();
	}

};




// Class HANGAR

class Hangar : public Button
{
	float x, y, w, h;
	float SpeedX, MAXspeed, Accel, scrollX, prevX, pressure, ship_thumb, padding;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	bool down, up, move;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	Hangar();
	~Hangar();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

    float tXhangar, tYhangar;
    static float Xhangar, Yhangar, XcHangar, YcHangar, MoveX;
    static bool scrolling;
    static float breakpointA;
    static float breakpointB;
    static float breakpointC;
    static float breakpointX;
    static float Xoffset;
	/*
	enum MenuID
	{
	MAIN = 0,
	NEWGAME = 1,
	PLAY = 2,
	SHIP = 3,
	OPTION = 4,
	VIDEO = 5,
	SOUND = 6,
	BACK = 7,
	RESUME = 8,
	NEXT = 9,
	MISSION = 10,
	EXIT = 11
	};
	MenuID menuID;
	*/

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	void onMove(float MoveX, float prevX);

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;


	void onDelete();

	static void AddOffset(int offset);

	static CMenu* Create()
	{
		return new Hangar();
	}

};




// Class EXPLORER

class Explorer : public Button
{
	float x, y, tXt, tYt, x1, y1, w, h;
    float SpeedX, MAXspeed, Accel;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
    bool down, up, move;
	std::string buttonTexture;

	SDL_Rect Level0;
	SDL_Rect Level1;
	SDL_Rect Level2;
	SDL_Rect Level3;
	SDL_Rect Level4;
	SDL_Rect Level5;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

	//static Explorer Instance;

public:
	Explorer();
	~Explorer();

	float tXm, tYm;
	static float Xc, Yc, X1, Y1, MoveX;
	static int Waa, Haa;
    static bool scrolling;

	//static Explorer* GetInstance();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();

	static int getWa();
	static int getHa();
	int mx, my;

	//float *GetPositionX() { return &Xc; }
	//float *GetPositionY() { return &Yc; }

	void onDelete();


	static CMenu* Create()
	{
		return new Explorer();
	}

};



// Class Button PLAY

class ButtonPlay : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonPlay();
	~ButtonPlay();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;


	void onDelete();


	static CMenu* Create()
	{
		return new ButtonPlay();
	}

};


// Class Button NEXT

class ButtonNext : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonNext();
	~ButtonNext();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;


	void onDelete();


	static CMenu* Create()
	{
		return new ButtonNext();
	}


};





// Class Button RESUME

class ButtonResume : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonResume();
	~ButtonResume();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;


	void onDelete();


	static CMenu* Create()
	{
		return new ButtonResume();
	}


};





// Class Button DEBRIEF

class ButtonDebrief : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;
    int starSX_x, starSX_y;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;
    SDL_Surface*    Surface_bonus = NULL;

    SDL_Point   starSX;
    SDL_Point   starMM;
    SDL_Point   starM1;
    SDL_Point   starBB;

public:
	ButtonDebrief();
	~ButtonDebrief();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;


	void onDelete();


	static CMenu* Create()
	{
		return new ButtonDebrief();
	}


};




// Class Button OPTION

class ButtonShip : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonShip();
	~ButtonShip();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;


	void onDelete();


	static CMenu* Create()
	{
		return new ButtonShip();
	}

};



// Class Button OPTION

class ButtonOpt : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonOpt();
	~ButtonOpt();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;


	void onDelete();


	static CMenu* Create()
	{
		return new ButtonOpt();
	}

};

// Class Button EXIT
class ButtonExit : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	bool exitGame;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonExit();
	~ButtonExit();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonExit();
	}

};



// Class Button RETURN
class ButtonReturn : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonReturn();
	~ButtonReturn();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonReturn();
	}

};



// Class Button VIDEO
class ButtonVideo : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonVideo();
	~ButtonVideo();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonVideo();
	}

};


// Class Button SOUND
class ButtonSound : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonSound();
	~ButtonSound();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonSound();
	}

};

// Class Button VolumeSX
class ButtonVolumeSX : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int i = 16;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonVolumeSX();
	~ButtonVolumeSX();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonVolumeSX();
	}

};

// Class Button SOUND
class ButtonVolumeDX : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	int i = 16;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonVolumeDX();
	~ButtonVolumeDX();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonVolumeDX();
	}

};

/**** SELECTOR LEVELS BUTTON ****/

// Class Button Level1
class ButtonLevel0 : public Button
{
	float x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonLevel0();
	~ButtonLevel0();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	bool LevelON;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonLevel0();
	}

};

// Class Button Level1
class ButtonLevel1 : public Button
{
	float x, y, w, h;
	float tXm, tYm, tX, tY;
	int xa, ya, wa, ha;
	int buttonID;
	bool displayButton;
	bool LevelON = false;
	std::string buttonTexture;

	SDL_Point offset;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonLevel1();
	~ButtonLevel1();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	//void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonLevel1();
	}

};

// Class Button Level2
class ButtonLevel2 : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	bool LevelON = false;

	std::string buttonTexture;

    SDL_Point offset;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonLevel2();
	~ButtonLevel2();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	
	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonLevel2();
	}

};

// Class Button Level3
class ButtonLevel3 : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	bool LevelON = false;

	std::string buttonTexture;

    SDL_Point offset;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonLevel3();
	~ButtonLevel3();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonLevel3();
	}

};

// Class Button LevelX
class ButtonLevelX : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	bool LevelON = false;

	std::string buttonTexture;

    SDL_Point offset;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonLevelX();
	~ButtonLevelX();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	
	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonLevelX();
	}

};

// Class Button Level4
class ButtonLevel4 : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	bool LevelON = false;

	std::string buttonTexture;

    SDL_Point offset;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	ButtonLevel4();
	~ButtonLevel4();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new ButtonLevel4();
	}

};






// Class Button GetShipA
class GetShipA : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	bool LevelON = false;

	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	GetShipA();
	~GetShipA();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;


	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new GetShipA();
	}

};

// Class Button GetShipB
class GetShipB : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	bool LevelON = false;

	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	GetShipB();
	~GetShipB();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;


	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new GetShipB();
	}

};

// Class Button GetShipC
class GetShipC : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	bool LevelON = false;

	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	GetShipC();
	~GetShipC();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;


	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new GetShipC();
	}

};


// Class Button GetShipXXX
class GetShipX : public Button
{
    int x, y, w, h;
    int xa, ya, wa, ha;
    int buttonID = 0;
    bool displayButton;
    bool LevelON = false;

    std::string buttonTexture;

    SDL_Renderer*   buttonRenderer;
    SDL_Window*     buttonWindow;

public:
    GetShipX();
    ~GetShipX();

    enum buttonSprite
    {
        BUTTON_SPRITE_OUT = 0,
        BUTTON_SPRITE_HOVER = 1,
        BUTTON_SPRITE_DOWN = 2,
        BUTTON_SPRITE_UP = 3,
        BUTTON_SPRITE_TOTAL = 4
    };
    buttonSprite currentSprite;

    enum MenuID
    {
        MAIN = 0,
        NEWGAME = 1,
        PLAY = 2,
        SHIP = 3,
        OPTION = 4,
        VIDEO = 5,
        SOUND = 6,
        BACK = 7,
        RESUME = 8,
        NEXT = 9,
        MISSION = 10,
        EXIT = 11
    };
    MenuID menuID;


    void showButton(bool on_off);
    bool getShowButton();

    void init();
    void init2();
    void onLoop();
    void onRender();

    // implement your own action in CPP code/file
    void handleEvent(SDL_Event* e);
    void onClick();
    void offClick();
    void onMouseOver();
    void onTouchDown();
    void onTouchUp();
    void onTouchMove();

    SDL_Rect getBounds();
    int getX();
    int getY();
    int getH();
    int getW();
    int mx, my;

    void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

    void onDelete();

    static CMenu* Create()
    {
        return new GetShipX();
    }

};



// Class DEFAULT button
class SoundBar : public Button
{
	int x, y, w, h;
	int xa, ya, wa, ha;
	bool displayButton;

	SDL_Surface*	theSurf;
	SDL_Texture*	theTexture;
	static SDL_Rect		theBar;
	static int wRatio;


public:

	SoundBar();
	SoundBar(int bID);
	~SoundBar();

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;
	
	
	void init();
	void init2();
	void onLoop();
	void onRender();

	
	static void setBounds(int x, int y, int h, int w);
	static SDL_Rect getBounds();
	static int getWratio();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;


	void onDelete();


	static CMenu* Create()
	{
		return new SoundBar();
	}


};



// Mission selector class
class Mission0 : public Button
{
	float x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 0;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	Mission0();
	~Mission0();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	static bool LevelON;
	static int	 missionID;

	

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new Mission0();
	}

};

// Mission selector class
class Mission1 : public Button
{
	float x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 1;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	Mission1();
	~Mission1();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	static bool LevelON;
	static int	 missionID;

	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new Mission1();
	}

};
// Mission selector class
class Mission2 : public Button
{
	float x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 2;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	Mission2();
	~Mission2();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	static bool LevelON;
	static int	 missionID;

	
	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new Mission2();
	}

};
// Mission selector class
class Mission3 : public Button
{
	float x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 3;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	Mission3();
	~Mission3();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	static bool LevelON;
	static int	 missionID;

	
	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new Mission3();
	}

};
// Mission selector class
class Mission4 : public Button
{
	float x, y, w, h;
	int xa, ya, wa, ha;
	int buttonID = 4;
	bool displayButton;
	std::string buttonTexture;

	SDL_Renderer*   buttonRenderer;
	SDL_Window*     buttonWindow;

public:
	Mission4();
	~Mission4();

	enum buttonSprite
	{
		BUTTON_SPRITE_OUT = 0,
		BUTTON_SPRITE_HOVER = 1,
		BUTTON_SPRITE_DOWN = 2,
		BUTTON_SPRITE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	buttonSprite currentSprite;

	enum MenuID
	{
		MAIN = 0,
		NEWGAME = 1,
		PLAY = 2,
		SHIP = 3,
		OPTION = 4,
		VIDEO = 5,
		SOUND = 6,
		BACK = 7,
		RESUME = 8,
		NEXT = 9,
		MISSION = 10,
		EXIT = 11
	};
	MenuID menuID;

	static bool LevelON;
	static int	 missionID;

	
	void showButton(bool on_off);
	bool getShowButton();

	void init();
	void init2();
	void onLoop();
	void onRender();

	// implement your own action in CPP code/file
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	SDL_Rect getBounds();
	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

	void onDelete();

	static CMenu* Create()
	{
		return new Mission4();
	}

};

// Mission selector class
class Mission5 : public Button
{
    float x, y, w, h;
    int xa, ya, wa, ha;
    int buttonID = 5;
    bool displayButton;
    std::string buttonTexture;

    SDL_Renderer*   buttonRenderer;
    SDL_Window*     buttonWindow;

public:
    Mission5();
    ~Mission5();

    enum buttonSprite
    {
        BUTTON_SPRITE_OUT = 0,
        BUTTON_SPRITE_HOVER = 1,
        BUTTON_SPRITE_DOWN = 2,
        BUTTON_SPRITE_UP = 3,
        BUTTON_SPRITE_TOTAL = 4
    };
    buttonSprite currentSprite;

    enum MenuID
    {
        MAIN = 0,
        NEWGAME = 1,
        PLAY = 2,
        SHIP = 3,
        OPTION = 4,
        VIDEO = 5,
        SOUND = 6,
        BACK = 7,
        RESUME = 8,
        NEXT = 9,
        MISSION = 10,
        EXIT = 11
    };
    MenuID menuID;

    static bool LevelON;
    static int	 missionID;


    void showButton(bool on_off);
    bool getShowButton();

    void init();
    void init2();
    void onLoop();
    void onRender();

    // implement your own action in CPP code/file
    void handleEvent(SDL_Event* e);
    void onClick();
    void offClick();
    void onMouseOver();
    void onTouchDown();
    void onTouchUp();
    void onTouchMove();

    SDL_Rect getBounds();
    int getX();
    int getY();
    int getH();
    int getW();
    int mx, my;

    void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

    void onDelete();

    static CMenu* Create()
    {
        return new Mission5();
    }

};

// Mission selector class
class Mission6 : public Button
{
    float x, y, w, h;
    int xa, ya, wa, ha;
    int buttonID = 6;
    bool displayButton;
    std::string buttonTexture;

    SDL_Renderer*   buttonRenderer;
    SDL_Window*     buttonWindow;

public:
    Mission6();
    ~Mission6();

    enum buttonSprite
    {
        BUTTON_SPRITE_OUT = 0,
        BUTTON_SPRITE_HOVER = 1,
        BUTTON_SPRITE_DOWN = 2,
        BUTTON_SPRITE_UP = 3,
        BUTTON_SPRITE_TOTAL = 4
    };
    buttonSprite currentSprite;

    enum MenuID
    {
        MAIN = 0,
        NEWGAME = 1,
        PLAY = 2,
        SHIP = 3,
        OPTION = 4,
        VIDEO = 5,
        SOUND = 6,
        BACK = 7,
        RESUME = 8,
        NEXT = 9,
        MISSION = 10,
        EXIT = 11
    };
    MenuID menuID;

    static bool LevelON;
    static int	 missionID;


    void showButton(bool on_off);
    bool getShowButton();

    void init();
    void init2();
    void onLoop();
    void onRender();

    // implement your own action in CPP code/file
    void handleEvent(SDL_Event* e);
    void onClick();
    void offClick();
    void onMouseOver();
    void onTouchDown();
    void onTouchUp();
    void onTouchMove();

    SDL_Rect getBounds();
    int getX();
    int getY();
    int getH();
    int getW();
    int mx, my;

    void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

    void onDelete();

    static CMenu* Create()
    {
        return new Mission6();
    }

};


// Mission selector class
class Mission7 : public Button
{
    float x, y, w, h;
    int xa, ya, wa, ha;
    int buttonID = 7;
    bool displayButton;
    std::string buttonTexture;

    SDL_Renderer*   buttonRenderer;
    SDL_Window*     buttonWindow;

public:
    Mission7();
    ~Mission7();

    enum buttonSprite
    {
        BUTTON_SPRITE_OUT = 0,
        BUTTON_SPRITE_HOVER = 1,
        BUTTON_SPRITE_DOWN = 2,
        BUTTON_SPRITE_UP = 3,
        BUTTON_SPRITE_TOTAL = 4
    };
    buttonSprite currentSprite;

    enum MenuID
    {
        MAIN = 0,
        NEWGAME = 1,
        PLAY = 2,
        SHIP = 3,
        OPTION = 4,
        VIDEO = 5,
        SOUND = 6,
        BACK = 7,
        RESUME = 8,
        NEXT = 9,
        MISSION = 10,
        EXIT = 11
    };
    MenuID menuID;

    static bool LevelON;
    static int	 missionID;


    void showButton(bool on_off);
    bool getShowButton();

    void init();
    void init2();
    void onLoop();
    void onRender();

    // implement your own action in CPP code/file
    void handleEvent(SDL_Event* e);
    void onClick();
    void offClick();
    void onMouseOver();
    void onTouchDown();
    void onTouchUp();
    void onTouchMove();

    SDL_Rect getBounds();
    int getX();
    int getY();
    int getH();
    int getW();
    int mx, my;

    void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

    void onDelete();

    static CMenu* Create()
    {
        return new Mission7();
    }

};


// Mission selector class
class Mission8 : public Button
{
    float x, y, w, h;
    int xa, ya, wa, ha;
    int buttonID = 8;
    bool displayButton;
    std::string buttonTexture;

    SDL_Renderer*   buttonRenderer;
    SDL_Window*     buttonWindow;

public:
    Mission8();
    ~Mission8();

    enum buttonSprite
    {
        BUTTON_SPRITE_OUT = 0,
        BUTTON_SPRITE_HOVER = 1,
        BUTTON_SPRITE_DOWN = 2,
        BUTTON_SPRITE_UP = 3,
        BUTTON_SPRITE_TOTAL = 4
    };
    buttonSprite currentSprite;

    enum MenuID
    {
        MAIN = 0,
        NEWGAME = 1,
        PLAY = 2,
        SHIP = 3,
        OPTION = 4,
        VIDEO = 5,
        SOUND = 6,
        BACK = 7,
        RESUME = 8,
        NEXT = 9,
        MISSION = 10,
        EXIT = 11
    };
    MenuID menuID;

    static bool LevelON;
    static int	 missionID;


    void showButton(bool on_off);
    bool getShowButton();

    void init();
    void init2();
    void onLoop();
    void onRender();

    // implement your own action in CPP code/file
    void handleEvent(SDL_Event* e);
    void onClick();
    void offClick();
    void onMouseOver();
    void onTouchDown();
    void onTouchUp();
    void onTouchMove();

    SDL_Rect getBounds();
    int getX();
    int getY();
    int getH();
    int getW();
    int mx, my;

    void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

    void onDelete();

    static CMenu* Create()
    {
        return new Mission8();
    }

};


// Mission selector class
class Mission9 : public Button
{
    float x, y, w, h;
    int xa, ya, wa, ha;
    int buttonID = 9;
    bool displayButton;
    std::string buttonTexture;

    SDL_Renderer*   buttonRenderer;
    SDL_Window*     buttonWindow;

public:
    Mission9();
    ~Mission9();

    enum buttonSprite
    {
        BUTTON_SPRITE_OUT = 0,
        BUTTON_SPRITE_HOVER = 1,
        BUTTON_SPRITE_DOWN = 2,
        BUTTON_SPRITE_UP = 3,
        BUTTON_SPRITE_TOTAL = 4
    };
    buttonSprite currentSprite;

    enum MenuID
    {
        MAIN = 0,
        NEWGAME = 1,
        PLAY = 2,
        SHIP = 3,
        OPTION = 4,
        VIDEO = 5,
        SOUND = 6,
        BACK = 7,
        RESUME = 8,
        NEXT = 9,
        MISSION = 10,
        EXIT = 11
    };
    MenuID menuID;

    static bool LevelON;
    static int	 missionID;


    void showButton(bool on_off);
    bool getShowButton();

    void init();
    void init2();
    void onLoop();
    void onRender();

    // implement your own action in CPP code/file
    void handleEvent(SDL_Event* e);
    void onClick();
    void offClick();
    void onMouseOver();
    void onTouchDown();
    void onTouchUp();
    void onTouchMove();

    SDL_Rect getBounds();
    int getX();
    int getY();
    int getH();
    int getW();
    int mx, my;

    void SetXY(int xx, int yy) { this->x = xx; this->y = yy; }

    void onDelete();

    static CMenu* Create()
    {
        return new Mission9();
    }

};



class ButtonTEST : public Button
{
	
	int x, y, h, w;
	int xa, ya, wa, ha;

public:
	ButtonTEST();
	~ButtonTEST();

	
	int buttonID;

	void init();
	void init2();
	void onLoop();
	void onRender();

	SDL_Rect getBounds();
	
	void handleEvent(SDL_Event* e);
	void onClick();
	void offClick();
	void onMouseOver();
	void onTouchDown();
	void onTouchUp();
	void onTouchMove();

	static CMenu* Create()
	{
		return new ButtonTEST();
	}

	int getX();
	int getY();
	int getH();
	int getW();
	int mx, my;

	void onDelete();
};


class CMenuFactory
{
	CMenuFactory();
	CMenuFactory(const CMenuFactory&) {}
	CMenuFactory &operator=(const CMenuFactory&) { return *this; }
	

	

public:
	~CMenuFactory();

	//typedef std::map<Panel::panelID, CMenu::CreateMenuFn>  FactoryMap;
	typedef std::map<std::string, CMenu::CreateMenuFn> FactoryMap;
	FactoryMap m_FactoryMap;

	static CMenuFactory *getFactory();

	//void set(const Panel::panelID &id, CMenu::CreateMenuFn pfnCreate);
	void set(const std::string b_name, CMenu::CreateMenuFn pfnCreate);

	CMenu *CreateMenu(const std::string b_name);

};










#endif // CMENU
