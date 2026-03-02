#include "EntityTemplate.h"

EntityTemplate::EntityTemplate()
{
	currentLifeTime = baseLifeTime;
	active = true;
}

bool EntityTemplate::GetEntityActiveStatus()
{
	return active;
}

void EntityTemplate::EntityUpdate(float deltaTime)
{
	if (isPlayer)
		return;

	currentLifeTime -= deltaTime;
	if (currentLifeTime <= 0)
	{
		active = false;
	}
}

void EntityTemplate::DrawEntity()
{

}
