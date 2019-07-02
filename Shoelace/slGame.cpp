#include "slGame.h"

#include "cResources.h"
#include "slComponent.h"
#include "cWorld.h"

slGame slGame::inst;

void slGame::Init(const char* name, int width, int height)
{
	Init(new sf::RenderWindow{ sf::VideoMode(width, height), name, sf::Style::Close });
}

void slGame::Init(sf::RenderWindow* w)
{
	inst.window = w;
	inst.resources = new cResources;
}

void slGame::Run(slGameState* startState)
{
	currentState = startState;
	currentState->Init();
	for (auto pair : currentState->entities)
	{
		for (slComponent* c : pair.second->components) {
			c->Start();
		}
	}
	RunLoop();
}

void slGame::SetState(slGameState* state)
{
	nextState = state;
	requestStateChange = true;
}

void slGame::Exit()
{
	inst.running = false;
}

slGame::slGame() :
	targetFrameRate{ 60.0f },
	running{ true },
	requestStateChange{ false }
{
}

slGame::~slGame()
{
	delete window;
	delete currentState;
}

void slGame::RunLoop()
{
	while (running)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			for (auto inputPriorityGroup : currentState->inputRegistry) {
				for (slComponent* component : inputPriorityGroup.second) {
					component->Input(&event);
				}
			}
		}
		float dt = clock.restart().asSeconds();
		for (auto updatePriorityGroup : currentState->updateRegistry) {
			for (slComponent* component : updatePriorityGroup.second) {
				component->Update(dt);
			}
		}
		window->clear(background);
		for (auto drawPriorityGroup : currentState->drawRegistry) {
			for (slComponent* component : drawPriorityGroup.second) {
				component->Draw();
			}
		}
		window->display();
		if (requestStateChange) {
			delete currentState;
			currentState = nextState;
			currentState->Init();
			requestStateChange = false;
		}
	}
	window->close();
}
