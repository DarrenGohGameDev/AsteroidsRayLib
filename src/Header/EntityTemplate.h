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

#pragma region MovementGetter function

		float GetEntityRotation() { return movement.rotation; }
		float GetEntityRotationSpeed() { return movement.rotationSpeed; }
		Vector2 GetEntityPosition() { return movement.position; }
		Vector2 GetEntityVelocity() { return movement.velocity; }

#pragma endregion

	protected:

		int entityHp = 3;

		float baseImmunityTimer = 3.0f;

		float immunityTimer;

		float baseLifeTime = 10.0f;

		float currentLifeTime = 0.0f;

		float creationTime;

		bool useEntityActiveTimer = true;

		bool debugMode = false;

		Movable movement;

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

	private:

		ENTITYSTATE currentEntityState = DISABLE;

		bool isChangingState = false;

};

