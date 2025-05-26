class CTrtSystem
{
    public: 
        char Unknown[16];
        int SaveFlag;
        int IsExistSaveData(CTrtSystem *arg0, int arg1);
        void func_00130450(CTrtSystem *arg0, int arg1, int arg2);
};
int CTrtSystem::IsExistSaveData(CTrtSystem* arg0, int arg1) {
    return arg0->SaveFlag & arg1;
}

void CTrtSystem::func_00130450(CTrtSystem* arg0, int arg1, int arg2) {
    int var_v1;

    if (arg2 != 0) {
        var_v1 = arg0->SaveFlag | arg1;
        arg0->SaveFlag = var_v1;
        return;
    } else {
        var_v1 = arg0->SaveFlag & ~arg1;
        arg0->SaveFlag = var_v1;
    }
}
#define func_00130440 CTrtSystem::IsExistSaveData