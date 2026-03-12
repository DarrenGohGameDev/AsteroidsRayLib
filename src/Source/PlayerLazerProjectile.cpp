#include "PlayerLazerProjectile.h"
#include "raymath.h"

PlayerLazerProjectile::PlayerLazerProjectile()
{
	SetEntityRadius();
}

void PlayerLazerProjectile::Init(Vector2 spawnPosition ,float spawnRotation ,float creeatedTime)
{
	movement.position = spawnPosition;
	movement.rotation = spawnRotation;
	creationTime = creeatedTime;
	currentLifeTime = baseLifeTime;
	ChangeEntityState(ACTIVE);
}

void PlayerLazerProjectile::EntityActiveStateUpdate(float deltaTime)
{
	float radians = movement.rotation * DEG2RAD;

	Vector2 direction = {
		cosf(radians),
		sinf(radians)
	};

	movement.velocity = Vector2Scale(direction, projectileSpeed);
	movement.position.x += direction.x * projectileSpeed * deltaTime;
	movement.position.y += direction.y * projectileSpeed * deltaTime;
}

void PlayerLazerProjectile::DrawEntity()
{
	if (GetCurrentEntityState() == DISABLE)
		return;

	Rectangle rect = { movement.position.x,movement.position.y,projectileThicknes,projectileLength };
	Vector2 origin = { rect.width / 2,rect.height / 2 };

	DrawRectanglePro(rect, origin, movement.rotation + 90.0f, BLUE);

	if (debugMode || GameManager::Get().InDebugMode())
	{
		DrawCircle(movement.position.x,
				movement.position.y,
				GetEntityRadius(),
				Fade(GREEN, 0.2f));
	}
}

void PlayerLazerProjectile::SetEntityRadius()
{
	entityRadius = projectileLength * 0.5f;
}

void PlayerLazerProjectile::EntityHit()
{
	ChangeEntityState(DISABLE);
}

void PlayerLazerProjectile::ResetEntity()
{
	ChangeEntityState(DISABLE);
}
