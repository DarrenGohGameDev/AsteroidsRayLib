#pragma once
#include "GlobalManagerTemplate.h"
#include "GameManager.h"
#include "Player.h"
#include "ShootMeBtnEntity.h"

class UIManager : public GlobalManagerTemplate<UIManager>
{
public :

	UIManager();

	ShootMeBtnEntity shootMeBtn;

	void DrawCurrentStateUI();

	void SetPlayer(Player* player);


private:

	Player* playerStat;


	void DrawGameMenuUI();

	void DrawInGameUI();

	void DrawGamePauseUI();

	void DrawGameOverUI();

	void StopDrawingAllUI();

	void DrawTutorialText();

	void DrawCenteredText(const char* text, int fontSize, Color color, Vector2 padding = {0.0f,0.0f});
};

