#include "raylib.h"
#include "time.h"
#include "stdlib.h"
#include "raymath.h"
#include "Asteroid.h"
#include "AsteroidsManager.h"
#include "PlayerLazerProjectileManager.h"
#include "ScoreManager.h"
#include "Player.h"
#include "SoundManager.h"
#include "GameManager.h"

const int screenWidth = 600;
const int screenHeight = 600;
const Vector2 screenSize = { screenWidth,screenHeight };
const Vector2 screenCenter = { screenWidth / 2,screenHeight / 2 };

AsteroidsManager asteroidManager;

PlayerLazerProjectileManager projectileManager;

Player player(screenSize,screenCenter);

void UpdateDrawFrame(void);

int main(void)
{
	srand(time(0));

	SetTraceLogLevel(LOG_DEBUG);

	InitWindow(screenWidth, screenHeight,"Test");

	SoundManager::Get().LoadSfxAssets();
	player.LoadPlayerTexture();

	PlayMusicStream(SoundManager::Get().BGM);

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

	ClearBackground(RED);

	player.EntityUpdate(deltaTime);

	asteroidManager.UpdateAllAsteroids(deltaTime, currentTime, screenSize,screenCenter);

	projectileManager.UpdateAllProjectile(deltaTime);

	for (size_t p = 0; p < projectileManager._projectile.size(); p++)
	{
		if (projectileManager._projectile[p].GetCurrentEntityState() == DISABLE)
			continue;

		for (size_t a = 0; a < asteroidManager._asteroids.size(); a++)
		{
			if (asteroidManager._asteroids[a].GetCurrentEntityState() == DISABLE)
				continue;

			if (projectileManager._projectile[p].CheckEntityCollision(&asteroidManager._asteroids[a]))
			{
				ScoreManager::Get().UpdateScore(1);

				PlaySound(SoundManager::Get().AsteroidHit);

				AsteroidSize hitResult = asteroidManager._asteroids[a].AsteroidHit();

				if (hitResult != ASTEROIDS_SMALL)
				{
					switch (hitResult)
					{
					case ASTEROIDS_MEDIUM:

						for (int i = 0; i < 2; i++)
						{
							asteroidManager.SpawnAsteroid(asteroidManager._asteroids[a].GetEntityPosition(), screenCenter, true, hitResult);
						}

						break;

					case ASTEROIDS_LARGE:

						for (int i = 0; i < 3; i++)
						{
							asteroidManager.SpawnAsteroid(asteroidManager._asteroids[a].GetEntityPosition(), screenCenter, true, hitResult);
						}

						break;

					default:
						break;
					}
				}

				break; // projectile destroyed → stop checking this projectile
			}
		}
	}

	if (player.GetCurrentEntityState() == ACTIVE)
	{
		for (size_t a = 0; a < asteroidManager._asteroids.size(); a++)
		{
			if (asteroidManager._asteroids[a].GetCurrentEntityState() == DISABLE)
				continue;

			if (player.CheckEntityCollision(&asteroidManager._asteroids[a]))
			{
				PlaySound(SoundManager::Get().playerHit);
				break;
			}
		}
	}


	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && player.CanFire(currentTime) && GameManager::Get().GetCurrentGameState() == PLAYING)
	{
		projectileManager.SpawnProjectile(player.GetEntityPosition(), player.GetEntityRotation(), currentTime);
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		asteroidManager.SpawnAsteroid(screenSize,screenCenter);
	}

	if (IsKeyPressed(KEY_P))
	{
		GameManager::Get().GetDispatcher().trigger(GamePauseRequest{});
	}

	if (IsKeyPressed(KEY_Q))
	{
		GameManager::Get().GetDispatcher().trigger(StartGameRequest{});
	}

	if (IsKeyPressed(KEY_R))
	{
		GameManager::Get().GetDispatcher().trigger(GameRestartRequest{});
	}

	if (asteroidManager.debugMode)
	{
		asteroidManager.DrawDebugLine();
	}

	UpdateMusicStream(SoundManager::Get().BGM);

	player.DrawEntity();

	asteroidManager.DrawAllAsteroids();

	projectileManager.DrawAllProjectile();

	ScoreManager::Get().DrawScore();

	EndDrawing();
}