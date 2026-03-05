#pragma once
#include "GlobalManagerTemplate.h"
#include "entt/entt.hpp"

typedef enum GAMESTATE
{
	MENU = 0,
	PLAYING = 1,
	PAUSED = 2,
	GAMEOVER = 3,
};

struct OnGameStateChange 
{
	GAMESTATE oldState;
	GAMESTATE newState;
};

struct StartGameRequest{};

struct GameEndRequest {};

struct GamePauseRequest {};

struct GameRestartRequest {};

class GameManager : public GlobalManagerTemplate<GameManager>
{
	public:

		GameManager();

		entt::dispatcher& GetDispatcher() { return dispatcher; }

		GAMESTATE GetCurrentGameState() { return currentGameState; }

		float GetCurrentGameSpeed() { return gameSpeed; }

	private :

		GAMESTATE currentGameState;

		GAMESTATE prevGameState;

		entt::dispatcher dispatcher;

		float gameSpeed = 1.0f;

		void ChangeGameState(GAMESTATE newState);

		void OnStartGameRequest();

		void OnGameEndRequest();

		void OnGamePauseRequest();

		void OnGameRestartRequest();
};

