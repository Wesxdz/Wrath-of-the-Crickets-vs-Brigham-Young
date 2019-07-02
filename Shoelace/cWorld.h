#pragma once

#include "slComponent.h"

#include "SFMLDebugDraw.h"

class cWorld : public slComponent
{
public:
	static cWorld* inst;

public:
	b2World world;
	float time;
	float timeStep;
	int32 velocityIterations;
	int32 positionIterations;
	bool enableDebugDraw;
	SFMLDebugDraw debug;

	static const int PIXELS_PER_METER = 32;
	static const float METERS_PER_PIXEL;

public:
	cWorld();
	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event* e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;

	static inline float ToPixels(float meters) { return meters * PIXELS_PER_METER; }
	static sf::Vector2f ToPixels(b2Vec2 meters);
	static inline float ToMeters(float pixels) { return pixels * 1/PIXELS_PER_METER; }
	template<class T> static b2Vec2 ToMeters(sf::Vector2<T> pixels);

};

template<class T>
inline b2Vec2 cWorld::ToMeters(sf::Vector2<T> pixels)
{
	return b2Vec2(ToMeters(pixels.x), ToMeters(pixels.y));
}
