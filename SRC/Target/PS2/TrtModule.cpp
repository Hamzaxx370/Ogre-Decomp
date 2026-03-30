// ============================================================================
//  Module.cpp
//  Implementation of CTrtModule
// ============================================================================

// Includes
#include"../TrtModule.h"

const char* szCDRom0 =  "cdrom0:\\";
const char* szOgreVol4 = "OGREVO4:";
const char* szOgreVol3 = "OGREVO3:";
const char* szOgreVol2 = "OGREVO2:";
const char* szOgreVol = "OGREVOL:";

const char* pMainModule[] =
{
    "MAIN.BIN;1"
};

const char* pMedia4Modules[] = 
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
const char* const *pModules[] = 
{
    { (const char* const*)0 },
    pMainModule,
    pMedia4Modules
};

//TO DO
//Find the name for this
int func_0011A828(void*, unsigned int, unsigned int);                         /* extern */

void (*pModuleInit[])() = 
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

void (*pModuleEnd[])() = 
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


static INT CreateTrtModule(const char* arg0) {
    CTrtModule* s0;
    D_00156308 = &D_00165650;
    s0 = D_00156308;
    sprintf(s0->m_cBuf, szCDRom0);
    s0->m_eModuleID = eMODULEID_FORCE_DWORD;
    return 0;
}


INT CTrtModule::GetProgRoot(LPSTR outBuf) {
    sprintf(outBuf, "%s", m_cBuf);
    return 0;
}


INT CTrtModule::GetCRIFilePath(LPSTR outBuf, LPCSTR path) {
    sprintf(outBuf, "%s", path);
    return 0;
}

int CTrtModule::GetFilePath(LPSTR outBuf, LPCSTR fname) {
    CHAR    tBuf[0x100 + 1]; // 256 + NUL
    DWORD   nameLen;
    DWORD   i;

    strcpy(tBuf, fname);
    nameLen = strlen(tBuf);

    // convert to uppercase
    for (i = 0; i < nameLen; i++) {
        if (tBuf[i] >= 'a' && tBuf[i] <= 'z') {
            tBuf[i] -= 'a'-'A';
        }
    }
    
    if (func_4195D0(tBuf, "MEDIA4", strlen("MEDIA4")) == 0) {
        sprintf(outBuf, "%s%s", szOgreVol4, &tBuf);
    } else if (func_4195D0(tBuf, "MEDIA3", strlen("MEDIA3")) == 0) {
        sprintf(outBuf, "%s%s", szOgreVol3, &tBuf);
    } else if (func_4195D0(tBuf, "MEDIA2", strlen("MEDIA2")) == 0) {
        sprintf(outBuf, "%s%s", szOgreVol2, &tBuf);
    } else {
        sprintf(outBuf, "%s%s", szOgreVol, &tBuf);
    }
    return 0;
}


int CTrtModule::GetOverlayFilePath(LPSTR buf, eMODULEID mId, DWORD NameId) {
    sprintf(buf, "%s", pModules[mId][NameId]);
    return 0;
}


int CTrtModule::SetOverlay(eMODULEID arg0, DWORD arg1 , LPCVOID arg2, DWORD arg3,DWORD arg4) {

    DWORD   temp_s0;
    LPVOID  temp_s1;
    INT     temp_v1;

    temp_s0 = arg4;
    if (arg1 == 2) {
        temp_v1 = m_eModuleID;
        if ((temp_v1 != (INT)arg2) && (temp_v1 != -1)) {
            pModuleEnd[temp_v1]();
        }
    }
    temp_s1 = mwGetGroupAddress(arg1);
    func_0011A828(temp_s1, arg3, temp_s0);
    FlushCache(0);
    mwOverlayInit(temp_s1,  temp_s0);
    if (arg1 == 2) {
        pModuleInit[(INT)arg2]();
        m_eModuleID = (eMODULEID)(INT)arg2;
    }
    return 0;
}

INT func_001002A0(LPSTR, LPVOID);   
CHAR D_00156300;

static inline INT test(LPSTR finalPath, LPVOID ovlAddr, INT loadSize){
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
    sprintf(finalPath, "%s%s", m_cBuf, ovlPath);
    FlushCache(WRITEBACK_DCACHE);

    wasLoaded = test(finalPath, ovlAddr, loadSize);
    
    if (mId == 0x2) {
        pModuleEnd[arg2]();
    }
    
    D_00156300 = 0;

    return wasLoaded;
}
