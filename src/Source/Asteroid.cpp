#include "Asteroid.h"
#include "raymath.h"
#include "GameManager.h"

Asteroid::Asteroid()
{
}

void Asteroid::Init(Vector2 spawnPosition, Vector2 spawnVelocity, AsteroidSize spawnSize, float spawnRotation, float spawnRotationSpeed, float createdTime)
{
	movement.position = spawnPosition;
	movement.rotation = spawnRotation;
	movement.rotationSpeed = spawnRotationSpeed;
	movement.velocity = spawnVelocity;
	size = spawnSize;
	creationTime = createdTime;
	currentLifeTime = baseLifeTime;
	ChangeEntityState(ACTIVE);
	SetEntityRadius();
}

void Asteroid::EntityActiveStateUpdate(float deltaTime)
{
	movement.Move(deltaTime);
	movement.rotation += movement.rotationSpeed * deltaTime * GameManager::Get().GetCurrentGameSpeed();
}

void Asteroid::DrawEntity()
{
	if (GetCurrentEntityState() == DISABLE)
		return;

	DrawPolyLines(movement.position, 3, 16*(int)(size), movement.rotation, WHITE);

	if (debugMode)
	{
		DrawCircleLines(
			movement.position.x,
			movement.position.y,
			GetEntityRadius(),
			GREEN
		);
	}
}

void Asteroid::SetEntityRadius()
{
	entityRadius =  16 * (int)size;
}

void Asteroid::EntityHit()
{
	ChangeEntityState(DISABLE);
}

const AsteroidSize& Asteroid::AsteroidHit()
{
	EntityHit();
	return size;
}

void Asteroid::ResetEntity()
{
	ChangeEntityState(DISABLE);
}
