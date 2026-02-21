#include "AsteroidsManager.h"

Asteroid AsteroidsManager::CreateAstroid(Vector2 position, Vector2 velocity, AsteroidSize size)
{
	return Asteroid(position, velocity, size, GetRandomValue(0, 360), GetRandomValue(asteroidRotSpeedMin, asteroidRotSpeedMax));
}

void AsteroidsManager::UpdateAllAsteroids(float deltaTime)
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		_asteroids[i].AsteroidUpdate(deltaTime);
	}
}

void AsteroidsManager::DrawAllAsteroids()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		_asteroids[i].DrawAsteroid();
	}
}

void AsteroidsManager::SpawnAsteeroid(Vector2 position, Vector2 velocity)
{
	bool spawnNewAsteroid = false;

	for (size_t i = 0; i < maxAsteroids; i++)
	{
		if (_asteroids[i].GetAsteroidStatus())
		{
			continue;
		}

		AsteroidSize newAsteroidSize = _asteroidsSize[GetRandomValue(0, 2)];
		Asteroid newAsteroid = CreateAstroid(position, velocity, newAsteroidSize);
		
		_asteroids[i] = newAsteroid;

		spawnNewAsteroid = true;

		break;
	}

	if (!spawnNewAsteroid)
	{
		TraceLog(LOG_DEBUG,"Failed to creeate new asteroid because there was no inactive asteroid");
	}
}
