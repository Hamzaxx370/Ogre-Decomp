/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/08/22 17:24:27 $
 * $Revision: 1.25 $
 */

/*
	The purpose of this file is to set up those aspects of the environment
	that are global to both the C and C++ library.  The top of the dependency
	tree for the C library is ansi_parms.h.  The top for the C++ library is
	mcompile.h.  In order to avoid duplicating code in these two files, this
	file will be included by both ansi_parms.h and mcompile.h.  Only put stuff
	in here that otherwise would have to have been duplicated in ansi_parms.h
	and mcompile.h.
*/

#ifndef _MSLGLOBALS_H
#define _MSLGLOBALS_H

#ifndef __ansi_prefix__

	#if defined(__MC68K__)  /*- beb 990804 -*/
		#if defined(__PALMOS_TRAPS__)
			#include <ansi_prefix.Palm_OS.h>
		#elif defined(__embedded__)
			#include <ansi_prefix.e68k.h>
		#else
			#include <ansi_prefix.mac.h>
		#endif
	#elif (defined(__POWERPC__) && !defined(__PPC_EABI__)) && __MACH__
		#include <ansi_prefix.mach.h>
	#elif (defined(__POWERPC__) && !defined(__PPC_EABI__))
		#include <ansi_prefix.mac.h>
	#elif defined(__BEOS__)  /*- bs 990121 -*/
	    #include <ansi_prefix.be.h>
	#elif defined(__PPCGEKKO__)
		#include <ansi_prefix.PPCEABI.Gamecube.h>
	#elif defined(__PPC_EABI__)
		#include <ansi_prefix.PPCEABI.bare.h>
	#elif defined(__INTEL__)
		#if defined(__linux__)
			#include <ansi_prefix.Linux_x86.h>
		#elif !defined(UNDER_CE)
			#include <ansi_prefix.Win32.h>
		#endif
	#elif (defined(__MIPS__) && !defined(UNDER_CE))
		#if defined(__MIPS_PSX2__)	/* for PS2 */
			#include <ansi_prefix.MIPS_PS2.h>
		#else
			#include <ansi_prefix.MIPS_bare.h>
		#endif
		
    #elif defined(__m56800E__) || defined(__m56800__)
	    #include <ansi_prefix_dsp.h> 
			
	#elif defined (__MCORE__)
		#include <ansi_prefix.MCORE_EABI_bare.h>
	#elif defined (__SH__) 
		#include <ansi_prefix.SH_bare.h>
	#else
		#ifndef RC_INVOKED  /*- hh 990525 -*/
			#error mslGlobals.h could not include prefix file
		#endif
	#endif

#endif /* __ansi_prefix__ */

	#if __option(longlong) && !defined(_No_LongLong)
		#define __MSL_LONGLONG_SUPPORT__ 
	#endif

#endif /* _MSLGLOBALS_H */


/* Change record:
 * hh  980120 created
 * mm  981028 Added #include for ansi_prefix.56800.h
 * vss 981116 MIPS doesn't want namespaces  (?)
 * mf  981118 made mips ce not include ansi_prefix.mips.bare.h
 *            and changed __MSL_LONGLONG_SUPPORT__  def to work with
 *            what is already in all msl source files
 * bs  990121 Added BEOS
 * hh  990525 Protected error from resource compiler
 * beb 990804 Added e68k
 * vss 990804 Added mcore
 * blc 990823 Added x86 Linux
 * as  990824 Added SH
 * hh  000302 Moved namespace flag to the ansi_prefix.XXX.h files
 * as  001101 Changed __mcore__ to __MCORE__ for ABI
 * JWW 001109 Updated for Mach-O
 * cc  010202 Added __MIPS_PSX2__
 * cc  010822 Added PPCGEKKO prefix file
 */
