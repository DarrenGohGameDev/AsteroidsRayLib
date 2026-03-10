#include "GameManager.h"
#include "raylib.h"

GameManager::GameManager()
{
	currentGameState = MENU;

	dispatcher.sink<StartGameRequest>().connect<&GameManager::OnStartGameRequest>(this);
	dispatcher.sink<GamePauseRequest>().connect<&GameManager::OnGamePauseRequest>(this);
	dispatcher.sink<GameEndRequest>().connect<&GameManager::OnGameEndRequest>(this);
	dispatcher.sink<GameRestartRequest>().connect<&GameManager::OnGameRestartRequest>(this);
}

void GameManager::ChangeGameState(GAMESTATE newState)
{
	if (currentGameState == newState)
		return;

	if (isChangingState)
		return;

	isChangingState = true;

	GAMESTATE old = currentGameState;
	currentGameState = newState;

	gameSpeed = (newState == PAUSED) ? 0.0f : 1.0f;

	if (InDebugMode())
	{
		switch (newState)
		{
		case MENU:
			TraceLog(LOG_DEBUG, "Change game state to menu");
			break;
		case PLAYING:
			TraceLog(LOG_DEBUG, "Change game state to playing");
			break;
		case PAUSED:
			TraceLog(LOG_DEBUG, "Change game state to paused");
			break;
		case GAMEOVER:
			TraceLog(LOG_DEBUG, "Change game state to game over");
			break;
		}
	}

	dispatcher.trigger(OnGameStateChange{ old, newState });
	isChangingState = false;
}

void GameManager::OnStartGameRequest()
{
	ChangeGameState(PLAYING);
}

void GameManager::OnGamePauseRequest()
{
	if (currentGameState != PAUSED)
	{
		prevGameState = currentGameState;
		ChangeGameState(PAUSED);
	}
	else
	{
		ChangeGameState(prevGameState);
	}
	
}

void GameManager::OnGameRestartRequest()
{
	ChangeGameState(PLAYING);
}

void GameManager::OnGameEndRequest()
{
	ChangeGameState(GAMEOVER);
}