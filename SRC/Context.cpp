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
}