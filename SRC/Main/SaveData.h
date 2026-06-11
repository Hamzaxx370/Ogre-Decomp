#ifndef SAVEDATA_H
#define SAVEDATA_H

// ============================================================================
//  SaveData.h
//  Definition of CSystemData
// ============================================================================

// Includes
#include "..\ogre_defs.h"

enum eULTIMATE_BOX_ESTIMATE_RANK {

};

// ============================================================================
//  Class CSystemData
// ============================================================================

class CSystemData
{
public:
    // Members
    INT     unk0;
    INT     unk4;
    INT     unk8;
    CHAR    unkC;
    CHAR    unkD;
    SHORT   unkE;
    INT     unk10;
    INT     unk14;
    INT     unk18;
    INT     unk1C;
    INT     unk20;
    CHAR    unk24[0x74-0x24];
    DWORD   unk74;
    DWORD   unk78[0x40];

    // Functions
    INT     GetFlag(DWORD);
    VOID    SetFlag(DWORD, DWORD);
    INT     Decode(LPVOID);
    INT     Encode(LPVOID);
    BOOL    CheckCRC(LPVOID arg1) {
        
    };
    VOID CalcCRC(VOID *arg1) {
        UCHAR* buf = (UCHAR*)arg1;
        *(INT*)(buf + 0x74) = 0;
        *(INT*)(buf + 0x178) = 0;
        *(INT*)(buf + 0x178) = CalcCRC32(0x17C, buf);
    };
    VOID    SetBoolClear(VOID);
    INT     GetBoolClear(VOID);
    BOOL    BoolKenkaMaster();
    INT     GetUltimateBoxEstimate(DWORD);
    VOID    SetUltimateBoxEstimate(DWORD, eULTIMATE_BOX_ESTIMATE_RANK);
    LPVOID  GetSystemData(LPVOID);
    VOID    SetSystemData(LPVOID);
    VOID    SystemDataReset(VOID);
    VOID    get_subscenario_clear_info(DWORD*, DWORD*);
    VOID    get_miniscenario_clear_info(DWORD*, DWORD*);

    BOOL BoolClearEasy(VOID) {
        return this->unk4 & 2;
    };
    BOOL BoolClearNormal(VOID) {
        return this->unk4 & 1;
    };
    BOOL BoolClearHard(VOID) {
        return this->unk4 & 4;
    };
    BOOL BoolClearSuperHard(VOID){
        return this->unk4 & 8;
    };
};

#endif