/*
 *	ansi_prefix.MIPS_bare.h
 *	
 *		Copyright © 1997 Metrowerks, Inc.
 *		All rights reserved.
 */

#ifndef __ansi_prefix__
#define __ansi_prefix__

#include <__config.h>
#include <ansi_parms.h>


#if __MIPS_WinCE__

	#define __dest_os	__wince_os

#elif __MIPS__

	#define __dest_os	__mips_bare

	#define __IDT_SIM__		(0) /* Running under IDT sim7 		*/
	#define __PMON__		(0)	/* PMOM board					*/
	#define __PS2__			(1)	/* New PlayStation				*/

#else

	#error Unknown OS

#endif

	/* the following are OS services that aren't available 		*/
#define _No_Time_OS_Support
#define _No_Alloc_OS_Support
#define _No_Disk_File_OS_Support

	/* uncomment _No_Console if you do not want to	*/
	/* write and read to a console window.  		*/
//#define _No_Console
#ifndef _No_Console
	/* the serial 1 and 2 UARTlibs have unbuffered	*/
	/* IO; comment out the following line if  		*/
	/* you are either not using either the serial 1 */
	/* or 2 UARTlibs or if your OS has buffered IO.	*/
#define _Unbuffered_Console
#endif

#define TARGET_IEEE754
#define TARGET_HEAP_ALIGNMENT	8

#define NEWMODE NEWMODE_MALLOC		//	always use malloc for new

#ifndef	long128
typedef	signed __int128		long128;
#endif
#ifndef	u_long128
typedef	unsigned __int128	u_long128;
#endif

/* GCC uses __extension__ in some places to suppress -pedantic warnings
   about GCC extensions.  See ansidecl.h in the 2.43 SDK */
#define __extension__

#endif
