#include "..\Context.cpp"

enum eACTID
{
    eACTID_MISSION = 2,
    eACTID_YACTMAN = 4,
    eACTID_PLAYERCTRL = 7,
    eACTID_PLAYER = 8,
    eACTID_ENEMY_MANAGER = 825,
    eACTID_ENEMY_START= 826,
    eACTID_ENEMY_END= 858,
    eACTID_ENEMY_CONTROL_MANAGER = 791,
    eACTID_ENEMY_CONTROL_START = 792,
    eACTID_ENEMY_CONTROL_END = 824,
    eACTID_MG_BACCARA = 1749,
};

enum eACTMODE {
    eACTMODE_NORMAL = 0,
    eACTMODE_EVENT = 1,
    eACTMODE_EVENT_STOP = 2,
    eACTMODE_PAUSE = 3,
    eACTMODE_REPLAY = 4,
    eACTMODE_STOP = 5,
    eACTMODE_MEMCARD = 6,
    eACTMODE_SPECIAL = 7,
    eACTMODE_FILEWAIT = 8,
    eACTMODE_MSSNFILEWAIT = 9,
    eACTMODE_NUM = 10,
    eACTMODE_INVALID = 2147483646,
    eACTMODE_FORCE_DWORD = 2147483647,
};

enum eACTPRIORITY {
    eACTPRIORITY_TOP = 0,
    eACTPRIORITY_CAMERA = 1,
    eACTPRIORITY_NORMAL = 2,
    eACTPRIORITY_BOTTOM = 3,
    eACTPRIORITY_NUM = 4,
    eACTPRIORITY_FORCE_DWORD = 2147483647,
};

enum eACTSPDTYPE {
    TSPDTYPE_NORMAL = 0x00,
    TSPDTYPE_PLAYER = 0x01,
    TSPDTYPE_ENEMY = 0x02,
    TSPDTYPE_CAMERA = 0x03,
    TSPDTYPE_NUM = 0x04,
    // TSPDTYPE_FORCE_DWORD = 0x43416505,
};

enum eFILECATEGORY {
    eFILECATEGORY_MAIN = 0,
    eFILECATEGORY_YACT = 0,
    eFILECATEGORY_ROFS = 1,
    eFILECATEGORY_EFFECT = 2,
    eFILECATEGORY_2D = 3,
    eFILECATEGORY_SOUND = 4,
    eFILECATEGORY_MSG = 5,
    eFILECATEGORY_STAGE = 6,
    eFILECATEGORY_MOVIE = 6,
    eFILECATEGORY_PAUSE = 7,
    eFILECATEGORY_STAGE_PEOPLE = 8,
    eFILECATEGORY_WDR = 8,
    eFILECATEGORY_CHARA = 9,
    eFILECATEGORY_EVENT = 9,
    eFILECATEGORY_ARC = 10,
    eFILECATEGORY_NUM = 11,
    eFILECATEGORY_ILLEGAL = 0x80000000,
    eFILECATEGORY_FORCE_DWORD = 0x7FFFFFFF,
};

class CActMan {
    // total size: 0x2780
public:
    CActMan();
    void systemInit();
    class CActHumanManager* GetAction(int);
    class CActBase * m_lpRootAction; // offset 0x0, size 0x4
    class CActBase * m_lpActExecRoot[4]; // offset 0x4, size 0x10
    class CActBase * * m_lplpActExecPtr[4]; // offset 0x14, size 0x10
    class CActBase * m_lpExecYetRoot[4]; // offset 0x24, size 0x10
    class CActBase * * m_lplpExecYetPtr[4]; // offset 0x34, size 0x10
    class CActBase * m_lpDelSameRoot; // offset 0x44, size 0x4
    class CActBase * * m_lplpDelSamePtr; // offset 0x48, size 0x4
    class CActBase * m_lpDelNextRoot; // offset 0x4C, size 0x4
    class CActBase * * m_lplpDelNextPtr; // offset 0x50, size 0x4
    class CActBase * m_pActTypeListRoot[5][16]; // offset 0x54, size 0x140
    class CActBase * * m_ppActTypeListPtr[5][16]; // offset 0x194, size 0x140
    unsigned int m_dwActTypeIDCount[5]; // offset 0x2D4, size 0x14
    class CActBase * m_lpActTbl[1755]; // offset 0x2E8, size 0x1D6C

    union {
        unsigned int m_dwWork[7]; // offset 0x1E54, size 0x1C
        signed int m_lWork[7]; // offset 0x1E54, size 0x1C
        float m_fWork[7]; // offset 0x1E54, size 0x1C
        void * m_lpWork[7]; // offset 0x1E54, size 0x1C
    };

