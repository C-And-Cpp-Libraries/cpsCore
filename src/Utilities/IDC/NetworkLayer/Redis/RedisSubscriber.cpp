/*
 * RedisSubscriber.cpp
 *
 *  Created on: Jan 30, 2019
 *      Author: mirco
 */

#include "cpsCore/Utilities/IDC/NetworkLayer/Redis/RedisSubscriber.h"
#include "cpsCore/Logging/CPSLogger.h"

RedisSubscriber::RedisSubscriber(const RedisChannelParams& params)
{
	subscriber_.connect(params.hostIP_, params.port_,
			[](const std::string& host, std::size_t port, cpp_redis::connect_state status)
			{	if (status == cpp_redis::connect_state::dropped)
				{	CPSLOG_ERROR << "Client disconnected from " << host << ": " << port;}});
	if (!params.auth_.empty())
		subscriber_.auth(params.auth_);
	subscriber_.subscribe(params.channel_,
			std::bind(&RedisSubscriber::onChannel, this, std::placeholders::_1,
					std::placeholders::_2));
}

RedisSubscriber::~RedisSubscriber()
{
	subscriber_.disconnect(false);
}

boost::signals2::connection
RedisSubscriber::subscribe(const OnPacket::slot_type& slot)
{
	return onPacket_.connect(slot);
}

void
RedisSubscriber::start()
{
	subscriber_.commit();
}

void
RedisSubscriber::onChannel(const std::string& channel, const std::string& message)
{
	onPacket_(Packet(message));
}

void
RedisSubscriber::cancel()
{
	subscriber_.disconnect(false);
}
