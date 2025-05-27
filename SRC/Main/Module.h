#pragma mpwc_relax on

#define sprintf func_0011D568

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
CTrtModule TrtModule;
#define D_00165650 TrtModule
CTrtModule* TrtModulePtr;
#define D_00156308 TrtModulePtr

extern const char D_0013A100;

extern const char* D_00153500 = "cdrom0:\\";
extern const char* D_00153510 = "OGREVO4:";
extern const char* D_0015350C = "OGREVO3:";
extern const char* D_00153508 = "OGREVO2:";
extern const char* D_00153504 = "OGREVOL:";

extern eMODULEID* D_00136CF0[];

//TO DO
//Put the function entries for moduleinit and moduleend
extern void* D_0013A0A0[];
extern void* D_0013A0D0[];
extern int D_00153490[];

char D_00156300;

#define func_00130030 CTrtModule::GetFilePath
#define func_00130000 CTrtModule::GetCRIFilePath
#define func_0012ffd0 CTrtModule::GetProgRoot
#define func_001301a0 CTrtModule::GetOverlayFilePath
#define func_001301f0 CTrtModule::SetOverlay
#define  func_001302f0 CTrtModule::LoadOverlay