#pragma once

#include "slComponent.h"

class cMultiplayerPlay;

class cUI : public slComponent
{
public:
	sf::Font heading;
	sf::Text wealthCount;
	sf::Sprite wealthIcon;
	sf::Sprite roles;
	sf::Sprite selectedRole;
	cMultiplayerPlay* multiplayer;

public:
	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event * e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;
};

