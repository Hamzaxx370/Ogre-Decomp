/*
 *	__config.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 *	
 */
#ifndef __config_mips___
#define __config_mips___
#include <os_enum.h>

/*
 *	Number returned by the __MIPS_processor__ macro
 *
 */
#define __MIPS_R3081__	0x010

#define __MIPS_R4640__	0x020
#define	__MIPS_R4650__	0x021

#define	__MIPS_R4700__	0x040

#define	__MIPS_R32364__	0x050

#define	__MIPS_VR4100__	0x060
#define	__MIPS_VR4111__	0x061
#define	__MIPS_VR4121__	0x062

#define	__MIPS_VR4200__	0x070

#define	__MIPS_VR4300__ 0x080

#define	__MIPS_VR5000__	0x090
#define	__MIPS_VR5400__	0x100

#define __MIPS_RM7000__	0x110
#define __MIPS_TR4101__	0x120
#define	__MIPS_R5900__	0x130
#define __MIPS_R4500__	0x140
#define __MIPS_unknown__	-1


/*
 *	Call instruction for pc relative and absolute mode
 *
 */
#if __pc_relative__

	#define	_CALL	bal

#else

	#define	_CALL	jal

#endif


#if __ptr64__

	typedef long long address;
	#define _LOADPTR	ld		/*	Load an address			*/
	#define _STOREPTR	sd		/*	Store an address		*/
	#define _ADDPTR		daddu	/*	Add offset to address	*/			
	#define _ADDPTRi	daddui	/*	Add offset to address	*/			

#else

	typedef int address;
	#define _LOADPTR	lw		/*	Load an address			*/
	#define _STOREPTR	sw		/* 	Store an address		*/
	#define _ADDPTR		addu	/*	Add offset to address	*/			
	#define _ADDPTRi	addui	/*	Add offset to address	*/			

#endif


/*
 *	Heap and stack alignment.  Never set the alignment to 
 *	something <= 8
 *
 */
#if __MIPS_ISA3__ || __MIPS_ISA4__ || __MIPS_ISA5__

	#if __n64abi__ || __cpu128__ 
		#define __ALIGNMENT__	16L
	#else
		#define __ALIGNMENT__	8L
	#endif
	
#else

	#define __ALIGNMENT__	8L

#endif


#if (__cpu32__ && __fpu64__)
	#error	//	Unsuported combination	
#endif

#if __cpu128__

	#define _REG_TYPE	__int128			// Register type.
											
	/*
	 * Load and Store registers instructions
	 *
	 */
	#define _LOAD		lq					// Load register
	#define	_STORE		sq					// Store register
	#define _MOVE		qmove				// Register copy

#elif __cpu64__

	#define _REG_TYPE	long long			// Register type.  In ISA3 mode it is
											// better to keep register signed for 
											// compatibility with ISA1
											
	/*
	 * Load and Store registers instructions for the given ISA level
	 *
	 */
	#define _LOAD		ld					// Load register
	#define	_STORE		sd					// Store register
	#define _MOVE		dmove				// Register copy
	
#else

	#define _REG_TYPE	unsigned int		// Register type 	

	/*
	 * Load and Store registers instructions for the given ISA level
	 *
	 */
	#define _LOAD		lw					// Load register
	#define	_STORE		sw					// Store register
	#define _MOVE		move				// Register copy

#endif


#if __fpu64__

	#define	_FREG_TYPE	unsigned long long	// 64 bit registers
	#define _LOADF		ldc1
	#define _STOREF		sdc1

#else

	#define _FREG_TYPE 	unsigned int		// 32 bit registers
	#define _LOADF		lwc1
	#define _STOREF		swc1

#endif

#if __MIPS_WinCE__
	#define __PACKED_EXCEPTION_TABLE	0	// do not allow mis-aligned addresses
#else
	#define __PACKED_EXCEPTION_TABLE	1	// allow mis-aligned addresses
#endif


#if __option(prefetch)

	//	Generate a pref (prefetch) instruction for machine supporting it.
	//	Hint has the following meaning:
	//
	#define __HINT_LOAD				0	// Data is expected to be loaded (not modified)
	#define __HINT_STORE			1	// Data is expected to be stored or modified
	#define __HINT_LOAD_STREAMED	4	// Data is expected to be loaded (not modified) but not
										// reused extensively; it streams through cache.
										// Fetch data as if for a load and place it in the cache
										// so that it does not displace data prefetched as "retained"
	#define __HINT_STORE_STREAMED	5	// Data is expected to be loaded or modified but not
										// reused extensively; it streams through cache.
										// Fetch data as if for a store and place it in the cache
										// so that it does not displace data prefetched as "retained"
	#define __HINT_LOAD_RETAINED	6	// Data is expected to be loaded (not modified) and 
										// reused extensively; it should be retained in the cache
										// Fetch data as if for a load and place it in the cache
										// so that it is not displaced by a data prefetched by "stream"
	#define __HINT_STORE_RETAINED	7	// Data is expected to be loaded or modified and
										// reused extensively; it should be retained in the cache
										// Fetch data as if for a store and place it in the cache
										// so that it is not displaced by a data prefetched by "stream"
	#define __HINT_WRITEBACK_INVALIDATE	25
									

	#if __MIPS_processor__ == __MIPS_R5900__

		//	5900 supports only __HINT_LOAD
		#define __PREFETCH(hint,object)	(	asm (pref __HINT_LOAD, object)	)

	#else

		#define __PREFETCH(hint,object)	(	asm (pref hint, object)	)

	#endif

#else

	#define __PREFETCH(hint,object)	(0)

#endif

#if __ALIGNMENT__ < 8
	#error	Must be at least 2 *sizeof(size_t)
#endif

#endif