/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/03/08 21:13:02 $ 
 * $Revision: 1.13 $ 
 */

// typeinfo.h

#ifndef _TYPEINFO_H
#define _TYPEINFO_H

#include <typeinfo>

#ifndef _MSL_NO_CPP_NAMESPACE
	using std::type_info;
	using std::bad_cast;
	using std::bad_typeid;
#endif

#endif  // _TYPEINFO_H

// hh 971206  Added namespace support
// hh 990120 changed name of MSIPL flags
// hh 991113 modified using policy
