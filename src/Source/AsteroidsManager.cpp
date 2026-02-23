#include "AsteroidsManager.h"
#include "raymath.h"

void AsteroidsManager::UpdateAllAsteroids(float deltaTime,float currentTime, Vector2 screenSize,Vector2 screenCenter)
{
	int totalActiveAsteroids = 0;

	for (int i = 0; i < maxAsteroids; i++)
	{
		_asteroids[i].AsteroidUpdate(deltaTime);

		if (currentTime > lastASteroidCreationTime + asteroidSpawnDelay)
		{
			SpawnAsteeroid(screenSize,screenCenter);
			lastASteroidCreationTime = currentTime;
		}

		if (DebugingMode)
		{
			if (_asteroids[i].GetAsteroidStatus())
			{
				totalActiveAsteroids++;
			}
		}
	}

	if (DebugingMode)
	{
		DrawText(TextFormat("ASTEROIDS:%d", totalActiveAsteroids), 20, 20, 32, WHITE);
	}
}

void AsteroidsManager::DrawAllAsteroids()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		_asteroids[i].DrawAsteroid();
	}
}

void AsteroidsManager::SpawnAsteeroid(Vector2 screenSize,Vector2 screenCenter)
{
	bool spawnNewAsteroid = false;

	for (size_t i = 0; i < maxAsteroids; i++)
	{
		if (_asteroids[i].GetAsteroidStatus())
		{
			continue;
		}

		Asteroid newAsteroid = CreateAstroid(screenSize, screenCenter);
		
		_asteroids[i] = newAsteroid;

		spawnNewAsteroid = true;

		break;
	}

	if (!spawnNewAsteroid)
	{
		TraceLog(LOG_DEBUG,"Failed to creeate new asteroid because there was no inactive asteroid");
	}
}

Asteroid AsteroidsManager::CreateAstroid(Vector2 screenSize, Vector2 screenCenter)
{
	AsteroidSize newAsteroidSize = _asteroidsSize[GetRandomValue(0, 2)];

	float newAsteroidSpeed = GetRandomValue(asteroidMoveSpeedMin, asteroidMoveSpeedMax);

	Vector2 newAsteroidSpawnPosition = GetAsteroidSpawnPosition(screenSize);

	Vector2 newAsteroidVelocity = Vector2Subtract(screenCenter, newAsteroidSpawnPosition);

	newAsteroidVelocity = Vector2Scale(Vector2Normalize(newAsteroidVelocity), newAsteroidSpeed);

	if (DebugingMode)
	{
		asteroidDebugSpawnLine0[0] = newAsteroidSpawnPosition;
		asteroidDebugSpawnLine1[0] = newAsteroidSpawnPosition;
		asteroidDebugSpawnLine2[0] = newAsteroidSpawnPosition;

		asteroidDebugSpawnLine0[1] = Vector2Add(newAsteroidSpawnPosition, Vector2Rotate(Vector2Scale(newAsteroidVelocity, 10), -asteroidRandomAngle));
		asteroidDebugSpawnLine1[1] = Vector2Add(newAsteroidSpawnPosition, Vector2Rotate(Vector2Scale(newAsteroidVelocity, 10), asteroidRandomAngle));
	}

	newAsteroidVelocity = Vector2Rotate(newAsteroidVelocity, (float)GetRandomValue(-asteroidRandomAngle, asteroidRandomAngle));

	if (DebugingMode)
	{
		asteroidDebugSpawnLine2[1] = Vector2Add(newAsteroidSpawnPosition, Vector2Scale(newAsteroidVelocity, 10));
	}

	return Asteroid(newAsteroidSpawnPosition, newAsteroidVelocity, newAsteroidSize, GetRandomValue(0, 360), GetRandomValue(asteroidRotSpeedMin, asteroidRotSpeedMax), GetTime());
}

Vector2 AsteroidsManager::GetAsteroidSpawnPosition(Vector2 screenSize)
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

	return result;
}

void AsteroidsManager::DrawDebugLine()
{
	DrawLineV(asteroidDebugSpawnLine0[0], asteroidDebugSpawnLine0[1],GREEN);
	DrawLineV(asteroidDebugSpawnLine1[0], asteroidDebugSpawnLine1[1],BLUE);
	DrawLineV(asteroidDebugSpawnLine2[0], asteroidDebugSpawnLine2[1],BLACK);
}

