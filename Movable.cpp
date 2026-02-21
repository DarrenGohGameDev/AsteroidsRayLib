#include "Movable.h"
#include "raymath.h"

void Movable::Move(Movable* movable, float deltaTime)
{
	movable->position = Vector2Add(movable->position, Vector2Scale(movable->velocity, deltaTime));
}
