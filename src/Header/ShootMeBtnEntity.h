#pragma once
#include "EntityTemplate.h"

class ShootMeBtnEntity : public EntityTemplate
{
public: 

	ShootMeBtnEntity();

	void DrawEntity() override;

	void EntityHit() override;

protected:

	void SetEntityRadius() override;

private:

	const char* btnText = "Shoot me to start the game";

	float btnWidth;

	float btnHeight;

	int fontSize = 20;

	float fontPadding = 20.0f;
};

