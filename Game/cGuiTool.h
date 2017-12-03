#pragma once

#include "slComponent.h"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

class cGuiTool : public slComponent
{

public:
	sfg::SFGUI sfgui;
	sfg::Desktop desktop;

public:

	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event * e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;
};

