#include "ActPlayer_Main.cpp"

void CActPlayer::playerSetRideOnAttack(eATTACK_TYPE arg1) {
    this->CActPlayer_unk244 = 0x359;
    
    if (((this->CActPlayer_unk2F0 == 6) || (this->CActPlayer_unk2F0 == 0xA)) && ((unsigned char)arg1 == 1)) {
        playerSetRideOnScatter();
        return;
    }
    else if (((this->CActPlayer_unk40 & 4) != 0) && (this->CActPlayer_unk2F0 != 0xF)) {
        return;
    }
    this->CActPlayer_unk295 = arg1;
    this->CActHumanBase_unk3AC = 0;
    this->CActPlayer_unk1DE4 = 1;
    
    return;
}