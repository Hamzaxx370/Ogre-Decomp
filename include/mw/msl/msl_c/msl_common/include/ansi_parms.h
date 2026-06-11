/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/10/27 19:50:22 $
 * $Revision: 1.43 $
 */

#ifndef _MSL_ANSI_PARMS_H
#define _MSL_ANSI_PARMS_H

#include <msl_c_version.h>

#include <mslGlobals.h>  /* hh 980120 added */

#ifndef _MSL_USING_MW_C_HEADERS
#define _MSL_USING_MW_C_HEADERS 1
#endif

/* rjk 980313 added the _MSL_IMP_EXP macro
   This macro is set to NULL for targets that link to MSL statically
   and to __declspec(dllimport) for targets that link to MSL in a DLL
   Here is it defaulted to NULL if undefined.
*/

#ifndef _MSL_IMP_EXP
#define _MSL_IMP_EXP
#endif

#ifndef _MSL_IMP_EXP_C
#define _MSL_IMP_EXP_C _MSL_IMP_EXP
#endif

#ifndef _MSL_IMP_EXP_SIOUX
#define _MSL_IMP_EXP_SIOUX _MSL_IMP_EXP
#endif

#ifndef _MSL_IMP_EXP_RUNTIME
#define _MSL_IMP_EXP_RUNTIME _MSL_IMP_EXP
#endif

#ifndef	_MSL_NO_FLOAT_HEX
#define _MSL_NO_FLOAT_HEX
#endif

#ifndef _MSL_USES_EXIT_PROCESS
#define _MSL_USES_EXIT_PROCESS 0
#endif

#ifndef _MSL_NEEDS_EXTRAS
#define _MSL_NEEDS_EXTRAS 0
#endif

/* JWW 010918 added the _MSL_MATH_ERHANDLING macro
   This macro is set to MATH_ERRNO (the value 1) by default.  If a particular platform
   has different math requirements, it should set _MSL_MATH_ERRHANDLING to the appropriate
   value in the platform prefix file.  C99 requires that MATH_ERRHANDLING (and thus
   _MSL_MATH_ERRHANDLING) be a value of MATH_ERRNO (1), MATH_ERREXCEPT (2), or
   MATH_ERRNO | MATH_ERREXCEPT (3).  No other values are valid.
*/

#ifndef _MSL_MATH_ERRHANDLING
#define _MSL_MATH_ERRHANDLING 1		/* Define to MATH_ERRNO by default */
#endif

#ifndef _MSL_POSIX
#define _MSL_POSIX 0
#endif

/*	990811 vss
 *  The following define is supplied to update library functions and 
 *  definitions to the C9X specification.  This does not guarantee
 *  the full functionality of C9X, but does guard around behavior
 *  that differs from defacto or the 1989 ANSI C Standard where the
 *  difference is signficant.	
*/
#if __dest_os != __emb_68k
	#define _MSL_C9X_
#endif

#ifdef __cplusplus
	#define _MSL_BEGIN_EXTERN_C extern "C" {
	#define _MSL_END_EXTERN_C }
	
	#ifdef _MSL_USING_NAMESPACE
		#define _MSL_BEGIN_NAMESPACE_STD namespace std {
		#define _MSL_END_NAMESPACE_STD }
		
		#define __std(ref) ::std::ref
		#define __global() ::
	#else
		#define _MSL_BEGIN_NAMESPACE_STD
		#define _MSL_END_NAMESPACE_STD
		
		#define __std(ref) ref
		#define __global()
	#endif
#else
	#define _MSL_BEGIN_EXTERN_C
	#define _MSL_END_EXTERN_C
	
	#define _MSL_BEGIN_NAMESPACE_STD
	#define _MSL_END_NAMESPACE_STD
	
	#define __std(ref) ref
	#define __global()
#endif

#if	(__dest_os == __win32_os || __dest_os == __wince_os)
	#define __tls		__declspec(thread)
	#define _MSL_CDECL	__cdecl  
#else
	#define __tls
	#define _MSL_CDECL
#endif

#endif /* ndef _MSL_ANSI_PARMS_H */

/* Change record:
 * MEA 972306 Added __dest_os __ppc_eabi_bare.  New symbol __no_os
 *			  is only defined for bare board embedded systems.
 *			  Do not define long long yet for PPC EABI.
 * SCM 971507 Added __nec_eabi_bare and __nec_eabi_os.
 * MEA 972007 Changed __ppc_eabi_bare to __ppc_eabi.
 * MEA 971109 Added support for long long.
 * vss 971015 New version 2.2
 * hh  971206 reworked macro magic for namespace support
 * hh  971206 Added "define OS" code
 * hh  980120 added <mslGlobals.h>
 * hh  980217 added __ANSI_OVERLOAD__
 * rjk 909313 ADDED _MSL_IMP_EXP macro
 * ah  010121 hawk dsp housekeeping
 * cc  010125 added _MSL_CDECL
 * ah  010131 removed hawk dsp housekeeping -- back to _Old_DSP_IO_Interface
 * cc  010409 updated defines to JWW new namespace macros
 * JWW 010912 Use new msl_c_version.h file for tracking the MSL version number
 * JWW 010918 Added definitions for C99 math error handling macros
 * JWW 010926 Changed _POSIX to _MSL_POSIX to control what happens with POSIX functions in ANSI headers
 * cc  011022 Added _MSL_NO_FLOAT_HEX, _MSL_USES_EXIT_PROCESS, _MSL_NEEDS_EXTRAS
 * JWW 011027 New _MSL_USING_MW_C_HEADERS define to control if the MSL C headers are used or not
 */