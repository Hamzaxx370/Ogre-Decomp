/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/03/08 21:08:34 $ 
 * $Revision: 1.5 $ 
 */
 
// stringfwd.h

// WARNING
//
// stringfwd.h is a non-standard, non-portable header.
//
// WARNING

#ifndef _STRINGFWD_H
#define _STRINGFWD_H

#include <stringfwd>

#ifndef _MSL_NO_CPP_NAMESPACE

	using std::allocator;
	using std::char_traits;
	using std::basic_string;
	using std::string;
#ifndef _MSL_NO_WCHART_CPP_SUPPORT
	using std::wstring;
#endif

#endif

#endif // _STRINGFWD_H

// hh 991114 Created
