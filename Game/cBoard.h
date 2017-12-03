#pragma once

#include "slComponent.h"
#include "Tiles.h"
#include <array>

class cBoard : public slComponent
{
public:
	sf::Sprite background;
	sf::Sprite tilesSpritesheet;
	std::array<std::array<std::shared_ptr<Tile>, 14>, 10> tiles;

public:
	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event * e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;
};

