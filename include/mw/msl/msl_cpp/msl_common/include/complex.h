/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/03/08 20:53:18 $ 
 * $Revision: 1.14 $ 
 */
                                       
// complex.h        // hh 971206 Changed filename from complex to complex.h

#ifndef _COMPLEX_H         // hh 971206 Made include guards standard
#define _COMPLEX_H

#include <complex>

#ifndef _MSL_NO_CPP_NAMESPACE      // hh 971206 Backward compatibility added with "using"
#ifndef _No_Floating_Point
	using std::complex;
#endif
#endif

#endif  // _COMPLEX_H

// hh 971206 Changed filename from complex to complex.h
// hh 971206 Made include guards standard
// hh 971206 Backward compatibility added with "using"
// hh 990120 changed name of MSIPL flags
// hh 991112 modified using policy
