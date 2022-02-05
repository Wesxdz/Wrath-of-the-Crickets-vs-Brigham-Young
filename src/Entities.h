#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>
class cBoard;
struct Tile;

struct TilePlacement
{
	sf::Vector2i index;
	std::shared_ptr<Tile> tile;
};

enum EntityType {
	CRICKET, SEAGULL, FIRE
};

struct Entity
{
	sf::Uint32 handle = 0; // a primary key for this enti-ty!
	EntityType type;
	sf::Vector2i index;
	float turnSpeed = 1.f;
	float timeToNextTurn = 1.f;
	cBoard* board;
	sf::Sprite entities;
	Entity();
	virtual void Update(float dt);
	virtual void Draw() = 0;
	virtual void OnTurn() = 0;
	virtual std::vector<TilePlacement> GetAdjacent();
	friend sf::Packet& operator<<(sf::Packet& pk, std::shared_ptr<Entity>& entity);
	friend sf::Packet& operator >>(sf::Packet& pk, std::shared_ptr<Entity>& entity);
	bool operator==(const Entity& entity);
};

struct Cricket : public Entity
{
	Cricket();
	// Inherited via Entity
	virtual void Draw() override;
	virtual void OnTurn() override;
};

struct Seagull : public Entity
{
	Seagull();
	// Inherited via Entity
	virtual void Draw() override;
	virtual void OnTurn() override;
};

struct Fire : public Entity
{
	Fire();
	// Inherited via Entity
	virtual void Draw() override;
	virtual void OnTurn() override;
};

