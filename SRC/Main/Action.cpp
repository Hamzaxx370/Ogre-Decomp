#include"Action.h"
CActMan::CActMan() {

    for (unsigned int i = 0; i < 1755; i++) {
        this->m_lpActTbl[i] = 0;
    }

    this->m_lpRootAction = NULL;
    
    for (unsigned int i = 0; i < 4; i++) {
        this->m_lpActExecRoot[i] = NULL;
        this->m_lplpActExecPtr[i] = &this->m_lpActExecRoot[i];
        this->m_lpExecYetRoot[i] = NULL;
        this->m_lplpExecYetPtr[i] = &this->m_lpExecYetRoot[i];
    }

    this->m_lpDelSameRoot = NULL;
    this->m_lplpDelSamePtr = &this->m_lpDelSameRoot;
    this->m_lpDelNextRoot = NULL;
    this->m_lplpDelNextPtr = &this->m_lpDelNextRoot;
    
    this->m_lpVisibleRoot = NULL;
    this->m_lplpVisiblePtr = &this->m_lpVisibleRoot;

    for (unsigned int i = 0; i < 0x20; i++) {
        this->m_lpDrawBaseRoot[i] = 0;
        this->m_lplpDrawBasePtr[i] = &this->m_lpDrawBaseRoot[i];
        this->m_lpDrawBaseSortRoot[i] = NULL;
        this->m_lplpDrawBaseSortPtr[i] = &this->m_lpDrawBaseSortRoot[i];
    }
    
    for (unsigned int i = 0; i < 5; i++) {
        this->m_dwActTypeIDCount[i] = 0;
        for (unsigned int j = 0; j < 0x10; j++) {
            this->m_pActTypeListRoot[i][j] = NULL;
            this->m_ppActTypeListPtr[i][j] = &this->m_pActTypeListRoot[i][j];
        }
    }
    
    memset(&this->m_lpDrawBaseSortedRoot, 0, 0x80);
    
    this->m_ActMode = eACTMODE_NORMAL;
    this->m_ChangeActMode = this->m_ActMode;
    this->m_lpCurrentCamera = NULL;
    this->m_dwFrameCount = 0;
    this->m_dwAnimCount = 0;
    this->m_dwAnimStep = 0;
    this->m_dwDrawSkipFrame = 0;
    this->m_dwDrawSkipFrameRegist = 0;
    this->m_dwInt = 2;
    this->m_dwIntRegist = 2;
    this->m_fActSpeedRatio = 1.0f;
    this->m_fActSpeedSquareRatio = 1.0f;
    this->m_pCurrentDraw = NULL;
    
    this->systemInit();
    
    for (unsigned int i = 0; i < 7; i++) {
        this->m_dwWork[i] = NULL;
    }
    
    this->m_SaveFileWaitActMode = eACTMODE_INVALID;
}

inline void CActBase::insertActionTreeSub(CActBase *base) {
    CActBase* iVar2 = base->m_lpChild;
    if (iVar2 != 0x0) {
        for (CActBase* iVar1 = iVar2->m_lpSibling; iVar1 != 0x0; iVar1 = iVar1->m_lpSibling) {
            iVar2 = iVar1;
        }
        iVar2->m_lpSibling = this;
        this->m_lplpConnect = &iVar2->m_lpSibling;
    } else {
        base->m_lpChild = this;
        this->m_lplpConnect = &base->m_lpChild;
    }
    this->m_lpParent = base;
}

inline void CActBase::insertActionTree(CActBase *base) {
    if (base != 0x0) {
        if ((base->m_dwActFlag & 0x3) != 0x0) {
            this->m_dwActFlag |= 2;
        }
        this->insertActionTreeSub(base);
        // return;
    }
    
    else if (D_1572A0->m_lpRootAction != 0x0) {
        this->insertActionTreeSub(D_1572A0->m_lpRootAction);
        // return;
    } else {
        D_1572A0->m_lpRootAction = this;
        this->m_lplpConnect = 0x0;
        this->m_lpParent = (CActBase*)D_1572A0;
    }
    // return;
}

CActBase::CActBase(CActBase * base, int arg2, eACTPRIORITY arg3) {
    this->m_dwActFlag = 4;
    this->m_dwActExecFlag = 0;
    this->m_lpParent = 0;
    this->m_lpChild = 0;
    this->m_lpSibling = 0;
    this->m_lplpConnect = 0;
    this->m_lplpActExecBefore = 0;
    this->m_lpActExecNext = 0;
    this->m_lplpExecYetBefore = 0;
    this->m_lpExecYetNext = 0;
    this->m_lplpDelSameBefore = 0;
    this->m_lpDelSameNext = 0;
    this->m_lplpDelNextBefore = 0;
    this->m_lpDelNextNext = 0;
    this->m_ppListTypePtr = 0;
    this->m_pListTypeNext = 0;
    this->m_lpVisibleRoot = 0;
    this->m_lplpVisiblePtr = &this->m_lpVisibleRoot;
    this->m_lpDrawListRoot = 0;
    this->m_lplpDrawListPtr = &this->m_lpDrawListRoot;
    this->m_eActPriority = arg3;
    this->m_ActID = arg2;

    // inline?
    CActMan* aMan1 = D_1572A0;
    if ((this->m_ActID >= 0 && !((this->m_ActID >> 0x18) & 0x7F))) {
        aMan1->m_lpActTbl[this->m_ActID & 0x00FFFFFF] = this;
    }
    
    // inline?
    CActMan* aMan = D_1572A0;
    if (this->m_ActID >= 0) {
        unsigned int top = ((this->m_ActID >> 0x18) & 0x7F);
        unsigned int btm = this->m_ActID & 0xF;

        if (top < 5) {
            *aMan->m_ppActTypeListPtr[top][btm] = this;
            this->m_ppListTypePtr = aMan->m_ppActTypeListPtr[top][btm];
            aMan->m_ppActTypeListPtr[top][btm] = &this->m_pListTypeNext;
            this->m_pListTypeNext = 0;
        }
    }

    // this is an actual member function in WiiU, but the inlines don't nest for some reason
    if (base != 0x0) {
        if ((base->m_dwActFlag & 0x3) != 0x0) {
            this->m_dwActFlag |= 2;
        }
        this->insertActionTreeSub(base);
    }
    else if (D_1572A0->m_lpRootAction != 0x0) {
        this->insertActionTreeSub(D_1572A0->m_lpRootAction);
    } else {
        D_1572A0->m_lpRootAction = this;
        this->m_lplpConnect = (CActBase**)D_1572A0;
        this->m_lpParent = 0;
    }

    // inline?
    CActMan* aMan2 = D_1572A0;
    this->m_lplpExecYetBefore = aMan2->m_lplpExecYetPtr[this->m_eActPriority];
    *aMan2->m_lplpExecYetPtr[this->m_eActPriority] = this;
    aMan2->m_lplpExecYetPtr[this->m_eActPriority] = &this->m_lpExecYetNext;
    
    if (base != 0) {
        this->m_ActSpdType = base->m_ActSpdType;
    } else {
        this->m_ActSpdType = (eACTSPDTYPE)0;
    }

    this->m_fActSpeed = D_001572C4->GetActionSpeed(this->m_ActSpdType);
    this->m_fActSpeedSquare = D_001572C4->GetActionSpeedSquare(this->m_ActSpdType);
    this->m_dwActSpeedCounter = 0;
    this->m_fActSpeedStep = 0;
}
class CSysActionSpeed {
    public:
    f32 GetActionSpeed(eACTSPDTYPE);
    f32 GetActionSpeedSquare(eACTSPDTYPE);
};
