#pragma once
#include "raylib.h"
#include "Movable.h"
#include "Asteroid.h"

class Projectile
{
	public :

		Projectile();

		Projectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime);

		Projectile CreateProjectile(Vector2 position,float rotation,float creeatedTime);

		void ProjectileUpdate(float deltaTime);

		void DrawProjectile();

		bool GetProjectileStatus();

		float GetRadius();

		bool CheckProjectileAsteroidCollision(Asteroid asteroid);
		
		Movable movableStats;

	protected :

		bool active;

		float lifeTime = 10.0f;

		float projectileSpeed = 600.0f;

		float creationTime;

		float projectileThicknes = 10.0f;

		float projectileLength = 30.0f;
};

