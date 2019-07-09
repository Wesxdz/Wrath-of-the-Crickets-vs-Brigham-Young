#pragma once

#include "slGameState.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <vector>

class cResources;

class slGame
{

public:
	static slGame inst;

public:
	slGameState* currentState;
	sf::RenderWindow* window;
	sf::Color background;
	sf::Clock clock;
	float targetFrameRate;
	cResources* resources;
	sf::String path;

public:
	static void Init(const char* name, int width, int height);
	static void Init(sf::RenderWindow* w);
	void Run(slGameState* startState);
	void SetState(slGameState* state);
	static void Exit();

private:
	slGameState* nextState;
	bool requestStateChange;
	bool running;

private:
	slGame();
	~slGame();
	void RunLoop();

};

