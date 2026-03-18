#pragma once
#include "Movable.h"
#include "GameManager.h"

enum ENTITYSTATE
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

		virtual ~EntityTemplate();

		const ENTITYSTATE& GetCurrentEntityState() { return currentEntityState; }

		void EntityUpdate(float deltaTime);

		void EntityLifeSpanCountdown(float deltaTime);

		virtual void DrawEntity();

		virtual void EntityHit();

		virtual bool CheckEntityCollision(EntityTemplate * entity);

		const float& GetEntityRadius() { return entityRadius; }

		const int& GetEntityHp() { return entityHp; }

#pragma region MovementGetter function

		const float& GetEntityRotation() { return movement.rotation; }
		const float& GetEntityRotationSpeed() { return movement.rotationSpeed; }
		const Vector2& GetEntityPosition() { return movement.position; }
		const Vector2& GetEntityVelocity() { return movement.velocity; }

#pragma endregion

	protected:
		
		int baseEntityHp = 3;

		int entityHp;

		float baseImmunityTimer = 1.0f;

		float immunityTimer;

		float baseLifeTime = 10.0f;

		float currentLifeTime = 0.0f;

		float creationTime;

		float entityRadius;

		bool useEntityActiveTimer = true;

		bool debugMode = false;

		Movable movement;

		virtual void SetEntityRadius();

#pragma region STATES Enter / Update / Exit and state related function

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

		void OnGameManagerStateChange(const OnGameStateChange& state);

		virtual void ResetEntity();

#pragma endregion

	private:

		ENTITYSTATE currentEntityState = DISABLE;

		ENTITYSTATE prevEntityState;

		bool isChangingState = false;

};

