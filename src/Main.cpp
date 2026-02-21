#include "raylib.h"
#include "time.h"
#include "stdlib.h"
#include "raymath.h"

const int screenWidth = 600;
const int screenHeight = 600;
const Vector2 screenSize = { screenWidth,screenHeight };

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
	BeginDrawing();

	ClearBackground(RED);

	EndDrawing();
}