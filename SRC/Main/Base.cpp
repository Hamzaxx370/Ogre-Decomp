#include"../Context.cpp"
extern "C" {
    int sprintf(char*, const char *, ...);
    int memset(void*, u32, u32);
}
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
    eACTPRIORITY_FORCE_DWORD = 0x7FFFFFFF,
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