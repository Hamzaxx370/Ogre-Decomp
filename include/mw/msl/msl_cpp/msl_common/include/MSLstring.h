/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/04/02 18:28:15 $ 
 * $Revision: 1.16 $ 
 */

// MSLstring.h

#ifndef _MSLSTRING_H
#define _MSLSTRING_H

// _MSLstring is a special simple string class used by <stdexept>.  This
// class breaks a potentially cyclic relationship between <stdexcept> and
// <string>.  Without this class, <string> throws classes from <stdexcept>
// and <stdexcept> processes <string>.  By making <stdexcept> depend on
// _MSLstring instead of <string>, the cycle is broken.
// hh 971226

#include <mslconfig>
#include <RefCountedPtrArray.h>
#include <stringfwd>
#include <cstring>

#pragma options align=native

#ifdef _MSL_FORCE_ENUMS_ALWAYS_INT
	#if _MSL_FORCE_ENUMS_ALWAYS_INT
		#pragma enumsalwaysint on
	#else
		#pragma enumsalwaysint off
	#endif
#endif

#ifdef _MSL_FORCE_ENABLE_BOOL_SUPPORT
	#if _MSL_FORCE_ENABLE_BOOL_SUPPORT
		#pragma bool on
	#else
		#pragma bool off
	#endif
#endif

#ifndef _MSL_NO_CPP_NAMESPACE
	namespace std {
#endif

class _MSLstring {
public:
	_MSLstring(const char* value);
	_MSL_IMP_EXP_CPP _MSLstring(const string& value);
	const char* c_str() const;
protected:
private:
	_RefCountedPtr<char, _Array<char> > data_;
};

inline
_MSLstring::_MSLstring(const char* value)
	: data_(new char [strlen(value)+1])
{
	strcpy(const_cast<char*>(static_cast<const char*>(data_)), value);
}

inline
const char*
_MSLstring::c_str() const
{
	return data_;
}

#ifndef _MSL_NO_CPP_NAMESPACE
	} // namespace std 
#endif

#ifdef _MSL_FORCE_ENUMS_ALWAYS_INT
	#pragma enumsalwaysint reset
#endif

#ifdef _MSL_FORCE_ENABLE_BOOL_SUPPORT
	#pragma bool reset
#endif

#pragma options align=reset

#endif // _MSLSTRING_H

// hh 990120 changed name of MSIPL flags
// hh 990314 Added const char* constructor to support nonstandard const char* constructors
//           on all of the standard exceptions.
// hh 991114 Uses <stringfwd>.
// hh 000130 Installed _MSL_IMP_EXP_CPP
// hh 010402 Removed 68K CMF support
