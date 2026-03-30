#ifndef OGRE_DEFS_H
#define OGRE_DEFS_H

// ============================================================================
//  ogre_defs.h
//  Definitions of base types
// ============================================================================

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
#define TRUE 1
#define FALSE 0
#define NULL ((void*)0)

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

#endif