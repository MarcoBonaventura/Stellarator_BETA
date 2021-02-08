#ifndef _CMEDAL_H_
    #define _CMEDAL_H_

#include "CEntity.h"

#define POINTS_COUNT 2000

typedef struct
{
	float x;
	float y;
}
Point2D;



class CMedal : public CEntity {

        static SDL_Renderer* Renderer;
        SDL_Point points[POINTS_COUNT] = {};
        SDL_Color dotColor = { 255, 0, 0, 255 };
	
        bool    expired;
        float   alpha, MAXalpha, ray;
        float   x1, y1, r, k, accel, MoveX;

		Point2D cp[4];
		Point2D curve[POINTS_COUNT];

        char*   soundBeep;

        int 	selectCollider, offset, medalMove, i, j;
		int 	x2, y2, w2, h2;

		SDL_Rect	ret;
		

    public:

		CMedal(float x, float y, float h, float r, char* soundFX, eFlag F, eMove moving);
        ~CMedal();


        float Xm, Ym;

		bool OnLoad(char *File);

        void OnLoop();

        void OnInit();

        void OnRender();

        void RenderDot(float x, float y, int w, int h, SDL_Color dotColor);

        bool OnCollision(CEntity *Entity);

        void CollisionLoop();

        void shiftColliders();

        std::vector<SDL_Rect>& getColliders();

        void OnCleanup();

        void OnMove();
		void OnMove2();
		void OnMove3();
		void OnMove3(int numberOfPoints);
		void OnMove3(Point2D cp[4], int numberOfPoints, Point2D curve[POINTS_COUNT], int Flags);

		Point2D PointOnCubicBezier(Point2D cp[4], float t, float k);

        float MedalGetX();

        float MedalGetY();

        void EntityDEL();


};


#endif
