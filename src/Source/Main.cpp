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
#include "UIManager.h"

AsteroidsManager asteroidManager;

PlayerLazerProjectileManager projectileManager;

Player player(GameManager::Get().screenSize, GameManager::Get().screenCenter);

void UpdateDrawFrame(void);

int main(void)
{
	srand(time(0));

	SetTraceLogLevel(LOG_DEBUG);

	InitWindow(GameManager::Get().screenWidth, GameManager::Get().screenHeight,"Test");

	SoundManager::Get().LoadSfxAssets();
	UIManager::Get().SetPlayer(&player);
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

	asteroidManager.UpdateAllAsteroids(deltaTime, currentTime, GameManager::Get().screenSize, GameManager::Get().screenCenter);

	projectileManager.UpdateAllProjectile(deltaTime);

	for (size_t p = 0; p < projectileManager._projectile.size(); p++)
	{
		if (projectileManager._projectile[p].GetCurrentEntityState() == DISABLE)
			continue;

		UIManager::Get().shootMeBtn.CheckEntityCollision(&projectileManager._projectile[p]);

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
							asteroidManager.SpawnAsteroid(asteroidManager._asteroids[a].GetEntityPosition(), GameManager::Get().screenCenter, true, hitResult);
						}

						break;

					case ASTEROIDS_LARGE:

						for (int i = 0; i < 3; i++)
						{
							asteroidManager.SpawnAsteroid(asteroidManager._asteroids[a].GetEntityPosition(), GameManager::Get().screenCenter, true, hitResult);
						}

						break;

					default:
						break;
					}
				}

				break;
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


	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && player.CanFire(currentTime) && GameManager::Get().GetCurrentGameState() != PAUSED)
	{
		projectileManager.SpawnProjectile(player.GetEntityPosition(), player.GetEntityRotation(), currentTime);
	}

	if (IsKeyPressed(KEY_P))
	{
		GameManager::Get().GetDispatcher().trigger(GamePauseRequest{});
	}

	if (IsKeyPressed(KEY_R) && GameManager::Get().GetCurrentGameState() == GAMEOVER)
	{
		GameManager::Get().GetDispatcher().trigger(GameRestartRequest{});
	}

	if (GameManager::Get().InDebugMode())
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			asteroidManager.SpawnAsteroid(GameManager::Get().screenSize, GameManager::Get().screenCenter);
		}
	}

	if (asteroidManager.debugMode)
	{
		asteroidManager.DrawDebugLine();
	}

	UpdateMusicStream(SoundManager::Get().BGM);

	player.DrawEntity();

	asteroidManager.DrawAllAsteroids();

	projectileManager.DrawAllProjectile();

	UIManager::Get().DrawCurrentStateUI();

	EndDrawing();
}