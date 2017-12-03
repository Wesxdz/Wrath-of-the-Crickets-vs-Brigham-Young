#include "Gameplay.h"

#include "slEntity.h"
#include "cSceneControls.h"
#include "cResources.h"
#include "slComponent.h"
#include "cBoard.h"
#include "cUI.h"

void Gameplay::Init()
{
	auto multi = new slEntity;
	if (multiplayer) {
		multi->AddComponent(multiplayer);
	}
	entities["multi"] = multi;

	auto scene = new slEntity;
	scene->AddComponent(new cSceneControls);
	scene->AddComponent(new cBoard);
	entities["scene"] = scene;

	auto ui = new slEntity;
	ui->AddComponent(new cUI);
	entities["ui"] = ui;
}

void Gameplay::Reset()
{
}
