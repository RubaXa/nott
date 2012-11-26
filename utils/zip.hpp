// -*- coding: utf-8; indent-tabs-mode: nil; tab-width: 4; c-basic-offset: 4; -*-

/*
* nott::utils::zip
*
* This class prevents the copying any class derived from this one
*
* Example:
*	std::list<std::string> list1 = {"1", "2", "3"};
*	std::set<int> list2 = {4, 5, 6};
*
*	auto data = nott::utils::zip(list1, list2);
*
*	for (auto i : data)
*		std::cout << std::get<1>(i) << std::endl;
*
*	Explicity:
*	std::__1::tuple<int, int> data = list.front();
*
* @author: Alexander Guinness
* @version: 0.0.1
* @license: MIT
* @date: 25/11/2012 21:05 PM
*/

#ifndef __NOTT_ZIP__
#define __NOTT_ZIP__

#include <tuple>
#include <list>
#include <utility>

namespace nott
{
	namespace utils
	{
		namespace details
		{
			template <std::size_t n, typename ...T>
				struct make_index final
				{
					const static std::size_t i = n - 1;

					using type = typename make_index
						<i, std::integral_constant<std::size_t, i>, T...>::type
					;
				}
			;

			template <typename ...T>
				struct make_index <0, T ...> final
				{
					typedef std::tuple<T ...> type;
				}
			;
		}


		template <typename T, std::size_t ...index, typename __list>
			auto zip (std::tuple<std::integral_constant <std::size_t, index> ...>, __list const &list) -> T
				{
					T result;

					auto it  = std::make_tuple(std::get<index>(list).begin() ...);
					auto end = std::make_tuple(std::get<index>(list).end() ...);

					while (std::max<bool>({std::get<index>(it) == std::get<index>(end) ...}) == false)
						result.emplace_back(*std::get<index>(it)++ ...);

					return result;
			}
		;


		template <typename ...T>
			const std::list<std::tuple<typename T::value_type ...>> zip (T const & ...list)
			{
				return zip <std::list<std::tuple <typename T::value_type ...>>> (
					typename details::make_index<sizeof ...(list)>::type(), std::tie (list ...)
				);
		}
	}
}

#endif
