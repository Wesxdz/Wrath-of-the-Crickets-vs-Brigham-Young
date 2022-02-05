#include "cUI.h"
#include "cResources.h"
#include "cMultiplayerPlay.h"
#include <SFML/Graphics.hpp>
#include "cBoard.h"

void cUI::Init()
{
	Reg(slRegister::DRAW | slRegister::INPUT, 20);
	multiplayer = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
	heading = *slGame::inst.resources->LoadFont("madness.ttf");
	wealthIcon.setTexture(*slGame::inst.resources->LoadTexture("icons.png"));
	roles.setTexture(*slGame::inst.resources->LoadTexture("roles.png"));
	roles.setScale({ 4, 4 });
	selectedRole.setTexture(*slGame::inst.resources->LoadTexture("selected_role.png"));
	selectedRole.setScale({ 4, 4 });
	wealthCount.setFont(heading);
	wealthCount.setCharacterSize(100);
	wealthCount.setScale({ 0.4f, 0.4f });
	wealthIcon.setScale({ 4.f, 4.f });
}

bool cUI::Input(sf::Event * e)
{
	auto board = slGame::inst.currentState->entities["scene"]->GetComponent<cBoard>();
	if (e->type == sf::Event::MouseButtonPressed) {
		if (e->mouseButton.x > (224 * 4)) {
			board->sounds["click"].play();
			if (e->mouseButton.y > 128 * 4) {
				if (e->mouseButton.x > 272 * 4) {
					multiplayer->GetSelf()->role = PlayerRole::SCULPTOR;
				}
				else {
					multiplayer->GetSelf()->role = PlayerRole::BIRDWATCHER;
				}
			}
			else {
				if (e->mouseButton.x > 272 * 4) {
					multiplayer->GetSelf()->role = PlayerRole::ARSONIST;
				}
				else {
					multiplayer->GetSelf()->role = PlayerRole::FARMER;
				}
			}
		}
	}
	else if (e->type == sf::Event::KeyPressed) {
		if (e->key.code == sf::Keyboard::W) {
			if (multiplayer->GetSelf()->role == PlayerRole::BIRDWATCHER) {
				multiplayer->GetSelf()->role = PlayerRole::FARMER;
				board->sounds["click"].play();
			}
			else if (multiplayer->GetSelf()->role == PlayerRole::SCULPTOR) {
				multiplayer->GetSelf()->role = PlayerRole::ARSONIST;
				board->sounds["click"].play();
			}
		}
		else if (e->key.code == sf::Keyboard::A) {
			if (multiplayer->GetSelf()->role == PlayerRole::ARSONIST) {
				multiplayer->GetSelf()->role = PlayerRole::FARMER;
				board->sounds["click"].play();
			}
			else if (multiplayer->GetSelf()->role == PlayerRole::SCULPTOR) {
				multiplayer->GetSelf()->role = PlayerRole::BIRDWATCHER;
				board->sounds["click"].play();
			}
		}
		else if (e->key.code == sf::Keyboard::S) {
			if (multiplayer->GetSelf()->role == PlayerRole::FARMER) {
				multiplayer->GetSelf()->role = PlayerRole::BIRDWATCHER;
				board->sounds["click"].play();
			}
			else if (multiplayer->GetSelf()->role == PlayerRole::ARSONIST) {
				multiplayer->GetSelf()->role = PlayerRole::SCULPTOR;
				board->sounds["click"].play();
			}
		}
		else if (e->key.code == sf::Keyboard::D) {
			if (multiplayer->GetSelf()->role == PlayerRole::FARMER) {
				multiplayer->GetSelf()->role = PlayerRole::ARSONIST;
				board->sounds["click"].play();
			}
			else if (multiplayer->GetSelf()->role == PlayerRole::BIRDWATCHER) {
				multiplayer->GetSelf()->role = PlayerRole::SCULPTOR;
				board->sounds["click"].play();
			}
		}
	}
	return false;
}

void cUI::Update(float dt)
{
}

void cUI::Draw()
{

	for (int i = 0; i < 4; i++) {
		roles.setTextureRect({ 0, i * 16, 32, 16 });
		roles.setPosition((232 + (i % 2) * 48)* 4, (104 + i/2 * 32) * 4);
		slGame::inst.window->draw(roles);
	}


	PlayerRole role = PlayerRole::FARMER;
	if (multiplayer->GetSelf()) {
		role = multiplayer->GetSelf()->role;
	}
	selectedRole.setPosition((224 + (role % 2) * 48) * 4, (96 + role / 2 * 32) * 4);
	slGame::inst.window->draw(selectedRole);

	wealthCount.setPosition(selectedRole.getPosition());
	wealthCount.move(16, 8);
	auto board = slGame::inst.currentState->entities["scene"]->GetComponent<cBoard>();
	int actionCost = 0;
	switch (role) {
	case PlayerRole::FARMER:
		actionCost = board->plantWheatCost;
		break;
	case PlayerRole::ARSONIST:
		actionCost = board->startFireCost;
		break;
	case PlayerRole::BIRDWATCHER:
		actionCost = board->seeBirdCost;
		break;
	case PlayerRole::SCULPTOR:
		actionCost = board->statueCost;
		break;
	}
	wealthCount.setString("x" + std::to_string(actionCost));
	slGame::inst.window->draw(wealthIcon);
	wealthCount.setFillColor(sf::Color::Black);
	wealthCount.move({ 2, 3 });
	slGame::inst.window->draw(wealthCount);
	wealthCount.move({ -2, -3 });
	wealthCount.setFillColor(sf::Color::White);
	slGame::inst.window->draw(wealthCount);



	for (int i = 0; i < multiplayer->players.size(); i++) {
		wealthCount.setPosition({ 932.f, 32.f + 64 * i });
		wealthIcon.setPosition({ 880.f, 16.f + 64 * i});
		wealthCount.setString("x" + std::to_string(multiplayer->players[i].wealth));
		slGame::inst.window->draw(wealthIcon);
		wealthCount.setFillColor(sf::Color::Black);
		wealthCount.move({ 2, 3 });
		slGame::inst.window->draw(wealthCount);
		wealthCount.move({ -2, -3 });
		wealthCount.setFillColor(sf::Color::White);
		slGame::inst.window->draw(wealthCount);

		wealthCount.move({ 32, -32 });
		switch (multiplayer->players[i].id) {
		case 0:
			wealthCount.setFillColor(sf::Color(244, 108, 108));
			break;
		case 1:
			wealthCount.setFillColor(sf::Color(0, 218, 107));
			break;
		case 2:
			wealthCount.setFillColor(sf::Color(204, 77, 255));
			break;
		case 3:
			wealthCount.setFillColor(sf::Color(27, 157, 227));
			break;
		}
		wealthCount.setString(multiplayer->players[i].name);
		slGame::inst.window->draw(wealthCount);
	}
}
