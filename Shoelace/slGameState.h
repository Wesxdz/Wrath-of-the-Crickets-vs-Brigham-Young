#pragma once

#include "slEntity.h"

#include <map>
#include <SFML\Window\Event.hpp>

class slComponent;

// Bitmasks for adding functions to a slGameState's registries
class slRegister {

public:
	static const char INPUT;
	static const char UPDATE;
	static const char DRAW;

};

// A container for slEntities and slComponent function registration
class slGameState
{

public:
	std::map<sf::String, slEntity*> entities;
	std::map<int, std::vector<slComponent*>> inputRegistry;
	std::map<int, std::vector<slComponent*>> updateRegistry;
	std::map<int, std::vector<slComponent*>> drawRegistry;

public:
	~slGameState();
	virtual void Init() = 0;
	virtual void Reset() = 0;
	void Register(slComponent* component, int priority, char functions);

};