// -*- coding: utf-8; indent-tabs-mode: nil; tab-width: 4; c-basic-offset: 4; -*-

/*
* nott::utils::noncopyable
*
* This class prevents the copying any class derived from this one
*
* Example:
* class T: public nott::utils::noncopyable {
*    // ...
* };
*
* @author: Alexander Guinness
* @version: 0.0.1
* @license: MIT
* @date: 25/11/2012 21:05 PM
*/

#ifndef __NOTT_NOCOPYABLE__
#define __NOTT_NOCOPYABLE__

namespace nott
{
	namespace utils
	{
		class noncopyable
		{
			private:
				noncopyable(noncopyable const &) = delete;
				noncopyable const &operator=(noncopyable const &) = delete;

			protected:
				 noncopyable() {};
				~noncopyable() {};
		};
	}
}

#endif
