#include "Asteroid.h"
#include "raymath.h"

Asteroid::Asteroid()
{
	active = false;
}

Asteroid::Asteroid(Vector2 spawnPosition, Vector2 spawnVelocity, AsteroidSize spawnSize, float spawnRotation, float spawnRotationSpeed,float createdTime)
{
	active = true;
	movableStats.position = spawnPosition;
	movableStats.rotation = spawnRotation;
	movableStats.rotationSpeed = spawnRotationSpeed;
	movableStats.velocity = spawnVelocity;
	size = spawnSize;
	creationTime = createdTime;
}

void Asteroid::AsteroidUpdate(float deltaTime)
{
	if (!active)
		return;

	movableStats.Move(deltaTime);
	movableStats.rotation += movableStats.rotationSpeed * deltaTime;

	if (GetTime() > creationTime + lifeTime)
	{
		active = false;
		return;
	}
}

void Asteroid::DrawAsteroid()
{
	if (!active)
		return;

	DrawPolyLines(movableStats.position, 3, 16*(int)(size), movableStats.rotation, WHITE);
}

bool Asteroid::GetAsteroidStatus()
{
	return active;
}
