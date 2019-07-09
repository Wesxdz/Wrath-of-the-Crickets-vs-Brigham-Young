#define _CRT_SECURE_NO_WARNINGS

#include "slGame.h"
#include "Setup.h"
#include "cResources.h"
#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "Path: " << argv[0] << "\n";
	slGame::Init("Wrath of the Crickets vs Brigham Young", 1280, 640);
	auto path = std::string(argv[0]);
	slGame::inst.path = path;
	slGame::inst.resources->resourcePath = path.substr(0, path.length() - 8) + "../resources"; // To work when launched from user's computer
	slGame::inst.window->setVerticalSyncEnabled(true);
	slGame::inst.Run(new Setup);
}