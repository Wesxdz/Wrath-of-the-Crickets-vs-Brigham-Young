#pragma once

#include <SFML/Network.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include "ClientSession.h"
#include <stack>

class HostSession
{
public:
	HostSession();
public:
	sf::UdpSocket socket;
	std::vector<Client> clients;
	std::stack<sf::Uint8> availableIds;
};

