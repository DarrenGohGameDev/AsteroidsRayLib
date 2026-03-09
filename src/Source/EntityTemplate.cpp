#include "EntityTemplate.h"
#include "raymath.h"
#include "GameManager.h"

EntityTemplate::EntityTemplate()
{
	currentLifeTime = baseLifeTime;
	currentEntityState = DISABLE;
	entityHp = baseEntityHp;
	SetEntityRadius();
	GameManager::Get().GetDispatcher().sink<GamePauseRequest>().connect<&EntityTemplate::OnEntityPause>(this);
	GameManager::Get().GetDispatcher().sink<GameRestartRequest>().connect<&EntityTemplate::ResetEntity>(this);
}

ENTITYSTATE EntityTemplate::GetCurrentEntityState()
{
	return currentEntityState;
}

void EntityTemplate::EntityUpdate(float deltaTime)
{
	if (GetCurrentEntityState() == DISABLE)
		return;

	if (isChangingState)
		return;

	switch (currentEntityState)
	{
		case ACTIVE:
			EntityActiveStateUpdate(deltaTime);
			break;
		case INVULNERABLE:
			EntityInvulnerableStateUpdate(deltaTime);
			break;
		case PAUSE:
			EntityPauseStateUpdate(deltaTime);
			break;
		case DISABLE:
			EntityDisableStateUpdate(deltaTime);
			break;
		default:
			break;
	}

	EntityLifeSpanCountdown(deltaTime);
}

void EntityTemplate::EntityLifeSpanCountdown(float deltaTime)
{
	if (!useEntityActiveTimer)
		return;

	if (GameManager::Get().GetCurrentGameState() == PAUSED)
		return;

	currentLifeTime -= deltaTime;
	if (currentLifeTime <= 0)
	{
		ChangeEntityState(DISABLE);
	}
}

void EntityTemplate::DrawEntity()
{
}

void EntityTemplate::EntityHit()
{
}

float EntityTemplate::GetEntityRadius()
{
	return entityRadius;
}

void EntityTemplate::SetEntityRadius()
{
	
}

bool EntityTemplate::CheckEntityCollision(EntityTemplate* entity)
{
	if (!entity)
	{
		TraceLog(LOG_DEBUG, "Entity is null for checking collision");
		return false;
	}

	if (entity->GetCurrentEntityState() == DISABLE)
		return false;

	float distance = Vector2Distance(GetEntityPosition(), entity->GetEntityPosition());

	bool hit = distance < (GetEntityRadius() + entity->GetEntityRadius());

	if (hit)
	{
		EntityHit();
	}

	
	return hit;
}

#pragma region STATES Enter / Update / Exit function

	void EntityTemplate::EntityActiveStateEnter()
	{

	}

	void EntityTemplate::EntityInvulnerableStateEnter()
	{

	}

	void EntityTemplate::EntityPauseStateEnter()
	{

	}

	void EntityTemplate::EntityDisableStateEnter()
	{

	}

	void EntityTemplate::EntityActiveStateUpdate(float deltaTime)
	{

	}

	void EntityTemplate::EntityInvulnerableStateUpdate(float deltaTime)
	{

	}

	void EntityTemplate::EntityPauseStateUpdate(float deltaTime)
	{

	}

	void EntityTemplate::EntityDisableStateUpdate(float deltaTime)
	{

	}

	void EntityTemplate::EntityActiveStateExit()
	{

	}

	void EntityTemplate::EntityInvulnerableStateExit()
	{

	}

	void EntityTemplate::EntityPauseStateExit()
	{

	}

	void EntityTemplate::EntityDisableStateExit()
	{

	}

	void EntityTemplate::OnEntityPause()
	{
		if (currentEntityState != PAUSE)
		{
			prevEntityState = currentEntityState;
			ChangeEntityState(PAUSE);
		}
		else
		{
			ChangeEntityState(prevEntityState);
		}
	}

	void EntityTemplate::ResetEntity()
	{

	}

#pragma endregion



void EntityTemplate::ChangeEntityState(ENTITYSTATE state)
{
	if (currentEntityState == state)
		return;

	isChangingState = true;

	switch (currentEntityState)
	{
		case ACTIVE:
			EntityActiveStateExit();
			break;
		case INVULNERABLE:
			EntityInvulnerableStateExit();
			break;
		case PAUSE:
			EntityPauseStateExit();
			break;
		case DISABLE:
			EntityDisableStateExit();
			break;
	}

	switch (state)
	{
	case ACTIVE:
		EntityActiveStateEnter();
		break;
	case INVULNERABLE:
		EntityInvulnerableStateEnter();
		break;
	case PAUSE:
		EntityPauseStateEnter();
		break;
	case DISABLE:
		EntityDisableStateEnter();
		break;
	}
	currentEntityState = state;
	isChangingState = false;
}


