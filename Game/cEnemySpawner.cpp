#include "cEnemySpawner.h"

#include "Entities.h"
#include "cBoard.h"
#include "cMultiplayerPlay.h"
#include "Packets.h"

void cEnemySpawner::Init()
{
	if (GetSiblingComponent<cMultiplayerPlay>()->host) {
		Reg(slRegister::UPDATE);
		difficulty = 30;
		board = slGame::inst.currentState->entities["scene"]->GetComponent<cBoard>();
		for (int row = 0; row < board->tiles.size(); row++) {
			for (int col = 0; col < board->tiles[row].size(); col++) {
				auto tile = board->tiles[row][col];
				if (tile->type != TileType::ROCK && 
					(row == 0 || col == 0 || col == board->tiles[0].size() - 1|| row == board->tiles.size() - 1)) {
					possibleSpawns.push_back({ col, row });
				}
			}
		}
	}
}

bool cEnemySpawner::Input(sf::Event * e)
{
	return false;
}

void cEnemySpawner::Update(float dt)
{
	if (enabled) {
		for (int row = 0; row < board->tiles.size(); row++) {
			for (int col = 0; col < board->tiles[row].size(); col++) {
				std::shared_ptr<Tile> tile = board->tiles[row][col];
				if (tile->type == TileType::WHEAT) { // More wheat implies we should spawn more crickets
					points += dt;
				}
			}
		}
		while (points >= difficulty) {
			points -= difficulty;
			Spawn(std::make_shared<Cricket>());
		}
	}
}

void cEnemySpawner::Draw()
{
}

void cEnemySpawner::Spawn(std::shared_ptr<Entity> entity)
{
	entity->index = possibleSpawns[rand() % possibleSpawns.size()];
	auto multiplayer = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
	entity->handle = multiplayer->NextHandle();
	pk::EntityChange change{ pk::EntityChangeType::CREATE, entity };
	sf::Packet send;
	send << change;
	multiplayer->Broadcast(send);
}
