#include "AsteroidsManager.h"
#include "GameManager.h"
#include "raymath.h"

AsteroidsManager::AsteroidsManager()
{
	for (int i = 0; i < initialAsteroidsSpawnAmount; i++)
	{
		asteroids.push_back(std::make_unique<Asteroid>());
	}

	GameManager::Get().GetDispatcher().sink<GameRestartRequest>().connect<&AsteroidsManager::OnGameReset>(this);
	OnGameReset();
}

void AsteroidsManager::UpdateAllAsteroids(float deltaTime, float currentTime, Vector2 screenSize, Vector2 screenCenter)
{
	if (GameManager::Get().GetCurrentGameState() != PLAYING)
		return;

	int totalActiveAsteroids = 0;

	spawnSpeedUpMultiplier += deltaTime * spawnSpeedRamp;

	spawnSpeedUpMultiplier = Clamp(spawnSpeedUpMultiplier, 1.0f, maxSpawnSpeedMultiplier);

	float delay = asteroidSpawnDelay / spawnSpeedUpMultiplier;

	if (currentTime > lastAsteroidCreationTime + delay)
	{
		SpawnAsteroid(screenSize, screenCenter);
		lastAsteroidCreationTime = currentTime;
	}

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->EntityUpdate(deltaTime);

		if (debugMode || GameManager::Get().InDebugMode())
		{
			if (asteroids[i]->GetCurrentEntityState() == ACTIVE)
			{
				totalActiveAsteroids++;
			}
		}
	}

	if (debugMode || GameManager::Get().InDebugMode())
	{
		DrawText(TextFormat("ASTEROIDS:%d", totalActiveAsteroids), 20, 90, 32, WHITE);
		DrawText(TextFormat("ASTEROIDS Size:%d", asteroids.size()), 20, 140, 32, WHITE);
	}
}

void AsteroidsManager::DrawAllAsteroids()
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->DrawEntity();
	}
}

void AsteroidsManager::SpawnAsteroid(Vector2 screenSize ,Vector2 screenCenter ,bool asteroidHitSpawn ,AsteroidSize asteroidSize)
{
	if (GameManager::Get().GetCurrentGameState() != PLAYING)
		return;

	bool reuseAsteroid = false;

	for (int i = 0; i < asteroids.size(); i++)
	{
		if (asteroids[i]->GetCurrentEntityState() != ACTIVE)
		{
			CreateAsteroid(*asteroids[i], screenSize, screenCenter, asteroidHitSpawn, asteroidSize);

			reuseAsteroid = true;
			return;
		}
	}

	if (!reuseAsteroid)
	{
		asteroids.push_back(std::make_unique<Asteroid>());
		CreateAsteroid(*asteroids.back(), screenSize, screenCenter, asteroidHitSpawn, asteroidSize);
	}
}

void AsteroidsManager::CreateAsteroid(Asteroid& inactiveAsteroid ,Vector2 screenSize ,Vector2 screenCenter ,bool asteroidHitSpawn ,AsteroidSize asteroidSize)
{
	AsteroidSize newAsteroidSize = asteroidsSize[GetRandomValue(0, 2)];

	float newAsteroidSpeed = GetRandomValue(asteroidMoveSpeedMin, asteroidMoveSpeedMax);

	Vector2 newAsteroidSpawnPosition = GetAsteroidSpawnPosition(screenSize, asteroidHitSpawn);

	Vector2 newAsteroidVelocity = asteroidHitSpawn ? 
		 Vector2Rotate(Vector2{ 0,1 }, (float)GetRandomValue(0, 359)) :
		 Vector2Subtract(screenCenter, newAsteroidSpawnPosition);

	if (asteroidHitSpawn)
	{
		switch (asteroidSize)
		{
		case ASTEROIDS_SMALL:
			break;

		case ASTEROIDS_MEDIUM:

			newAsteroidSize = ASTEROIDS_SMALL;

			break;

		case ASTEROIDS_LARGE:

			newAsteroidSize = ASTEROIDS_MEDIUM;

			break;

		default:
			break;
		}
	}

	newAsteroidVelocity = Vector2Scale(Vector2Normalize(newAsteroidVelocity), newAsteroidSpeed);

	if (debugMode || GameManager::Get().InDebugMode())
	{
		asteroidDebugSpawnLine0[0] = newAsteroidSpawnPosition;
		asteroidDebugSpawnLine1[0] = newAsteroidSpawnPosition;
		asteroidDebugSpawnLine2[0] = newAsteroidSpawnPosition;

		asteroidDebugSpawnLine0[1] = Vector2Add(newAsteroidSpawnPosition, Vector2Rotate(Vector2Scale(newAsteroidVelocity, 10), -asteroidRandomAngle));
		asteroidDebugSpawnLine1[1] = Vector2Add(newAsteroidSpawnPosition, Vector2Rotate(Vector2Scale(newAsteroidVelocity, 10), asteroidRandomAngle));
	}

	newAsteroidVelocity = Vector2Rotate(newAsteroidVelocity, (float)GetRandomValue(-asteroidRandomAngle, asteroidRandomAngle));

	if (debugMode || GameManager::Get().InDebugMode())
	{
		asteroidDebugSpawnLine2[1] = Vector2Add(newAsteroidSpawnPosition, Vector2Scale(newAsteroidVelocity, 10));
	}

	inactiveAsteroid.Init(newAsteroidSpawnPosition, newAsteroidVelocity, newAsteroidSize, GetRandomValue(asteroidSpawnRotationMin, asteroidSpawnRotationMax), GetRandomValue(asteroidRotSpeedMin, asteroidRotSpeedMax), GetTime());
}

Vector2 AsteroidsManager::GetAsteroidSpawnPosition(Vector2 screenSize ,bool asteroidHitSpawn)
{
	Vector2 result;

	int side = GetRandomValue(0, 3);

	switch (side)
	{
		case 0: // Top
			result.x = GetRandomValue(0, screenSize.x);
			result.y = -(asteroidSpawnPadding.y);
			break;
		
		case 1: // Bottom
			result.x = GetRandomValue(0, screenSize.x);
			result.y = screenSize.y + asteroidSpawnPadding.y;
			break;

		case 2: // Left
			result.x = -asteroidSpawnPadding.x;
			result.y = GetRandomValue(0, screenSize.y);
			break;

		case 3: // Right
			result.x = screenSize.x + asteroidSpawnPadding.x;
			result.y = GetRandomValue(0, screenSize.y);
			break;
	}

	if (asteroidHitSpawn)
	{
		result = screenSize;
	}

	return result;
}

void AsteroidsManager::OnGameReset()
{
	lastAsteroidCreationTime = -1;
	spawnSpeedUpMultiplier = baseSpawnSpeedUpMultiplier;
	spawnSpeedRamp = baseSpawnSpeedRamp;
}

void AsteroidsManager::DrawDebugLine()
{
	DrawLineV(asteroidDebugSpawnLine0[0], asteroidDebugSpawnLine0[1],GREEN);
	DrawLineV(asteroidDebugSpawnLine1[0], asteroidDebugSpawnLine1[1],BLUE);
	DrawLineV(asteroidDebugSpawnLine2[0], asteroidDebugSpawnLine2[1],BLACK);
}

