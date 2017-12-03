#pragma once

#include <SFML/Graphics.hpp>
class cBoard;

class Entity
{
	sf::Vector2i index;
	cBoard* board;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
};

