#pragma once

#include "slComponent.h"
#include <memory>
struct Entity;

class cBoard;

class cEnemySpawner : public slComponent
{

public:
	cBoard* board;
	// how many points required to spawn Cricket
	float difficulty;
	float points;
	std::vector<sf::Vector2i> possibleSpawns;

public:
	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event * e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;

	// Finds placement for entity and adds to board
	void Spawn(std::shared_ptr<Entity> entity);

};

