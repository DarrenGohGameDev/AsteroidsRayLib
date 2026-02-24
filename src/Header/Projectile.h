#pragma once
#include "raylib.h"
#include "Movable.h"

class Projectile
{
	public :

		Projectile();

		Projectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime);

		Projectile CreateProjectile(Vector2 position,float rotation,float creeatedTime);

		void ProjectileUpdate(float deltaTime);

		void DrawProjectile();

		bool GetProjectileStatus();
		
	protected :

		bool active;

		Movable movableStats;

		float lifeTime = 10.0f;

		float projectileSpeed = 400.0f;

		float creationTime;

		float projectileThicknes = 10.0f;

		float projectileLength = 30.0f;
};

