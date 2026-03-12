#pragma once
#include "Movable.h"
#include "EntityTemplate.h"

enum AsteroidSize
{
	ASTEROIDS_SMALL = 1,
	ASTEROIDS_MEDIUM = 2,
	ASTEROIDS_LARGE = 4,
};

class Asteroid :public EntityTemplate
{
	public:
		Asteroid();

		void Init(Vector2 spawnPosition ,Vector2 spawnVelocity ,AsteroidSize spawnSize ,float spawnRotation ,float spawnRotationSpeed ,float createdTime);

		void EntityActiveStateUpdate(float deltaTime) override;

		void DrawEntity() override;

		void EntityHit() override;

		const AsteroidSize& AsteroidHit();

	protected:

		AsteroidSize size;

		void ResetEntity() override;

		void SetEntityRadius() override;
};
