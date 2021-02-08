//==============================================================================
#include "CAnimation.h"

//==============================================================================
CAnimation::CAnimation() {



    CurrentFrame    = 0;
    MaxFrames       = 0;
    FrameInc        = 1;

    FrameRate       = 100; //Milliseconds
    OldTime         = 0;

    Oscillate       = false;


}

//------------------------------------------------------------------------------
void CAnimation::OnAnimate() {

    if (FrameRate < 1) FrameRate = 1;
    if (OldTime + FrameRate > SDL_GetTicks()) { return; }

    unsigned short frame_counter = (SDL_GetTicks() - OldTime) / FrameRate;

    OldTime = SDL_GetTicks();

    while (frame_counter)
    {
        CurrentFrame += FrameInc;

        if(Oscillate)
        {
            if(FrameInc > 0)
            {
                if(CurrentFrame >= MaxFrames) { FrameInc = -FrameInc; }
            }
            else
            {
                if(CurrentFrame <= 0) { FrameInc = -FrameInc; }
            }
        }
        else
        {
            if(CurrentFrame >= MaxFrames) { CurrentFrame = 0; }
        }
        frame_counter--;
    }



}

//==============================================================================
void CAnimation::SetFrameRate(int Rate) {

    FrameRate = Rate;

}

//------------------------------------------------------------------------------
void CAnimation::SetCurrentFrame(int Frame) {


    if(Frame < 0 || Frame >= MaxFrames) return;

    CurrentFrame = Frame;

}

//------------------------------------------------------------------------------
int CAnimation::GetCurrentFrame() {



    //SDL_Delay(100);
    return CurrentFrame;

}

//==============================================================================
