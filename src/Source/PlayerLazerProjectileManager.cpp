#include "PlayerLazerProjectileManager.h"
#include "raymath.h"

PlayerLazerProjectileManager::PlayerLazerProjectileManager()
{
	_projectile.resize(initialProjectilesSpawnAmount);
}

void PlayerLazerProjectileManager::UpdateAllProjectile(float deltaTIme)
{
	int totalActiveProjectile = 0;

	for (size_t i = 0; i < _projectile.size(); i++)
	{
		_projectile[i].EntityUpdate(deltaTIme);

		if (debugMode)
		{
			if (_projectile[i].GetCurrentEntityState() == ACTIVE)
			{
				totalActiveProjectile++;
			}
		}
	}

	if (debugMode)
	{
		DrawText(TextFormat("projectile:%d", totalActiveProjectile), 20, 180, 32, WHITE);
		DrawText(TextFormat("projectile Size:%d", _projectile.size()), 20, 210, 32, WHITE);
	}
}

void PlayerLazerProjectileManager::SpawnProjectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime)
{
	bool spawnNewProjectile = false;

	for (size_t i = 0; i < _projectile.size(); i++)
	{
		if (_projectile[i].GetCurrentEntityState() != ACTIVE)
		{
			CreateProjectile(&_projectile[i],spawnPosition, spawnRotation, creeatedTime);

			spawnNewProjectile = true;
			return;
		}
	}

	if (!spawnNewProjectile)
	{
		_projectile.emplace_back();
		CreateProjectile(&_projectile.back(), spawnPosition, spawnRotation, creeatedTime);
	}
}

void PlayerLazerProjectileManager::DrawAllProjectile()
{
	for (size_t i = 0; i < _projectile.size(); i++)
	{
		_projectile[i].DrawEntity();
	}
}

void PlayerLazerProjectileManager::CreateProjectile(PlayerLazerProjectile* inactiveProjectile,Vector2 spawnPosition, float spawnRotation, float creeatedTime)
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

	inactiveProjectile->Init(spawnPos, spawnRotation, creeatedTime);
}