#pragma once

#include <raylib.h>
#include "Defines.h"
#include "Timer.h"

struct Ball {
public:
	Vector2 position = { 0,0 };
	Vector2 speed = { 0, 0 };

	Timer   nextEco;
	Vector2 ecos[BallEcosCount];
public:
	void Reset();
	void Eco();
	void Move();
};
