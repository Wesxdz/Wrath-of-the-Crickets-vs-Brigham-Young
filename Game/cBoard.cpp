#include "cBoard.h"
#include "cResources.h"
#include <time.h>
#include <stdlib.h>
#include "Packets.h"
#include "cMultiplayerPlay.h"
#include "Tiles.h"
#include "cEnemySpawner.h"

void cBoard::Init()
{
	sounds["plant"].setBuffer(*slGame::inst.resources->Load<sf::SoundBuffer>("plant.ogg"));
	sounds["harvest"].setBuffer(*slGame::inst.resources->Load<sf::SoundBuffer>("harvest.ogg"));
	srand(time(NULL));
	Reg(slRegister::DRAW | slRegister::UPDATE | slRegister::INPUT);
	background.setTexture(*slGame::inst.resources->Load<sf::Texture>("background.png"));
	tilesSpritesheet.setTexture(*slGame::inst.resources->Load<sf::Texture>("tiles.png"));
	background.setScale({ 4, 4 });
	tilesSpritesheet.setScale({ 4, 4 });
	// TODO: Seed packet
	for (int row = 0; row < tiles.size(); row++) {
		for (int col = 0; col < tiles[row].size(); col++) {
			int foo = rand() % 30;
			if (foo < 2) {
				auto rock = std::make_shared<Rock>();
				rock->variation = foo;
				tiles[row][col] = rock;
			}
			else if (foo < 14) {
				auto grass = std::make_shared<Grass>();
				grass->variation = foo % 2;
				tiles[row][col] = grass;
			}
			else {
				tiles[row][col] = std::make_shared<Dirt>();
			}
		}
	}
}

bool cBoard::Input(sf::Event * e)
{
	if (e->type == sf::Event::MouseButtonPressed) {
		if (e->mouseButton.x < 224 * 4) {
			auto multi = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
			sf::Vector2i index = { e->mouseButton.x / 64, e->mouseButton.y / 64 };
			if (multi->GetSelf()->role == PlayerRole::FARMER) {
				std::shared_ptr<Tile> replace = tiles[index.y][index.x]->OnClick();
				if (replace) {
					tiles[index.y][index.x].reset();
					tiles[index.y][index.x] = replace;
					pk::TileChange info{ {index.x, index.y}, replace };
					sf::Packet packet;
					packet << info;
					multi->client->SendToHost(packet);
				}
			}
			else if (multi->GetSelf()->role == PlayerRole::BIRDWATCHER) {
				auto seagull = std::make_shared<Seagull>();
				seagull->index = { index.x, 10 };
				pk::EntityChange create{ pk::EntityChangeType::CREATE, seagull };
				sf::Packet packet;
				packet << create;
				multi->client->SendToHost(packet);
			}
		}
	}
	return false;
}

void cBoard::Update(float dt)
{
	for (int row = 0; row < tiles.size(); row++) {
		for (int col = 0; col < tiles[row].size(); col++) {
			tiles[row][col]->Update(dt);
		}
	}
	// Only the host should update Entities
	auto multi = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
	if (multi->host) {
		for (auto entity : entities) {
			entity->Update(dt);
		}
	}
}

void cBoard::Draw()
{
	slGame::inst.window->draw(background);
	for (int row = 0; row < tiles.size(); row++) {
		for (int col = 0; col < tiles[row].size(); col++) {
			if (tiles[row][col]->type == TileType::DIRT) continue;
			tilesSpritesheet.setPosition(col * 64.f, row * 64.f);
			tiles[row][col]->Draw(tilesSpritesheet);
		}
	}
	for (auto entity : entities) {
		if (entity->type == EntityType::CRICKET) {
			entity->Draw();
		}
	}
	for (auto entity : entities) {
		if (entity->type == EntityType::FIRE) {
			entity->Draw();
		}
	}
	for (auto entity : entities) {
		if (entity->type == EntityType::SEAGULL) {
			entity->Draw();
		}
	}
}
