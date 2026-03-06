#pragma once
#include "GlobalManagerTemplate.h"
#include "GameManager.h"

class UIManager : public GlobalManagerTemplate<UIManager>
{
public :

	UIManager();

	void DrawCurrentStateUI();
private:

	void DrawGameMenuUI();

	void DrawInGameUI();

	void DrawGamePauseUI();

	void DrawGameOverUI();

	void StopDrawingAllUI();

	void DrawCenteredText(const char* text, int fontSize, Color color, Vector2 padding = {0.0f,0.0f});
};

