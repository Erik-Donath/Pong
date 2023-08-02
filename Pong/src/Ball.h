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
	void Reset() { // Could be in a .cpp file? But since it is only used in Main.cpp the compiler wont throw an error.
		position = { (float)HWidth, (float)HHeight };

		// Random angle that is not in range 355..5, 85..95, 175..185, 265..275
		int angle; // TODO: Ajust angles so that the ball does not bounc to much on top and bottom!
		do {
			angle = GetRandomValue(0, 3600);
		} while (
			(angle > 3550 || angle < 50)   ||
			(angle > 850  && angle < 950)  ||
			(angle > 1750 && angle < 1850) ||
			(angle > 2650 && angle < 2750)
		);

		float angleRad = (angle / 10.0f) * (PI / 180.0f); // Convert deg to rad
		speed.x = cos(angleRad) * 300.0f;
		speed.y = sin(angleRad) * 300.0f;

		for (unsigned int i = 0; i < BallEcosCount; i++)
			ecos[i] = { -1.0f, -1.0f };
		nextEco.Set(GameTimeoutDelay);
	}
	void Eco() {
		if (!nextEco.Check()) {
			for (unsigned int i = BallEcosCount - 1; i > 0; i--)
				ecos[i] = ecos[i - 1];
			ecos[0] = position;
			nextEco.Set(0.02);
		}
	}
	inline void Move() {
		position.x += speed.x * GetFrameTime();
		position.y += speed.y * GetFrameTime();

		if (position.y < 0)
			speed.y = fabs(speed.y);
		if (position.y > Height)
			speed.y = -fabs(speed.y);
	}
};
