#pragma once
#include "GlobalManagerTemplate.h"
#include "GameManager.h"

class UIManager : public GlobalManagerTemplate<UIManager>
{
public :

	UIManager();

private:

	void ChangeGameUIBaseOnGameState(const OnGameStateChange& gameState);

	void DrawGameMenuUI();

	void DrawInGameUI();

	void DrawGamePauseUI();

	void DrawGameOverUI();

	void StopDrawingAllUI();
};

