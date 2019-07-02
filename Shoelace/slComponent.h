#pragma once

#include "slGame.h"
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <iostream>

class slEntity;

class slComponent
{
public:
	virtual ~slComponent();
	// Called when this component is added to an entity
	virtual void Init() = 0;
	// Called on all entity components after slGameState is initialized
	virtual void Start();
	virtual bool Input(sf::Event* e) = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;

	template <class T>
	T* GetSiblingComponent()
	{
		return owner->GetComponent<T>();
	}
public:
	// Could be nullptr if not attached to a specific Entity
	slEntity* owner{ nullptr };

protected:
	void Reg(char functions, int priority = 0);
	void Show(sf::Drawable* draw);

};

