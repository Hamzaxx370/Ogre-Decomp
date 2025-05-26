#include"..\MAIN\HumanBase.cpp"
class CActPlayerBase: public CActHumanBase {
    public:
    // int CActPlayerBase_unk0;
    // int CActPlayerBase_unk4;
    // int CActPlayerBase_unk8;
    // int CActPlayerBase_unkC;
    // int CActPlayerBase_unk10;
    // int CActPlayerBase_unk14;
    CActPlayerBase(CActBase *base, int arg2)
    : CActHumanBase(base, arg2, 0xd) {
    };
};