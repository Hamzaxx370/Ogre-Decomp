#include"Action.h"
#include"TrtSystem.cpp"
#include"TrtFile.h"
#include"Util.h"
#include"PauseManager.h"
#include"FadeCtrl.h"

extern int D_153538;
void func_002D58E0();
int ogre_main() {
    D_153538 = 0x400000;
    SystemInit();
    D_157454 = new MTRandom(_Random());
    FadeCtrl::Initialize();
    D_1573A8 = new CPauseManager();
    D_1572A0 = new CActMan();
    D_1572A0->Init();
    
    do {
        FileIdle();
        func_002D58E0();
    } while (D_1572A0->Idle() >= 0);
    
    delete D_1572A0;
    delete D_1573A8;
    FadeCtrl::Finalize();
    delete D_157454;
    SystemDest();
    return 0;
}