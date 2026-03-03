#include "PlayerLazerProjectileManager.h"
#include "raymath.h"

void PlayerLazerProjectileManager::UpdateAllProjectile(float deltaTIme)
{
	for (int i = 0; i < maxProjectiles; i++)
	{
		_projectile[i].EntityUpdate(deltaTIme);
	}
}

void PlayerLazerProjectileManager::SpawnProjectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime)
{
	bool spawnNewProjectile = false;

	for (size_t i = 0; i < maxProjectiles; i++)
	{
		if (_projectile[i].GetCurrentEntityState() == ACTIVE)
		{
			continue;
		}

		PlayerLazerProjectile newProjectile = CreateProjectile(spawnPosition,spawnRotation,creeatedTime);

		_projectile[i] = newProjectile;

		spawnNewProjectile = true;

		TraceLog(LOG_DEBUG, "spawned projectile");

		break;
	}

	if (!spawnNewProjectile)
	{
		TraceLog(LOG_DEBUG, "Failed to creeate new projectile because there was no inactive projectile");
	}
}

void PlayerLazerProjectileManager::DrawAllProjectile()
{
	for (size_t i = 0; i < maxProjectiles; i++)
	{
		_projectile[i].DrawEntity();
	}
}

PlayerLazerProjectile PlayerLazerProjectileManager::CreateProjectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime)
{
	float radians = spawnRotation * DEG2RAD;

	Vector2 forward = {
		cosf(radians),
		sinf(radians)
	};

	Vector2 spawnPos = Vector2Add(
		spawnPosition,
		Vector2Scale(forward, 24.0f)
	);

	return PlayerLazerProjectile(spawnPos,spawnRotation,creeatedTime);
}