#pragma once
#include "raylib.h"

struct Movable
{
	float rotation;
	float rotationSpeed;
	Vector2 position;
	Vector2 velocity;

	virtual void Move(Movable movable,float deltaTime);
};