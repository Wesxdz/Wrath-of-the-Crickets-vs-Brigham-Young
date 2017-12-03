#pragma once

#include "slGameState.h"

class Setup : public slGameState
{
public:
	Setup();
	~Setup();

	// Inherited via slGameState
	virtual void Init() override;
	virtual void Reset() override;
};

