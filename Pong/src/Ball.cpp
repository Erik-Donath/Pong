#include <raylib.h>
#include <raymath.h>
#include "Defines.h"
#include "Timer.h"
#include "Ball.h"

void Ball::Reset() {
	position = { (float)HWidth, (float)HHeight };

	// Random angle that is not in range 355..5, 85..95, 175..185, 265..275
	int angle;
	do {
		angle = GetRandomValue(0, 3600);
	} while (
		(angle > 3550 || angle < 50) ||
		(angle > 850 && angle < 950) ||
		(angle > 1750 && angle < 1850) ||
		(angle > 2650 && angle < 2750)
	);

	float angleRad = (angle / 10.0f) * (PI / 180.0f); // Convert deg to rad
	speed.x = cos(angleRad) * BallStartSpeed;
	speed.y = sin(angleRad) * BallStartSpeed;

	for (unsigned int i = 0; i < BallEcosCount; i++)
		ecos[i] = { -1.0f, -1.0f };
	nextEco.Set(GameTimeoutDelay);
}
void Ball::Eco() {
	if (!nextEco.InTimeout()) {
		for (unsigned int i = BallEcosCount - 1; i > 0; i--)
			ecos[i] = ecos[i - 1];
		ecos[0] = position;
		nextEco.Set(0.02);
	}
}
void Ball::Move() {
	position.x += speed.x * GetFrameTime();
	position.y += speed.y * GetFrameTime();

	//Bounc Top and Bottom
	if (position.y < 0)
		speed.y = fabs(speed.y);
	if (position.y > Height)
		speed.y = -fabs(speed.y);
}
