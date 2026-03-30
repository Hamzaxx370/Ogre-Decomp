#ifndef MODULE_H
#define MODULE_H

// ============================================================================
//  Module.h
//  Definition of CTrtModule
// ============================================================================

#pragma mpwc_relax on

// Includes
#include "..\ogre_defs.h"

// Modules
#include "..\Modules\Baccara\Baccara.h"
#include "..\Modules\BattingCenter\BattingCenter.h"
#include "..\Modules\BlackJack\BlackJack.h"
#include "..\Modules\Cabaret\Cabaret.h"
#include "..\Modules\CarChase\CarChase.h"
#include "..\Modules\Game\Game.h"
#include "..\Modules\Health\Health.h"
#include "..\Modules\OddOrEven\OddOrEven.h"
#include "..\Modules\Pachislot\Pachislot.h"
#include "..\Modules\Roulette\Roulette.h"
#include "..\Modules\UfoCatcher\UfoCatcher.h"

enum eMODULEID
{
    eMODULEID_GROUP_MAIN,
    eMODULEID_GROUP_SUB,
    eMODULEID_FORCE_DWORD = -1,
};

// ============================================================================
//  Class CTrtModule
// ============================================================================

class CTrtModule 
{
public:
    // Members
    eMODULEID   m_eModuleID;
    CHAR        m_cBuf[0x100];

    // Functions
    INT     GetFilePath(LPSTR, LPCSTR);
    INT     GetCRIFilePath(LPSTR, LPCSTR);
    INT     GetProgRoot(LPSTR);
    INT     GetOverlayFilePath(CHAR *buf, eMODULEID mId, DWORD NameId);
    INT     SetOverlay(eMODULEID, DWORD, LPCVOID, DWORD,DWORD arg4);
    BOOL    LoadOverlay(eMODULEID mId, DWORD arg2);
    //CTrtModule() {}
    //~CTrtModule();
};

STATIC INT CreateTrtModule(LPCSTR);
CTrtModule D_00165650;
CTrtModule* D_00156308;

#endif