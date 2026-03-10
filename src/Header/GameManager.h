#pragma once
#include "GlobalManagerTemplate.h"
#include "raylib.h"
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

		const float screenWidth = 600.0f;

		const float screenHeight = 600.0f;

		const Vector2 screenSize = { screenWidth,screenHeight };

		const Vector2 screenCenter = { screenWidth / 2,screenHeight / 2 };

		GameManager();

		entt::dispatcher& GetDispatcher() { return dispatcher; }

		GAMESTATE GetCurrentGameState() { return currentGameState; }

		float GetCurrentGameSpeed() { return gameSpeed; }

		bool InDebugMode() { return true; }

	private :

		GAMESTATE currentGameState;

		GAMESTATE prevGameState;

		entt::dispatcher dispatcher;

		float gameSpeed = 1.0f;

		bool isChangingState = false;

		void ChangeGameState(GAMESTATE newState);

		void OnStartGameRequest();

		void OnGameEndRequest();

		void OnGamePauseRequest();

		void OnGameRestartRequest();
};

