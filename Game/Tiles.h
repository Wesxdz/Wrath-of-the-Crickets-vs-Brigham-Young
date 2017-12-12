#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <memory>


enum TileType
{
	NONE, DIRT, GRASS, ROCK, WHEAT, SCULPTURE, CHARRED_WHEAT
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
	Dirt();
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
	virtual void Draw(sf::Sprite& spritesheet) override;
};

struct Grass : public Dirt
{
	Grass();
	int variation;
	virtual void Draw(sf::Sprite& spritesheet) override;
};

struct Sculpture : public Tile
{
	Sculpture();
	virtual void Draw(sf::Sprite& spritesheet) override;
};

struct CharredWheat : public Tile
{
	CharredWheat();
	virtual void Draw(sf::Sprite& spritesheet) override;
};

