#ifndef __CAPPSTATENONE_H__
    #define __CAPPSTATENONE_H__

#include "CAppState.h"

class CAppStateNone : public CAppState {

    private:

        static CAppStateNone Instance;

    private:

        CAppStateNone();

    public:

        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender();

    public:

        static CAppStateNone* GetInstance();


};

#endif
