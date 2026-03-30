// Incomplete

#include "..\Target\Module.h"

int main(int argc,char** argv) {
    CreateTrtModule(argv[0]);
    D_00156308 -> LoadOverlay((eMODULEID)D_00156308->m_eModuleID, 0);
    return 0;
}

extern "C" void __start() {
    char* argv[3];
    argv[0] = "None";
    main(0,argv);
}