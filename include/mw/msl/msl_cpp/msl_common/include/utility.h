/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/03/08 21:13:08 $ 
 * $Revision: 1.13 $ 
 */

// utility.h       // hh 971207 Changed filename from utility to utility.h

#ifndef  _UTILITY_H           // hh 971207 added standard include guards
#define  _UTILITY_H

#include <utility>

#ifndef _MSL_NO_CPP_NAMESPACE     // hh 971207 Added backward compatibility
	using std::pair;
	using std::make_pair;
	using namespace std::rel_ops;
	namespace std { using namespace rel_ops; }
#endif

#endif  // _UTILITY_H

// hh 971207 Changed filename from utility to utility.h
// hh 971207 added standard include guards
// hh 971207 Added backward compatibility
// hh 990120 changed name of MSIPL flags
// hh 991113 modified using policy
