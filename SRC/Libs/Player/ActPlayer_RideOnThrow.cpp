#include "ActPlayer_Main.cpp"
extern PlayerCommand* D_006BA380[];
extern PlayerCommand* D_006BA388;
extern PlayerCommand* D_006BA38C;
extern PlayerCommand* D_006BA398;
extern PlayerCommand* D_006BA3A0;
extern PlayerCommand* D_006BA3A4;

void CActPlayer::playerSetRideOnThrow(tag_SHumanSync * arg1, unsigned char arg2) {
    long temp_a1;
    ePLAYERID_STATUS temp_v0;
    PlayerCommand* var_v1;

    if (this->CActPlayer_unk314 == -1) return;
    
    if ((this->SetSyncAttack(arg1, (CActHumanBase*)D_1572A0->GetAction(this->CActPlayer_unk314), 1) == 0)) {
        return;
    }
    
    this->CActPlayer_unk1DE4 = 3;
    this->CActPlayer_unk2A4 = arg2;
    this->CActPlayer_unk34 &= ~4;
    temp_v0 = this->searchStatusFromMTB(this->GetSyncAttackMotion());
    switch (temp_v0) {
        case 0x90:
            this->CActPlayer_unk48F8 =  D_006BA380[3];
        break;
        case 0x95:
            this->CActPlayer_unk48F8 =  D_006BA380[9];
        break;
        case 0x105:
            this->CActPlayer_unk48F8 =  D_006BA380[0];
        break;
        case 0x108:
            this->CActPlayer_unk48F8 =  D_006BA380[2];
        break;
        case 0x10B:
            this->CActPlayer_unk48F8 =  D_006BA380[6];
        break;
        case 0x10E:
            this->CActPlayer_unk48F8 =  D_006BA380[8];
        break;
        case 0x92:
        case 0x97:
        case 0x106:
        case 0x10C:
        break;
        default:
            this->CActPlayer_unk48F8 = 0;
        break;
    }
    this->setNextStatus(temp_v0, 0);
}
void CActPlayer::playerFuncRideOnThrowInit() {
    this->CActPlayer_unk107C->Ignore(1 << this->CActPlayer_unk319);
    this->CActPlayer_unk107C->Hijack( 1 << this->CActPlayer_unk319);
    this->CActPlayer_unk34 &= ~0x100;
    CActPlayerCtrl* PlayerCtrl = (CActPlayerCtrl*)D_1572A0->GetAction(this->CActPlayer_unk210);
    PlayerCtrl->ClearHistory();
}
