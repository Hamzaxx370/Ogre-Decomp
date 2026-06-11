/*
 *	NewHand.h
 *	
 *		Copyright © 1996 Metrowerks, Inc.
 *		All rights reserved.
 *
 *	Modification History
 *	--------------------
 *
 *	5-Sep-96 KO	Made this file. The original MSL file new.cpp was split
 *	            into NewHand.cpp, NewHand.h,  newop.cpp, and delop.cpp so
 *              you can overload the new and delete operators.
 */

#ifndef NEWHAND_H
#define NEWHAND_H

#include <new>

#ifndef _MSL_NO_CPP_NAMESPACE          // hh 971207 Added namespace support
	namespace std {
#endif

// Regular MSL uses this variable as a static variable in new.cpp called
// new_handler_func (no leading underscore).
extern new_handler	_new_handler_func;

#ifndef _MSL_NO_CPP_NAMESPACE          // hh 971207 Added namespace support
	}
#endif

#endif

// hh 971207 Added namespace support