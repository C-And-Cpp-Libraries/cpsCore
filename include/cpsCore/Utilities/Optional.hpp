/*
 * Optional.h
 *
 *  Created on: Jun 12, 2019
 *      Author: mirco
 */

#ifndef UAVAP_UAVAP_CORE_PROPERTYMAPPER_OPTIONAL_HPP_
#define UAVAP_UAVAP_CORE_PROPERTYMAPPER_OPTIONAL_HPP_

#ifdef NO_RTTI

template<typename Type>
struct Optional
{
	inline
	Optional() :
			isSet(false)
	{
	}

	inline
	Optional(const Type& val) :
			value(val), isSet(true)
	{
	}

	inline bool
	operator!() const
	{
		return isSet;
	}

	inline void
	operator=(const Type& val)
	{
		value = val;
		isSet = true;
	}

	inline Type
	operator*() const
	{
		return value;
	}

	inline
	operator bool() const
	{
		return isSet;
	}

	inline const Type*
	operator->() const
	{
		return &value;
	}

	inline Type*
	operator->()
	{
		return &value;
	}

	inline bool
	is_initialized() const
	{
		return isSet;
	}

	Type value;
	bool isSet;
};

#else

#include <optional>

template <typename Type>
using Optional = std::optional<Type>;

#endif

#endif /* UAVAP_UAVAP_CORE_PROPERTYMAPPER_OPTIONAL_HPP_ */
