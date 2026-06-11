//	===========================================================================
//	mwUtils.h			©1999-2000 Metrowerks Inc. All rights reserved.
//	===========================================================================
//
//	Metrowerks Utilities
//
//	Version.1.6
//
//  10/17/2001  rcampana,	added mwAllocateProfilePointBuffer()
//	06/08/2000	kashima,	rename _overlay_group_addreses to _overlay_group_addresses
//	05/17/2000	kashima,	rename mwDebuggerBreak() to mwDbgBreak()
//	02/01/2000	kashima,	add mwDebuggerBreak()
//	01/25/2000	kashima,	change mwNotifyOverlayLoaded()
//	01/13/2000	kashima,	add overlay support
//	10/27/1999	kashima,	1st

#pragma once

#ifndef	__MWUTILS_H__
#define	__MWUTILS_H__

/*******************************************************************************
	INCLUDE 
*******************************************************************************/
/*	OS dependent header	*/
/*	STANDARD header	*/
/*	PROJECT header	*/

#ifdef __cplusplus
extern	"C"	{
#endif

/*******************************************************************************
	DEFINE
*******************************************************************************/

/*------------------------------------------------------------------------------
 *	mwDbgBreak
 *	break in debugger
 *	debugger will stop at this macro
------------------------------------------------------------------------------*/
#ifdef	DEBUG
#define	mwDbgBreak()	asm volatile ("breakc 0x0")
#else
#define	mwDbgBreak()
#endif

/*******************************************************************************
	TYPEDEF
*******************************************************************************/

/*******************************************************************************
	EXTERN
*******************************************************************************/

/*------------------------------------------------------------------------------
 *	for overlay
------------------------------------------------------------------------------*/
extern	void*	_overlay_group_addresses[];


/*******************************************************************************
	FUNCTION
*******************************************************************************/

/*------------------------------------------------------------------------------
 *	mwInit
 *	initialize the C++ runtime
 *	call static initializers and initialize exception table
 *	--- CAUTION ---
 *	you have to call this function at the top of main() fucntion in c++ project
------------------------------------------------------------------------------*/
void	mwInit(void);

/*------------------------------------------------------------------------------
 *	mwExit
 *	destroy all constructed global objects
 *	--- CAUTION ---
 *	you need to call this function at the top of main() fucntion in c++ project
------------------------------------------------------------------------------*/
void	mwExit(void);

/*------------------------------------------------------------------------------
 *	mwGetGroupAddress
 *	return the address of the overlay group
 *	--- CAUTION ---
 *	index 0	 : main segment
 *	index 1- : each overlay group
------------------------------------------------------------------------------*/
inline
void*	mwGetGroupAddress(unsigned int inIndex)
{
	return	_overlay_group_addresses[inIndex];
}

/*------------------------------------------------------------------------------
 *	mwOverlayInit
 *	initialize overlay
 *	--- CAUTION ---
 *	you have to call this function after the overlay file is loaded
------------------------------------------------------------------------------*/
void	mwOverlayInit(const void* pAddress, int inFileSize);

/*------------------------------------------------------------------------------
 *	mwOverlayNotifyToDebugger
 *	notify to debugger
 *	--- CAUTION ---
 *	you have to call this function after the overlay file is loaded
------------------------------------------------------------------------------*/
#ifdef	DEBUG
#define	mwOverlayNotifyToDebugger	MWNotifyOverlayLoaded
void	mwOverlayNotifyToDebugger(const void* pAddress);
#else
#define	mwOverlayNotifyToDebugger(pAddress)
#endif

/*------------------------------------------------------------------------------
 *	mwBload
 *	utility function to load the file into memory
------------------------------------------------------------------------------*/
int		mwBload(const char* pFilePath, const void* pAddress);

/*------------------------------------------------------------------------------
 *	mwLoadOverlay
 *	utility function to load overlay file
 *	this function will load the overlay file and inltialize that overlay
------------------------------------------------------------------------------*/
int		mwLoadOverlay(const char* pFilePath, const void* pAddress);

/*------------------------------------------------------------------------------
 *	mwAllocateProfilePointBuffer
 *	utility function to reserve the buffer for ProfilePoint
------------------------------------------------------------------------------*/
void mwAllocateProfilePointBuffer( );


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __MWUTILS_H__ */