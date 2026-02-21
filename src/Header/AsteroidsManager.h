#pragma once
#include "Asteroid.h"
#include "raylib.h"

#define maxAsteroids 64

class AsteroidsManager
{
	public : 

		void UpdateAllAsteroids(float deltaTIme, float currentTime, Vector2 screenCenter,Vector2 screenSize);

		void DrawAllAsteroids();

		void SpawnAsteeroid(Vector2 screenCenter,Vector2 position);

		Asteroid _asteroids[maxAsteroids];

		AsteroidSize _asteroidsSize[3] = {ASTEROIDS_SMALL, ASTEROIDS_MEDIUM,ASTEROIDS_LARGE };

	private :

		const int asteroidRotSpeedMin = 5;

		const int asteroidRotSpeedMax = 240;

		const int asteroidMoveSpeedMin = 100;
		
		const int asteroidMoveSpeedMax = 300;

		const int asteroidRandomAngle = 30 * DEG2RAD;

		const float asteroidSpawnDelay = 0.25f;

		const Vector2 asteroidSpawnPadding = { 20,20 };

		float lastASteroidCreationTime = -1;

		const bool showAsteroidCount = true;

		Asteroid CreateAstroid(Vector2 screenSize, Vector2 screenCenter);

		Vector2 GetAsteroidSpawnPosition(Vector2 screenSize);
};

