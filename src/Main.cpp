#include "raylib.h"
#include "time.h"
#include "stdlib.h"
#include "raymath.h"
#include "Asteroid.h"
#include "AsteroidsManager.h"
#include "ProjectileManager.h"
#include "ScoreManager.h"
#include "Player.h"

const int screenWidth = 600;
const int screenHeight = 600;
const Vector2 screenSize = { screenWidth,screenHeight };
const Vector2 screenCenter = { screenWidth / 2,screenHeight / 2 };

AsteroidsManager asteroidManager;

ProjectileManager projectileManager;

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
	ScoreManager::Get().DrawScore();
	asteroidManager.UpdateAllAsteroids(deltaTime, currentTime, screenSize,screenCenter);
	projectileManager.UpdateAllProjectile(deltaTime);

	for (int p = 0; p < maxProjectiles; p++)
	{
		if (!projectileManager._projectile[p].GetProjectileStatus())
			continue;

		for (int a = 0; a < maxAsteroids; a++)
		{
			if (!asteroidManager._asteroids[a].GetAsteroidStatus())
				continue;

			if (projectileManager._projectile[p].CheckProjectileAsteroidCollision(
				asteroidManager._asteroids[a]))
			{
				ScoreManager::Get().UpdateScore(1);

				AsteroidSize hitResult = asteroidManager._asteroids[a].AsteroidHit();

				if (hitResult != ASTEROIDS_SMALL)
				{
					switch (hitResult)
					{
					case ASTEROIDS_MEDIUM:

						for (int i = 0; i < 2; i++)
						{
							asteroidManager.SpawnAsteeroid(asteroidManager._asteroids[a].movableStats.position, screenCenter, true, hitResult);
						}

						break;

					case ASTEROIDS_LARGE:

						for (int i = 0; i < 3; i++)
						{
							asteroidManager.SpawnAsteeroid(asteroidManager._asteroids[a].movableStats.position, screenCenter, true, hitResult);
						}

						break;

					default:
						break;
					}
				}
				

				break; // projectile destroyed → stop checking this projectile
			}

			if (player.GetPlayerStatus() && player.CheckProjectileAsteroidCollision(asteroidManager._asteroids[a]))
			{

				break;
			}
		}
	}


	for (int a = 0; a < maxAsteroids; a++)
	{
		if (!asteroidManager._asteroids[a].GetAsteroidStatus())
			continue;

		if (player.GetPlayerStatus() && player.CheckProjectileAsteroidCollision(asteroidManager._asteroids[a]))
		{

			break;
		}
	}


	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && player.CanFire(currentTime))
	{
		projectileManager.SpawnProjectile(player.movableStats.position,player.movableStats.rotation,currentTime);
	}

	if (IsKeyPressed(KEY_SPACE))
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