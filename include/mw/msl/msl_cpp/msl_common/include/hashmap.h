/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/06/19 00:46:21 $ 
 * $Revision: 1.15 $ 
 */
 
// hashmap.h

/*
	WARNING - WARNING - WARNING
	
	This header is OBSOLETE
	
	Please use <hash_map> instead
*/

#ifndef _HASHMAP_H
#define _HASHMAP_H

#include <hash_map>
#include <hashfun.h>

#pragma ANSI_strict off
#warning This header is obsolete.  Please use hash_map instead.
#pragma ANSI_strict reset

#ifndef _MSL_NO_CPP_NAMESPACE
	namespace std
	{
		using Metrowerks::hash_map;
	}
#endif

#endif // _HASHMAP_H

// 970723 sm wrapped entire file in #ifndef _No_Floating_Point
// hh 971220 fixed MOD_INCLUDE
// hh 971222 added alignment wrapper
// hh 991224 Rewrote
