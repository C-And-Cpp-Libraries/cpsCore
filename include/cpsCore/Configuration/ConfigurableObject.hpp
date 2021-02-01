/*
 * ConfigurableObject.hpp
 *
 *  Created on: Jun 24, 2019
 *      Author: mirco
 */

#ifndef UAVAP_CORE_PROPERTYMAPPER_CONFIGURABLEOBJECT_HPP_
#define UAVAP_CORE_PROPERTYMAPPER_CONFIGURABLEOBJECT_HPP_
#include "cpsCore/Configuration/Configuration.hpp"
#include "cpsCore/Configuration/PropertyMapper.hpp"

template<class ParameterSet>
class ConfigurableObject
{
public:

	using ParamType = ParameterSet;

	ConfigurableObject() = default;

	inline ConfigurableObject(const ParameterSet& p) :
			params(p)
	{
	}

	inline void
	setParams(const ParameterSet& set)
	{
		params = set;
	}

	inline bool
	configure(const Configuration& config)
	{
		PropertyMapper<Configuration> pm(config);
		params.template configure(pm);
		return pm.map();
	}

	inline const ParameterSet&
	getParams() const
	{
		return params;
	}

	inline ParameterSet&
	getParams()
	{
		return params;
	}

//	template<typename Config>
//	inline static void
//	configureParams(ConfigurableObject<ParameterSet>& obj, Config& config)
//	{
//		obj.params.template configure(config);
//	}

	template<typename Config>
	inline static ParameterSet
	configureParamsStatic(Config& config)
	{
		ParameterSet p;
		p.template configure(config);
		return p;
	}

protected:

	ParameterSet params;
};


/**
 * For use with nested configurable objects, where the root object doesn't need to be configured
 */
struct PlaceholderParams
{
	template <typename Config>
	void
	configure(Config& c)
	{

	}
};

#endif /* UAVAP_CORE_PROPERTYMAPPER_CONFIGURABLEOBJECT_HPP_ */
