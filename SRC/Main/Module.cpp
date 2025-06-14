#include"Module.h"


static int CreateTrtModule(char const* arg0) {
    CTrtModule* s0;
    TrtModulePtr = &TrtModule;
    s0 = TrtModulePtr;
    sprintf(s0->m_Buffer, D_00153500);
    s0->m_ModuleID = (eMODULEID)-1;
    return 0;
}


int CTrtModule::GetProgRoot(char* outBuf) {
    sprintf(outBuf, "%s", this->m_Buffer);
    return 0;
}


int CTrtModule::GetCRIFilePath(char* outBuf, char const *path) {
    sprintf(outBuf, "%s", path);
    return 0;
}

#pragma mpwc_relax on

#define sprintf func_0011D568
#define strcpy func_0011DCF8
#define strlen func_0011DE10
extern "C" {
    int sprintf(void*, const char*, ...);
    char* strcpy(char* dest, const char* src);
    unsigned int strlen(const char*);

    // from main overlay
    bool func_4195D0(char*, const char*, unsigned int);
}


int CTrtModule::GetFilePath(char* outBuf, char const *fname) {
    char tBuf[0x100 + 1]; // 256 + NUL
    unsigned int nameLen;
    unsigned int i;

    strcpy(tBuf, fname);
    nameLen = strlen(tBuf);

    // convert to uppercase
    for (i = 0; i < nameLen; i++) {
        if (tBuf[i] >= 'a' && tBuf[i] <= 'z') {
            tBuf[i] -= 'a'-'A';
        }
    }
    
    if (func_4195D0(tBuf, "MEDIA4", strlen("MEDIA4")) == 0) {
        sprintf(outBuf, "%s%s", D_00153510, &tBuf);
    } else if (func_4195D0(tBuf, "MEDIA3", strlen("MEDIA3")) == 0) {
        sprintf(outBuf, "%s%s", D_0015350C, &tBuf);
    } else if (func_4195D0(tBuf, "MEDIA2", strlen("MEDIA2")) == 0) {
        sprintf(outBuf, "%s%s", D_00153508, &tBuf);
    } else {
        sprintf(outBuf, "%s%s", D_00153504, &tBuf);
    }
    return 0;
}


int CTrtModule::GetOverlayFilePath(char* arg1, eMODULEID arg2, unsigned int arg3) {
    sprintf(arg1, &D_0013A100, D_00136CF0[arg2][arg3]);
    return 0;
}

int CTrtModule::SetOverlay(eMODULEID arg0, unsigned int arg1 , void const * arg2, unsigned int arg3,unsigned int arg4) {

    unsigned int  temp_s0;
    eMODULEID* temp_s1;
    int temp_v1;
    temp_s0 = arg4;
    if (arg1 == 2) {
        temp_v1 = this->m_ModuleID;
        if ((temp_v1 != (int)arg2) && (temp_v1 != -1)) {
            ((void (*)())D_0013A0D0[temp_v1])();
        }
    }
    temp_s1 = (eMODULEID*)*(&D_00153490[arg1]);
    func_0011A828(temp_s1, arg3, temp_s0);
    func_00105420(0);
    func_00100350(temp_s1,  temp_s0);
    if (arg1 == 2) {
        ((void (*)())D_0013A0A0[(int)arg2])();
        this->m_ModuleID = (eMODULEID)(int)arg2;
    }
    return 0;
}


int CTrtModule::LoadOverlay(eMODULEID* arg0, unsigned int arg1,unsigned int arg2) {
    char sp160[272];
    char sp50[272];
    int temp_s1 = (D_00153490[(int)arg0]);
    int temp_v0;
    int var_s3;

    sprintf(sp50, "%s", D_00136CF0[(int)arg0][arg1]);
    sprintf(sp160, "%s%s", m_Buffer, &sp50);
    func_00105420(0);
    var_s3 = 0;
    temp_v0 = func_001002A0(sp160, temp_s1);
    if (temp_v0 > 0) {
        func_00100350((eMODULEID*)temp_s1, (unsigned int)temp_v0);
        var_s3 = 1;
    }
    if ((int)arg0 == 2) {
        (*(void (**)())&D_0013A0A0[arg1])();
    }
    D_00156300 = 0;
    return var_s3;
}                            

