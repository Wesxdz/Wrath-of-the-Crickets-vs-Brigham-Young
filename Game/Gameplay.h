#pragma once

#include "slGameState.h"
#include "cMultiplayerPlay.h"

class Gameplay : public slGameState
{
public:
	// Inherited via slGameState
	virtual void Init() override;
	virtual void Reset() override;
	// Set from Setup GameState
	cMultiplayerPlay* multiplayer = nullptr;
};

