#pragma mpwc_relax on

#define sprintf func_0011D568
const char* D_00153500 = "cdrom0:\\";
const char* eMEDIA4MODULEID[]
{
    
};
enum eMODULEID
{
};
class CTrtModule {
    public:
        eMODULEID ModuleID;
        char buf[0x100];
        int GetFilePath(char *, char const *);
        int GetCRIFilePath(char *, char const *);
        int GetProgRoot(char *);
        int GetOverlayFilePath(char *arg1, eMODULEID arg2, unsigned int arg3);
        int SetOverlay(eMODULEID, unsigned int, void const *, unsigned int,unsigned int arg4);
        int LoadOverlay(eMODULEID *arg0, unsigned int arg1, unsigned int arg2);
        // CTrtModule();
        // ~CTrtModule();
};