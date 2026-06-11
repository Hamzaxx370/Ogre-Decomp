// ============================================================================
//  SaveData.cpp
//  Implementation of CSystemData
// ============================================================================

// Includes
#include "SaveData.h"

INT CSystemData::GetFlag(DWORD arg1) {
    return this->unk10 & arg1;
}

VOID CSystemData::SetFlag(DWORD arg1, DWORD arg2) {
    if (arg2) {
        this->unk10 |= arg1;
    } else {
        this->unk10 &= ~arg1;
    }
}

INT CSystemData::Decode(LPVOID arg1) {
    INT     temp_s1;
    INT*    temp_s2;
    DWORD*  var_s2;
    UCHAR*  var_s4;
    CHAR*   temp_v0;
    CHAR*   var_s3_1;
    CHAR*   var_s3;
    CSystemData* t = (CSystemData*)arg1;
    UCHAR   *buf = (unsigned char*)arg1;
    DWORD   i;
    DWORD   j;
    DWORD   oldcrc;
    UCHAR*  temp_s0;
    INT     r;

    temp_s0 = (u8*)&t->unk74;
    _SeedRandom(t->unk74);
    var_s3_1 = (char*)TmpBufLock();

    var_s3 = var_s3_1;
    var_s4 = buf;
    for (i = 0; i < 0x17C; i++) {
        // if (i == 0x74 || i == 0x75 || i == 0x76 || i == 0x77) {
        //     var_s3[i] = buf[i];
        // } else if (i == 0x0 || i == 0x1 || i == 0x2 || i == 0x3) {
        //     var_s3[i] = buf[i];
        // } else {
        //     var_s3[i] = buf[i] ^ ((_Random() % 255) + 1);
        // }
        if ((u32)&t->unk74 <= (u32)var_s4 && var_s4 < temp_s0+4) {
            *var_s3 = *var_s4;
        } else if (buf <= var_s4 && var_s4 < buf+4) {
            *var_s3 = *var_s4;
        } else {
            *var_s3 = *var_s4 ^ ((_Random() % 255) + 1);
        }
        var_s3++;
        var_s4++;
    }
    
    memcpy(buf, var_s3, 0x17C);
    TmpBufUnLock();
    var_s2 = (DWORD*)((INT)buf + 0x178);
    oldcrc = *(INT*)((INT)buf + 0x178);
    *(INT*)temp_s0 = 0;
    *(u32*)((INT)buf + 0x178) = 0;
    *var_s2 = CalcCRC32(0x17C, buf);
    // CalcCRC(arg1);
    r = oldcrc == *var_s2;
    if (r == 0)
    {
        return r;
    };
    return r = 1;
    // r = CheckCRC(buf);
    // if (r) {
    // return 1;
    // }
    // return 0;
}

INT CSystemData::Encode(LPVOID arg1) {
    INT     temp_s1;
    UCHAR*  temp_s0;
    INT*    temp_s2;
    DWORD*  var_s2;
    DWORD   i;
    CHAR*   temp_v0;
    CHAR*   var_s3;
    UCHAR*  var_s4;
    DWORD   rseed;
    DWORD   rseed2;
    DWORD   rseed1;
    UCHAR   top;
    UCHAR   btm;
    INT     old;
    UCHAR   unkbuf[0x20];
    CSystemData* t = (CSystemData*)arg1;
    UCHAR*  buf = (unsigned char*)arg1;
    DWORD   oldcrc;

    temp_s0 = (UCHAR*)&t->unk74;
    // CalcCRC(arg1);
    var_s2 = (DWORD*)((INT)buf + 0x178);
    oldcrc = *(INT*)((INT)buf + 0x178);
    *(INT*)temp_s0 = 0;
    *(DWORD*)((INT)buf + 0x178) = 0;
    *var_s2 = CalcCRC32(0x17C, buf);

    rseed1 = _Random();
    rseed = _Random();
    rseed = rseed << 0x12 | (rseed1 << 0x10 | rseed) >> 0xe;
    _SeedRandom(rseed);

    for (i = 0; i < 0x20; i++) {
        unkbuf[i] = i;
    }
    
    for (i = 0; i < 0x64; i++) {
        top = _Random() & 0x1F;
        btm = _Random() & 0x1F;
        old = unkbuf[top]; 
        unkbuf[top] = unkbuf[btm];
        unkbuf[btm] = old;
    }

    rseed2 = 0;
    for (i = 0; i < 0x20; i++) {
        u32 x = rseed & 0x1 << unkbuf[i];
        rseed2 += ((x) >> unkbuf[i]) << i;
    }
    
    var_s3 = (char*)TmpBufLock();
    *(INT*)(buf + 0x74) = rseed2;
    _SeedRandom(rseed2);
    
    var_s4 = buf;
    for (i = 0; i < 0x17C; i++) {
        if (i >= 0x74 && i <= 0x78) {
            var_s3[i] = var_s4[i];
        } else if (i >= 0 && i <= 0x4) {
            var_s3[i] = var_s4[i];
        } else {
            var_s3[i] = var_s4[i] ^ ((_Random() % 255) + 1);
        }
    }
    
    memcpy(buf, var_s3, 0x17C);
    TmpBufUnLock();
}

