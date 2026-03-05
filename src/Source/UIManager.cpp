#include "UIManager.h"

UIManager::UIManager()
{
	GameManager::Get().GetDispatcher().sink<OnGameStateChange>().connect<&UIManager::ChangeGameUIBaseOnGameState>(this);
}

void UIManager::ChangeGameUIBaseOnGameState(const OnGameStateChange& gameState)
{
	StopDrawingAllUI();

	switch (gameState.newState)
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
}

void UIManager::DrawInGameUI()
{
}

void UIManager::DrawGamePauseUI()
{
}

void UIManager::DrawGameOverUI()
{
}

void UIManager::StopDrawingAllUI()
{

}
