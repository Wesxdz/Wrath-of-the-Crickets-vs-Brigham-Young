#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>


enum TileType
{
	DIRT, GRASS, ROCK, WHEAT
};

struct Tile
{
	TileType type;
	virtual void Update(float dt);
	virtual void Draw(sf::Sprite& spritesheet);
	virtual std::unique_ptr<Tile> OnClick();
	friend sf::Packet& operator<<(sf::Packet& packet, std::shared_ptr<Tile>& tile);
	friend sf::Packet& operator >>(sf::Packet& packet, std::shared_ptr<Tile>& tile);
};

struct Dirt : public Tile
{
	virtual std::unique_ptr<Tile> OnClick();
};

enum WheatGrowth {
	PLANT, SAP, MID, BIG, FULL, ROT
};

struct Wheat : public Tile
{
	sf::Uint8 owner = 0;
	WheatGrowth growthStage;
	float timeToGrow;
	Wheat();
	virtual void Update(float dt);
	virtual void Draw(sf::Sprite& spritesheet);
	virtual std::unique_ptr<Tile> OnClick();
};

struct Rock : public Tile
{
	int variation;
	Rock();
	virtual void Draw(sf::Sprite& spritesheet);
};

struct Grass : public Dirt
{
	Grass();
	int variation;
	virtual void Draw(sf::Sprite& spritesheet);
};

