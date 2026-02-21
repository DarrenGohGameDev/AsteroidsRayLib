#include "raylib.h"
#include "time.h"
#include "stdlib.h"
#include "raymath.h"

#include "Asteroid.h"
#include "AsteroidsManager.h"

const int screenWidth = 600;
const int screenHeight = 600;
const Vector2 screenSize = { screenWidth,screenHeight };

AsteroidsManager asteroidManager;

void UpdateDrawFrame(void);

int main(void)
{
	srand(time(0));
	InitWindow(screenWidth, screenHeight,"Test");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		UpdateDrawFrame();
	}

	CloseWindow();

	return 0;
}

void UpdateDrawFrame(void)
{
	float deltaTime = GetFrameTime();
	BeginDrawing();
	asteroidManager.UpdateAllAsteroids(deltaTime);

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 newDummyVelocity = { 200,0 };
		asteroidManager.SpawnAsteeroid(GetMousePosition(), newDummyVelocity);
	}

	ClearBackground(RED);
	asteroidManager.DrawAllAsteroids();

	EndDrawing();
}