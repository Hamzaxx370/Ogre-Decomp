/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/03/08 20:53:46 $ 
 * $Revision: 1.14 $ 
 */

// fstream.h           // hh 971207 Changed filename from fstream to fstream.h

#ifndef _FSTREAM_H      // hh 971207 added standard include guards
#define _FSTREAM_H

#include <fstream>

#ifndef _MSL_NO_CPP_NAMESPACE        // hh 971207 Added backward compatibility
#ifndef _MSL_NO_IO
	using std::basic_filebuf;
	using std::filebuf;
	using std::basic_ifstream;
	using std::ifstream;
	using std::basic_ofstream;
	using std::ofstream;
	using std::basic_fstream;
	using std::fstream;
#ifndef _MSL_NO_WCHART_CPP_SUPPORT
	using std::wfilebuf;
	using std::wifstream;
	using std::wofstream;
	using std::wfstream;
#endif
#endif
#endif

#endif  // _FSTREAM_H

// hh 971207 Changed filename from fstream to fstream.h
// hh 971207 added standard include guards
// hh 971207 Added backward compatibility
// hh 990120 changed name of MSIPL flags
// hh 991112 modified using policy
