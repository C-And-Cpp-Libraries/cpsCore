/*
 * TypeTraits.hpp
 *
 *  Created on: Aug 18, 2019
 *      Author: mirco
 */

#ifndef UAVAP_CORE_TYPETRAITS_HPP_
#define UAVAP_CORE_TYPETRAITS_HPP_
#include <string>
#include <type_traits>
#include <vector>
#include <map>
#include <unordered_map>

template<typename T>
struct is_vector: public std::false_type
{
};

/**
 * @brief is_vector struct true_type because T is a vector
 */
template<typename T, typename A>
struct is_vector<std::vector<T, A>> : public std::true_type
{
};

template<typename T>
struct is_string_key_map: public std::false_type
{
};

template<typename T, typename A>
struct is_string_key_map<std::map<std::string, T, A>> : public std::true_type
{
};

template<typename T, typename A>
struct is_string_key_map<std::unordered_map<std::string, T, A>> : public std::true_type
{
};

template<typename Type>
using enable_if_is_vector = typename std::enable_if<is_vector<Type>::value, Type>::type;
template<typename Type>
using enable_if_not_is_vector = typename std::enable_if<!is_vector<Type>::value, Type>::type;

template<typename Type>
using enable_if_is_string_key_map = typename std::enable_if<is_string_key_map<Type>::value, Type>::type;
template<typename Type>
using enable_if_is_not_string_key_map = typename std::enable_if<!is_string_key_map<Type>::value, Type>::type;




template <typename Type>
using is_string = std::is_same<Type, std::string>;


#endif /* UAVAP_CORE_TYPETRAITS_HPP_ */
