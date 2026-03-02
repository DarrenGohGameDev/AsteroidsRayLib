#include "projectile.h"
#include "raymath.h"

Projectile::Projectile()
{
	active = false;
}

Projectile::Projectile(Vector2 spawnPosition, float spawnRotation, float creeatedTime)
{
	movableStats.position = spawnPosition;
	movableStats.rotation = spawnRotation;
	creationTime = creeatedTime;
	active = true;
}

void Projectile::EntityUpdate(float deltaTime)
{
	if (!active)
		return;

	float radians = movableStats.rotation * DEG2RAD;

	Vector2 direction = {
		cosf(radians),
		sinf(radians)
	};

	movableStats.velocity = Vector2Scale(direction, projectileSpeed);
	movableStats.position.x += direction.x * projectileSpeed * deltaTime;
	movableStats.position.y += direction.y * projectileSpeed * deltaTime;

	if (GetTime() > creationTime + currentLifeTime)
	{
		active = false;
	}

	DrawProjectile();
}

void Projectile::DrawProjectile()
{
	if (!active)
		return;

	Rectangle rect = { movableStats.position.x,movableStats.position.y,projectileThicknes,projectileLength };
	Vector2 origin = { rect.width / 2,rect.height / 2 };

	DrawRectanglePro(rect, origin, movableStats.rotation +90.0f, BLUE);
}

bool Projectile::GetProjectileStatus()
{
	return active;
}

float Projectile::GetRadius()
{
	return projectileLength * 0.5f;
}

bool Projectile::CheckProjectileAsteroidCollision(Asteroid asteroid)
{
	if (!asteroid.GetAsteroidStatus())
		return false;

	float distance = Vector2Distance(movableStats.position, asteroid.movableStats.position);

	bool hit = distance < (GetRadius() + asteroid.GetRadius());

	if (hit)
	{
		active = false;
	}

	return hit;
}
