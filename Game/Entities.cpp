#include "Entities.h"
#include "cBoard.h"
#include "cResources.h"
#include "Tiles.h"
#include "Packets.h"
#include "cMultiplayerPlay.h"

#include "slGame.h"

Entity::Entity()
{
	handle = 0;
	entities.setTexture(*slGame::inst.resources->Load<sf::Texture>("entities.png"));
	entities.setScale({ 4.f, 4.f });
	board = slGame::inst.currentState->entities["scene"]->GetComponent<cBoard>();
}

void Entity::Update(float dt)
{
	timeToNextTurn -= dt;
	if (timeToNextTurn <= 0) {
		timeToNextTurn = turnSpeed;
		OnTurn();
	}
}

std::vector<TilePlacement> Entity::GetAdjacent()
{
	std::vector<TilePlacement> adjacent;
	if (index.x > 0) {
		adjacent.push_back({ {index.x - 1, index.y }, board->tiles[index.y][index.x - 1] });
	}
	if (index.x < board->tiles[0].size() - 1) {
		adjacent.push_back({ { index.x + 1, index.y }, board->tiles[index.y][index.x + 1] });
	}
	if (index.y < board->tiles.size() - 1) {
		adjacent.push_back({ { index.x, index.y + 1 }, board->tiles[index.y + 1][index.x] });
	}
	if (index.y > 0) {
		adjacent.push_back({ { index.x, index.y - 1 }, board->tiles[index.y - 1][index.x] });
	}
	return adjacent;
}

bool Entity::operator==(const Entity & entity)
{
	return handle == entity.handle;
}

Cricket::Cricket()
{
	type = EntityType::CRICKET;
	entities.setTextureRect({0, 0, 16, 16});
}

void Cricket::Draw()
{
	turnSpeed = 1.f;
	entities.setPosition(index.x * 64.f, index.y * 64.f);
	slGame::inst.window->draw(entities);
}

void Cricket::OnTurn()
{
	auto moveOptions = GetAdjacent();
	moveOptions.erase(std::remove_if(moveOptions.begin(), moveOptions.end(), [&moveOptions](const TilePlacement& tilePlacement) {
		return tilePlacement.tile->type == TileType::ROCK;
	}), moveOptions.end());
	if (moveOptions.size() > 0) {
		int choice = rand() % moveOptions.size();
		sf::Packet packet;
		auto updatedCricket = std::make_shared<Cricket>(*this);
		updatedCricket->index = moveOptions[choice].index;
		pk::EntityChange update{ pk::EntityChangeType::MOVE, updatedCricket };
		packet << update;
		auto multi = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
		multi->Broadcast(packet);
		if (board->tiles[updatedCricket->index.y][updatedCricket->index.x]->type == TileType::WHEAT | TileType::GRASS) {
			sf::Packet packet;
			pk::TileChange tileChange{ updatedCricket->index, std::make_shared<Dirt>() };
			packet << tileChange;
			multi->Broadcast(packet);
		}
	}
}

Seagull::Seagull()
{
	type = EntityType::SEAGULL;
	turnSpeed = 0.2f;
	timeToNextTurn = 0.0f;
}

void Seagull::Draw()
{
	entities.setTextureRect({ 16, 0, 32, 16 });
	entities.setPosition((index.x - 0.5f) * 64.f, index.y * 64.f);
	slGame::inst.window->draw(entities);
}

void Seagull::OnTurn()
{
	auto multi = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
	sf::Packet packet;
	if (index.y == 0) {
		pk::EntityChange change{ pk::EntityChangeType::DESTROY, std::make_shared<Seagull>(*this) };
		packet << change;
		multi->Broadcast(packet);
	}
	else {
		index.y--;
		pk::EntityChange change{pk::EntityChangeType::MOVE, std::make_shared<Seagull>(*this)};
		packet << change;
		for (auto entity : board->entities) {
			if (entity->type == EntityType::CRICKET) {
				if (entity->index == index) {
					pk::EntityChange eat{ pk::EntityChangeType::DESTROY, entity };
					packet << eat;
				}
			}
		}
		multi->Broadcast(packet);
	}
}

Fire::Fire()
{
	type = EntityType::FIRE;
	entities.setTextureRect({ 48, 0, 16, 16 });
	timeToNextTurn = 0.5f;
	turnSpeed = 1.f;
}

void Fire::Draw()
{
	entities.setPosition(index.x * 64.f, index.y * 64.f);
	slGame::inst.window->draw(entities);
}

void Fire::OnTurn()
{
	auto multi = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
	auto nearby = GetAdjacent();
	sf::Packet packet;
	auto burtTile = board->tiles[index.y][index.x];
	if (burtTile->type == TileType::GRASS) {
		pk::TileChange remains{ index, std::make_shared<Dirt>() };
		packet << remains;
	}
	else if (burtTile->type == TileType::WHEAT) {
		if (static_cast<Wheat*>(burtTile.get())->growthStage != WheatGrowth::PLANT) {
			pk::TileChange remains{ index, std::make_shared<CharredWheat>() };
			packet << remains;
		}
	}
	pk::EntityChange burnout{ pk::EntityChangeType::DESTROY, std::make_shared<Fire>(*this) };
	packet << burnout;
	for (auto entity : board->entities) {
		if (entity->type == EntityType::CRICKET && index == entity->index) {
			pk::EntityChange kill{ pk::EntityChangeType::DESTROY, entity };
			packet << kill;
		}
	}
	for (auto tilePlacement : nearby) {
		if (tilePlacement.tile->type == TileType::GRASS || 
			tilePlacement.tile->type == TileType::WHEAT && static_cast<Wheat*>(tilePlacement.tile.get())->growthStage != WheatGrowth::PLANT) {
			auto fire = std::make_shared<Fire>();
			fire->index = tilePlacement.index;
			pk::EntityChange spread{ pk::EntityChangeType::CREATE, fire };
			packet << spread;
		}
	}
	multi->Broadcast(packet);
}

sf::Packet& operator<<(sf::Packet& pk, std::shared_ptr<Entity>& entity) {
	return pk << sf::Uint8(entity->type) << entity->handle << entity->index.x << entity->index.y;
}

sf::Packet& operator >>(sf::Packet& pk, std::shared_ptr<Entity>& entity) {
	sf::Uint8 type;
	pk >> type;
	if (type == EntityType::CRICKET) {
		entity = std::make_shared<Cricket>();
	}
	else if (type == EntityType::SEAGULL) {
		entity = std::make_shared<Seagull>();
	}
	else if (type == EntityType::FIRE) {
		entity = std::make_shared<Fire>();
	}
	entity->type = (EntityType)type;
	pk >> entity->handle >> entity->index.x >> entity->index.y;
	return pk;
}

