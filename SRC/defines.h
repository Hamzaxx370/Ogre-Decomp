/* 
    defines.h 
    comment: contains win32 typedefs.
    should probably rename and make a wrapper for windows.h?
*/

#pragma once

// Signed types
typedef char    CHAR;
typedef short   SHORT;
typedef int     INT;
typedef long    LONG;

// Unsigned types
typedef unsigned char   UCHAR;
typedef unsigned char   BYTE;
typedef unsigned short  USHORT;
typedef unsigned short  WORD;
typedef unsigned int    UINT;
typedef unsigned int    DWORD;

// Floating point
typedef float   FLOAT;
typedef double  DOUBLE;

// Bool
typedef bool    BOOL;

#ifdef TRUE
#undef TRUE
#endif
#define TRUE 1

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

#ifdef NULL
#undef NULL
#endif
#define NULL (0)

// Pointers
typedef void*       LPVOID;
typedef const void* LPCVOID;
typedef char*       LPSTR;
typedef const char* LPCSTR;

// Others
typedef void VOID;
#define CONST const
#define VOLATILE volatile;
#define STATIC static
#define INLINE inline