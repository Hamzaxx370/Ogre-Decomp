/*
    SaveData.h
*/

#ifndef SAVEDATA_H
#define SAVEDATA_H

// Includes
#include "defines.h"

enum eSAVE_COLOSSEUM {
    eSAVE_COLOSSEUM_NUM = 10,
    eSAVE_COLOSSEUM_NUM_FORCE_DWORD = 0xFFFFFFFF
};

struct sdDefeat {
    WORD  wClassNum[4];
    DWORD dwClassExp[4];
};

struct sdColosseum {
    DWORD lpdwWinCount[eSAVE_COLOSSEUM_NUM];
    DWORD lpdwLoseCount[eSAVE_COLOSSEUM_NUM];
    DWORD lpdwVictoryCount[eSAVE_COLOSSEUM_NUM];
};

struct sdData {
    UCHAR dwPad[0xd20];
    sdColosseum ColosseumFlag;
    //sdDefeat 
    //DWORD dwData[0x11b8 / 4];  
};

class CSaveData {
public:
    sdData m_SaveData;
    sdData m_SaveBack;
    
    VOID GetColosseumPrize(eSAVE_COLOSSEUM, int);
    VOID BoolColosseumEntry(eSAVE_COLOSSEUM);
    DWORD GetColosseumVictoryCount(eSAVE_COLOSSEUM);
    VOID SetColosseumVictoryCount(eSAVE_COLOSSEUM, DWORD);
    DWORD GetColosseumLoseCount(eSAVE_COLOSSEUM);
    VOID SetColosseumLoseCount(eSAVE_COLOSSEUM, DWORD);
    DWORD GetColosseumWinCount(eSAVE_COLOSSEUM);
    VOID SetColosseumWinCount(eSAVE_COLOSSEUM, DWORD);
    VOID ResetDefeat();
    VOID GetLockerRate();
    VOID SaveDataResetPtr(sdData*);
    VOID SaveDataHeaderResetPtr(sdData*);
    
    /* TODO:
        figure out the inlining here.
    */
    CSaveData () {};
};

enum eULTIMATE_BOX_ESTIMATE_RANK {
    eULTIMATE_BOX_ESTIMATE_RANK_FORCE_DWORD = 0xFFFFFFFF
};

extern DWORD CalcCRC32(DWORD, UCHAR*);

class CSystemData
{
public:
    INT     unk0;
    INT     m_dwClearFlag;
    DWORD   unk8;
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

    INT  GetFlag(DWORD);
    VOID SetFlag(DWORD, DWORD);
    INT  Decode(LPVOID);
    INT  Encode(LPVOID);
    BOOL CheckCRC(LPVOID arg1) {
        return 0;
    };
    VOID CalcCRC(VOID *arg1) {
        UCHAR* buf = (UCHAR*)arg1;
        *(INT*)(buf + 0x74) = 0;
        *(INT*)(buf + 0x178) = 0;
        *(INT*)(buf + 0x178) = CalcCRC32(0x17C, buf);
    };
    VOID SetBoolClear(VOID);
    INT  GetBoolClear(VOID);
    BOOL BoolKenkaMaster();
    INT  GetUltimateBoxEstimate(DWORD);
    VOID SetUltimateBoxEstimate(DWORD, eULTIMATE_BOX_ESTIMATE_RANK);
    VOID GetSystemData(LPVOID);
    VOID SetSystemData(LPVOID);
    VOID SystemDataReset(VOID);
    VOID get_subscenario_clear_info(DWORD*, DWORD*);
    VOID get_miniscenario_clear_info(DWORD*, DWORD*);

    BOOL BoolClearEasy(VOID) {
        return m_dwClearFlag & 2;
    };
    BOOL BoolClearNormal(VOID) {
        return m_dwClearFlag & 1;
    };
    BOOL BoolClearHard(VOID) {
        return m_dwClearFlag & 4;
    };
    BOOL BoolClearSuperHard(VOID){
        return m_dwClearFlag & 8;
    };
    
    /* TODO:
        figure out the inlining here.
    */
    CSystemData() {SystemDataReset();};
};

extern CSaveData   g_SaveData;
extern CSystemData g_SystemData;

#endif