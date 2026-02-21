#include "AsteroidsManager.h"
#include "raymath.h"

void AsteroidsManager::UpdateAllAsteroids(float deltaTime,float currentTime,Vector2 screenCenter,Vector2 screenSize)
{
	int totalActiveAsteroids = 0;

	for (int i = 0; i < maxAsteroids; i++)
	{
		_asteroids[i].AsteroidUpdate(deltaTime);

		if (currentTime > lastASteroidCreationTime + asteroidSpawnDelay)
		{
			SpawnAsteeroid(screenCenter, screenSize);
			lastASteroidCreationTime = currentTime;
		}

		if (showAsteroidCount)
		{
			if (_asteroids[i].GetAsteroidStatus())
			{
				totalActiveAsteroids++;
			}
		}
	}

	if (showAsteroidCount)
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

void AsteroidsManager::SpawnAsteeroid(Vector2 screenCenter,Vector2 position)
{
	bool spawnNewAsteroid = false;

	

	for (size_t i = 0; i < maxAsteroids; i++)
	{
		if (_asteroids[i].GetAsteroidStatus())
		{
			continue;
		}

		Asteroid newAsteroid = CreateAstroid(position, screenCenter);
		
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

	Vector2Rotate(newAsteroidVelocity, (float)GetRandomValue(-asteroidRandomAngle, asteroidRandomAngle));

	return Asteroid(newAsteroidSpawnPosition, newAsteroidVelocity, newAsteroidSize, GetRandomValue(0, 360), GetRandomValue(asteroidRotSpeedMin, asteroidRotSpeedMax), GetTime());
}

Vector2 AsteroidsManager::GetAsteroidSpawnPosition(Vector2 screenSize)
{
	Vector2 result;

	int side = GetRandomValue(0, 3);

	switch (side)
	{
		case 0: // Top
			result.x = GetRandomValue(-screenSize.x, screenSize.x);
			result.y = -(asteroidSpawnPadding.y);
			break;
		
		case 1: // Bottom
			result.x = GetRandomValue(-screenSize.x, screenSize.x);
			result.y = screenSize.y + asteroidSpawnPadding.y;
			break;

		case 2: // Left
			result.x = -asteroidSpawnPadding.x;
			result.y = GetRandomValue(-screenSize.y, screenSize.y);
			break;

		case 3: // Right
			result.x = screenSize.x + asteroidSpawnPadding.x;
			result.y = GetRandomValue(-screenSize.y, screenSize.y);
			break;
	}

	return result;
}

