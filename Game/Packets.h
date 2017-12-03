#pragma once

#include <SFML/Network.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <string>
struct Tile;

namespace pk
{

	enum Type {
		JOIN_GAME, PLAYER_JOIN, PLAYER_LEAVE, GAME_START, PLAYER_WEALTH_CHANGE, TILE_CHANGE
	};

	// ClientSession to HostSession
	struct JoinGame {
		std::string name;
		friend sf::Packet& operator<<(sf::Packet& pk, JoinGame& joinGame);
		friend sf::Packet& operator >>(sf::Packet& pk, JoinGame& joinGame);
	};

	// HostSession to ClientSession
	struct PlayerJoin {
		sf::Uint8 id;
		std::string name;
		friend sf::Packet& operator<<(sf::Packet& pk, PlayerJoin& playerJoin);
		friend sf::Packet& operator >>(sf::Packet& pk, PlayerJoin& playerJoin);
	};

	// Both
	struct PlayerLeave {
		sf::Uint8 id;
		std::string name;
		friend sf::Packet& operator<<(sf::Packet& packet, PlayerLeave& playerLeave);
		friend sf::Packet& operator >>(sf::Packet& packet, PlayerLeave& playerLeave);
	};

	struct GameStart {
		friend sf::Packet& operator<<(sf::Packet& packet, GameStart& playerLeave);
	};

	struct PlayerWealthChange {
		sf::Uint8 id;
		int wealth;
		friend sf::Packet& operator<<(sf::Packet& packet, PlayerWealthChange& playerWealthChange);
		friend sf::Packet& operator >>(sf::Packet& packet, PlayerWealthChange& playerWealthChange);
	};

	struct TileChange {
		sf::Vector2i index;
		std::shared_ptr<Tile> tile;
		friend sf::Packet& operator<<(sf::Packet& packet, TileChange& tileChange);
		friend sf::Packet& operator >>(sf::Packet& packet, TileChange& tileChange);
	};

	// TODO: Entity create, move, destroy

}

