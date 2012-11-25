// -*- coding: utf-8; indent-tabs-mode: nil; tab-width: 4; c-basic-offset: 4; -*-

#ifndef __NOTT_TO_NUMERIC___
#define __NOTT_TO_NUMERIC___

#include <string>
#include <cctype>

/*
TODO: punycode
*/

namespace nott
{
	namespace utils
	{
		class url final
		{
			public:
				url() {};
				~url() {};

				std::string encode(const std::string &, const bool & = false) const;
				std::string decode(const std::string &) const;

			private:
				url(const url&);
				const url& operator=(const url&);

				char unhex(const char &value) const noexcept {
					return std::isdigit(value) ? value - '0' : std::tolower(value) - 'a' + 10;
				}
		};

		/*
		  RFC 3986 section 2.2 Reserved Characters:
		  	!, *, ', (, ), ;, :, @, &, =, +, $, , /, ?, #, [, ]

		  	%21, %23, %24, %26, %27, %28, %29, %2A, %2B, %2C,
		  	%2F, %3A, %3B, %3D, %3F, %40, %5B, %5D

		  RFC 3986 section 2.3 Unreserved Characters:
		  	[aA-zZ0-9_.~-]

		  Common characters after percent-encoding (ASCII or UTF-8 based):
		  	newline space ", %, -, . <, >, \, ^, _, `, {, |, }, ~

		  	%0A or %0D or %0D%0A, %20, %22, %25, %2D, %2E, %3C, %3E, %5C, %5E, %5F, %60, %7B, %7C, %7D, %7E

		  application/x-www-form-encoded:
		  	+
		*/

		/** url::encode */
		std::string url::encode (const std::string &value, const bool &plus) const
		{
			const std::string except("-_.~");

			const size_t reserve = 4;
			char buffer[reserve];

			std::string result;
			std::string::const_iterator i = value.begin();

			while (i != value.end()) {
				if (std::isalnum(*i) || ~except.find(*i))
					result.push_back(*i);

				else if (plus && *i == ' ')
					result.push_back('+');

				else {
					std::snprintf(buffer, reserve, "%c%.2X", '%', *i & 0xff);
					result.append(buffer);
				}

				++i;
			}

			return result;
		};

		/** url::decode */
		std::string url::decode (const std::string &value) const
		{
			std::string result;
			std::string::const_iterator i = value.begin();

			while (i != value.end()) {
				if (*i == '%' && isxdigit(*(i + 2))) {
					result.push_back(this->unhex(*(i + 1)) << 4 | this->unhex(*(i + 2)));
					i += 2;
				}

				else
					result.push_back(*i == '+' ? ' ' : *i);

				++i;
			}

			return result;
		};
	}
}

#endif

