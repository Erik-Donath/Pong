#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#include "Defines.h"
#include "GameState.h"
#include "Ball.h"

GameState state;
Ball ball;

Rectangle leftPaddel;
Rectangle rightPaddel;

void Reset() {
	state.Reset();
	ball.Reset();

	leftPaddel  = { 5.0f,          HHeight - 50.0f, 10.0f, 100.0f };
	rightPaddel = { Width - 15.0f, HHeight - 50.0f, 10.0f, 100.0f };
	printf("[INFO]: Game reseted!\n");
}
void HandleSpecialInput() {
	if (IsKeyPressed(KEY_SPACE)) state.Pause();
	if (IsKeyPressed(KEY_R)) Reset();
}
void HandleInput() {
	if (IsKeyDown(KEY_W)  && leftPaddel.y  > 0) leftPaddel.y  -= PaddelSpeed * GetFrameTime();
	if (IsKeyDown(KEY_UP) && rightPaddel.y > 0) rightPaddel.y -= PaddelSpeed * GetFrameTime();
	if (IsKeyDown(KEY_S)    && leftPaddel.y  < Height - 100) leftPaddel.y  += 450.0f * GetFrameTime();
	if (IsKeyDown(KEY_DOWN) && rightPaddel.y < Height - 100) rightPaddel.y += 450.0f * GetFrameTime();
}
void UpdateGame() {
	HandleInput();

	ball.Eco();
	ball.Move();

	if (CheckCollisionCircleRec(ball.position, 5, leftPaddel))  ball.speed.x =  fabs(ball.speed.x);
	if (CheckCollisionCircleRec(ball.position, 5, rightPaddel)) ball.speed.x = -fabs(ball.speed.x);
	
	if (ball.position.x < 0) {
		printf("[INFO]: Right won the Game!\n");
		Reset();
		state.winner = Winner::Right;
	}
	if (ball.position.x > Width) {
		printf("[INFO]: Left won the Game!\n");
		Reset();
		state.winner = Winner::Left;
	}
}
void RenderGame() {
	Color darkGlobalColor = state.GetDarkerMainColor();
	DrawRectangleRec(leftPaddel,  darkGlobalColor);
	DrawRectangleRec(rightPaddel, darkGlobalColor);

	if (!state.timeout.InTimeout()) {
		for (unsigned int i = BallEcosCount - 1; i > 0; i--) {
			Vector2 eco = ball.ecos[i];
			float near = 1.0f - (i / (float)BallEcosCount); // How near eco is to ball
			DrawCircle(eco.x, eco.y, 4.5f * near, state.GetMainColor(240 * near));
		}
		DrawCircle(ball.position.x, ball.position.y, 5, state.GetMainColor());
	}
}
void RenderOverlay() {
	if (state.paused) {
		const char* pauseText = "- Pause -"; 
		DrawRectangle(0, 0, Width, Height, { 20, 20, 20, 192 });
		DrawText(pauseText, HWidth - MeasureText(pauseText, 20) / 2, HHeight - 10, 20, state.GetMainColor());
	}
	else if (state.timeout.InTimeout()) {
		const char* timeoutText = "Ready?";
		double animation = state.timeout.InvertedProgress();
		DrawCircle(HWidth, HHeight, animation * 70.0f, state.GetMainColor(animation * 25 + 10));
		DrawText(timeoutText, HWidth - MeasureText(timeoutText, 20) / 2, HHeight - 10, 20, state.GetMainColor(animation * 205 + 50));

		const char* winnerText = nullptr;
		if (state.winner == Winner::Left)  winnerText = "Left Wins!";
		if (state.winner == Winner::Right) winnerText = "Right Wins!";
		DrawText(winnerText, HWidth - MeasureText(winnerText, 30) / 2, 50, 30, state.GetMainColor(animation * 255));
	}
}
void RunGame() {
	InitWindow(800, 600, "Pong!");
	//SetWindowState(FLAG_VSYNC_HINT); // VSYNC
	Reset();

	while (!WindowShouldClose()) {
		HandleSpecialInput();
		if (!state.timeout.InTimeout() && !state.paused) {
			UpdateGame();
		}

		BeginDrawing();
			ClearBackground({ 45, 45, 45, 255 });
			RenderGame();
			RenderOverlay();
			DrawFPS(0, 0);
		EndDrawing();
	}
	CloseWindow();
}
int main() {
	RunGame();
	return 0;
}
