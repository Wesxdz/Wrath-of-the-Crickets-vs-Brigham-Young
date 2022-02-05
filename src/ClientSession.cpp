#include "ClientSession.h"



ClientSession::ClientSession()
{
}


ClientSession::~ClientSession()
{
}

sf::Socket::Status ClientSession::SendToHost(sf::Packet packet)
{
	return socket.send(packet, hostIP, hostPort);
}
