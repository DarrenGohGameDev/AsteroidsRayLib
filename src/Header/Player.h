#pragma once
#include "Movable.h"
#include "Asteroid.h"

class Player
{
	public:

		Player(Vector2 screenSize ,Vector2 screenCenter);

		virtual void PlayrUpdate(float deltaTime);

		bool GetPlayerStatus();

		void MovePlayer(Vector2 playerMovement, float playerFaceDirection, float deltaTime);
		
		void Init();

		Movable movableStats;

		bool CanFire(float currentTime);

		float GetRadius();

		bool CheckProjectileAsteroidCollision(Asteroid asteroid);


	protected:

		Texture2D playerTexture;

		bool active;

		Vector2 gameScreenSize;

		float lastFireTime;

		float playerFireRate = 0.25f;

		int playerHp = 3;

		void PlayerHit();

		void DrawPlayer();

#pragma region PlayerMovement

		float playerMovementAcceleration = 480.0f;

		float playerMovementFriction = 2.0f;

		float playerMaxVelocity = 1300.0f;

		float playerMoveSpeed = 90.0f;

		float playerRadius = 24.0f;

		float playerWarpBackToScreenNudge = 100.0f;

		void WarpPlayerBackToScreen();

#pragma endregion

};

