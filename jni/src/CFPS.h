#ifndef _CFPS_H_
    #define _CFPS_H_

#include <SDL.h>

class CFPS {

    private:

        float       LastTime;
        float       SpeedFactor;

        int         OldTime;
        int         Frames;


    public:

        CFPS();

		float			FPS;

        static      CFPS FPSControl;

        void        OnLoop();

    public:

        float       GetSpeedFactor();


        int         NumFrames;

        int         GetFPS();

        void        SetOldTime(int newTime) { OldTime -= newTime; }


};

#endif
