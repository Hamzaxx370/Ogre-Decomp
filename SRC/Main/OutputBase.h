#include"Action.h"
class CActOutputBase : public CActBase {
    // total size: 0x88
    public:
    int Output_unk0[8];
    CActOutputBase(CActBase * base, int arg2) : CActBase(base, arg2, (eACTPRIORITY)2) {
        memset(this->Output_unk0, 0, sizeof(Output_unk0));
    }
    virtual void __GetNodeMatrix(void*, unsigned long) ;
    virtual void __GetEventNodeIndex(long *, unsigned long) ;
    virtual void __SetHumanCondition(void) ;
};