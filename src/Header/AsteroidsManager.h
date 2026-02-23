#pragma once
#include "Asteroid.h"
#include "raylib.h"

#define maxAsteroids 64

class AsteroidsManager
{
	public : 

		void UpdateAllAsteroids(float deltaTIme, float currentTime, Vector2 screenSize, Vector2 screenCenter);

		void DrawAllAsteroids();

		void SpawnAsteeroid(Vector2 screenSize, Vector2 screenCenter);

		Asteroid _asteroids[maxAsteroids];

		AsteroidSize _asteroidsSize[3] = {ASTEROIDS_SMALL, ASTEROIDS_MEDIUM,ASTEROIDS_LARGE };

#pragma region DEBUGING

		const bool DebugingMode = false;

		Vector2 asteroidDebugSpawnLine0[2];

		Vector2 asteroidDebugSpawnLine1[2];

		Vector2 asteroidDebugSpawnLine2[2];

		void DrawDebugLine();

#pragma endregion

	private :

		const int asteroidRotSpeedMin = 5;

		const int asteroidRotSpeedMax = 240;

		const int asteroidMoveSpeedMin = 100;
		
		const int asteroidMoveSpeedMax = 300;

		const float asteroidRandomAngle = 30 * DEG2RAD;

		const float asteroidSpawnDelay = 5.25f;

		const Vector2 asteroidSpawnPadding = { 20,20 };

		float lastASteroidCreationTime = -1;

		Asteroid CreateAstroid(Vector2 screenSize, Vector2 screenCenter);

		Vector2 GetAsteroidSpawnPosition(Vector2 screenSize);
};

