#include "Player.h"
#include "raymath.h"
#include "SoundManager.h"
#include "GameManager.h"

Player::Player()
{

}

Player::Player(Vector2 screenSize,Vector2 screenCenter)
{
	movement.rotation = 180;
	Vector2 spawnPosition = { screenCenter.x,screenCenter.y - 200.0f };
	movement.position = spawnPosition;
	playerSpawnPosition = spawnPosition;
	gameScreenSize = screenSize;
	useEntityActiveTimer = false;
	ChangeEntityState(ACTIVE);
	SetEntityRadius();
	playerTextureColor = WHITE;
}

void Player::EntityActiveStateEnter()
{
	playerTextureColor = WHITE;
}

void Player::EntityActiveStateUpdate(float deltaTime)
{
	PlayerMovement(deltaTime);
}

void Player::EntityInvulnerableStateEnter()
{
	immunityTimer = baseImmunityTimer;
	blinkTime = 0.0f;
}

void Player::EntityInvulnerableStateUpdate(float deltaTime)
{
	blinkTime += deltaTime;
	float alpha = (sinf(blinkTime * 20) + 1) / 2;
	Color tint = WHITE;
	tint.a = (unsigned char)(alpha * 255);
	playerTextureColor = tint;

	PlayerMovement(deltaTime);
	immunityTimer -= deltaTime;
	if (immunityTimer <= 0)
	{
		ChangeEntityState(ACTIVE);
	}
}

void Player::EntityInvulnerableStateExit()
{
	immunityTimer = baseImmunityTimer;
}

void Player::DrawEntity()
{
	if (GetCurrentEntityState() == DISABLE)
		return;

	const Rectangle source = { 0,0,32,32 };
	Rectangle dest = { movement.position.x,movement.position.y, 48,48};
	Vector2 origin = { dest.width / 2,dest.height / 2 };

	DrawTexturePro(playerTexture, source,dest,origin,movement.rotation + 90.0f, playerTextureColor);
}

void Player::WarpPlayerBackToScreen()
{
	if (movement.position.x > gameScreenSize.x + playerRadius)
	{
		movement.position.x = -playerRadius;
		if (movement.velocity.x < playerWarpBackToScreenNudge)
		{
			movement.velocity.x = playerWarpBackToScreenNudge;
		}
	}
	else if (movement.position.x < -playerRadius)
	{
		movement.position.x = gameScreenSize.x + playerRadius;
		if (movement.velocity.x < playerWarpBackToScreenNudge)
		{
			movement.velocity.x = -playerWarpBackToScreenNudge;
		}
	}
	else if (movement.position.y > gameScreenSize.y + playerRadius)
	{
		movement.position.y = -playerRadius;
		if (movement.velocity.y < playerWarpBackToScreenNudge)
		{
			movement.velocity.y = playerWarpBackToScreenNudge;
		}
	}
	else if (movement.position.y < -playerRadius)
	{
		movement.position.y = gameScreenSize.y + playerRadius;
		if (movement.velocity.y < playerWarpBackToScreenNudge)
		{
			movement.velocity.y = -playerWarpBackToScreenNudge;
		}
	}
}

void Player::PlayerMovement(float deltaTime)
{
	Vector2 playerMovement;

	Vector2 playerFaceDirection;

	playerFaceDirection = Vector2Subtract(GetMousePosition(), movement.position);

	float angle = atan2f(playerFaceDirection.y, playerFaceDirection.x) * RAD2DEG;

	playerMovement.x = (int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A);
	playerMovement.y = (int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W);

	movement.rotation = angle;

	//PlaySound(SoundManager::Get().playerMove);

	if (Vector2Length(playerMovement) > 0.0f)
	{
		Vector2 accelDir = Vector2Normalize(playerMovement);
		movement.velocity = Vector2Add(
			movement.velocity,
			Vector2Scale(accelDir, playerMovementAcceleration * deltaTime)
		);
	}
	else
	{
		movement.velocity = Vector2Scale(
			movement.velocity,
			1.0f - playerMovementFriction * deltaTime
		);
	}

	if (Vector2Length(movement.velocity) > playerMaxVelocity)
	{
		movement.velocity = Vector2Scale(
			Vector2Normalize(movement.velocity),
			playerMaxVelocity
		);
	}

	movement.Move(deltaTime);

	WarpPlayerBackToScreen();
}

void Player::LoadPlayerTexture()
{
	playerTexture = LoadTexture("Assets/Texture/ship.png");
}

bool Player::CanFire(float currentTime)
{
	bool canFire = false;

	if (GetCurrentEntityState() == DISABLE)
	{
		return false;
	}
	
	if (currentTime > lastFireTime + playerFireRate)
	{
		canFire = true;
		lastFireTime = currentTime;
	}

	return canFire;
}

void Player::SetEntityRadius()
{
	entityRadius = playerTexture.height * 0.5f;
}

void Player::EntityHit()
{
	if (GetCurrentEntityState() == INVULNERABLE)
		return;

	entityHp--;

	if (entityHp <= 0)
	{
		PlaySound(SoundManager::Get().playerDeath);
		GameManager::Get().GetDispatcher().trigger(GameEndRequest{});
		ChangeEntityState(DISABLE);
	}
	else
	{
		ChangeEntityState(INVULNERABLE);
	}
}

void Player::ShootLazer(float currentTime)
{
	if (GetCurrentEntityState() == DISABLE || GetCurrentEntityState() == PAUSE)
		return;

	PlaySound(SoundManager::Get().playerShoot);
	projectileManager.SpawnProjectile(GetEntityPosition(), GetEntityRotation(), currentTime);
}

void Player::ResetEntity()
{
	movement.rotation = 180;
	movement.position = playerSpawnPosition;
	ChangeEntityState(ACTIVE);
	entityHp = baseEntityHp;
	movement.rotationSpeed = 0;
	movement.velocity = Vector2Zero();
}
