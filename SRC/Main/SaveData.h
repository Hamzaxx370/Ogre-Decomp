#include"..\Context.cpp"
class CSystemData
{
    int unk0;
    int unk4;
    int unk8;
    char unkC;
    char unkD;
    short unkE;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
    int unk20;
    char unk24[0x74-0x24];
    unsigned int unk74;
    unsigned int unk78[0x40];
    int GetFlag(unsigned int);
    void SetFlag(unsigned int, unsigned int);
    int Decode(void *);
    int Encode(void *);
    bool CheckCRC(void *arg1) {
        
    };
    void CalcCRC(void *arg1) {
        unsigned char* buf = (unsigned char*)arg1;
        *(int*)(buf + 0x74) = 0;
        *(int*)(buf + 0x178) = 0;
        *(int*)(buf + 0x178) = CalcCRC32(0x17C, buf);
    };
    void SetBoolClear(void);
    int GetBoolClear(void);
    bool BoolKenkaMaster();
    int GetUltimateBoxEstimate(unsigned int);
    void SetUltimateBoxEstimate(unsigned int, eULTIMATE_BOX_ESTIMATE_RANK);
    void* GetSystemData(void *);
    void SetSystemData(void *);
    void SystemDataReset(void);
    void get_subscenario_clear_info(unsigned int *, unsigned int *);
    void get_miniscenario_clear_info(unsigned int *, unsigned int *);

    bool BoolClearEasy(void) {
        return this->unk4 & 2;
    };
    bool BoolClearNormal(void) {
        return this->unk4 & 1;
    };
    bool BoolClearHard(void) {
        return this->unk4 & 4;
    };
    bool BoolClearSuperHard(void){
        return this->unk4 & 8;
    };
};