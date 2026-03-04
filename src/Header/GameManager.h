#pragma once
#include "GlobalManagerTemplate.h"

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

class GameManager : public GlobalManagerTemplate<GameManager>
{
public:
	void ChangeGameState(GAMESTATE newState);

private :

	GAMESTATE currentGameState;
};

