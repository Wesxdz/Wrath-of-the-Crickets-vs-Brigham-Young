#pragma once

#include <SFML/Network.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

struct Client
{
	sf::IpAddress ip;
	sf::Uint16 port;
	std::string name;
	sf::Uint8 id;
};

class ClientSession
{
public:
	sf::UdpSocket socket;
	sf::IpAddress hostIP;
	sf::Uint16 hostPort;
	Client info;

public:
	ClientSession();
	~ClientSession();
	sf::Socket::Status SendToHost(sf::Packet packet);
};

