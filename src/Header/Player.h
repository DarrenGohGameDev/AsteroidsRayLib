#pragma once
#include "EntityTemplate.h"

class Player : public EntityTemplate
{
	public:

		Player();

		Player(Vector2 screenSize ,Vector2 screenCenter);

		void EntityActiveStateUpdate(float deltaTime) override;

		void EntityInvulnerableStateEnter() override;

		void EntityInvulnerableStateUpdate(float deltaTime) override;

		void EntityInvulnerableStateExit() override;
		
		void LoadPlayerTexture();

		float GetEntityRadius() override;

		bool CanFire(float currentTime);

		void DrawEntity() override;

		void EntityHit() override;

	protected:

		Texture2D playerTexture;

		Vector2 gameScreenSize;

		float lastFireTime;

		float playerFireRate = 0.25f;

		Vector2 playerSpawnPosition;

		void ResetEntity() override;

#pragma region PlayerMovement

		float playerMovementAcceleration = 480.0f;

		float playerMovementFriction = 2.0f;

		float playerMaxVelocity = 1300.0f;

		float playerMoveSpeed = 90.0f;

		float playerRadius = 24.0f;

		float playerWarpBackToScreenNudge = 100.0f;

		void PlayerMovement(float deltaTime);

		void WarpPlayerBackToScreen();

#pragma endregion

};

