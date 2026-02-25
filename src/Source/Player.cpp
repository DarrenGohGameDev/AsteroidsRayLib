#include "Player.h"
#include "raymath.h"

Player::Player(Vector2 screenSize,Vector2 screenCenter)
{
	movableStats.rotation = 180;
	movableStats.position = screenCenter;
	active = true;
	gameScreenSize = screenSize;
}

void Player::PlayrUpdate(float deltaTime)
{
	Vector2 playerMoveDirection;

	Vector2 playerFaceDirection;

	playerFaceDirection = Vector2Subtract(GetMousePosition(),movableStats.position);

	float angle = atan2f(playerFaceDirection.y, playerFaceDirection.x) * RAD2DEG;

	playerMoveDirection.x = (int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A);
	playerMoveDirection.y = (int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W);

	MovePlayer(playerMoveDirection, angle,deltaTime);

	DrawPlayer();
}

void Player::DrawPlayer()
{
	if (!active)
		return;

	//DrawPolyLines(movableStats.position, 3, 64, movableStats.rotation, WHITE);
	const Rectangle source = { 0,0,32,32 };
	Rectangle dest = { movableStats.position.x,movableStats.position.y, 48,48};
	Vector2 origin = { dest.width / 2,dest.height / 2 };
	DrawTexturePro(playerTexture, source,dest,origin,movableStats.rotation + 90.0f,WHITE);
}

void Player::WarpPlayerBackToScreen()
{
	if (movableStats.position.x > gameScreenSize.x + playerRadius)
	{
		movableStats.position.x = -playerRadius;
		if (movableStats.velocity.x < playerWarpBackToScreenNudge)
		{
			movableStats.velocity.x = playerWarpBackToScreenNudge;
		}
	}
	else if (movableStats.position.x < -playerRadius)
	{
		movableStats.position.x = gameScreenSize.x + playerRadius;
		if (movableStats.velocity.x < playerWarpBackToScreenNudge)
		{
			movableStats.velocity.x = -playerWarpBackToScreenNudge;
		}
	}
	else if (movableStats.position.y > gameScreenSize.y + playerRadius)
	{
		movableStats.position.y = -playerRadius;
		if (movableStats.velocity.y < playerWarpBackToScreenNudge)
		{
			movableStats.velocity.y = playerWarpBackToScreenNudge;
		}
	}
	else if (movableStats.position.y < -playerRadius)
	{
		movableStats.position.y = gameScreenSize.y + playerRadius;
		if (movableStats.velocity.y < playerWarpBackToScreenNudge)
		{
			movableStats.velocity.y = -playerWarpBackToScreenNudge;
		}
	}
}

bool Player::GetPlayerStatus()
{
	return active;
}

void Player::MovePlayer(Vector2 playerMovement,float playerFaceDirection,float deltaTime)
{
	movableStats.rotation = playerFaceDirection;

	if (Vector2Length(playerMovement) > 0.0f)
	{
		Vector2 accelDir = Vector2Normalize(playerMovement);
		movableStats.velocity = Vector2Add(
			movableStats.velocity,
			Vector2Scale(accelDir, playerMovementAcceleration * deltaTime)
		);
	}
	else
	{
		movableStats.velocity = Vector2Scale(
			movableStats.velocity,
			1.0f - playerMovementFriction * deltaTime
		);
	}

	if (Vector2Length(movableStats.velocity) > playerMaxVelocity)
	{
		movableStats.velocity = Vector2Scale(
			Vector2Normalize(movableStats.velocity),
			playerMaxVelocity
		);
	}

	movableStats.Move(deltaTime);

	WarpPlayerBackToScreen();
}

void Player::Init()
{
	playerTexture = LoadTexture("Assets/Texture/ship.png");
}

bool Player::CanFire(float currentTime)
{
	bool canFire = false;

	if (currentTime > lastFireTime + playerFireRate)
	{
		canFire = true;
		lastFireTime = currentTime;
	}

	return canFire;
}

float Player::GetRadius()
{
	return playerTexture.height * 0.5f;
}

bool Player::CheckProjectileAsteroidCollision(Asteroid asteroid)
{
	if (!asteroid.GetAsteroidStatus())
		return false;

	float distance = Vector2Distance(movableStats.position, asteroid.movableStats.position);

	bool hit = distance < (GetRadius() + asteroid.GetRadius());

	if (hit)
	{
		PlayerHit();
	}

	return hit;
}

void Player::PlayerHit()
{
	playerHp--;

	if (playerHp <= 0)
	{
		active = false;
	}
}
