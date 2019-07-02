#pragma once

#include <SFML/Graphics.hpp>

class slSpritesheet
{
public:
	slSpritesheet(sf::Texture* tex, sf::IntRect firstTile, int cols, int rows = 1);
	~slSpritesheet();
	sf::IntRect GetTile(int tile);
public:
	sf::Texture* texture;
	sf::IntRect origin;
	int numRows;
	int numCols;
};

