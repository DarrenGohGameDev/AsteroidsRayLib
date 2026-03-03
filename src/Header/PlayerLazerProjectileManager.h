#pragma once
#include "PlayerLazerProjectile.h"
#include "raylib.h"

#define maxProjectiles 64

class PlayerLazerProjectileManager
{
	public :


		PlayerLazerProjectile _projectile[maxProjectiles];

		void UpdateAllProjectile(float deltaTIme);

		void SpawnProjectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime);

		void DrawAllProjectile();

	protected:

		PlayerLazerProjectile CreateProjectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime);
};

