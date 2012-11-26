// -*- coding: utf-8; indent-tabs-mode: nil; tab-width: 4; c-basic-offset: 4; -*-

/*
* nott::utils::is_container
*
* nott::utils::is_container<std::array<int>>::value;
*
* @author: Alexander Guinness
* @version: 0.0.1
* @license: MIT
* @date: 26/11/2012 04:18 PM
*/

#ifndef __NOTT_IS_CONTAINER__
#define __NOTT_IS_CONTAINER__

#include <type_traits>
#include <valarray>
#include <ratio>

namespace nott
{
	namespace utils
	{
		namespace details
		{
			template <typename T, T, T>
				struct is {
					typedef void type;
				}
			;
		}

		template <typename T, typename = void>
			struct is_container : std::false_type { };
		;

		template <typename T>
			struct is_container <std::valarray<T>> : std::true_type { };
		;

		template <std::intmax_t T>
			struct is_container <std::ratio<T, T>> : std::true_type { };
		;

		template <typename T>
			struct is_container
			<T, typename details::is <typename T::const_iterator(T::*)() const, &T::begin, &T::end>::type> :
			std::is_class<T> { };
		;
	}
}

#endif

