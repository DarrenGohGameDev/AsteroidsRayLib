#include "ShootMeBtnEntity.h"
#include "GameManager.h"

ShootMeBtnEntity::ShootMeBtnEntity()
{
	movement.position = GameManager::Get().screenCenter;
	int textWidth = MeasureText(btnText, fontSize);
	btnWidth = textWidth + fontPadding;
	btnHeight = fontSize + fontPadding;
    SetEntityRadius();
}

void ShootMeBtnEntity::DrawEntity()
{
	float rectX = movement.position.x - btnWidth / 2;
    float rectY = movement.position.y - btnHeight / 2;

    DrawRectangleLines(rectX, rectY, btnWidth, btnHeight, WHITE);

    int textWidth = MeasureText(btnText, fontSize);

    float textX = rectX + (btnWidth - textWidth) / 2;
    float textY = rectY + (btnHeight - fontSize) / 2;

    DrawText(btnText, textX, textY, fontSize, DARKBLUE);
}

void ShootMeBtnEntity::EntityHit()
{
    GameManager::Get().GetDispatcher().trigger(StartGameRequest{});
	ChangeEntityState(DISABLE);
}

bool ShootMeBtnEntity::CheckEntityCollision(EntityTemplate* entity)
{
	if (!entity)
	{
		if (GameManager::Get().InDebugMode())
		{
			TraceLog(LOG_DEBUG, "Entity is null for checking collision");
		}
		return false;
	}

	if (entity->GetCurrentEntityState() == DISABLE)
		return false;

	bool hit = CheckCollisionCircleRec(
		entity->GetEntityPosition(),
		entity->GetEntityRadius(),
		GetEntityRect()
	);

	if (hit)
	{
		EntityHit();
	}

	return hit;
}

Rectangle ShootMeBtnEntity::GetEntityRect()
{
	return Rectangle{
		movement.position.x - btnWidth / 2,
		movement.position.y - btnHeight / 2,
		btnWidth,
		btnHeight
	};
}