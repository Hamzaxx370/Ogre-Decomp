/*
    TrtModule.cpp
    comment: no interface?
*/

#include <stdio.h>
#include <string.h>
//#include <eekernel.h> /* broken?? */
/* temporary solution */
extern "C" void FlushCache(int);
#define WRITEBACK_DCACHE 0
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

static LPCSTR s_szProgRoot =  "cdrom0:\\";
static LPCSTR s_szOgreVol = "OGREVOL:";
static LPCSTR s_szOgreVol2 = "OGREVO2:";
static LPCSTR s_szOgreVol3 = "OGREVO3:";
static LPCSTR s_szOgreVol4 = "OGREVO4:";

static LPCSTR s_szMainModules[] =
{
    "MAIN.BIN;1"
};

static LPCSTR s_szSubModules[] = 
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
    NULL
};
static LPCSTR* s_pszModulePaths[] = 
{
    NULL,
    s_szMainModules,
    s_szSubModules,
    NULL
};

typedef const void (*ModuleFunc)();

static const ModuleFunc s_lpfnModuleInits[] = 
{
    (ModuleFunc)ModuleInit_Game,
    (ModuleFunc)ModuleInit_UfoCatcher,
    (ModuleFunc)ModuleInit_OddOrEven,
    (ModuleFunc)ModuleInit_BattingCenter,
    (ModuleFunc)ModuleInit_Cabaret,
    (ModuleFunc)ModuleInit_Pachislot,
    (ModuleFunc)ModuleInit_CarChase,
    (ModuleFunc)ModuleInit_Health,
    (ModuleFunc)ModuleInit_Baccara,
    (ModuleFunc)ModuleInit_Roulette,
    (ModuleFunc)ModuleInit_BlackJack,
    (ModuleFunc)NULL
};

static const ModuleFunc s_lpfnModuleEnds[] = 
{
    (ModuleFunc)ModuleEnd_Game,
    (ModuleFunc)ModuleEnd_UfoCatcher,
    (ModuleFunc)ModuleEnd_OddOrEven,
    (ModuleFunc)ModuleEnd_BattingCenter,
    (ModuleFunc)ModuleEnd_Cabaret,
    (ModuleFunc)ModuleEnd_Pachislot,
    (ModuleFunc)ModuleEnd_CarChase,
    (ModuleFunc)ModuleEnd_Health,
    (ModuleFunc)ModuleEnd_Baccara,
    (ModuleFunc)ModuleEnd_Roulette,
    (ModuleFunc)ModuleEnd_BlackJack,
    (ModuleFunc)NULL
};

CTrtModule* CTrtModule::m_pInstance = NULL;
static CTrtModule s_TrtModule;

void ReleaseTrtModule() {
    return;
}

INT CreateTrtModule(LPCSTR szArg) {
    CTrtModule* pInstance;
    
    CTrtModule::m_pInstance = &s_TrtModule;
    
    pInstance = CTrtModule::m_pInstance;
    
    sprintf(pInstance->m_cProgRoot,s_szProgRoot);
    pInstance->m_eModuleID = (eMODULEID)-1;
    
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

extern bool ogre_strncmp(LPCSTR, LPCSTR, INT);

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
    
    if (ogre_strncmp(cBuf, "MEDIA4", strlen("MEDIA4")) == 0) {
        sprintf(szOut, "%s%s", s_szOgreVol4, &cBuf);
    } else if (ogre_strncmp(cBuf, "MEDIA3", strlen("MEDIA3")) == 0) {
        sprintf(szOut, "%s%s", s_szOgreVol3, &cBuf);
    } else if (ogre_strncmp(cBuf, "MEDIA2", strlen("MEDIA2")) == 0) {
        sprintf(szOut, "%s%s", s_szOgreVol2, &cBuf);
    } else {
        sprintf(szOut, "%s%s", s_szOgreVol, &cBuf);
    }
    return 0;
}


INT CTrtModule::GetOverlayFilePath(LPSTR szOut, eMODULEID eModuleId, DWORD dwNameId) {
    sprintf(szOut, "%s", s_pszModulePaths[eModuleId][dwNameId]);
    return 0;
}


INT CTrtModule::SetOverlay(DWORD dwArg1, eMODULEID dwArg2, LPVOID lpArg, DWORD dwArg3) {
    DWORD   temp_s0;
    LPVOID  temp_s1;
    INT     temp_v1;

    temp_s0 = dwArg3;
    if (dwArg1 == eMODULEID_SUB) {
        temp_v1 = m_eModuleID;
        if ((temp_v1 != dwArg2) && (temp_v1 != -1)) { /* ?????? */
            s_lpfnModuleEnds[temp_v1]();
        }
    }
    temp_s1 = mwGetGroupAddress(dwArg1);
    memcpy(temp_s1, lpArg, temp_s0);
    FlushCache(WRITEBACK_DCACHE);
    mwOverlayInit(temp_s1,  temp_s0);
    if (dwArg1 == eMODULEID_SUB) {
        s_lpfnModuleInits[dwArg2]();
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
    sprintf(ovlPath, "%s", s_pszModulePaths[mId][arg2]); // maybe -1?
    sprintf(finalPath, "%s%s", m_cProgRoot, ovlPath);
    FlushCache(WRITEBACK_DCACHE);

    wasLoaded = test(finalPath, ovlAddr, loadSize);
    
    if (mId == eMODULEID_SUB) {
        s_lpfnModuleInits[arg2]();
    }
    
    g_dwOverlayThing = 0;

    return wasLoaded;
}

CTrtModule::~CTrtModule() {

}