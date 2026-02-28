#pragma once

class EntityTemplate
{
	public:

		EntityTemplate();

		float baseLifeTime = 10.0f;

		float currentLifeTime = 0.0f;

		bool isPlayer = false;

		bool GetEntityActiveStatus();

		virtual void EntityUpdate(float deltaTime);

	private:

		bool active;
};

