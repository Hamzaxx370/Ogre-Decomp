/*
    TrtModule.h
*/

#pragma once

#pragma mpwc_relax on

// Includes
#include "defines.h"

enum eMODULEID
{
    eMODULEID_MAIN = 1,
    eMODULEID_SUB = 2,
    eMODULEID_FORCE_DWORD = 0xFFFFFFFF,
};

#define MODULE_MAIN 0

class CTrtModule 
{
public:
    // Members
    eMODULEID   m_eModuleID;
    CHAR        m_cProgRoot[0x100];

    // Functions
    INT     GetFilePath(LPSTR, LPCSTR);
    INT     GetCRIFilePath(LPSTR szOut, LPCSTR szPath);
    INT     GetProgRoot(LPSTR szOut);
    INT     GetOverlayFilePath(CHAR *buf, eMODULEID mId, DWORD NameId);
    INT     SetOverlay(DWORD dwArg1, eMODULEID dwArg2, LPVOID lpArg, DWORD dwArg3);
    BOOL    LoadOverlay(eMODULEID mId, DWORD arg2);
    //CTrtModule() {}
    ~CTrtModule();

    static CTrtModule* m_pInstance;
};

INT CreateTrtModule(LPCSTR);
void ReleaseTrtModule();