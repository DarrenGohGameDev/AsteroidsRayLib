#pragma once
#include "Movable.h"

typedef enum ENTITYSTATE
{
	ACTIVE = 1,
	INVULNERABLE = 0,
	PAUSE = 2,
	DISABLE = -1,
};

class EntityTemplate
{
	public:

		EntityTemplate();

		ENTITYSTATE GetCurrentEntityState();

		void EntityUpdate(float deltaTime);

		void EntityLifeSpanCountdown(float deltaTime);

		virtual void DrawEntity();

		virtual void EntityHit();

		virtual float GetEntityRadius();

		virtual bool CheckEntityCollision(EntityTemplate * entity);

#pragma region STATES Enter / Update / Exit function

		virtual void EntityActiveStateEnter();
		virtual void EntityInvulnerableStateEnter();
		virtual void EntityPauseStateEnter();
		virtual void EntityDisableStateEnter();

		virtual void EntityActiveStateUpdate(float deltaTime);
		virtual void EntityInvulnerableStateUpdate(float deltaTime);
		virtual void EntityPauseStateUpdate(float deltaTime);
		virtual void EntityDisableStateUpdate(float deltaTime);

		virtual void EntityActiveStateExit();
		virtual void EntityInvulnerableStateExit();
		virtual void EntityPauseStateExit();
		virtual void EntityDisableStateExit();

		void ChangeEntityState(ENTITYSTATE state);

#pragma endregion

#pragma region MovementGetter function

		float GetEntityRotation() { return movement.rotation; }
		float GetEntityRotationSpeed() { return movement.rotationSpeed; }
		Vector2 GetEntityPosition() { return movement.position; }
		Vector2 GetEntityVelocity() { return movement.velocity; }

#pragma endregion

	protected:

		float baseLifeTime = 10.0f;

		float currentLifeTime = 0.0f;

		float creationTime;

		bool useEntityActiveTimer = true;

		Movable movement;

	private:

		ENTITYSTATE currentEntityState = DISABLE;

		bool isChangingState = false;

};

