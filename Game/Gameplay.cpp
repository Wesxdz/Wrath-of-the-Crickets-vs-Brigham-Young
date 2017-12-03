#include "Gameplay.h"

#include "slEntity.h"
#include "cSceneControls.h"
#include "cResources.h"
#include "slComponent.h"
#include "cBoard.h"
#include "cUI.h"
#include "cEnemySpawner.h"

void Gameplay::Init()
{
	auto scene = new slEntity;
	scene->AddComponent(new cSceneControls);
	scene->AddComponent(new cBoard);
	entities["scene"] = scene;

	auto multi = new slEntity;
	if (multiplayer) {
		multi->AddComponent(multiplayer);
	}
	multi->AddComponent(new cEnemySpawner);
	entities["multi"] = multi;

	auto ui = new slEntity;
	ui->AddComponent(new cUI);
	entities["ui"] = ui;
}

void Gameplay::Reset()
{
}
