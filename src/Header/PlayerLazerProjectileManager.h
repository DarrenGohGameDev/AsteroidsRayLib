#pragma once
#include "PlayerLazerProjectile.h"
#include "raylib.h"
#include <vector>

#define initialProjectilesSpawnAmount 30

class PlayerLazerProjectileManager
{
	public :

		PlayerLazerProjectileManager();

		std::vector<PlayerLazerProjectile>  _projectile;

		void UpdateAllProjectile(float deltaTIme);

		void SpawnProjectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime);

		void DrawAllProjectile();

		const bool debugMode = false;

	protected:

		void CreateProjectile(PlayerLazerProjectile* inactiveProjectile,Vector2 spawnPosition, float spawnRotation, float creeatedTime);
};

