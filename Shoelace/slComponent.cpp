#include "slComponent.h"


slComponent::~slComponent()
{
}

void slComponent::Start()
{
}

void slComponent::Reg(char functions, int priority)
{
	slGame::inst.currentState->Register(this, priority, functions);
}

void slComponent::Show(sf::Drawable* draw)
{
	slGame::inst.window->draw(*draw);
}
