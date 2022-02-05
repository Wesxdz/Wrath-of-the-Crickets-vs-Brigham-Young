#include "slGameState.h"

#include <iostream>

const char slRegister::INPUT =	0b0001;
const char slRegister::UPDATE =	0b0010;
const char slRegister::DRAW =	0b0100;

slGameState::~slGameState()
{
	for (auto entity : entities) {
		delete entity.second;
	}
}

void Add(std::map<int, std::vector<slComponent*>>* registry, slComponent* component, int priority) {
	if (registry->count(priority)) {
		(*registry)[priority].push_back(component);
	}
	else {
		std::vector<slComponent*> reg;
		reg.push_back(component);
		(*registry)[priority] = reg;
	}
}

void slGameState::Register(slComponent* entity, int priority, char functions)
{
	if (functions & slRegister::INPUT) {
		Add(&inputRegistry, entity, priority);
	}
	if (functions & slRegister::UPDATE) {
		Add(&updateRegistry, entity, priority);
	}
	if (functions & slRegister::DRAW) {
		Add(&drawRegistry, entity, priority);
	}
}
