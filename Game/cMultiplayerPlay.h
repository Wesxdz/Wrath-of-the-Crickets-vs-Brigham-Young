#pragma once

#include "slComponent.h"

#include "HostSession.h"
#include "ClientSession.h"
#include <memory>
#include "Packets.h"

struct Player
{
	sf::Uint8 id;
	std::string name;
	int wealth;
};

class cMultiplayerPlay : public slComponent
{
public:
	std::shared_ptr<HostSession> host;
	std::shared_ptr<ClientSession> client;
	std::vector<Player> players;

	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event * e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;

	void Broadcast(sf::Packet packet);
	Player* GetSelf();
};

