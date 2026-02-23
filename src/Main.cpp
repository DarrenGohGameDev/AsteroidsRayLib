#include "raylib.h"
#include "time.h"
#include "stdlib.h"
#include "raymath.h"
#include "Asteroid.h"
#include "AsteroidsManager.h"
#include "Player.h"

const int screenWidth = 600;
const int screenHeight = 600;
const Vector2 screenSize = { screenWidth,screenHeight };
const Vector2 screenCenter = { screenWidth / 2,screenHeight / 2 };

AsteroidsManager asteroidManager;

Player player(screenSize,screenCenter);

void UpdateDrawFrame(void);

int main(void)
{
	srand(time(0));
	InitWindow(screenWidth, screenHeight,"Test");
	player.Init();
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
	float currentTime = GetTime();
	BeginDrawing();

	player.PlayrUpdate(deltaTime);

	asteroidManager.UpdateAllAsteroids(deltaTime, currentTime, screenSize,screenCenter);

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		asteroidManager.SpawnAsteeroid(screenSize,screenCenter);
	}

	ClearBackground(RED);
	asteroidManager.DrawAllAsteroids();

	if (asteroidManager.DebugingMode)
	{
		asteroidManager.DrawDebugLine();
	}

	EndDrawing();
}