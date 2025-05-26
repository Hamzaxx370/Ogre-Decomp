#include "ActPlayer_Main.cpp"

extern tag_SHumanSync* D_153800[];

void CActPlayer::playerSetRideOnSeize() {
    s32 temp_a1;

    temp_a1 = this->CActPlayer_unk314;
    if (temp_a1 == -1) {
        return;
    }
    if (this->SetSyncAttack(D_153800[this->CActPlayer_unk2A3], (CActHumanBase*)D_1572A0->GetAction(temp_a1), 0) != 0) {
        this->CActPlayer_unk1DE4 = 2;
    }
    this->CActPlayer_unk2A6 = 0;
    
}
