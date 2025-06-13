#include"ActPlayer_Main.h"

extern void* D_15735C;

void LibInit_Player()
{
    D_15735C = &SetPlayer;
}

void SetPlayer(CActBase* lpParent, SPlayerInfo* lpPlayerInfo) {
    CActPlayerCtrl* pCtrl = new CActPlayerCtrl(lpParent, eACTID_PLAYERCTRL);
    if (pCtrl)
        pCtrl->DebugSetFileInfo("CActPlayerCtrl(lpParent, eACTID_PLAYERCTRL)", (eFILECATEGORY)2, "ActPlayerCtrl.cpp", 0x154);

    CActPlayer *pPlayer = new CActPlayer(lpParent, eACTID_PLAYER, lpPlayerInfo, eACTID_PLAYERCTRL);
    if (pPlayer)
        pPlayer->DebugSetFileInfo("CActPlayer(lpParent, eACTID_PLAYER, lpPlayerInfo, eACTID_PLAYERCTRL)", (eFILECATEGORY)2, "ActPlayerCtrl.cpp", 0x156);
}