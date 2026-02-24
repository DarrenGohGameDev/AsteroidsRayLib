#include "ProjectileManager.h"
#include "raymath.h"

void ProjectileManager::UpdateAllProjectile(float deltaTIme)
{
	for (int i = 0; i < maxProjectiles; i++)
	{
		_projectile[i].ProjectileUpdate(deltaTIme);
	}

	DrawAllProjectile();
}

void ProjectileManager::DrawAllProjectile()
{
	for (int i = 0; i < maxProjectiles; i++)
	{
		_projectile[i].DrawProjectile();
	}
}

void ProjectileManager::SpawnProjectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime)
{
	bool spawnNewProjectile = false;

	for (size_t i = 0; i < maxProjectiles; i++)
	{
		if (_projectile[i].GetProjectileStatus())
		{
			continue;
		}

		Projectile newProjectile = CreateProjectile(spawnPosition,spawnRotation,creeatedTime);

		_projectile[i] = newProjectile;

		spawnNewProjectile = true;

		break;
	}

	if (!spawnNewProjectile)
	{
		TraceLog(LOG_DEBUG, "Failed to creeate new projectile because there was no inactive projectile");
	}
}

Projectile ProjectileManager::CreateProjectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime)
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

	return Projectile(spawnPos,spawnRotation,creeatedTime);
}