#include "cMultiplayerPlay.h"
#include "cBoard.h"

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
				sf::Packet send;
				send << info;
				Broadcast(send);
			}
		}
	}
	if (client) {
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
				auto board = slGame::inst.currentState->entities["scene"]->GetComponent<cBoard>();
				board->tiles[info.index.y][info.index.x] = info.tile;
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
