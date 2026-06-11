/*
    TrtModule.cpp
    comment: no interface?
*/

#include <stdio.h>
#include <string.h>
//#include <eekernel.h> /* broken?? */
#include <mwUtils.h>

#include "Target/TrtModule.h"

/* includes for module init/end */
#include "Modules\Baccara\Baccara.h"
#include "Modules\BattingCenter\BattingCenter.h"
#include "Modules\BlackJack\BlackJack.h"
#include "Modules\Cabaret\Cabaret.h"
#include "Modules\CarChase\CarChase.h"
#include "Modules\Game\Game.h"
#include "Modules\Health\Health.h"
#include "Modules\OddOrEven\OddOrEven.h"
#include "Modules\Pachislot\Pachislot.h"
#include "Modules\Roulette\Roulette.h"
#include "Modules\UfoCatcher\UfoCatcher.h"

LPCSTR szCDRom0 =  "cdrom0:\\";
LPCSTR szOgreVol4 = "OGREVO4:";
LPCSTR szOgreVol3 = "OGREVO3:";
LPCSTR szOgreVol2 = "OGREVO2:";
LPCSTR szOgreVol = "OGREVOL:";

LPCSTR pMainModule[] =
{
    "MAIN.BIN;1"
};

LPCSTR pMedia4Modules[] = 
{
    "Media4\\Module\\game.bin",
    "Media4\\Module\\ufocatcher.bin",
    "Media4\\Module\\oddoreven.bin",
    "Media4\\Module\\battingcenter.bin",
    "Media4\\Module\\cabaret.bin",
    "Media4\\Module\\pachislot.bin",
    "Media4\\Module\\carchase.bin",
    "Media4\\Module\\health.bin",
    "Media4\\Module\\baccara.bin",
    "Media4\\Module\\roulette.bin",
    "Media4\\Module\\blackjack.bin",
};
LPCSTR const *pModules[] = 
{
    { (LPCSTR const*)0 },
    pMainModule,
    pMedia4Modules
};

VOID (*g_lpfnModuleInit[])() = 
{
    ModuleInit_Game,
    ModuleInit_UfoCatcher,
    ModuleInit_OddOrEven,
    ModuleInit_BattingCenter,
    ModuleInit_Cabaret,
    ModuleInit_Pachislot,
    ModuleInit_CarChase,
    ModuleInit_Health,
    ModuleInit_Baccara,
    ModuleInit_Roulette,
    ModuleInit_BlackJack,
};

VOID (*g_lpfnModuleEnd[])() = 
{
    ModuleEnd_Game,
    ModuleEnd_UfoCatcher,
    ModuleEnd_OddOrEven,
    ModuleEnd_BattingCenter,
    ModuleEnd_Cabaret,
    ModuleEnd_Pachislot,
    ModuleEnd_CarChase,
    ModuleEnd_Health,
    ModuleEnd_Baccara,
    ModuleEnd_Roulette,
    ModuleEnd_BlackJack,
};

CTrtModule* CTrtModule::m_pInstance = NULL;
CTrtModule s_TrtModule;

void ReleaseTrtModule() {
    return;
}

INT CreateTrtModule(LPCSTR szArg) {
    CTrtModule::m_pInstance = &s_TrtModule;
    sprintf(CTrtModule::m_pInstance->m_cProgRoot,"cdrom0:\\");
    CTrtModule::m_pInstance->m_eModuleID = (eMODULEID)-1;
    return 0;
}


INT CTrtModule::GetProgRoot(LPSTR szOut) {
    sprintf(szOut, "%s", m_cProgRoot);
    return 0;
}


INT CTrtModule::GetCRIFilePath(LPSTR szOut, LPCSTR szPath) {
    sprintf(szOut, "%s", szPath);
    return 0;
}

extern INT ogre_strcmp(LPSTR, LPSTR, INT);

INT CTrtModule::GetFilePath(LPSTR szOut, LPCSTR szPath) {
    CHAR    cBuf[0x100 + 1]; // 256 + NUL
    DWORD   dwLen;
    DWORD   i;

    strcpy(cBuf, szPath);
    dwLen = strlen(cBuf);

    // convert to uppercase
    for (i = 0; i < dwLen; i++) {
        if (cBuf[i] >= 'a' && cBuf[i] <= 'z') {
            cBuf[i] -= 'a'-'A';
        }
    }
    
    if (ogre_strcmp(cBuf, "MEDIA4", strlen("MEDIA4")) == 0) {
        sprintf(szOut, "%s%s", szOgreVol4, cBuf);
    } else if (ogre_strcmp(cBuf, "MEDIA3", strlen("MEDIA3")) == 0) {
        sprintf(szOut, "%s%s", szOgreVol3, cBuf);
    } else if (ogre_strcmp(cBuf, "MEDIA2", strlen("MEDIA2")) == 0) {
        sprintf(szOut, "%s%s", szOgreVol2, cBuf);
    } else {
        sprintf(szOut, "%s%s", szOgreVol, cBuf);
    }
    return 0;
}


INT CTrtModule::GetOverlayFilePath(LPSTR szOut, eMODULEID eModuleId, DWORD dwNameId) {
    sprintf(szOut, "%s", pModules[eModuleId][dwNameId]);
    return 0;
}


INT CTrtModule::SetOverlay(DWORD dwArg1, eMODULEID dwArg2, LPVOID lpArg, DWORD dwArg3) {
    DWORD   temp_s0;
    LPVOID  temp_s1;
    INT     temp_v1;

    temp_s0 = dwArg3;
    if (dwArg1 == 2) {
        temp_v1 = m_eModuleID;
        if ((temp_v1 != dwArg2) && (temp_v1 != -1)) { /* ?????? */
            g_lpfnModuleEnd[temp_v1]();
        }
    }
    temp_s1 = mwGetGroupAddress(dwArg1);
    memcpy(temp_s1, lpArg, temp_s0);
    //FlushCache(WRITEBACK_DCACHE);
    mwOverlayInit(temp_s1,  temp_s0);
    if (dwArg1 == 2) {
        g_lpfnModuleInit[dwArg2]();
        m_eModuleID = dwArg2;
    }
    return 0;
}

INT func_001002A0(LPSTR, LPVOID);   
CHAR g_dwOverlayThing;

STATIC INLINE INT test(LPSTR finalPath, LPVOID ovlAddr, INT loadSize){
    INT wasLoaded = false;
    loadSize = mwBload(finalPath, ovlAddr);
    if (loadSize > 0x0) {
        mwOverlayInit(ovlAddr, loadSize);
        wasLoaded = true;
    }
    return wasLoaded;
}

BOOL CTrtModule::LoadOverlay(eMODULEID mId, DWORD arg2) {
    LPVOID  ovlAddr;
    INT     loadSize;
    BOOL    wasLoaded;
    CHAR    finalPath [0x100 + 1]; // 0x100 + NUL
    CHAR    ovlPath [0x100 + 1]; // 0x100 + NUL
    
    ovlAddr = mwGetGroupAddress(mId);
    sprintf(ovlPath, "%s", pModules[mId][arg2]); // maybe -1?
    sprintf(finalPath, "%s%s", m_cProgRoot, ovlPath);
    //FlushCache(WRITEBACK_DCACHE);

    wasLoaded = test(finalPath, ovlAddr, loadSize);
    
    if (mId == 0x2) {
        g_lpfnModuleInit[arg2]();
    }
    
    g_dwOverlayThing = 0;

    return wasLoaded;
}

CTrtModule::~CTrtModule() {

}