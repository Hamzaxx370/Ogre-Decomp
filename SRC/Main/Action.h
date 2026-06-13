/*
    Action.h
*/

#ifndef ACTION_H
#define ACTION_H

#include "defines.h"

typedef int ACTID;

enum eFILECATEGORY {
    eFILECATEGORY_FORCE_DWORD = 0xFFFFFFFF
};

enum eACTSPDTYPE {
};

enum eACTPRIORITY {
    eACTPRIORITY_FORCE_DWORD = 0xFFFFFFFF
};

class CActBase {
public:
    DWORD m_dwActFlag; // offset 0x0, size 0x4
    DWORD m_dwActExecFlag; // offset 0x4, size 0x4
    ACTID m_ActID; // offset 0x8, size 0x4
    eACTSPDTYPE m_ActSpdType; // offset 0xC, size 0x1
    FLOAT m_fActSpeed; // offset 0x10, size 0x4
    FLOAT m_fActSpeedSquare; // offset 0x14, size 0x4
    DWORD m_dwActSpeedCounter; // offset 0x18, size 0x4
    FLOAT m_fActSpeedStep; // offset 0x1C, size 0x4
    eACTPRIORITY m_eActPriority; // offset 0x20, size 0x4
    CActBase * m_lpParent; // offset 0x24, size 0x4
    CActBase * m_lpChild; // offset 0x28, size 0x4
    CActBase * m_lpSibling; // offset 0x2C, size 0x4
    CActBase * * m_lplpConnect; // offset 0x30, size 0x4
    CActBase * * m_lplpActExecBefore; // offset 0x34, size 0x4
    CActBase * m_lpActExecNext; // offset 0x38, size 0x4
    CActBase * * m_lplpExecYetBefore; // offset 0x3C, size 0x4
    CActBase * m_lpExecYetNext; // offset 0x40, size 0x4
    CActBase * * m_lplpDelSameBefore; // offset 0x44, size 0x4
    CActBase * m_lpDelSameNext; // offset 0x48, size 0x4
    CActBase * * m_lplpDelNextBefore; // offset 0x4C, size 0x4
    CActBase * m_lpDelNextNext; // offset 0x50, size 0x4
    class CVisible * m_lpVisibleRoot; // offset 0x54, size 0x4
    class CVisible * * m_lplpVisiblePtr; // offset 0x58, size 0x4
    class CDrawBase * m_lpDrawListRoot; // offset 0x5C, size 0x4
    class CDrawBase * * m_lplpDrawListPtr; // offset 0x60, size 0x4
    CActBase * * m_ppListTypePtr; // offset 0x64, size 0x4
    CActBase * m_pListTypeNext; // offset 0x68, size 0x4
    eFILECATEGORY m_eCategory; // offset 0x6C, size 0x4
    
    virtual ~CActBase();
};

#endif