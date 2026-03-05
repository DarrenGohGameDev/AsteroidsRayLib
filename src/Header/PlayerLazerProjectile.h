#pragma once
#include "raylib.h"
#include "Movable.h"
#include "Asteroid.h"
#include "EntityTemplate.h"

class PlayerLazerProjectile : public EntityTemplate
{
	public :

		PlayerLazerProjectile();

		void Init(Vector2 spawnPosition, float spawnRotation, float creeatedTime);

		void EntityActiveStateUpdate(float deltaTime) override;

		void DrawEntity() override;

		float GetEntityRadius() override;

		void EntityHit() override;

	protected :

		float projectileSpeed = 600.0f;

		float projectileThicknes = 10.0f;

		float projectileLength = 30.0f;
};

