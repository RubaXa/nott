//#include "nott.hpp"

#include <iostream>

#include "utils/url.hpp"
#include "utils/noncopyable.hpp"
#include "utils/join.hpp"
#include "utils/to_numeric.hpp"

#include "utils/is_container.hpp"

#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <set>
#include <array>
#include <list>

using namespace std;


/*
template<typename T>
    typename std::enable_if
    < nott::utils::is_container<T>::value, std::ostream >::type&
    operator<<(std::ostream& os, const T& a)
{
    os << '[';
    std::copy(a.begin(), a.end(), std::ostream_iterator<typename T::value_type>(os, ", "));
    os << ']';
    return os;
}

10.0.3.4
::FFFF:10.0.3.4
::FFFF:a00:304
0:0:0:0:0:ffff:a00:304

*/


int main()
{

//	std::list<std::string> list1 = {"1", "2", "3"};
	std::list<int> list1 = {4, 5, 6};
	std::list<int> list2 = {4, 5, 6};

	nott::utils::url url("2001:0000:1234:0000:0000:C1C0:ABCD:0876");

	cout <<  url.host() << endl;


	//cout <<  url.verify() << endl;


		/*
		foo://example.com:8042/over/there?name=ferret#nose
         \_/   \______________/\_________/ \_________/ \__/
          |           |            |            |        |
       scheme     authority       path        query   fragment
          |   _____________________|__
         / \ /                        \
         urn:example:animal:ferret:nose
		*/

		std::map<std::string, std::string> comp = {

			/*
			Basic Latin alphabet
			*/
			{"alpha", "a-z"},

			/*
			0-9
			*/
			{"digit", "\\d"},

			/*
			6.2.2.1. Case Normalization

			For all URIs, the hexadecimal digits within a percent-encoding
			triplet (e.g., "%3a" versus "%3A") are case-insensitive and therefore
			should be normalized to use uppercase letters for the digits A-F.

			2.1. Percent-Encoding

			A percent-encoded octet is encoded as a character
			triplet, consisting of the percent character "%" followed by the two
			hexadecimal digits representing that octet's numeric value.  For
			example, "%20" is the percent-encoding for the binary octet
			"00100000" (ABNF: %x20), which in US-ASCII corresponds to the space
			character (SP).
			*/
			{"hex", "%[a-f\\d]{2}"},

			/*
			3.1. Scheme

			Scheme names consist of a sequence of characters beginning with a
			letter and followed by any combination of letters, digits, plus
			("+"), period ("."), or hyphen ("-").

			scheme = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
			*/
			{"scheme", "^[a-z\\d.+-]+(?=://)"},

			/*
			3.2.2. Host

			The host subcomponent of authority is identified by an IP literal
			encapsulated within square brackets, an IPv4 address in dotted-
			decimal form, or a registered name.  The host subcomponent is case-
			insensitive.

			 host = IP-literal / IPv4address / reg-name
			*/
			{"host", "1"},

			/*
			3.2.3. Port
			The port subcomponent of authority is designated by an optional port
			number in decimal following the host and delimited from it by a
			single colon (":") character.

			port = *DIGIT
			*/
			{"port", "1"},

			/*
			3.4. Query

			The query component contains non-hierarchical data that, along with
			data in the path component
			The query component is indicated by the first question
			mark ("?") character and terminated by a number sign ("#") character
			or by the end of the URI.

			query = *( pchar / "/" / "?" )
			*/

			{"query", "1"},

			/*
			3.5. Fragment

			A fragment identifier component is indicated by the presence of a
			number sign ("#") character and terminated by the end of the URI.

			fragment = *( pchar / "/" / "?" )
			*/


			/*
			4.1. URI Reference

			URI-reference = URI / relative-ref
			*/
			{"URI-reference", "1"},

			/*
			4.2. Relative Reference

			relative-ref = relative-part [ "?" query ] [ "#" fragment ]
			*/
			{"relative-ref", "1"},

			/*
			4.2. Relative Reference

			relative-part = "//" authority path-abempty / path-absolute / path-noscheme / path-empty
			*/
			{"relative-part", "1"},

			/*
			4.3. Absolute URI

			absolute-URI = scheme ":" hier-part [ "?" query ]
			*/
			{"absolute-URI", "1"},

			/*
			3.2. Authority

			The authority component is preceded by a double slash ("//") and is
			terminated by the next slash ("/"), question mark ("?"), or number
			sign ("#") character, or by the end of the URI.

			authority = [ userinfo "@" ] host [ ":" port ]
			*/
			{"authority", "1"},

			/*
			3.2.1. User Information

			The userinfo subcomponent may consist of a user name and, optionally,
			scheme-specific information about how to gain authorization to access
			the resource.  The user information, if present, is followed by a
			commercial at-sign ("@") that delimits it from the host.

			Use of the format "user:password" in the userinfo field is
			deprecated.  Applications should not render as clear text any data
			after the first colon (":") character found within a userinfo
			subcomponent unless the data after the colon is the empty string
			(indicating no password).

			userinfo = *( unreserved / pct-encoded / sub-delims / ":" )
			*/

			{"userinfo", "^[a-z\\d.+-]+://(?:[\\w\\d!$&'()*+,:;=.~-]+|%[a-f\\d]{2})+(?=@)"},

			/*
			2.2. Reserved Characters

			These characters are called "reserved" because they may (or may not)
			be defined as delimiters by the generic syntax, by each scheme-specific syntax,
			or by the implementation-specific syntax of a URI's dereferencing algorithm.
			If data for a URI component would conflict with a reserved character's purpose
			as a delimiter, then the conflicting data must be
			percent-encoded before the URI is formed.

			reserved   = gen-delims / sub-delims
			gen-delims = ":" / "/" / "?" / "#" / "[" / "]" / "@"
			sub-delims = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="
			*/

			{"reserved", "1"},


			{"unreserved", "1"},


			{"sub-delims", "1"},

			/*
			3.2.2. Host

			IP-literal = "[" ( IPv6address / IPvFuture  ) "]"
			*/
			{"IP-literal", "1"},

			/*
			IPv4address = dec-octet "." dec-octet "." dec-octet "." dec-octet
			*/
			{"IPv4address", "1"},

			/*
			IPv6address = 6( h16 ":" ) ls32
             /                       "::" 5( h16 ":" ) ls32
             / [               h16 ] "::" 4( h16 ":" ) ls32
             / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
             / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
             / [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
             / [ *4( h16 ":" ) h16 ] "::"              ls32
             / [ *5( h16 ":" ) h16 ] "::"              h16
             / [ *6( h16 ":" ) h16 ] "::"
			*/
			{"IPv6address", "1"},

			/*
			3.2.2. Host

			IPvFuture = "v" 1*HEXDIG "." 1*( unreserved / sub-delims / ":" )
			*/
			{"IPvFuture", "1"},


			/*
			 reg-name = *( unreserved / pct-encoded / sub-delims )
			*/
			{"reg-name", "1"},


			{"dec-octet", "1"},

			/*
			 h16 = 1*4HEXDIG
			*/
			{"h16", "1"},

			/*
			ls32 = ( h16 ":" h16 ) / IPv4address
			*/
			{"ls32", "1"},


			{"sub-delims", "1"},


			{"gen-delims", "1"}
		};


		/*
		5.4.1. Normal Examples
		g:h
		http://a/b/c/g
		http://a/b/c/g/
		http://a/g
		http://g
		http://a/b/c/d;p?y
		http://a/b/c/g?y
		http://a/b/c/d;p?q#s
		http://a/b/c/g#s
		http://a/b/c/g?y#s
		http://a/b/c/;x
		http://a/b/c/g;x
		http://a/b/c/g;x?y#s
		http://a/b/c/d;p?q
		http://a/b/c/
		http://a/b/
		http://a/b/g
		http://a/
		http://a/
		http://a/g
		http://example.com
		http://example.com/
		http://example.com:/
		http://example.com:80/
		*/

		//std::cout << comp.at("foo") << std::endl;

	//url parse foo;


	//url.params("http://www.cplusplus.com/reference/list/list/begin/?some=1&bar=1&get=&set=1");



	return 0;
}




