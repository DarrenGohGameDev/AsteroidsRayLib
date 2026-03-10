#pragma once
#include "EntityTemplate.h"
#include "PlayerLazerProjectileManager.h"

class Player : public EntityTemplate
{
	public:

		Player();

		PlayerLazerProjectileManager projectileManager;

		Player(Vector2 screenSize ,Vector2 screenCenter);

		void EntityActiveStateEnter() override;

		void EntityActiveStateUpdate(float deltaTime) override;

		void EntityInvulnerableStateEnter() override;

		void EntityInvulnerableStateUpdate(float deltaTime) override;

		void EntityInvulnerableStateExit() override;
		
		void LoadPlayerTexture();
		
		bool CanFire(float currentTime);

		void DrawEntity() override;

		void EntityHit() override;

		void ShootLazer(float currentTime);

	protected:

		Texture2D playerTexture;

		Vector2 gameScreenSize;

		float lastFireTime;

		float playerFireRate = 0.25f;

		Vector2 playerSpawnPosition;

		Color playerTextureColor;

		float blinkTime = 0.0f;

		void ResetEntity() override;

		void SetEntityRadius() override;

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

