#pragma once

#include "slComponent.h"

// Prototype controls for exiting and quitting game
class cSceneControls : public slComponent
{
public:
	cSceneControls();
	~cSceneControls();
	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event * e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;
};

