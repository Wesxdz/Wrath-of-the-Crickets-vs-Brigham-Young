#include "cWorld.h"

cWorld* cWorld::inst;

const int cWorld::PIXELS_PER_METER;
const float cWorld::METERS_PER_PIXEL = 1 / PIXELS_PER_METER;

cWorld::cWorld() :
	world{ b2Vec2(0, 0) },
	enableDebugDraw{ false },
	debug{ slGame::inst.window },
	timeStep{ 1/120.0f },
	velocityIterations{ 6 },
	positionIterations{ 2 }
{
	world.SetDebugDraw(&debug);
}

void cWorld::Init()
{
	Reg(slRegister::DRAW | slRegister::INPUT, 10);
	Reg(slRegister::UPDATE, -10);
	inst = this;
	debug.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_pairBit);
}

bool cWorld::Input(sf::Event* e)
{
	if (e->type == sf::Event::KeyPressed) {
		if (e->key.code == sf::Keyboard::Tab) {
			enableDebugDraw = !enableDebugDraw;
		}
	}
	return false;
}

void cWorld::Update(float dt)
{
	time += dt;
	while (time >= timeStep) {
		world.Step(timeStep, velocityIterations, positionIterations);
		time -= timeStep;
	}
}

void cWorld::Draw()
{
	if (enableDebugDraw) {
		world.DrawDebugData();
	}
}

sf::Vector2f cWorld::ToPixels(b2Vec2 meters)
{
	return sf::Vector2f(ToPixels(meters.x), ToPixels(meters.y));
}
