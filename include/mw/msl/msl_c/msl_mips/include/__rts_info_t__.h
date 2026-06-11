/*
 *	__rts_info_t__.h - Linker generated symbols
 *
 *	Copyright © 1995 metrowerks inc. All Rights Reserved.
 *
 */

/* Note: On systems having a .data and .sdata sections, the linker 		*/
/* generated symbols must be in the .data section otherwise we would	*/
/* not be able to load GP!												*/

#include <__config.h>

extern char _stack_addr[];

extern char _fsdata[];			/* 1st location of .sdata	*/

extern char _fsbss[];			/* 1st location of .sbss	*/
extern char _esbss[];			/* 1st location after .sbss	*/

extern char _fbss[];			/* 1st location of .bss		*/
extern char _ebss[];			/* 1st location after .bss	*/

extern char _ftext[];			/* 1st location of .text	*/
extern char _etext[];			/* 1st location after .text	*/

extern char _gp[];				/* should be __fsdata + 32K	*/
extern char _final_gp[];		/* See PID_LinkSegment.txt	*/


#ifdef __cplusplus
	extern "C" {
#endif

/* Beginning and end of the exception table index.	*/
/* Note: The exception table index should be in ROM	*/
/* with the .text section, therefore the symbol		*/
/* must be declared as functions so they are		*/
/* properly referenced in PC and GP relative mode.	*/
	void __exception_table_start__(void);
	void __exception_table_end__(void);
	void (*__static_init[])(void);
	void (*__static_init_end[])(void);

#ifdef __cplusplus
	}
#endif



extern char _heap_addr[];	// See linker command file for 
extern char _heap_end[];	//	exact meaning
extern char _end[];

extern char __dynrelopic[];		// Only for PIC/PID. See linker command file
extern char __dynrelopic_end[];	// Only for PIC/PID. See linker command file
extern char __dynrelopid[];		// Only for PIC/PID. See linker command file
extern char __dynrelopid_end[];	// Only for PIC/PID. See linker command file

extern char __loadaddress[];	// Only for PIC.  See linker command file


/*
 *	__getS7/__getGP	--	returns the value of the S7/GP register.  In PIC/PID mode 
 *	S7 contains the load address of the executable section and GP the load address
 *	of the data section biased by 32K.
 *
 */
extern asm address __getS7(void);
extern asm address __getGP(void);


/*
 *	2-bit mask used to decode at runtime a word address.
 *
 */
 
#define __ADDRESS_MASK_TYPE 	0x00000003
#define __ADDRESS_GP_RELATIVE	0x00000000
#define __ADDRESS_ABSOLUTE  	0x00000001
#define __ADDRESS_PC_RELATIVE	0x00000002

