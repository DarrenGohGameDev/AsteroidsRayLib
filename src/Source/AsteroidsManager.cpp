#include "AsteroidsManager.h"
#include "raymath.h"

AsteroidsManager::AsteroidsManager()
{
	_asteroids.resize(initialAsteroidsSpawnAmount);
}

void AsteroidsManager::UpdateAllAsteroids(float deltaTime,float currentTime, Vector2 screenSize,Vector2 screenCenter)
{
	int totalActiveAsteroids = 0;

	if (currentTime > lastASteroidCreationTime + asteroidSpawnDelay)
	{
		SpawnAsteeroid(screenSize, screenCenter);
		lastASteroidCreationTime = currentTime;
	}

	for (size_t i = 0; i < _asteroids.size(); i++)
	{
		_asteroids[i].EntityUpdate(deltaTime);

		if (debugMode)
		{
			if (_asteroids[i].GetCurrentEntityState() == ACTIVE)
			{
				totalActiveAsteroids++;
			}
		}
	}

	if (debugMode)
	{
		DrawText(TextFormat("ASTEROIDS:%d", totalActiveAsteroids), 20, 90, 32, WHITE);
		DrawText(TextFormat("ASTEROIDS Size:%d", _asteroids.size()), 20, 140, 32, WHITE);
	}
}

void AsteroidsManager::DrawAllAsteroids()
{
	for (size_t i = 0; i < _asteroids.size(); i++)
	{
		_asteroids[i].DrawEntity();
	}
}

void AsteroidsManager::SpawnAsteeroid(Vector2 screenSize,Vector2 screenCenter, bool asteroidHitSpawn, AsteroidSize asteroidSize)
{
	bool reuseAsteroid = false;

	for (size_t i = 0; i < _asteroids.size(); i++)
	{
		if (_asteroids[i].GetCurrentEntityState() != ACTIVE)
		{
			CreateAstroid(&_asteroids[i], screenSize, screenCenter, asteroidHitSpawn, asteroidSize);

			reuseAsteroid = true;
			return;
		}
	}

	if (!reuseAsteroid)
	{
		_asteroids.emplace_back();
		CreateAstroid(&_asteroids.back(), screenSize, screenCenter, asteroidHitSpawn, asteroidSize);
	}
}

void AsteroidsManager::CreateAstroid(Asteroid* inactiveAsteroid,Vector2 screenSize, Vector2 screenCenter, bool asteroidHitSpawn, AsteroidSize asteroidSize)
{
	AsteroidSize newAsteroidSize = _asteroidsSize[GetRandomValue(0, 2)];

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

	if (debugMode)
	{
		asteroidDebugSpawnLine0[0] = newAsteroidSpawnPosition;
		asteroidDebugSpawnLine1[0] = newAsteroidSpawnPosition;
		asteroidDebugSpawnLine2[0] = newAsteroidSpawnPosition;

		asteroidDebugSpawnLine0[1] = Vector2Add(newAsteroidSpawnPosition, Vector2Rotate(Vector2Scale(newAsteroidVelocity, 10), -asteroidRandomAngle));
		asteroidDebugSpawnLine1[1] = Vector2Add(newAsteroidSpawnPosition, Vector2Rotate(Vector2Scale(newAsteroidVelocity, 10), asteroidRandomAngle));
	}

	newAsteroidVelocity = Vector2Rotate(newAsteroidVelocity, (float)GetRandomValue(-asteroidRandomAngle, asteroidRandomAngle));

	if (debugMode)
	{
		asteroidDebugSpawnLine2[1] = Vector2Add(newAsteroidSpawnPosition, Vector2Scale(newAsteroidVelocity, 10));
	}

	inactiveAsteroid->Init(newAsteroidSpawnPosition, newAsteroidVelocity, newAsteroidSize, GetRandomValue(asteroidSpawnRotationMin, asteroidSpawnRotationMax), GetRandomValue(asteroidRotSpeedMin, asteroidRotSpeedMax), GetTime());
}

Vector2 AsteroidsManager::GetAsteroidSpawnPosition(Vector2 screenSize,bool asteroidHitSpawn)
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

void AsteroidsManager::DrawDebugLine()
{
	DrawLineV(asteroidDebugSpawnLine0[0], asteroidDebugSpawnLine0[1],GREEN);
	DrawLineV(asteroidDebugSpawnLine1[0], asteroidDebugSpawnLine1[1],BLUE);
	DrawLineV(asteroidDebugSpawnLine2[0], asteroidDebugSpawnLine2[1],BLACK);
}

