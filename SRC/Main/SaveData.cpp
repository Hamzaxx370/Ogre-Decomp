#include"SaveData.h"

int CSystemData::GetFlag(unsigned int arg1) {
    return this->unk10 & arg1;
}

void CSystemData::SetFlag(unsigned int arg1, unsigned int arg2) {
    if (arg2) {
        this->unk10 |= arg1;
    } else {
        this->unk10 &= ~arg1;
    }
}

int CSystemData::Decode(void *arg1) {
    int temp_s1;
    int* temp_s2;
    u32* var_s2;
    unsigned char* var_s4;
    char* temp_v0;
    char* var_s3_1;
    char* var_s3;
    CSystemData* t = (CSystemData*)arg1;
    unsigned char *buf = (unsigned char*)arg1;
    unsigned int i;
    unsigned int j;
    u32 oldcrc;
    u8* temp_s0;
    int r;

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
    var_s2 = (u32*)((int)buf + 0x178);
    oldcrc = *(int*)((int)buf + 0x178);
    *(int*)temp_s0 = 0;
    *(u32*)((int)buf + 0x178) = 0;
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

int CSystemData::Encode(void *arg1) {
    int temp_s1;
    u8* temp_s0;
    int* temp_s2;
    unsigned int *var_s2;
    unsigned int i;
    char* temp_v0;
    char* var_s3;
    unsigned char* var_s4;
    u32 rseed;
    u32 rseed2;
    u32 rseed1;
    u8 top;
    u8 btm;
    int old;
    unsigned char unkbuf[0x20];
    CSystemData* t = (CSystemData*)arg1;
    unsigned char *buf = (unsigned char*)arg1;
    u32 oldcrc;

    temp_s0 = (u8*)&t->unk74;
    // CalcCRC(arg1);
    var_s2 = (u32*)((int)buf + 0x178);
    oldcrc = *(int*)((int)buf + 0x178);
    *(int*)temp_s0 = 0;
    *(u32*)((int)buf + 0x178) = 0;
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
    *(int*)(buf + 0x74) = rseed2;
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

unsigned char D_001658B8[];
void CSystemData::SetBoolClear(void) {
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

int CSystemData::GetBoolClear(void) {
    u8 r ;
    // r = (int)(BoolClearNormal()||BoolClearEasy()||BoolClearHard()||BoolClearSuperHard());
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

bool CSystemData::BoolKenkaMaster(void) {
    unsigned int i;
    
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

int CSystemData::GetUltimateBoxEstimate(unsigned int arg1) {
    if (0x5 < this->unk78[arg1]) {
        this->unk78[arg1] = 0x5;
    }
    return this->unk78[arg1];
}

void CSystemData::SetUltimateBoxEstimate(unsigned int arg1, eULTIMATE_BOX_ESTIMATE_RANK rank) {
    if (this->unk78[arg1] > rank) {
        this->unk78[arg1] = rank;
    }
}

void *CSystemData::GetSystemData(void * arg1) {
    memcpy(arg1, this, 0x17c);
}

void CSystemData::SetSystemData(void *arg1) {
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

void CSystemData::SystemDataReset(void) {
    unsigned int i;
    
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

void CSystemData::get_subscenario_clear_info(unsigned int *arg1, unsigned int *arg2) {
    
}

void CSystemData::get_miniscenario_clear_info(unsigned int *arg1, unsigned int *arg2) {
    
}