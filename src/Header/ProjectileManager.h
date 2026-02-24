#pragma once
#include "Projectile.h"
#include "raylib.h"

#define maxProjectiles 64

class ProjectileManager
{
	public :


		Projectile _projectile[maxProjectiles];

		void UpdateAllProjectile(float deltaTIme);

		void SpawnProjectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime);

	protected:

		void DrawAllProjectile();

		Projectile CreateProjectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime);
};

