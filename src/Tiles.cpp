#include "Tiles.h"
#include "slGame.h"
#include "cResources.h"
#include "cMultiplayerPlay.h"
#include "Packets.h"
#include "cBoard.h"

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
	timeToGrow = 5.0f;
}

void Wheat::Update(float dt)
{
	if (growthStage != WheatGrowth::ROT) {
		timeToGrow -= dt;
		if (timeToGrow <= 0) {
			growthStage = (WheatGrowth)((int)growthStage + 1);
			if (growthStage == WheatGrowth::FULL) {
				timeToGrow = 8.0f;
			}
			else {
				timeToGrow = 3.0f;
			}
		}
	}
}

void Wheat::Draw(sf::Sprite & spritesheet)
{
	spritesheet.setTextureRect(sf::IntRect(growthStage * 16, 0, 16, 16));
	slGame::inst.window->draw(spritesheet);
	if (growthStage != WheatGrowth::ROT) {
		sf::Sprite ownership;
		ownership.setTexture(*slGame::inst.resources->LoadTexture("owner.png"));
		ownership.setPosition(spritesheet.getPosition());
		ownership.setTextureRect({ (int)owner * 16, 0, 16, 16 });
		ownership.setScale({ 4, 4 });
		slGame::inst.window->draw(ownership);
	}
}

std::unique_ptr<Tile> Wheat::OnClick()
{
	auto multi = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
	auto board = slGame::inst.currentState->entities["scene"]->GetComponent<cBoard>();
	auto self = multi->GetSelf();
	if (self->id == owner) {
		switch (growthStage) {
		case WheatGrowth::SAP:
			self->wealth += 2;
			break;
		case WheatGrowth::MID:
			self->wealth += 4;
			break;
		case WheatGrowth::BIG:
			self->wealth += 7;
			break;
		case WheatGrowth::FULL:
			self->wealth += 12;
			break;
		case WheatGrowth::ROT:
			self->wealth += 2;
		}
		sf::Packet packet;
		pk::PlayerWealthChange info{ self->id, self->wealth };
		packet << info;
		multi->client->SendToHost(packet);
		board->sounds["harvest"].play();
	}
	else if (growthStage == WheatGrowth::ROT) {
		self->wealth += 1;
		sf::Packet packet;
		pk::PlayerWealthChange info{ self->id, self->wealth };
		packet << info;
		multi->client->SendToHost(packet);
		board->sounds["harvest"].play();
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

Dirt::Dirt()
{
	type = TileType::DIRT;
}

std::unique_ptr<Tile> Dirt::OnClick()
{
	auto multi = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
	auto self = multi->GetSelf();
	auto board = slGame::inst.currentState->entities["scene"]->GetComponent<cBoard>();
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
	else if (type == TileType::SCULPTURE) {
		tile = std::make_shared<Sculpture>();
	}
	else if (type == TileType::CHARRED_WHEAT) {
		tile = std::make_shared<CharredWheat>();
	}
	else {
		tile = std::make_shared<Tile>();
	}
	tile->type = (TileType)type;
	return packet;
}

Sculpture::Sculpture()
{
	type = TileType::SCULPTURE;
}

void Sculpture::Draw(sf::Sprite & spritesheet)
{
	spritesheet.setTextureRect({ 112, 0, 16, 32 });
	spritesheet.move({ 0, -64 });
	slGame::inst.window->draw(spritesheet);
}

CharredWheat::CharredWheat()
{
	type = TileType::CHARRED_WHEAT;
}

void CharredWheat::Draw(sf::Sprite & spritesheet)
{
	spritesheet.setTextureRect({ 96, 0, 16, 16 });
	slGame::inst.window->draw(spritesheet);
}
