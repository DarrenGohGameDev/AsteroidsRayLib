#include "Movable.h"
#include "raymath.h"
#include "GameManager.h"

void Movable::Move(float deltaTime)
{
	position = Vector2Add(position, Vector2Scale(velocity, deltaTime * GameManager::Get().GetCurrentGameSpeed()));
}
