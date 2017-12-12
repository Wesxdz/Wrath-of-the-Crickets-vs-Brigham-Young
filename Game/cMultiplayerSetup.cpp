#include "cMultiplayerSetup.h"
#include "Packets.h"
#include "ClientSession.h"
#include "cMultiplayerPlay.h"

#include "cMultiOptions.h"

void cMultiplayerSetup::Init()
{
	Reg(slRegister::UPDATE);
}

bool cMultiplayerSetup::Input(sf::Event * e)
{
	return false;
}

void cMultiplayerSetup::Update(float dt)
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
			if (type == pk::JOIN_GAME) {
				if (host->availableIds.size() == 0) return;
				pk::JoinGame join;
				packet >> join;
				for (auto& client : host->clients) {
					sf::Packet previousJoin;
					pk::PlayerJoin previous{ client.id, client.name };
					previousJoin << previous;
					host->socket.send(previousJoin, clientIp, clientPort);
				}
				Client c{ clientIp, clientPort, join.name, host->availableIds.top() };
				host->availableIds.pop();
				host->clients.push_back(c);
				pk::PlayerJoin playerJoined{ c.id, join.name };
				sf::Packet announce;
				announce << playerJoined;
				Broadcast(announce);
			}
			else if (type == pk::PLAYER_LEAVE) {
				pk::PlayerLeave leaveInfo;
				packet >> leaveInfo;
				host->availableIds.push(leaveInfo.id);
				Broadcast(packet);
				host->clients.erase(std::find_if(begin(host->clients), end(host->clients), 
					[&leaveInfo](const Client& x) { return x.id == leaveInfo.id; }
				));
			}
			else if (type == pk::GAME_START) {
				next = new Gameplay;
				auto multiPlay = new cMultiplayerPlay;
				next->multiplayer = multiPlay;
				pk::GameStart info;
				packet >> info;
				sf::Packet p;
				p << info;
				Broadcast(p);
				multiPlay->host = std::move(host);
			}
		}
	}
	if (client) {
		sf::Packet packet;
		sf::IpAddress ipRec = client->hostIP; // lol I have no idea what is happening anymore
		sf::Uint16 portRec = client->hostPort;
		client->socket.receive(packet, ipRec, portRec);
		while (!packet.endOfPacket()) {
			sf::Uint8 type;
			packet >> type;
			std::cout << "Recieved Packet of type " << (pk::Type)type << " from HOST " << client->hostIP << ":" << client->hostPort << "\n";
			if (type == pk::PLAYER_JOIN) {
				pk::PlayerJoin join;
				packet >> join;
				if (client->info.name == join.name) {
					client->info.id = join.id;
				}
				options->StartLobby();
				auto tag = sfg::Label::Create(join.name);
				options->lobbyNames.push_back(tag);
				options->lobbyContent->Pack(tag);
			}
			else if (type == pk::PLAYER_LEAVE) {
				pk::PlayerLeave info;
				packet >> info;
				std::cout << (pk::Type)info.id << " " << info.name << " has left\n";
				if (info.id == sf::Uint8(0)) {
					std::cout << "Because it is the host\n";
				}
				if (info.id == client->info.id) {
					std::cout << "Because it is self";
				}
				if (info.id == sf::Uint8(0) || info.id == client->info.id) {
					options->lobbyContent.reset();
					options->lobbyNames.clear();
					client.reset();
					host.reset();
				}
				else {
					auto toRemove = std::find_if(begin(options->lobbyNames), end(options->lobbyNames), [&info](const std::shared_ptr<sfg::Label>& lbl) {
						return lbl->GetText().toAnsiString() == info.name;
					});
					options->lobbyContent->Remove(*toRemove);
					options->lobbyNames.erase(toRemove);
				}
			}
			else if (type == pk::GAME_START) {
				pk::GameStart startInfo;
				packet >> startInfo;
				srand(startInfo.seed);
				pk::PlayerJoin info{ client->info.id, client->info.name };
				sf::Packet send;
				send << info;
				client->socket.send(send, client->hostIP, client->hostPort);
				if (!next) {
					next = new Gameplay;
					auto multiPlay = new cMultiplayerPlay;
					next->multiplayer = multiPlay;
				}
				next->multiplayer->client = std::move(client);
				slGame::inst.SetState(next);
			}
		}
	}
}

void cMultiplayerSetup::Draw()
{
}

bool cMultiplayerSetup::HostGame(sf::Uint16 port)
{
	if (host) return false;
	host = std::make_shared<HostSession>();
	if (host->socket.bind(port) != sf::Socket::Status::Done) {
		return false;
	}
	host->socket.setBlocking(false);
	JoinGame("localhost", host->socket.getLocalPort());
	return true;
}

bool cMultiplayerSetup::JoinGame(sf::IpAddress ip, sf::Uint16 port)
{
	client = std::make_shared<ClientSession>();
	client->hostIP = sf::IpAddress(ip);
	client->hostPort = port;
	client->socket.bind(sf::Socket::AnyPort);
	pk::JoinGame join;
	join.name = options->enterUsername->GetText().toAnsiString();
	client->info.name = join.name;
	sf::Packet wealthCount;
	wealthCount << join;
	client->socket.setBlocking(false);
	client->socket.send(wealthCount, client->hostIP, client->hostPort);
	return true;
}

void cMultiplayerSetup::LeaveGame()
{
	sf::Packet myPacket;
	pk::PlayerLeave leaveInfo{ client->info.id, client->info.name };
	myPacket << leaveInfo;
	client->socket.send(myPacket, client->hostIP, client->hostPort);
}

void cMultiplayerSetup::Broadcast(sf::Packet packet)
{
	for (auto& client : host->clients) {
		host->socket.send(packet, client.ip, client.port);
	}
}
