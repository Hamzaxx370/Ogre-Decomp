/* Metrowerks Standard Library
 * Copyright © 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/04/02 18:28:40 $ 
 * $Revision: 1.16 $ 
 */

// RefCountedPtrArray.h

#ifndef _REFCOUNTEDPTR_H
#define _REFCOUNTEDPTR_H

/*
	WARNING:  This is a non-standard header and class.

	A reference counting handle class.
	
	This is to be used as a pointer to class T.  
	This will feel and smell just like a built-in pointer except:
	1.  There is no need to call delete on the pointer.
	2.  The default copy constructor and assignment implement ref-counting.
	3.  The user may call isNonUnique to determine if this pointer is
	    the only pointer to the data.  This can be used to hide the
	    ref-counting behavior of a class.
	4.  There are two "traits" classes which specify whether the single object
	    form of delete should be used, or the array form.  The default is single.
*/

#include <mslconfig>

#ifndef RC_INVOKED

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

// rebind members in _Single and _Array aid in auto_ptr conversions from auto_ptr<X>
// to auto_ptr<Y>.  The _Array rebind member uses T on purpose to prohibit such conversions.

template <class T>
struct _Single
{
	static void destroy(T* ptr) _MSL_THROW {delete ptr;}
#ifndef _MSL_NO_MEMBER_TEMPLATE
	template <class U> struct rebind { typedef _Single<U> other; };
#endif
};

template <class T>
struct _Array
{
	static void destroy(T* ptr) _MSL_THROW {delete [] ptr;}
#ifndef _MSL_NO_MEMBER_TEMPLATE
	template <class U> struct rebind { typedef _Array<T> other; };
#endif
};

template <class T, class traits = _Single<T> >
class _RefCountedPtr
{
public:
	_RefCountedPtr(T* ptr = 0);  // Accepts responsibility for ptr
	_RefCountedPtr(const _RefCountedPtr<T, traits>& other) _MSL_THROW;
	~_RefCountedPtr() _MSL_THROW;
	_RefCountedPtr<T, traits>& operator=(const _RefCountedPtr<T, traits>& rhs) _MSL_THROW;
	T* operator->() _MSL_THROW;
	const T* operator->() const _MSL_THROW;
	T& operator*() _MSL_THROW;
	const T& operator*() const _MSL_THROW;
	operator const T* () const _MSL_THROW;
	bool isNonUnique() const _MSL_THROW;
private:
	T* ptr_;
	int* refCount_;
};

template <class T, class traits>
_RefCountedPtr<T, traits>::_RefCountedPtr(T* ptr)
	: ptr_(ptr),
	refCount_(0)
{
#ifndef _MSL_NO_EXCEPTIONS
	try
	{
		if (ptr_ != 0)
			refCount_ = new int(1);
	}
	catch (...)
	{
		traits::destroy(ptr_);
		throw;
	}
#else
	if (ptr_ != 0)
	{
		refCount_ = new int(1);
		if (refCount_ == 0)
		{
			traits::destroy(ptr_);
			__msl_error("_RefCountedPtr out of memory");
		}
	}
#endif
}

template <class T, class traits>
_RefCountedPtr<T, traits>::_RefCountedPtr(const _RefCountedPtr<T, traits>& other) _MSL_THROW
	: ptr_(other.ptr_),
	refCount_(other.refCount_)
{
	if (refCount_ != 0)
		++(*refCount_);
}

template <class T, class traits>
_RefCountedPtr<T, traits>::~_RefCountedPtr() _MSL_THROW
{
	if (refCount_ != 0 && --(*refCount_) == 0)
	{
		traits::destroy(ptr_);
		delete refCount_;
	}
}

template <class T, class traits>
_RefCountedPtr<T, traits>&
_RefCountedPtr<T, traits>::operator=(const _RefCountedPtr<T, traits>& rhs) _MSL_THROW
{
	if (ptr_ != rhs.ptr_)
	{
		if (refCount_ != 0 && --(*refCount_) == 0)
		{
			traits::destroy(ptr_);
			delete refCount_;
		}
		ptr_ = rhs.ptr_;
		refCount_ = rhs.refCount_;
		if (refCount_ != 0)
			++(*refCount_);
	}
	return *this;
}

template <class T, class traits>
inline
T*
_RefCountedPtr<T, traits>::operator->() _MSL_THROW
{
	return ptr_;
}

template <class T, class traits>
inline
const T*
_RefCountedPtr<T, traits>::operator->() const _MSL_THROW
{
	return ptr_;
}

template <class T, class traits>
inline
T&
_RefCountedPtr<T, traits>::operator*() _MSL_THROW
{
	return *ptr_;
}

template <class T, class traits>
inline
const T&
_RefCountedPtr<T, traits>::operator*() const _MSL_THROW
{
	return *ptr_;
}

template <class T, class traits>
inline
_RefCountedPtr<T, traits>::operator const T* () const _MSL_THROW
{
	return ptr_;
}

template <class T, class traits>
inline
bool
_RefCountedPtr<T, traits>::isNonUnique() const _MSL_THROW
{
	if (refCount_ == 0)
		return false;
	return *refCount_ != 1;
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

#endif // RC_INVOKED

#endif // _REFCOUNTEDPTR_H

// hh 980804 changed __std() to _STD::
// hh 990120 changed name of MSIPL flags
// hh 990828 Added rebind members to _Single and _Array.
// hh 991206 Fixed bug in constructor for the exceptions disabled path
// hh 010402 Removed 68K CMF support
