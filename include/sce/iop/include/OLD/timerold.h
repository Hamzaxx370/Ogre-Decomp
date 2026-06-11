/* SCE CONFIDENTIAL
 "PlayStation 2" Programmer Tool Runtime Library Release 2.1
 */
/* $Id: timerold.h,v 1.2 2000/10/18 12:15:01 tei Exp $ */

/*
 *                     I/O Processor System Services
 *
 *      Copyright (C) 1998-1999 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 *                         timerold.h
 *                         Hard timer manager defines
 *
 *       Version        Date            Design      Log
 *  --------------------------------------------------------------------
 *       1.00           2000/10/04      tei
 */

#ifndef _TIMERMANOLD_H_
#define _TIMERMANOLD_H_

#include <timerman.h>

/* ====================== OBSOLETE !!!!!!!! =========================== */

#define	iSetTimerMode(timid, mode)	SetTimerMode((timid), (mode))
#define	iGetTimerStatus(timid)		GetTimerStatus(timid)
#define	iSetTimerCounter(timid,count)	SetTimerCounter((timid),(count))
#define	iSetTimerCompare(timid,compare) SetTimerCompare((timid),(compare))
#define	iGetTimerCompare(timid)		GetTimerCompare(timid)
#define	iSetHoldMode(holdnum, mode)	SetHoldMode((holdnum),(mode))
#define	iGetHoldMode(holdnum)		GetHoldMode(holdnum)
#define	iGetHoldReg(holdnum)		GetHoldReg(holdnum)

extern int		ReferHardTimer(int source, int size, int mode,
				       int modemask);
extern void		SetTimerMode(int timid, int mode);
extern long		GetTimerStatus(int timid);
extern void		SetTimerCounter(int timid, unsigned long count);
extern void		SetTimerCompare(int timid, unsigned long compare);
extern unsigned long	GetTimerCompare(int timid);
extern void		SetHoldMode(int holdnum, int mode);
extern unsigned long	GetHoldMode(int holdnum);
extern unsigned long	GetHoldReg(int holdnum);
extern int		GetHardTimerIntrCode(int timid);

#define tGATF_0       	(0<<0)
#define tGATF_1       	(1<<0)
#define tGATM(x)      	((x)<<1)
#define  tGATE_ON_count			0
#define  tGATE_ON_ClearSart		1
#define  tGATE_ON_Clear_OFF_Start	2
#define  tGATE_ON_Start			3
#define tZRET_0       	(0<<3)
#define tZRET_1       	(1<<3)
#define tCMP_0        	(0<<4)
#define tCMP_1        	(1<<4)
#define tOVFL_0       	(0<<5)
#define tOVFL_1       	(1<<5)
#define tREPT_0       	(0<<6)
#define tREPT_1       	(1<<6)
#define tLEVL_0       	(0<<7)
#define tLEVL_1       	(1<<7)
#define tEXTC_0       	(0<<8)
#define tEXTC_1       	(1<<8)
#define tPSCL_0       	(0<<9)
#define tPSCL_1       	(1<<9)
#define tINTF_0       	(0<<10)
#define tINTF_1       	(1<<10)
#define tEQUF_0       	(0<<11)
#define tEQUF_1       	(1<<11)
#define tOVFF_0       	(0<<12)
#define tOVFF_1       	(1<<12)
#define tNTPS(x)      	((x)<<13)

#define hTRG_0       	(0<<0)
#define hTRG_1       	(1<<0)
#define hTMD_0       	(0<<1)
#define hTMD_1       	(1<<1)
#define hHMD_0       	(0<<2)
#define hHMD_1       	(1<<2)
#define hATC_0       	(0<<3)
#define hATC_1       	(1<<3)

#endif /* _TIMERMANOLD_H_ */
