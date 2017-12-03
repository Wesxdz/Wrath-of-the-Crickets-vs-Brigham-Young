#include "Packets.h"
#include "Tiles.h"
#include "Entities.h"

sf::Packet & pk::operator<<(sf::Packet & pk, JoinGame & joinGame)
{
	// Pack in a sf::Uint8 to determine type when received
	return pk << sf::Uint8(0) << joinGame.name;
}

sf::Packet & pk::operator>>(sf::Packet & pk, JoinGame & joinGame)
{
	return pk >> joinGame.name;
}

sf::Packet & pk::operator<<(sf::Packet & pk, PlayerJoin & playerJoin)
{
	return pk << sf::Uint8(1) << playerJoin.id << playerJoin.name;
}

sf::Packet & pk::operator>>(sf::Packet & pk, PlayerJoin & playerJoin)
{
	return pk >> playerJoin.id >> playerJoin.name;
}

sf::Packet & pk::operator<<(sf::Packet & pk, EntityChange& entityChange)
{
	return pk << sf::Uint8(6) << sf::Uint8(entityChange.changeType) << entityChange.entity;
}

sf::Packet & pk::operator>>(sf::Packet & pk, EntityChange& entityChange)
{
	return pk >> entityChange.changeType >> entityChange.entity;
}

sf::Packet & pk::operator<<(sf::Packet & packet, PlayerLeave & playerLeave)
{
	return packet << sf::Uint8(2) << playerLeave.id << playerLeave.name;
}

sf::Packet & pk::operator>>(sf::Packet & packet, PlayerLeave & playerLeave)
{
	return packet >> playerLeave.id >> playerLeave.name;
}

sf::Packet & pk::operator<<(sf::Packet & packet, GameStart & playerLeave)
{
	return packet << sf::Uint8(3);
}

sf::Packet & pk::operator<<(sf::Packet & packet, PlayerWealthChange & playerWealthChange)
{
	return packet << sf::Uint8(4) << playerWealthChange.id << playerWealthChange.wealth;
}

sf::Packet & pk::operator>>(sf::Packet & packet, PlayerWealthChange & playerWealthChange)
{
	return packet >> playerWealthChange.id >> playerWealthChange.wealth;
}

sf::Packet & pk::operator<<(sf::Packet & packet, TileChange & tileChange)
{
	return packet << sf::Uint8(5) << tileChange.index.x << tileChange.index.y << tileChange.tile;
}

sf::Packet & pk::operator>>(sf::Packet & packet, TileChange & tileChange)
{
	return packet >> tileChange.index.x >> tileChange.index.y >> tileChange.tile;
}
