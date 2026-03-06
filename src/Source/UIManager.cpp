#include "UIManager.h"
#include "raylib.h"
#include "ScoreManager.h"

UIManager::UIManager()
{

}

void UIManager::DrawCurrentStateUI()
{
	switch (GameManager::Get().GetCurrentGameState())
	{
	case MENU:
		DrawGameMenuUI();
		break;
	case PLAYING:
		DrawInGameUI();
		break;
	case PAUSED:
		DrawGamePauseUI();
		break;
	case GAMEOVER:
		DrawGameOverUI();
		break;
	default:
		break;
	}
}

void UIManager::DrawGameMenuUI()
{
	DrawCenteredText("Asteroid", 80, WHITE,{0.0f,-100.0f});

	DrawText("W A S D to Move ", 40, 450, 32, WHITE);
	DrawText("Left Click to Shoot ", 40, 500, 32, WHITE);
	DrawText("P to PAUSE ", 40, 400, 32, WHITE);
}

void UIManager::DrawInGameUI()
{
	DrawText(TextFormat("Player Score:%d", ScoreManager::Get().GetTotalScore()), 300, 40, 32, WHITE);
}

void UIManager::DrawGamePauseUI()
{
	DrawCenteredText("PAUSE", 80, WHITE, { 0.0f,0.0f });
	DrawCenteredText("PRESS P TO UNPAUSE", 40, WHITE, { 0.0f,80.0f });
}

void UIManager::DrawGameOverUI()
{
	DrawCenteredText("GAME OVER",80,WHITE, { 0.0f,-100.0f });
	DrawCenteredText("PRESS R TO RETRY",32,WHITE, { 0.0f,0.0f });
	DrawCenteredText(TextFormat("TOTAL SCORE:%d", ScoreManager::Get().GetTotalScore()),40,WHITE,{0.0f,100.0f});
	DrawCenteredText(TextFormat("HIGHEST SCORE:%d", ScoreManager::Get().GetHighestScore()),40,WHITE, { 0.0f,150.0f });
}

void UIManager::StopDrawingAllUI()
{

}

void UIManager::DrawCenteredText(const char* text, int fontSize, Color color, Vector2 padding)
{
	int textWidth = MeasureText(text, fontSize);

	float x = GameManager::Get().screenCenter.x - textWidth / 2;
	float y = GameManager::Get().screenCenter.y - fontSize / 2;

	DrawText(text, x+ padding.x, y + padding.y, fontSize, color);
}
