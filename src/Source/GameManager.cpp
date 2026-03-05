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

	GAMESTATE old = currentGameState;
	currentGameState = newState;

	dispatcher.trigger(OnGameStateChange{ old, newState });
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
		gameSpeed = 0.0f;
	}
	else
	{
		ChangeGameState(prevGameState);
		gameSpeed = 1.0f;
	}
	
}

void GameManager::OnGameRestartRequest()
{
	TraceLog(LOG_DEBUG, "restart game");
	ChangeGameState(PLAYING);
}

void GameManager::OnGameEndRequest()
{
	ChangeGameState(GAMEOVER);
}