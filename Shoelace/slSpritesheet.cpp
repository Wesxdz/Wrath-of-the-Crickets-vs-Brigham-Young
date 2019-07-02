#include "slSpritesheet.h"

slSpritesheet::slSpritesheet(sf::Texture* tex, sf::IntRect firstTile, int cols, int rows) :
	texture{ tex },
	numCols{ cols },
	numRows{ rows }
{
	sf::Vector2i size =  {firstTile.width * cols, firstTile.height * rows};
	origin = firstTile;
}

slSpritesheet::~slSpritesheet()
{
}

sf::IntRect slSpritesheet::GetTile(int tile)
{
	int totalTiles = numRows * numCols;
	if (tile >= totalTiles) tile = tile % totalTiles;
	int row = tile / numCols;
	int col = tile - row * numCols;
	return sf::IntRect(origin.left + col * origin.width, origin.top + row * origin.height, origin.width, origin.height);
}
