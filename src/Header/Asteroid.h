#pragma once
#include "Movable.h"

typedef enum AsteroidSize
{
	ASTEROIDS_SMALL = 1,
	ASTEROIDS_MEDIUM = 2,
	ASTEROIDS_LARGE = 4,
};

class Asteroid
{
	public:
		Asteroid();
		Asteroid(Vector2 spawnPosition, Vector2 spawnVelocity, AsteroidSize spawnSize, float spawnRotation, float spawnRotationSpeed,float createdTime);

		virtual void AsteroidUpdate(float deltaTime);

		void DrawAsteroid();

		bool GetAsteroidStatus();

	protected:
		bool active;

		Movable movableStats;

		AsteroidSize size;

		float lifeTime = 10.0f;

		float creationTime;
};