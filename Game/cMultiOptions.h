#pragma once
#include "slComponent.h"

#include <SFML/Network.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

class cMultiplayerSetup;
class cGuiTool;

class cMultiOptions : public slComponent
{
public:
	std::shared_ptr<sfg::Window> mainWindow;
	std::shared_ptr<sfg::Window> hostWindow;
	std::shared_ptr<sfg::Window> clientWindow;
	std::vector<std::shared_ptr<sfg::Label>> lobbyNames;
	std::shared_ptr<sfg::Box> lobbyContent;
	std::shared_ptr<sfg::Entry> enterUsername;

	cMultiplayerSetup* multiplayer;
	cGuiTool* gui;

public:

	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event * e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;

	void StartLobby();
};

