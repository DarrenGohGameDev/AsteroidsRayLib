#include "Movable.h"
#include "raymath.h"

void Movable::Move(float deltaTime)
{
	position = Vector2Add(position, Vector2Scale(velocity, deltaTime));
}
