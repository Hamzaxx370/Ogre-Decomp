#include"Action.h"
enum eYACT_MODE {
    eYACT_MODE_NON = 0,
    eYACT_MODE_YACT = 1,
    eYACT_MODE_REACTION = 2,
    eYACT_MODE_WAIT = 3,
    eYACT_MODE_INVISIBLE = 4,
    eYACT_MODE_BREAK = 5,
    eYACT_MODE_YET = 6,
    eYACT_MODE_NUM = 7,
    eYACT_MODE_FORCE_DWORD = 2147483647,
};

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