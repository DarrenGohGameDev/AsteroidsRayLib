#pragma once
#include "raylib.h"

struct Movable
{
	public:

		float rotation;
		float rotationSpeed;
		Vector2 position;
		Vector2 velocity;

		virtual void Move(float deltaTime);
};