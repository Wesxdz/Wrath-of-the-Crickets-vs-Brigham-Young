#pragma once

#include "slComponent.h"
#include <Discord/discord.h>

class DiscordManager : public slComponent
{
public:
	discord::ClientId client_id{595486295137189890};
	discord::Core* core{};
	discord::User user{};

public:
	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event * e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;
};

