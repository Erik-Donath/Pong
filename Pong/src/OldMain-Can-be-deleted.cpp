/*
#include <stdio.h>

#include "raylib.h"
#include "raymath.h"
int main2();

#define Width  GetScreenWidth()
#define Height GetScreenHeight()
#define SpeedUp 1.025f
#define TimeoutDelay 2.0
#define Ecos 15

// Game States
bool pause;
double timeout;
float rpY, lpY;
Color color;
Vector2 ballPosition;
Vector2 ballSpeed;
Vector2 ballEco[Ecos];

enum Winner : unsigned char {
	None = 0, Left = 1, Right = 2
};
Winner win; // False: Left, True: Right

float transformX(float x) { return x + Width  / 2.0f;}
float transformY(float y) { return y + Height / 2.0f; }
inline bool IsInTimeout() { return timeout >= GetTime(); }

inline Color GetNormalColor(int a = 255) {
	Color ret = color;
	ret.a = a;
	return ret;
}
inline Color GetDarkerColor(int a = 255) {
	Color ret = color;
	ret.r /= 2; // Darker color is half of the global color
	ret.g /= 2;
	ret.b /= 2;
	ret.a = a;
	return ret;
}

void reset() {
	ballPosition.x = 0.0f;
	ballPosition.y = 0.0f;

	int angle;
	do {
		angle = GetRandomValue(0, 3600);
		#define Range 80
	} while (angle > 3600-Range || (angle > 900-Range && angle < 900+Range) || (angle > 1800-Range && angle < 1800+Range) || (angle > 2700-Range && angle < 2700+Range) || angle < 0+Range);
	float radi = angle / 10.0f * (PI / 180.0f);
	ballSpeed.x = cos(angle) * 300.0f;
	ballSpeed.y = sin(angle) * 300.0f;

	for (unsigned int i = 0; i < Ecos; i++) {
		ballEco[i] = { 0.0f, 0.0f };
	}

	rpY = 0.0f;
	lpY = 0.0f;

	switch (GetRandomValue(0, 30) % 4) {
	case 0: color = BLUE;
			break;
	case 1: color = RED;
			break;
	case 2: color = YELLOW;
			break;
	case 3: color = GREEN;
			break;
	default: color = RAYWHITE;
			break;
	}
	timeout = GetTime() + TimeoutDelay;
	pause = false;
}
void update() {
	for (unsigned int i = Ecos - 1; i > 0; i--) {
		ballEco[i] = ballEco[i - 1];
	}
	ballEco[0].x = ballPosition.x;
	ballEco[0].y = ballPosition.y;

	ballPosition.x += ballSpeed.x * GetFrameTime();
	ballPosition.y += ballSpeed.y * GetFrameTime();
	if (ballPosition.y >  Height / 2.0f) ballSpeed.y = -fabs(ballSpeed.y);
	if (ballPosition.y < -Height / 2.0f) ballSpeed.y =  fabs(ballSpeed.y);

	if (ballPosition.x > Width / 2.0f) {
		win = Winner::Left;
		reset();
	}
	if (ballPosition.x < -Width / 2.0f) {
		win = Winner::Right;
		reset();
	}

	if (IsKeyDown(KEY_W) && lpY > -Height / 2.0f + 51) { lpY -= 450.0f * GetFrameTime(); }
	if (IsKeyDown(KEY_S) && lpY <  Height / 2.0f - 51) { lpY += 450.0f * GetFrameTime(); }
	if (IsKeyDown(KEY_UP)   && rpY > -Height / 2.0f + 51) { rpY -= 450.0f * GetFrameTime(); }
	if (IsKeyDown(KEY_DOWN) && rpY <  Height / 2.0f - 51) { rpY += 450.0f * GetFrameTime(); }

	if (CheckCollisionCircleRec(ballPosition, 5, Rectangle{ 385 - 5, rpY - 50, 10, 100 })) {
		ballSpeed.x = -fabs(ballSpeed.x * SpeedUp);
		ballSpeed.y *= SpeedUp;
	}
	if (CheckCollisionCircleRec(ballPosition, 5, Rectangle{ -385 - 5, lpY - 50, 10, 100 })) {
		ballSpeed.x = fabs(ballSpeed.x * SpeedUp);
		ballSpeed.y *= SpeedUp;
	}
}

int main() {
	return main2();
	InitWindow(800, 600, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	reset();
	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_SPACE)) pause = !pause;
		if (IsKeyPressed(KEY_R)) {
			win = Winner::None;
			reset();
		}
		if (!IsInTimeout() && !pause) update();

		// Drawing
		BeginDrawing();
		ClearBackground({45, 45, 45, 255});

		if (IsInTimeout() && !pause) {
			double animation = (timeout - GetTime()) / TimeoutDelay;
			if (win == Winner::Left) {
				DrawRectangle(0, 0, Width / 2, Height, GetNormalColor(animation * 60));
				DrawRectangle(Width / 2, 0, Width, Height, GetDarkerColor(animation * 20));
				DrawText("Left Wins!", transformX(-50), 15, 25, GetNormalColor(animation * 255));
			}
			if (win == Winner::Right) {
				DrawRectangle(Width / 2, 0, Width, Height, GetDarkerColor(animation * 60));
				DrawRectangle(0, 0, Width / 2, Height, GetNormalColor(animation * 20));
				DrawText("Right Wins!", transformX(-55), 15, 25, GetNormalColor(animation * 255));
			}

			DrawCircle(transformX(0), transformY(0), animation * 70.0, GetNormalColor(35));
			DrawText("Ready?", transformX(-35), transformY(-10), 20, color);
		}
		if(!IsInTimeout()) {
			float change = 255.0f / (Ecos + 1.0f);

			//for (unsigned int i = 0; i < Ecos; i++) {
			for (unsigned int i = Ecos - 1; i > 0; i--) {
				DrawCircle(transformX(ballEco[i].x), transformY(ballEco[i].y), 4.0f, GetNormalColor(change * (Ecos - i + 1)));
			}

			DrawCircle(transformX(ballPosition.x), transformY(ballPosition.y), 5, color);
		}

		Color darker = GetDarkerColor();
		DrawRectangle(transformX(385 - 5), transformY(rpY - 50), 10, 100, darker);
		DrawRectangle(transformX(-385 - 5), transformY(lpY - 50), 10, 100, darker);

		if (pause) {
			DrawRectangle(0, 0, Width, Height, { 20, 20, 20, 192 });
			DrawText("- Pause -", Width / 2.0f - 45, Height / 2.0f - 10, 20, color);
		}
		DrawFPS(0, 0);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
*/