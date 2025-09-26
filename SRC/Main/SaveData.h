#ifndef SAVEDATA_H
#define SAVEDATA_H

// ============================================================================
//  SaveData.h
//  Definition of CSystemData
// ============================================================================

// Includes
#include "..\ogre_defs.h"

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
    void    SetFlag(DWORD, DWORD);
    INT     Decode(LPVOID);
    INT     Encode(LPVOID);
    BOOL    CheckCRC(LPVOID arg1) {
        
    };
    void CalcCRC(void *arg1) {
        UCHAR* buf = (UCHAR*)arg1;
        *(int*)(buf + 0x74) = 0;
        *(int*)(buf + 0x178) = 0;
        *(int*)(buf + 0x178) = CalcCRC32(0x17C, buf);
    };
    void    SetBoolClear(void);
    INT     GetBoolClear(void);
    BOOL    BoolKenkaMaster();
    INT     GetUltimateBoxEstimate(DWORD);
    void    SetUltimateBoxEstimate(DWORD, eULTIMATE_BOX_ESTIMATE_RANK);
    LPVOID  GetSystemData(LPVOID);
    void    SetSystemData(LPVOID);
    void    SystemDataReset(void);
    void    get_subscenario_clear_info(DWORD*, DWORD*);
    void    get_miniscenario_clear_info(DWORD*, DWORD*);

    BOOL BoolClearEasy(void) {
        return this->unk4 & 2;
    };
    BOOL BoolClearNormal(void) {
        return this->unk4 & 1;
    };
    BOOL BoolClearHard(void) {
        return this->unk4 & 4;
    };
    BOOL BoolClearSuperHard(void){
        return this->unk4 & 8;
    };
};

#endif