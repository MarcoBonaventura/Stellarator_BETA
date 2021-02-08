//==============================================================================
#ifndef _CENTITY_H_
    #define _CENTITY_H_

#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <string>
#include <exception>
#include <map>

#include "Carea.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CAnimation.h"
#include "Texture.h"
#include "CTile.h"
#include "CSoundBank.h"



//#include <boost/smart_ptr/shared_ptr.hpp>


enum eType
{
    ENTITY_TYPE_GENERIC     = 0,
    ENTITY_TYPE_PLAYER      = 1,
    ENTITY_TYPE_BOSS        = 2,
    ENTITY_TYPE_MyBULLET    = 3,
    ENTITY_TYPE_BULLET_E    = 4,
    ENTITY_TYPE_PARTICLE    = 5,
    ENTITY_TYPE_MyBOMB      = 6,
    ENTITY_TYPE_MEDAL       = 7,
	ENTITY_TYPE_GAMMARAY	= 8,
    ENTITY_TYPE_LASER       = 9,
    ENTITY_TYPE_ENEMY		= 10
};

enum eSize
{
    ENTITY_SIZE_PP          = 0,
    ENTITY_SIZE_SX          = 1,
    ENTITY_SIZE_SSX         = 2,
    ENTITY_SIZE_MM          = 3,
    ENTITY_SIZE_BB          = 4,
    ENTITY_SIZE_BOSS        = 5,
    ENTITY_SIZE_BOMB        = 6,
    ENTITY_SIZE_ROCKET      = 7,
    ENTITY_SIZE_MEDAL       = 8,
    ENTITY_SIZE_PB          = 9,
    ENTITY_SIZE_AST         = 10,
    ENTITY_SIZE_JOLLY       = 11,
    ENTITY_SIZE_NONE		= 12
};

enum eFlag
{
    ENTITY_FLAG_NONE        = 0,
    ENTITY_FLAG_GRAVITY     = 1,
    ENTITY_FLAG_GHOST       = 2,
    ENTITY_FLAG_MAPONLY     = 3,
    ENTITY_FLAG_ENEMY_S     = 4,
    ENTITY_FLAG_ENEMY_M     = 5,
	ENTITY_FLAG_ENEMY_M1	= 6,
	ENTITY_FLAG_ENEMY_M2	= 7,
    ENTITY_FLAG_ENEMY_F     = 8,
    ENTITY_FLAG_PLAYER      = 9,
    ENTITY_FLAG_BOSS        = 10,
    ENTITY_FLAG_GAMMARAY    = 11,
    ENTITY_FLAG_MyBULLET	= 12
};

enum eMove
{
	BEZIER 		= 0,
	LOGARITMIC 	= 1,
	BEZIER_BOSS = 2,
	MOVE_DX 	= 3,
	MOVE_SX 	= 4,
	MOVE_DOWN 	= 5,
	ESCAPE_DX 	= 6,
	ESCAPE_SX 	= 7,
	ROTATE 		= 8,
	FALLING 	= 9,
	SNAKE 		= 10,
	PYRAMID     = 11,
	DIAMOND     = 12,
	GRID        = 13,
    ASTEROID    = 14,
    NONE        = 15
};


enum EnemyFireMode
{
    NORMAL          = 0,
    SNIPER          = 1,
    ROCKET          = 2,
    SMART           = 3
};

enum MedalFire
{
    MEDAL_NONE      = 0,
    MEDAL_TRIPLE 	= 1,
    MEDAL_PENTA		= 2,
    MEDAL_ROCKET	= 3,
    MEDAL_GAMMARAY  = 4,
    MEDAL_COMBOTOT  = 5

};

enum BossPath
{
    BOSS_LF_RX      = 0,
    BOSS_ABC        = 1,
    BOSS_RANDOM     = 2,
    BOSS_SEEK       = 3,
    BOSS_CIRCUIT    = 4,
    BOSS_VANISH     = 5
};

enum Effect_type {
	EXPLOSION,
	FLARES_BIG,
	FLARES_SMALL,
	SMOOKY,
	COMBO_EFFECT
};


struct Vector {

    float X;
    float Y;

    Vector()
    {
        X = 0.0f;
        Y = 0.0f;
    }


};


//==============================================================================
class CEntity {

    protected:

        CAnimation      Anim_Control;

        SDL_Renderer*   entityRenderer;

        SDL_Window*     Window;

        SDL_Surface*    PrimarySurface;

        static int current_ID;
        static int counter_BRO;

        float       SpeedX;
        float       SpeedY;

        float       AccelX;
        float       AccelY;
        float		kAcc;

        double      degrees, alpha;

