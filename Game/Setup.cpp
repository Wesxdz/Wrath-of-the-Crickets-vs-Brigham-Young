#include "Setup.h"
#include "cGuiTool.h"
#include "cMultiOptions.h"
#include "cSceneControls.h"
#include "cMultiplayerSetup.h"
#include "DiscordManager.h"

Setup::Setup()
{
}


Setup::~Setup()
{
}

void Setup::Init()
{
	slGame::inst.background = sf::Color(74, 49, 81);

	auto scene = new slEntity();
	scene->AddComponent(new cSceneControls);
	entities["scene"] = scene;

	auto multi = new slEntity();
	multi->AddComponent(new cMultiplayerSetup);
	entities["multi"] = multi;

	auto discord = new slEntity();
	discord->AddComponent(new DiscordManager);
	entities["discord"] = discord;

	slGame::inst.window->resetGLStates();
	auto gui = new slEntity();
	gui->AddComponent(new cGuiTool);
	gui->AddComponent(new cMultiOptions);
	entities["gui"] = gui;

}

void Setup::Reset()
{
}
