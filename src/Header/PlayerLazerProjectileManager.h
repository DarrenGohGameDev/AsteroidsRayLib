#pragma once
#include "PlayerLazerProjectile.h"
#include "raylib.h"
#include <vector>

#define initialProjectilesSpawnAmount 30

class PlayerLazerProjectileManager
{
	public :

		PlayerLazerProjectileManager();

		std::vector<std::unique_ptr<PlayerLazerProjectile>>  _projectile;

		void UpdateAllProjectile(float deltaTIme);

		void SpawnProjectile(Vector2 spawnPosition ,float spawnRotation ,float creeatedTime);

		void DrawAllProjectile();

	protected:

		const bool debugMode = false;

		void CreateProjectile(PlayerLazerProjectile& inactiveProjectile ,Vector2 spawnPosition ,float spawnRotation ,float creeatedTime);
};

