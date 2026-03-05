#pragma once
#include "Asteroid.h"
#include "raylib.h"
#include <vector>

#define initialAsteroidsSpawnAmount 64

class AsteroidsManager
{
	public : 

		AsteroidsManager();

		void UpdateAllAsteroids(float deltaTIme, float currentTime, Vector2 screenSize, Vector2 screenCenter);

		void DrawAllAsteroids();

		void SpawnAsteeroid(Vector2 screenSize, Vector2 screenCenter, bool asteroidHitSpawn = false, AsteroidSize asteroidSize = ASTEROIDS_SMALL);

		std::vector<Asteroid>  _asteroids;

		AsteroidSize _asteroidsSize[3] = { ASTEROIDS_SMALL, ASTEROIDS_MEDIUM,ASTEROIDS_LARGE };

#pragma region DEBUGING

		const bool DebugingMode = true;

		Vector2 asteroidDebugSpawnLine0[2];

		Vector2 asteroidDebugSpawnLine1[2];

		Vector2 asteroidDebugSpawnLine2[2];

		void DrawDebugLine();

#pragma endregion

	private :

#pragma region CREATE ASTEROID SETTING

		const int asteroidRotSpeedMin = 5;

		const int asteroidRotSpeedMax = 240;

		const int asteroidMoveSpeedMin = 50;

		const int asteroidMoveSpeedMax = 150;

		const int asteroidSpawnRotationMin = 0;

		const int asteroidSpawnRotationMax = 360;

		const float asteroidRandomAngle = 30 * DEG2RAD;

		const float asteroidSpawnDelay = 5.25f;

		const Vector2 asteroidSpawnPadding = { 20,20 };

		float lastASteroidCreationTime = -1;

#pragma endregion

		void CreateAstroid(Asteroid* inactiveAsteroid,Vector2 screenSize, Vector2 screenCenter, bool asteroidHitSpawn, AsteroidSize asteroidSize);

		Vector2 GetAsteroidSpawnPosition(Vector2 screenSize, bool asteroidHitSpawn);
};

