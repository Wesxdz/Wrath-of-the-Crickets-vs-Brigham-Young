#include "cSceneControls.h"

cSceneControls::cSceneControls()
{
}

cSceneControls::~cSceneControls()
{
}

void cSceneControls::Init()
{
	Reg(slRegister::INPUT);
}

bool cSceneControls::Input(sf::Event* e)
{
	if (e->type == sf::Event::Closed) {
		slGame::inst.Exit();
	}
	if (e->type == sf::Event::KeyPressed) {
		if (e->key.code == sf::Keyboard::Escape) {
			slGame::inst.Exit();
		}
		if (e->key.code == sf::Keyboard::R) {
			slGame::inst.currentState->Reset();
		}
	}
	return false;
}

void cSceneControls::Update(float dt)
{
}

void cSceneControls::Draw()
{
}