UCHAR D_001658B8[];
VOID CSystemData::SetBoolClear(VOID) {
    switch (D_001658B8[0]) {
        case 0:
        this->unk4 |= 0x1;
        break;
        case 1:
        this->unk4 |= 0x2;
        break;
        case 2:
        this->unk4 |= 0x4;
        break;
        case 3:
        this->unk4 |= 0x8;
        break;
    }
    
    return;
}

INT CSystemData::GetBoolClear(VOID) {
    UCHAR r ;
    // r = (INT)(BoolClearNormal()||BoolClearEasy()||BoolClearHard()||BoolClearSuperHard());
    // if (BoolClearEasy()) {
    //     r = 0;
    // } else if (BoolClearNormal()) {
    //     r = 0;
    // } else if (BoolClearHard()) {
    //     r = 0;
    // } else if (BoolClearSuperHard()) {
    //     r = 0;
    // }
    // r = r;

    return (BoolClearNormal()|| BoolClearEasy() || BoolClearHard()|| BoolClearSuperHard());
    // return r;
    // if (BoolClearEasy()||BoolClearNormal()||BoolClearHard()||BoolClearSuperHard()) return 0;
    // return (BoolClearEasy()||BoolClearNormal()||BoolClearHard()||BoolClearSuperHard()) != 0;
}

BOOL CSystemData::BoolKenkaMaster(VOID) {
    DWORD   i;
    
    for (i = 0; i <= 0x36; i++) {
        if (0x5 < this->unk78[i]) {
            this->unk78[i] = 0x5;
        }
        if (this->unk78[i] != 0x0) {
            return false;
        }
    }
    return true;
}

INT CSystemData::GetUltimateBoxEstimate(DWORD arg1) {
    if (0x5 < this->unk78[arg1]) {
        this->unk78[arg1] = 0x5;
    }
    return this->unk78[arg1];
}

VOID CSystemData::SetUltimateBoxEstimate(DWORD arg1, eULTIMATE_BOX_ESTIMATE_RANK rank) {
    if (this->unk78[arg1] > rank) {
        this->unk78[arg1] = rank;
    }
}

VOID *CSystemData::GetSystemData(LPVOID arg1) {
    memcpy(arg1, this, 0x17c);
}

VOID CSystemData::SetSystemData(LPVOID arg1) {
    if (arg1 != 0x0) {
        memcpy(this, arg1, 0x17c);
    }
    
    if (this->unk8 & 0x8) {
        D_00157614->SetWideTV(WIDETV_6);
    } else {
        D_00157614->SetWideTV(WIDETV_0);
    }
    
    if (this->unk8 & 0x80) {
        D_00157188->SetOutput(SND_OUTPUT_2);
    }
    else if (this->unk8 & 0x2) {
        D_00157188->SetOutput(SND_OUTPUT_1);
    }
    else {
        D_00157188->SetOutput(SND_OUTPUT_0);
    }
}

VOID CSystemData::SystemDataReset(VOID) {
    unsigned INT i;
    
    memset(this, 0, 0x17c);
    this->unk0 = 0x11;
    this->unk8 = 0x67;
    this->unk8 = (u8)this->unk8 | 0x100;
    this->unk20 = 0x7fffffff;

    for (i = 0; i < 0x40; i++) {
        this->unk78[i] = 5;
    }
    
    this->unkC = 0x0;
    this->unkD = 0x0;
    this->unkE = 0x0;
    this->unk10 = 0x0;
    return;
}

VOID CSystemData::get_subscenario_clear_info(DWORD *arg1, DWORD *arg2) {
    
}

VOID CSystemData::get_miniscenario_clear_info(DWORD *arg1, DWORD *arg2) {
    
}