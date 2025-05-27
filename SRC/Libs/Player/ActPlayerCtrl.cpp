#include"..\..\Main\Action.h"
class CActPlayerCtrl : public CActBase
{
    public:
    int CActPlayerCtrl_unk0;
    int CActPlayerCtrl_unk4;
    int CActPlayerCtrl_unk8;
    int CActPlayerCtrl_unkC;
    int CActPlayerCtrl_unk10;
    int CActPlayerCtrl_unk14;
    int CActPlayerCtrl_unk18;
    int CActPlayerCtrl_unk1C;
    int CActPlayerCtrl_unk20;
    int CActPlayerCtrl_unk24;
    int CActPlayerCtrl_unk28;
    int CActPlayerCtrl_unk2C;
    int CActPlayerCtrl_unk30;
    int CActPlayerCtrl_unk34;
    int CActPlayerCtrl_unk38;
    int CActPlayerCtrl_unk3C;
    int CActPlayerCtrl_unk40;
    int CActPlayerCtrl_unk44;
    char CActPlayerCtrl_unk48;
    char CActPlayerCtrl_unk49;
    char CActPlayerCtrl_unk4A;
    char CActPlayerCtrl_unk4B;
    int CActPlayerCtrl_unk4C;
    CActPlayerCtrl(CActBase *base, int arg1) : CActBase(base, arg1, (eACTPRIORITY)eACTPRIORITY_NORMAL) {};
    void ClearHistory();
};

void CActPlayerCtrl::ClearHistory() {
    this->CActPlayerCtrl_unk48 = 0;
    this->CActPlayerCtrl_unk49 = 0;
    __gh_memclr32(this->CActPlayerCtrl_unk44, 0,0x3C0);
}
