/* Metrowerks PS2 Runtime Support Library 
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/12/07 22:54:54 $
 * $Revision: 1.2 $
 */

#ifndef _ALLOCA_H 
#define _ALLOCA_H

/* we cannot expose _alloca using an inline function because we cannot
 * guarentee that the function will be inlined, and __alloca must be called
 * in the correct stack frame -- if not, the space it allocates will be
 * released upon return to the caller -- we do expose both _alloca and
 * __alloca as both are recognized by the compiler as forms of __alloca */

#ifdef __cplusplus
extern "C" {
#endif

_MSL_IMP_EXP_C char * _alloca(__std(size_t) size);
_MSL_IMP_EXP_C char * __alloca(__std(size_t) size);

#ifdef __cplusplus
}
#endif

#define alloca __alloca

#endif /* _ALLOCA_H  */

/* Change record:
 * cc  010409 moved alloca from malloc.h
 */