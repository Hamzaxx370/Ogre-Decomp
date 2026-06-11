/*
    StartMain.cpp
*/

#include <mwUtils.h>
#include <sifrpc.h>
#include <sifdev.h>
#include <libcdvd.h>

#include "Target/TrtModule.h"
#include "Main/machine.h"

int main(int argc,char** argv) {
    /* not sure about these macros */
    
    /* cd/iop/sif init stuff */
    sceSifInitRpc(0);
    sceCdInit(SCECdINIT);
    while(!sceSifRebootIop("cdrom0:\\IOPRP300.IMG;1\0"));
    while(!sceSifSyncIop());
    sceSifLoadFileReset();
    sceFsReset();
    sceCdInit(SCECdINIT);
    sceCdMmode(SCECdDVD);
    sceCdDiskReady(SCECdINIT);
    /* init mw and modules */
    mwInit();
    CreateTrtModule(argv[0]);
    CTrtModule::m_pInstance->LoadOverlay(eMODULEID_GROUP_1, 0); /* load main.bin? */
    ogre_main(); /* game initialization/loop/destruction */
    ReleaseTrtModule();
    mwExit();

    return 0;
}