#include "cUI.h"
#include "cResources.h"
#include "cMultiplayerPlay.h"

void cUI::Init()
{
	Reg(slRegister::DRAW, 20);
	multiplayer = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerPlay>();
	heading = *slGame::inst.resources->Load<sf::Font>("madness.ttf");
	wealthIcon.setTexture(*slGame::inst.resources->Load<sf::Texture>("icons.png"));
	wealthCount.setFont(heading);
	wealthCount.setCharacterSize(100);
	wealthCount.setScale({ 0.4f, 0.4f });
	wealthIcon.setScale({ 4.f, 4.f });
}

bool cUI::Input(sf::Event * e)
{
	return false;
}

void cUI::Update(float dt)
{
}

void cUI::Draw()
{
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
