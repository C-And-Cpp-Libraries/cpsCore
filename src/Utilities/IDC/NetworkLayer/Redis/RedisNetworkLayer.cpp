/*
 * RedisNetworkLayer.cpp
 *
 *  Created on: Jan 25, 2019
 *      Author: mirco
 */

#include "cpsCore/Utilities/IDC/NetworkLayer/Redis/RedisNetworkLayer.h"
#include "cpsCore/Utilities/IDC/NetworkLayer/Redis/RedisPublisher.h"
#include "cpsCore/Utilities/IDC/NetworkLayer/Redis/RedisSubscriber.h"
#include "cpsCore/Configuration/PropertyMapper.hpp"
#include "cpsCore/Utilities/Scheduler/IScheduler.h"

bool
RedisNetworkLayer::sendPacket(const std::string& id, const Packet& packet)
{
	auto it = publishers_.find(id);
	if (it == publishers_.end())
	{
		CPSLOG_ERROR << "Connection id not specified: " << id;
		return false;
	}

	return it->second->publish(packet);
}

boost::signals2::connection
RedisNetworkLayer::subscribeOnPacket(const std::string& id, const OnPacket::slot_type& handle)
{
	auto it = subscribers_.find(id);
	if (it == subscribers_.end())
	{
		CPSLOG_ERROR << "Connection id not specified: " << id;
		return boost::signals2::connection();
	}

	return it->second->subscribe(handle);
}

bool
RedisNetworkLayer::run(RunStage stage)
{
	switch (stage)
	{
	case RunStage::INIT:
	{
		if (!isSet<IScheduler>())
		{
			CPSLOG_ERROR << "RedisNetworkLayer scheduler missing";
			return true;
		}

		for (const auto& it : params.sub())
		{
			subscribers_.emplace(it.channel(), std::make_shared<RedisSubscriber>(it));
		}
		for (const auto& it : params.pub())
		{
			publishers_.emplace(it.channel(), std::make_shared<RedisPublisher>(it));
		}


		break;
	}
	case RunStage::NORMAL:
	{
		auto sched = get<IScheduler>();
		for (const auto& it : subscribers_)
		{
			sched->schedule(std::bind(&RedisSubscriber::start, it.second), Milliseconds(0));
		}

		for (const auto& it : publishers_)
		{
			sched->schedule(std::bind(&RedisPublisher::startHandler, it.second), Milliseconds(0));
		}
		break;
	}
	default:
		break;
	}
	return false;
}
