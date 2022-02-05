#include "slEntity.h"

#include "slComponent.h"
#include "slGame.h"
#include "slGameState.h"


slEntity::~slEntity()
{
	for (auto component : components) {
		delete component;
	}
}

void slEntity::AddComponent(slComponent* c)
{
	c->owner = this;
	c->Init();
	components.push_back(c);
}