		int   		alpha_channel;
        int        	Col_X;
        int        	Col_Y;
        int        	Col_Width;
        int        	Col_Height;


    public:

		static std::vector<CEntity*>EntityList;
		static std::map<int, CEntity*> EntityMap;
		static std::map<int, CEntity*> TargetEnemyMap;

		static const int DOT_VEL = 1;

		std::string     entityTexture;

		bool collision;

		int ID, BRO;


		long time_lapse, laser_time, check_time;

        //int             ID;

        int             X, X1, X2, Xe, Xb;
        int             Y, Y1, Y2, Ye, Yb;

        int             mx, my;

        int             ib, kb;

        int             *XXP = &X;
        int             *YYP = &Y;
        int             *pX2 = &X2;
        int             *pY2 = &Y2;

        static int      Xp, Yp;

        int             Width, W2;
        int             Height, H2;

        int 			selected;

        int             counter;
		int				targetID;

        //int             PlayerHealth;
        int             PlayerScore;
        int             playerHonor;
        int             medalHonor;
        int             medalReward;

        int 			stamina;

        //-------------------------
        //SDL2 collision properties
        int mPosX, mPosY;
        //The velocity of the dot
		int mVelX, mVelY;
        /* Dot's collision boxes */
	    std::vector<SDL_Rect> mColliders;
	    int r;
        //Moves the collision boxes relative to the dot's offset
		//-------------------------

        int         AnimState;

        int         Sound_explSX, Sound_PlayerFire, Sound_PlayerXPL;

        bool        MoveLeft;
        bool        MoveRight;
        bool        MoveUp;
        bool        MoveDown;

        bool        boom;

        char        *anim_filename;


        int         Type;
        int         Size;
        int         Flags;
        int 		Move;
        eMove       motion;
        int 		Pattern;
        int         EnemyFireMode;

        bool        Dead = false;
        bool        bJolly = false;


        int         shot, fire, hit;
        int         TimeStart;
        int         triggerFIRE;
        int         id_MM2 = 0;
        SDL_Point   EnemyLimit;
        SDL_Point 	enemyOFFSET;

        Vector      position;
        Vector      origin;

        float       MaxSpeedX;
        float       MaxSpeedY;
        float 		MinSpeedX;
        float 		MinSpeedY;
        float		MaxSpeed;




    public:

		CEntity();
		//CEntity() : ID(current_ID++) {};

		virtual ~CEntity();

	public:

        virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        virtual bool OnLoad(char* File, int Width, int Height);

        virtual bool OnLoad(char* File, int RGBalpha);

        virtual bool OnLoad(char* File);

        virtual void OnLoop();

        virtual void OnRender();

        void OnCleanup();

        virtual void EntityDEL();

        virtual void OnDelete();

		virtual void OnAnimate();

		virtual bool OnCollision(CEntity* Entity);

		virtual void CollisionLoop();

		//new SDL2 collision engine
		//virtual void move( std::vector<SDL_Rect>& otherColliders );
		std::vector<SDL_Rect>& getColliders();
        virtual void shiftColliders();

        virtual void OnFire();

        bool canFIRE();
        bool booleanFIRE();

        virtual void IA();

		//virtual void OnBoom(int x, int y);

		static int GetX();
		static int GetY();

		static CEntity* GetEntity(int temp_ID);

		int GetEntityMoving();

		virtual int		EnemyGetX();
		virtual int		EnemyGetY();

		virtual float	PlayerGetX();
		virtual float 	PlayerGetY();

		bool    Jump();

		bool    Crash();

		void    ScoreInc();

    public:

        void    OnMove(float MoveX, float MoveY);

        void    StopMove();
		void    StopMoveX();
		void    StopMoveY();

    public:
        //bool    Collides(int oX, int oY, int oW, int oH);

    private:
        //bool    PosValid(int NewX, int NewY);

        //bool    PosValidEntity(CEntity* Entity, int NewX, int NewY);



    public:

        SDL_Rect GetBounds();

        SDL_Rect NormalizeBounds(const SDL_Rect& rect);

        //bool CollisionEntity(CEntity *Entity, int NewX, int NewY);

        static SDL_Rect Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB);

        //bool CheckCollision(CEntity *Entity); OLD****

        //SDL2 Collision Engine
        //bool CheckCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);
        void CheckCollision(CEntity* Entity);
        bool GetAlphaXY(CEntity* Entity, int x, int y);


};


class CEntityCol {

    public:
        static std::vector<CEntityCol>  EntityColList;

    public:
        CEntity *EntityA;
        CEntity *EntityB;


    public:
        CEntityCol();
};

//==============================================================================



#endif
