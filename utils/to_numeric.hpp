// -*- coding: utf-8; indent-tabs-mode: nil; tab-width: 4; c-basic-offset: 4; -*-

/**
 * to_numeric.hpp
 *
 * Converts a string value to numeric type
 *
 * @author: Alexander Guinness
 * @version: 0.0.1
 * @license: MIT
 * @date: Thu Mon 5 21:57:00 2012
 **/

#ifndef __NOTT_TO_NUMERIC___
#define __NOTT_TO_NUMERIC___

#include <type_traits>

namespace nott
{
	namespace utils
	{
		/*
		 * to_numeric
		 *
		 * @param {std::string const &} value - the string to convert
		 * @param {size_t *} index - address of an integer to store the index of the first unconverted character
		 *
		 * If the function does not throw an exception and index != 0,
		 * the function stores in *index the index of the first unconverted element of string.
		 *
		 * @param {int} base - the number base
		 *
		 * The valid integer value can consists of the following parts:
		 *  - plus or minus sign
		 *
		 *  - prefix (0) indicating octal base (applies only when the base is 8)
		 *
		 *  - prefix (0x or 0X) indicating hexadecimal base (applies only when the base is 16)
		 *
		 *  - a sequence of digits
		 *
		 * @throws
		 *
		 *  # std::stoi, std::stol, std::stoul, std::stoll, std::stoull:
		 *
		 *  - std::invalid_argument if std::strtol, std::strtoul, std::strtoll,
		 *	or std::strtoull reports that no conversion could be performed.
		 *
		 *  - std::out_of_range if the converted value is outside the range of representable values for the return type.
		 *
		 *  # std::stof, std::stod, std::stold:
		 *
		 *  - std::invalid_argument if std::strtod or std::strtold reports that no conversion could be performed.
		 *
		 *  - std::out_of_range if std::strtod or std::strtold sets std::errno to std::ERANGE.
		 *
		 * @returns {std::string} the converted result
		 */


		/** @name std::string / const char * -> unsigned int, short int */
		template<class T>
			static inline T to_numeric(const std::string &value, size_t *index = 0, int base = 10)
			{
				return static_cast<T>(std::stoi(value, index, base));
			}
		;

		/** @name std::string / const char * -> int */
		template<>
			inline int to_numeric<int>(const std::string &value, size_t *index, int base)
			{
				return std::stoi(value, index, base);
			}
		;

		/** @name std::string / const char * -> long */
		template<>
			inline long to_numeric<long>(const std::string &value, size_t *index, int base)
			{
				return std::stol(value, index, base);
			}
		;

		/** @name std::string / const char * -> long long */
		template<>
			inline long long to_numeric<long long>(const std::string &value, size_t *index, int base)
			{
				return std::stoll(value, index);
			}
		;

		/** @name std::string / const char * -> unsigned long */
		template<>
			inline unsigned long to_numeric<unsigned long>(const std::string &value, size_t *index, int base)
			{
				return std::stoul(value, index, base);
			}
		;

		/** @name std::string / const char * -> unsigned long long */
		template<>
			inline unsigned long long to_numeric<unsigned long long>(const std::string &value, size_t *index, int base)
			{
				return std::stoull(value, index, base);
			}
		;

		/** @name std::string / const char * -> float */
		template<>
			inline float to_numeric<float>(const std::string &value, size_t *index, int base)
			{
				return std::stof(value, index);
			}
		;

		/** @name std::string / const char * -> double */
		template<>
			inline double to_numeric<double>(const std::string &value, size_t *index, int base)
			{
				return std::stod(value, index);
			}
		;

		/** @name std::string / const char * -> long double */
		template<>
			inline long double to_numeric<long double>(const std::string &value, size_t *index, int base)
			{
				return std::stold(value, index);
			}
		;

		/** @name arithmetic cast */
		template<class to_type, class from_type>
			inline typename std::enable_if<std::is_arithmetic<from_type>::value, from_type>
			::type to_numeric(const from_type &value)
			{
				return static_cast<to_type>(value);
			}
		;
	}
}

#endif
