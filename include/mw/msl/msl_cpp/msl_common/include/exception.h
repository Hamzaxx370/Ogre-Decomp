/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/03/08 20:53:40 $ 
 * $Revision: 1.13 $ 
 */

// exception.h

#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <exception>

#ifndef _MSL_NO_CPP_NAMESPACE
	using std::exception;
	using std::bad_exception;
	using std::unexpected_handler;
	using std::set_unexpected;
	using std::unexpected;
//	using std::uncaught_exception;
	using std::terminate_handler;
	using std::set_terminate;
	using std::terminate;
#endif

#endif  // _EXCEPTION_H

// hh 971206  Added namespace support
// hh 990120 changed name of MSIPL flags
// hh 991112 modified using policy
