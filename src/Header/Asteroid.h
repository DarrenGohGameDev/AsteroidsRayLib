#pragma once
#include "Movable.h"
#include "EntityTemplate.h"

typedef enum AsteroidSize
{
	ASTEROIDS_SMALL = 1,
	ASTEROIDS_MEDIUM = 2,
	ASTEROIDS_LARGE = 4,
};

class Asteroid :public EntityTemplate
{
	public:
		Asteroid();

		Asteroid(Vector2 spawnPosition, Vector2 spawnVelocity, AsteroidSize spawnSize, float spawnRotation, float spawnRotationSpeed,float createdTime);

		Movable movableStats;

		void EntityUpdate(float deltaTime) override;

		void DrawAsteroid();

		bool GetAsteroidStatus();

		float GetRadius();

		AsteroidSize AsteroidHit();

	protected:
		bool active;

		AsteroidSize size;

		float lifeTime = 10.0f;

		float creationTime;
};
