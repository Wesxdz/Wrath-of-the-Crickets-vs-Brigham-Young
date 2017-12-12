#include "cMultiplayerPlay.h"
#include "cBoard.h"
#include "cEnemySpawner.h"

void cMultiplayerPlay::Init()
{
	Reg(slRegister::UPDATE);
}

bool cMultiplayerPlay::Input(sf::Event * e)
{
	return false;
}

void cMultiplayerPlay::Update(float dt)
{
	if (host) {
		sf::Packet packet;
		sf::IpAddress clientIp;
		sf::Uint16 clientPort;
		host->socket.receive(packet, clientIp, clientPort);
		while (!packet.endOfPacket()) {
			sf::Uint8 type;
			packet >> type;
			std::cout << "Recieved Packet of type " << (pk::Type)type << " from CLIENT " << clientIp << ":" << clientPort << "\n";
			if (type == pk::PLAYER_JOIN) {
				pk::PlayerJoin info;
				packet >> info;
				sf::Packet send;
				send << info;
				Broadcast(send);
			}
			else if (type == pk::PLAYER_WEALTH_CHANGE) {
				pk::PlayerWealthChange info;
				packet >> info;
				sf::Packet send;
				send << info;
				Broadcast(send);
			}
			else if (type == pk::TILE_CHANGE) {
				pk::TileChange info;
				packet >> info;
				if (info.tile->type == TileType::SCULPTURE) {
					GetSiblingComponent<cEnemySpawner>()->enabled = false;
				}
				sf::Packet send;
				send << info;
				Broadcast(send);
			}
			else if (type == pk::ENTITY_CHANGE) {
				pk::EntityChange info;
				packet >> info;
				if (info.entity->handle == 0) {
					info.entity->handle = NextHandle();
				}
				sf::Packet send;
				send << info;
				Broadcast(send);
			}
		}
	}
	if (client) {
		auto board = slGame::inst.currentState->entities["scene"]->GetComponent<cBoard>();
		sf::Packet packet;
		sf::IpAddress ipRec = client->hostIP;
		sf::Uint16 portRec = client->hostPort;
		client->socket.receive(packet, ipRec, portRec);
		while (!packet.endOfPacket()) {
			sf::Uint8 type;
			packet >> type;
			std::cout << "Recieved Packet of type " << (pk::Type)type << " from HOST " << client->hostIP << ":" << client->hostPort << "\n";
			if (type == pk::PLAYER_JOIN) {
				pk::PlayerJoin info;
				packet >> info;
				players.push_back(Player{ info.id, info.name, 30 });
			}
			else if (type == pk::PLAYER_WEALTH_CHANGE) {
				pk::PlayerWealthChange info;
				packet >> info;
				for (auto& player : players) {
					if (player.id == info.id) {
						player.wealth = info.wealth;
						break;
					}
				}
			}
			else if (type == pk::TILE_CHANGE) {
				pk::TileChange info;
				packet >> info;
				if (info.tile->type == TileType::SCULPTURE) {
					board->sounds["build_statue"].play();
				}
				else if (info.tile->type == TileType::WHEAT) {
					board->sounds["plant"].play();
				}
				board->tiles[info.index.y][info.index.x] = info.tile;
			}
			else if (type == pk::ENTITY_CHANGE) {
				pk::EntityChange info;
				packet >> info;
				auto board = slGame::inst.currentState->entities["scene"]->GetComponent<cBoard>();
				if (info.changeType == pk::EntityChangeType::CREATE) {
					if (info.entity->type == EntityType::CRICKET) {
						board->sounds["cricket_spawn"].play();
					}
					else if (info.entity->type == EntityType::SEAGULL) {
						board->sounds["bird_spawn"].play();
					}
					else if (info.entity->type == EntityType::FIRE) {
						if (board->sounds["fire_sprea"].getStatus() != sf::Sound::Status::Playing) {
							board->sounds["fire_spread"].play();
						}
					}
					std::cout << "Entity Created with Handle " << info.entity->handle << "\n";
					board->entities.push_back(info.entity);
				}
				else if (info.changeType == pk::EntityChangeType::DESTROY) {
					if (info.entity->type == EntityType::CRICKET) {
						board->sounds["cricket_die"].play();
					}
					auto it = std::find_if(board->entities.begin(), board->entities.end(), [&info](const std::shared_ptr<Entity>& entity) {
						return entity->handle == info.entity->handle;
					});
					if (it != board->entities.end()) {
						board->entities.erase(it);
					}
				}
				else if (info.changeType == pk::EntityChangeType::MOVE) {
					for (auto& entity : board->entities) {
						if (entity->handle == info.entity->handle) {
							entity->index = info.entity->index;
						}
					}
				}
			}
		}
	}
}

void cMultiplayerPlay::Draw()
{
}

void cMultiplayerPlay::Broadcast(sf::Packet packet)
{
	for (auto& client : host->clients) {
		host->socket.send(packet, client.ip, client.port);
	}
}

Player* cMultiplayerPlay::GetSelf()
{
	for (int i = 0; i < players.size(); i++) {
		if (client->info.id == players[i].id) {
			return &players[i];
		}
	}
	return nullptr;
}

sf::Uint32 cMultiplayerPlay::NextHandle()
{
	nextHandle++;
	return nextHandle;
}
