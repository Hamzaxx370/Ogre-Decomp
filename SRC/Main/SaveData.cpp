class CSystemData
{
    public: 
        char Unknown[16];
        int SaveFlag;
        int GetFlag(unsigned int arg1);
        void SetFlag(int arg1, int arg2);
};
int CSystemData::GetFlag(unsigned int arg1) {
    return this->SaveFlag & arg1;
}

void CSystemData::SetFlag(int arg1, int arg2) {
    int var_v1;

    if (arg2 != 0) {
        var_v1 = this->SaveFlag | arg1;
        this->SaveFlag = var_v1;
        return;
    } else {
        var_v1 = this->SaveFlag & ~arg1;
        this->SaveFlag = var_v1;
    }
}
#define func_00130440 CTrtSystem::IsExistSaveData