#include "Tiles.h"
#include "slGame.h"
#include "cResources.h"
#include "cMultiplayerPlay.h"
#include "Packets.h"

void Tile::Update(float dt)
{
}

void Tile::Draw(sf::Sprite & spritesheet)
{
}

std::unique_ptr<Tile> Tile::OnClick()
{
	return nullptr;
}

Wheat::Wheat()
{
	type = TileType::WHEAT;
	growthStage = WheatGrowth::PLANT;
	timeToGrow = 10.0f;
}

void Wheat::Update(float dt)
{
	if (growthStage != WheatGrowth::ROT) {
		timeToGrow -= dt;
		if (timeToGrow <= 0) {
			growthStage = (WheatGrowth)((int)growthStage + 1);
			timeToGrow = 5.0f;
		}
	}
}

void Wheat::Draw(sf::Sprite & spritesheet)
{
	spritesheet.setTextureRect(sf::IntRect(growthStage * 16, 0, 16, 16));
	slGame::inst.window->draw(spritesheet);
	if (growthStage != WheatGrowth::ROT) {
		sf::Sprite ownership;
		ownership.setTexture(*slGame::inst.resources->Load<sf::Texture>("owner.png"));
		ownership.setPosition(spritesheet.getPosition());
		ownership.setTextureRect({ (int)owner * 16, 0, 16, 16 });
		ownership.setScale({ 4, 4 });
		slGame::inst.window->draw(ownership);
	}
}

std::unique_ptr<Tile> Wheat::OnClick()
{
	auto multi = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
	auto self = multi->GetSelf();
	if (self->id == owner) {
		switch (growthStage) {
		case WheatGrowth::SAP:
			self->wealth += 1;
			break;
		case WheatGrowth::MID:
			self->wealth += 3;
			break;
		case WheatGrowth::BIG:
			self->wealth += 6;
			break;
		case WheatGrowth::FULL:
			self->wealth += 10;
			break;
		case WheatGrowth::ROT:
			self->wealth += 1;
		}
		sf::Packet packet;
		pk::PlayerWealthChange info{ self->id, self->wealth };
		packet << info;
		multi->client->SendToHost(packet);
	}
	else if (growthStage == WheatGrowth::ROT) {
		self->wealth += 1;
		sf::Packet packet;
		pk::PlayerWealthChange info{ self->id, self->wealth };
		packet << info;
		multi->client->SendToHost(packet);
	}
	else {
		return nullptr;
	}
	return std::make_unique<Dirt>();
}

Rock::Rock()
{
	type = TileType::ROCK;
}

void Rock::Draw(sf::Sprite & spritesheet)
{
	spritesheet.setTextureRect({ variation * 16 , 16, 16, 16 });
	slGame::inst.window->draw(spritesheet);
}

std::unique_ptr<Tile> Dirt::OnClick()
{
	auto multi = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
	auto self = multi->GetSelf();
	if (self->wealth >= 5) {
		self->wealth -= 5;
		sf::Packet packet;
		pk::PlayerWealthChange info{ self->id, self->wealth };
		packet << info;
		multi->client->SendToHost(packet);
		auto wheat = std::make_unique<Wheat>();
		wheat->owner = self->id;
		return std::move(wheat);
	}
	else {
		return nullptr;
	}
}

Grass::Grass()
{
	type = TileType::GRASS;
}

void Grass::Draw(sf::Sprite & spritesheet)
{
	spritesheet.setTextureRect({ 48 + variation * 16, 16, 16, 16 });
	slGame::inst.window->draw(spritesheet);
}

sf::Packet & operator<<(sf::Packet & packet, std::shared_ptr<Tile>& tile)
{
	packet << sf::Uint8(tile->type);
	if (tile->type == TileType::WHEAT) {
		Wheat* wheat = static_cast<Wheat*>(tile.get());
		packet << wheat->owner;
	}
	return packet;
}

sf::Packet & operator>>(sf::Packet & packet, std::shared_ptr<Tile>& tile)
{
	sf::Uint8 type;
	packet >> type;
	if (type == TileType::DIRT) {
		tile = std::make_shared<Dirt>();
	}
	else if (type == TileType::WHEAT) {
		auto wheat = std::make_shared<Wheat>();
		packet >> wheat->owner;
		tile = wheat;
	}
	tile->type = (TileType)type;
	return packet;
}
