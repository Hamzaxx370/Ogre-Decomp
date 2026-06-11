/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/06/19 00:46:19 $ 
 * $Revision: 1.17 $ 
 */
 
// hashfun.h

/*
	WARNING - WARNING - WARNING
	
	This header is OBSOLETE
	
	Please use <hash_fun> instead
*/

#ifndef _HASHFUN_H
#define _HASHFUN_H

#include <hash_fun>

#pragma ANSI_strict off
#warning This header is obsolete.  Please use hash_fun instead.
#pragma ANSI_strict reset

#ifndef _MSL_NO_CPP_NAMESPACE
	namespace std
	{
		using Metrowerks::hash;
		typedef hash<int>         hash_fun0;
		typedef hash<std::string> hash_fun1;
		typedef hash<std::string> hash_fun2;
		typedef hash<std::string> hash_fun3;
	}
#else
	typedef hash<int>    hash_fun0;
	typedef hash<string> hash_fun1;
	typedef hash<string> hash_fun2;
	typedef hash<string> hash_fun3;
#endif

#endif // _HASHFUN_H

// hh 971220 fixed MOD_INCLUDE and MOD_C_INCLUDE
// hh 971222 added alignment wraper
// hh 980408 wrapped up in #ifndef _No_Floating_Point
// hh 991224 Rewrote
// hh 010125 Added typedefs for no namespace case
