#include "cResources.h"

cResources::cResources() :
	resourcePath{ "../resources" },
	texturesFile{ "images" },
	fontsFile	{ "fonts" },
	soundsFile	{ "sounds" },
	shadersFile { "shaders" }
{
}

cResources::~cResources()
{
}

void cResources::Init()
{
}

bool cResources::Input(sf::Event * e)
{
	return false;
}

void cResources::Update(float dt)
{
}

void cResources::Draw()
{
}
