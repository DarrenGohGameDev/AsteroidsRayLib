#pragma once
#include "Asteroid.h"
#include "raylib.h"

#define maxAsteroids 64

class AsteroidsManager
{

	Asteroid CreateAstroid(Vector2 position,Vector2 velocity,AsteroidSize size);

	public : 

		void UpdateAllAsteroids(float deltaTIme);

		void DrawAllAsteroids();

		void SpawnAsteeroid(Vector2 position, Vector2 velocity);

		Asteroid _asteroids[maxAsteroids];

		AsteroidSize _asteroidsSize[3] = {ASTEROIDS_SMALL, ASTEROIDS_MEDIUM,ASTEROIDS_LARGE };

	private :

		const int asteroidRotSpeedMin = 5;

		const int asteroidRotSpeedMax = 240;


};

