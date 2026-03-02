#pragma once
#include "raylib.h"
#include "Movable.h"
#include "Asteroid.h"
#include "EntityTemplate.h"

class Projectile : public EntityTemplate
{
	public :

		Projectile();

		Projectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime);

		void EntityUpdate(float deltaTime) override;

		virtual void DrawProjectile();

		bool GetProjectileStatus();

		float GetRadius();

		bool CheckProjectileAsteroidCollision(Asteroid asteroid);
		
		Movable movableStats;

	protected :

		float projectileSpeed = 600.0f;

		float creationTime;

		float projectileThicknes = 10.0f;

		float projectileLength = 30.0f;
};

