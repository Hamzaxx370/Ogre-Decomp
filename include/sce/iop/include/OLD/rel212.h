/* SCE CONFIDENTIAL
 "PlayStation 2" Programmer Tool Runtime Library Release 2.1.4
 */
/* 
 *                      I/O Processor Library
 *                          Version 1.1
 *                           Shift-JIS
 *
 *      Copyright (C) 2001 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 *                        inet - rel212.h
 *              INET compatible header for Release-2.1.2
 *
 * $Id: rel212.h,v 1.2 2001/01/25 04:25:16 ywashizu Exp $
 */

#if !defined(_INET_REL212_H)
#define _INET_REL212_H

#if defined(__cplusplus)
extern "C" {
#endif

#define sceInetCnfEventHandlers		 sceInetCtlEventHandlers
#define sceInetCnfEventHandlers_t	 sceInetCtlEventHandlers_t

#define sceINETCNF_IEV_Attach		 sceINETCTL_IEV_Attach
#define sceINETCNF_IEV_Detach		 sceINETCTL_IEV_Detach
#define sceINETCNF_IEV_Start		 sceINETCTL_IEV_Start
#define sceINETCNF_IEV_Stop		 sceINETCTL_IEV_Stop
#define sceINETCNF_IEV_Error		 sceINETCTL_IEV_Error
#define sceINETCNF_IEV_Conf		 sceINETCTL_IEV_Conf
#define sceINETCNF_IEV_NoConf		 sceINETCTL_IEV_NoConf

#define sceInetCnfSetConfiguration	 sceInetCtlSetConfiguration
#define sceInetCnfUpInterface		 sceInetCtlUpInterface
#define sceInetCnfDownInterface		 sceInetCtlDownInterface
#define sceInetCnfSetAutoMode		 sceInetCtlSetAutoMode
#define sceInetCnfRegisterEventHandler	 sceInetCtlRegisterEventHandler
#define sceInetCnfUnregisterEventHandler sceInetCtlUnregisterEventHandler

#if defined(__cplusplus)
}
#endif

#endif	/* _INET_REL212_H */
