#define NULL (0)

// typedef enum bool {
//     false,
//     true,
// } bool;

typedef signed char    s8;
typedef signed short   s16;
typedef signed int     s32;
typedef signed long    s64;
typedef signed long    s128 __attribute__((mode(TI)));

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  u64;
typedef unsigned long  u128 __attribute__((mode(TI)));

typedef float  f32;
typedef double f64;

typedef volatile s8   vs8;
typedef volatile s16  vs16;
typedef volatile s32  vs32;
typedef volatile s64  vs64;
typedef volatile s128 vs128;

typedef volatile u8   vu8;
typedef volatile u16  vu16;
typedef volatile u32  vu32;
typedef volatile u64  vu64;
typedef volatile u128 vu128;

typedef volatile float  vf32;
typedef volatile double vf64;

// SCE types
typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;
typedef unsigned long  u_long;
typedef unsigned long  u_long128 __attribute__((mode(TI)));

typedef int qword[4] __attribute__ ((aligned(16)));
typedef int sceVu0IVECTOR[4] __attribute__((aligned (16)));
typedef int sceVu0IMATRIX[4][4] __attribute__((aligned (16)));
typedef float sceVu0FVECTOR[4] __attribute__((aligned (16)));
typedef float sceVu0FMATRIX[4][4] __attribute__((aligned (16)));

unsigned int CheckExpFlag(unsigned int);
int _ATan(float,float);
long __gh_memclr32(int,int,int);
extern "C"
{
    char* sprintf(char*, const char*, ...);
    void func_002A0D30(struct CActMan* t);
    int memset(void*, int, int);
    void* memcpy(void*, void*, unsigned int);
}
void _SeedRandom(unsigned int);
void* TmpBufLock(void);
void TmpBufUnLock(void);
unsigned int _Random(void);
int CalcCRC32(unsigned long, unsigned char *);

typedef enum eSND_OUTPUT {
    SND_OUTPUT_0 = 0,
    SND_OUTPUT_1 = 1,
    SND_OUTPUT_2 = 2,
} eSND_OUTPUT;

class CTrtSoundPS2 {
    public:
    virtual void virt0();
    virtual void virt2();
    virtual void virt3();
    virtual void virt4();
    virtual void virt5();
    virtual void virt6();
    virtual void virt7();
    virtual void virt8();
    virtual void virt9();
    virtual void virt10();
    virtual void virt11();
    virtual void virt12();
    virtual void virt13();
    virtual void virt14();
    virtual void virt15();
    virtual void virt16();
    virtual void virt17();
    virtual void virt18();
    virtual void virt19();
    virtual void virt20();
    virtual void virt21();
    virtual void virt22();
    virtual void virt23();
    virtual void virt24();
    virtual void virt25();
    virtual void virt26();
    virtual void virt27();
    virtual void virt28();
    virtual void virt29();
    virtual void virt30();
    virtual void virt31();
    virtual void virt32();
    virtual void virt33();
    virtual void virt34();
    virtual void virt35();
    virtual void virt36();
    virtual void virt37();
    virtual void virt38();
    virtual void virt39();
    virtual void virt40();
    virtual void virt41();
    virtual void virt42();
    virtual void virt43();
    virtual void virt44();
    virtual void virt45();
    virtual void SetOutput(eSND_OUTPUT);
};

extern CTrtSoundPS2 *D_00157188;

typedef enum eWIDETV {
    WIDETV_0 = 0,
    WIDETV_6 = 6,
} eWIDETV;

class CActWideTVManager {
    public:
    void SetWideTV(eWIDETV);
};

extern CActWideTVManager *D_00157614;

typedef enum eULTIMATE_BOX_ESTIMATE_RANK {

} eULTIMATE_BOX_ESTIMATE_RANK;