// -*- coding: utf-8; indent-tabs-mode: nil; tab-width: 4; c-basic-offset: 4; -*-

/*
* nott::utils::join
*
* Joins all elements of an container into a string.
* The delimiter specifies a value to separate each element of the container.
**
* @author: Alexander Guinness
* @version: 0.0.1
* @license: MIT
* @date: 26/11/2012 02:22 PM
*/

#ifndef __NOTT_JOIN__
#define __NOTT_JOIN__

#include <sstream>

namespace nott
{
	namespace utils
	{
		/**
		* nott::utils::join
		*
		* std::string nott::utils::join
		* (
		*	std::type<value>::iterator && &&begin,
		*	std::type<value>::iterator && &&end,
		*	const type &delimiter = ','
		* )
		*
		* @param {std::type<value>::iterator &&} begin - iterator begin()
		* @param {std::type<value>::iterator &&} end   - iterator end()
		* @param {const std::type<value> &} [ delimiter ]
		* @returns {std::string}
		*
		* Example:
		*
		* Implicity:
		* std::vector<int> array = {1, 2, 3};
		* std::string result = nott::utils::join (array.begin(), array.end(), ',');
		*
		* Explicity
		* std::string result =
		* nott::utils::join <std::vector<int>::iterator, char>(array.begin(), array.end(), ',');
		*
		*/
		template <typename __type, typename __delimiter = char>
			std::string join (__type &&begin, __type &&end, const __delimiter &delimiter = ',')
			{
				__type i = begin;

				std::string result;
				std::ostringstream stream;

				if (i != end)
					stream << *i++;

				while (i != end)
				{
					stream << delimiter << *i++;
					result = stream.str();
				}

				return result;
			}
		;

		/**
		* nott::utils::join
		*
		* std::string nott::utils::join (std::type<value> && &&, const type &delimiter = ',')
		*
		* @param {std::type<value> &&} container
		* @param {const std::type<value> &} [ delimiter ]
		* @returns {std::string}
		*
		* Example:
		*
		* Implicity:
		* std::vector<int> array = {1, 2, 3};
		* std::string result = nott::utils::join (array, ',');
		*
		* Explicity
		* std::string result = nott::utils::join <std::vector<int>, char>(array, ',');
		*/
		template <typename __type, typename __delimiter = char>
			std::string join (__type &&data, const __delimiter &delimiter = ',')
			{
				return join(data.begin(), data.end(), delimiter);
			}
		;
	}
}

#endif
