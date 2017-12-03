#include "cGuiTool.h"

void cGuiTool::Init()
{
	Reg(slRegister::DRAW | slRegister::INPUT | slRegister::UPDATE, 30);
}

bool cGuiTool::Input(sf::Event * e)
{
	desktop.HandleEvent(*e);
	return false;
}

void cGuiTool::Update(float dt)
{
	desktop.Update(dt);
}

void cGuiTool::Draw()
{
	sfgui.Display(*slGame::inst.window);
}
