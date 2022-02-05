#pragma once

#include "slComponent.h"

#include "HostSession.h"
#include "ClientSession.h"
#include "Gameplay.h"

class cMultiOptions;

class cMultiplayerSetup : public slComponent
{

public:
	std::shared_ptr<HostSession> host;
	std::shared_ptr<ClientSession> client;
	cMultiOptions* options;
	Gameplay* next = nullptr;


public:
	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event * e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;

	bool HostGame(sf::Uint16 port);
	bool JoinGame(sf::IpAddress ip, sf::Uint16 port);
	void LeaveGame();
	void Broadcast(sf::Packet packet);
};

