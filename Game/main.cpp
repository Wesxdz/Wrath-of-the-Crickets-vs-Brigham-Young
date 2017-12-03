
#include "slGame.h"
#include "Setup.h"
#include "Gameplay.h"

int main(int argc, char** argv)
{
	slGame::Init("Wrath of the Crickets vs Brigham Young", 1280, 640);
	slGame::inst.window->setVerticalSyncEnabled(true);

	slGame::inst.Run(new Setup);
}