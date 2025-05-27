#include"Module.cpp"
int D_00156308;
int main(int argc,char** argv) {
    func_00108760(0);
    func_00116138(0);
    while(!func_0010E8D0("cdrom0:\\IOPRP300.IMG;1"));
    while(!FUN_0010e880());
    func_0010DB30();
    func_0010A2C0();
    func_00116138(0);
    func_00116D10(2);
    func_00116638(0);
    func_001003E0();
    CreateTrtModule(argv[0]);
    D_00156308 -> LoadOverlay(&D_00156308->ModuleID, 1, 0);
    func_22CCC0();
    func_0012FF80();
    func_001003D0();
    return 0;
}