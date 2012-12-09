// -*- coding: utf-8; indent-tabs-mode: nil; tab-width: 4; c-basic-offset: 4; -*-

/*
* nott::utils::url
*
* This module is designed to work with URL
*
* @requires c++11
* @author: Alexander Guinness
* @version: 0.0.1
* @license: MIT
* @date: 25/11/2012 0:00 PM
*/

#ifndef __NOTT_URL__
#define __NOTT_URL__

#include <string>
#include <cctype>
#include <regex>

#include <map>

/*
TODO:
punycode, host, fragment, port, protocol, search, params, ip, icu, user, password, verify
RFC 1630, RFC 1738, RFC 2396, RFC 3986, RFC 3987 compliant
*/

namespace nott
{
	namespace utils
	{
		//template<T = std::string>
		class url
		{
			public:
				explicit url(const std::string &__url) : __url(__url) {};
				~url() {};

			private:
				url(const url&);
				const url& operator=(const url&);

				char unhex(const char &value) const noexcept {
					return std::isdigit(value) ? value - '0' : std::tolower(value) - 'a' + 10;
				}

				enum struct components {
					SCHEME, USERNAME, PASSWORD, HOST, PORT, PATH, QUERY, REF
				};

				const std::string __url;

			public:
				std::string encode(const bool & = false) const;
				std::string decode() const;

				// RFC 3986
				std::string scheme() const;
				std::string userinfo() const;
		};

		/*
		  RFC 1630, RFC 1738, RFC 2396, RFC 3987

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
		std::string url::encode(const bool &plus) const
		{
			const std::string except("-_.~");

			const size_t reserve = 4;
			char buffer[reserve];

			std::string result;
			std::string::const_iterator i = this->__url.begin();

			while (i != this->__url.end()) {
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
		std::string url::decode() const
		{
			std::string result;
			std::string::const_iterator i = this->__url.begin();

			while (i != this->__url.end()) {
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


		/**
		 RFC 3986 3.1 Scheme
		 scheme = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
		*/
		std::string url::scheme() const
		{
			std::match_results<std::string::const_iterator> result;

			try {
				const std::regex pattern("^[a-z\\d.+-]+(?=://)");
				std::regex_search(this->__url, result, pattern);
			}
			catch (const std::regex_error &error) {
				std::cout << "regex_error caught: " << error.what() << std::endl;
			}

			return result.str(0);
		};


		/**
		 RFC 3986 3.2.1. User Information
		 userinfo  = *( unreserved / pct-encoded / sub-delims / ":" )

		 pct-encoded = "%" HEXDIG HEXDIG
		 unreserved  = ALPHA / DIGIT / "-" / "." / "_" / "~"
		 sub-delims  = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="
		*/

		std::string url::userinfo() const
		{
			std::match_results<std::string::const_iterator> result;

			try {
				if (!this->scheme().empty()) {
					const std::regex pattern("^[a-z\\d.+-]+://(?:[\\w\\d!$&'()*+,:;=.~-]+|%[a-f\\d]{2})+(?=@)");
					std::regex_search(this->__url, result, pattern);
				}
			}
			catch (const std::regex_error &error) {
				std::cout << "regex_error caught: " << error.what() << '\n';
			}

			return result.str(0);
		};
	}
}

#endif

