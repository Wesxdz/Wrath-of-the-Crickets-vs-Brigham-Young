#pragma once

#include "slComponent.h"
#include "Tiles.h"
#include "Entities.h"
#include <array>

class cBoard : public slComponent
{
public:
	sf::Sprite background;
	sf::Sprite tilesSpritesheet;
	std::array<std::array<std::shared_ptr<Tile>, 14>, 10> tiles;
	std::map<std::string, sf::Sound> sounds;
	std::vector<std::shared_ptr<Entity>> entities;

	int plantWheatCost = 5;
	int startFireCost = 10;
	int statueCost = 500;
	int seeBirdCost = 2;

public:
	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event * e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;

};