    class CVisible * m_lpVisibleRoot; // offset 0x1E70, size 0x4
    class CVisible * * m_lplpVisiblePtr; // offset 0x1E74, size 0x4
    class CDrawBase * m_lpDrawBaseRoot[32]; // offset 0x1E78, size 0x80
    class CDrawBase * * m_lplpDrawBasePtr[32]; // offset 0x1EF8, size 0x80
    class CDrawBase * m_lpDrawBaseSortRoot[32]; // offset 0x1F78, size 0x80
    class CDrawBase * * m_lplpDrawBaseSortPtr[32]; // offset 0x1FF8, size 0x80
    class CDrawBase * m_lpDrawBaseSortedRoot[32]; // offset 0x2078, size 0x80
    enum eACTMODE m_ActMode; // offset 0x20F8, size 0x4
    enum eACTMODE m_ChangeActMode; // offset 0x20FC, size 0x4
    enum eACTMODE m_SaveFileWaitActMode; // offset 0x2100, size 0x4
    unsigned int m_dwFrameCount; // offset 0x2104, size 0x4
    unsigned int m_dwAnimCount; // offset 0x2108, size 0x4
    unsigned int m_dwAnimStep; // offset 0x210C, size 0x4
    class CCamera * m_lpCurrentCamera; // offset 0x2110, size 0x4
    unsigned int m_dwDrawSkipFrame; // offset 0x2114, size 0x4
    unsigned int m_dwDrawSkipFrameRegist; // offset 0x2118, size 0x4
    unsigned int m_dwInt; // offset 0x211C, size 0x4
    unsigned int m_dwIntRegist; // offset 0x2120, size 0x4
    float m_fActSpeedRatio; // offset 0x2124, size 0x4
    float m_fActSpeedSquareRatio; // offset 0x2128, size 0x4
    unsigned int m_pDrawListBuf[256]; // offset 0x212C, size 0x400
    class CDrawBase * m_pCurrentDraw; // offset 0x252C, size 0x4
    int GetAction(long);
    void Init();
    int Idle();
};

typedef struct unk_28 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2C;
} unk_28;
class CActBase {
    public:
    unsigned int m_dwActFlag; // offset 0x0, size 0x4
    unsigned int m_dwActExecFlag; // offset 0x4, size 0x4
    signed int m_ActID; // offset 0x8, size 0x4
    enum eACTSPDTYPE m_ActSpdType; // offset 0xC, size 0x1
    float m_fActSpeed; // offset 0x10, size 0x4
    float m_fActSpeedSquare; // offset 0x14, size 0x4
    unsigned int m_dwActSpeedCounter; // offset 0x18, size 0x4
    float m_fActSpeedStep; // offset 0x1C, size 0x4
    enum eACTPRIORITY m_eActPriority; // offset 0x20, size 0x4
    class CActBase * m_lpParent; // offset 0x24, size 0x4
    class CActBase * m_lpChild; // offset 0x28, size 0x4
    class CActBase * m_lpSibling; // offset 0x2C, size 0x4
    class CActBase * * m_lplpConnect; // offset 0x30, size 0x4
    class CActBase * * m_lplpActExecBefore; // offset 0x34, size 0x4
    class CActBase * m_lpActExecNext; // offset 0x38, size 0x4
    class CActBase * * m_lplpExecYetBefore; // offset 0x3C, size 0x4
    class CActBase * m_lpExecYetNext; // offset 0x40, size 0x4
    class CActBase * * m_lplpDelSameBefore; // offset 0x44, size 0x4
    class CActBase * m_lpDelSameNext; // offset 0x48, size 0x4
    class CActBase * * m_lplpDelNextBefore; // offset 0x4C, size 0x4
    class CActBase * m_lpDelNextNext; // offset 0x50, size 0x4
    class CVisible * m_lpVisibleRoot; // offset 0x54, size 0x4
    class CVisible * * m_lplpVisiblePtr; // offset 0x58, size 0x4
    class CDrawBase * m_lpDrawListRoot; // offset 0x5C, size 0x4
    class CDrawBase * * m_lplpDrawListPtr; // offset 0x60, size 0x4
    class CActBase * * m_ppListTypePtr; // offset 0x64, size 0x4
    class CActBase * m_pListTypeNext; // offset 0x68, size 0x4
    enum eFILECATEGORY m_eCategory; // offset 0x6C, size 0x4
    void DebugSetFileInfo(char *, eFILECATEGORY, char *, unsigned int);
    CActBase();
    CActBase(CActBase *, int, eACTPRIORITY);
    // virtual int ~CActBase()
    virtual void Exec0(unsigned long) ;
    virtual void Exec1(unsigned long) ;
    virtual void DrawList(void) ;
    virtual void __DeleteEffect(void) ;
    void SetDeleteSame();
    void insertActionTreeSub(CActBase *base);
    void insertActionTree(CActBase *base);
    
    
};
class CSysActionSpeed {
    public:
    f32 GetActionSpeed(eACTSPDTYPE);
    f32 GetActionSpeedSquare(eACTSPDTYPE);
};

CActMan* D_1572A0;

int D_0015727C;

CSysActionSpeed* D_001572C4;