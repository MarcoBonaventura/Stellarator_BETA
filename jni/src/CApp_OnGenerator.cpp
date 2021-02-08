//=============================================================================
#define _CRT_SECURE_NO_DEPRECATE

#include "CGenerator.h"
#include "CPlayerStat.h"


CGenerator CGenerator::EnemyMaker;

CGenerator::CGenerator() {

    DeadTime = 0;

};

bool CGenerator::OnGenerator(long counter) {

    a = c = 0;
    b = -128;
    //int c = WWIDTH -128;

    TimeLeft = SDL_GetTicks();

    if (counter %2 == 0) { MakeSmall(); }
    else { MakeMedium(); }



    /** TESTING */
    /*
    a += (rand() % 880 + 70);
    //std::cout<<"EnemySX.X -> "<<a<<" EnemySX.Y -> "<<b<<std::endl;


    CEnemySX *EnemySX = new CEnemySX(a,b);

    if(EnemySX->OnLoad("IMG/MySpaceship_animatedSX.png", 64, 64, 0) == false)
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "CEnemySX image load ERROR!", "");
        return false;
    }


    CEntity::EntityList.push_back(EnemySX);
    std::cout<<"enemySX entity pushed\n";
    //CEnemySX::EnemySXList.push_back(EnemyZ);
    std::cout<<"enemySX LIST VECTOR pushed\n";

    char TempC[255];
    int Temp = CEntity::EntityList.size();
    int n = sprintf(TempC, "%d", Temp);
    CApp::Logger.OnLog( __FILE__, __LINE__, "entitylist size after push EnemySX", TempC);




    if (TimeLeft > 3000) //10000 ms default value
    {
        c += (rand() % 832 + 70);
        CEnemyMM *EnemyMM = new CEnemyMM(c,b);

        if(EnemyMM->OnLoad("IMG/MySpaceship_animatedMM.png", 128, 128) == false)
        {
            CApp::Logger.OnLog( __FILE__, __LINE__, "CEnemyMM image load ERROR!", "");
            return false;
        }
        CEntity::EntityList.push_back(EnemyMM);
        //CEnemyMM::EnemyMMList.push_back(EnemyZ2);

        char TempC[255];
        int Temp = CEntity::EntityList.size();
        int n = sprintf(TempC, "%d", Temp);
        CApp::Logger.OnLog( __FILE__, __LINE__, "entitylist size after push EnemyZ2", TempC);



    }
    */
    /** END TESTING CODE */



    return true;

}


bool CGenerator::MakeSmall() {

    //-----GENERATE ENEMY SMALL SX---------------------------------------------


    a += (rand() % 880 + 70);
    //std::cout<<"EnemySX.X -> "<<a<<" EnemySX.Y -> "<<b<<std::endl;

    CEnemySX *EnemySX = new CEnemySX(a, b);


    CEntity::EntityList.push_back(EnemySX);
    std::cout<<"enemySX entity pushed\n";
    //CEnemySX::EnemySXList.push_back(EnemyZ);
    std::cout<<"enemySX LIST VECTOR pushed\n";

    char TempC[255];
    int Temp = CEntity::EntityList.size();
    int n = sprintf(TempC, "%d", Temp);
    CApp::Logger.OnLog( __FILE__, __LINE__, "entitylist size after push EnemySX", TempC);

    return true;

}


bool CGenerator::MakeMedium() {

    //-----Generate Enemy Small MM---------------------------------------------

    if (TimeLeft > 5000) //10000 ms default value
    {
        c += (rand() % 832 + 70);
        CEnemyMM *EnemyMM = new CEnemyMM(c,b);

        if(EnemyMM->OnLoad("IMG/MySpaceship_animatedMM.png", 128, 128) == false)
        {
            CApp::Logger.OnLog( __FILE__, __LINE__, "CEnemyMM image load ERROR!", "");
            return false;
        }
        CEntity::EntityList.push_back(EnemyMM);
        //CEnemyMM::EnemyMMList.push_back(EnemyZ2);

        char TempC[255];
        int Temp = CEntity::EntityList.size();
        int n = sprintf(TempC, "%d", Temp);
        CApp::Logger.OnLog( __FILE__, __LINE__, "entitylist size after push EnemyZ2", TempC);



    }

    return true;

}


bool CGenerator::MakeBoss() {

    CApp::Logger.OnLog( __FILE__, __LINE__, "I'M THE BOSS!!!", "");



    //CGenerator::EnemyMaker.MakeBoss();
    CApp::Logger.OnLog( __FILE__, __LINE__, "I'M THE BOSS!!!", "");

    x = 300;
    y = -700;

    EnemyBOSS1 = new CEnemyBOSS1(x,y);

    if(EnemyBOSS1->OnLoad("IMG/THE_BOSS1.png", 300, 150) == false)
    {
        CApp::Logger.OnLog( __FILE__, __LINE__, "CEnemyBOSS1 image load ERROR!", "");

    }
    CEntity::EntityList.push_back(EnemyBOSS1);



    return true;

}


//=============================================================================
bool CGenerator::LevelCompleted(){

    if(EnemyBOSS1)
    {
        if (EnemyBOSS1->Dead == true)
        {
            DeadTime = SDL_GetTicks();

            return true;
        }
    }

    return false;

}


//=============================================================================
int CGenerator::getDeadTime() {

    return DeadTime;

}



