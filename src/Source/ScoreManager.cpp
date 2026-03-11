#include "ScoreManager.h"
#include "GameManager.h"
#include "raylib.h"
#include "SaveManager.h"
#include <fstream>

ScoreManager::ScoreManager()
{
	GameManager::Get().GetDispatcher().sink<GameRestartRequest>().connect<&ScoreManager::ResetScore>(this);
	Init();
}

void ScoreManager::UpdateScore(int amount)
{
	totalScore += amount;
}

int ScoreManager::GetHighestScore()
{
	if (totalScore > HighestScore)
	{
		HighestScore = totalScore;
		SaveManager::Get().SavePlayerHighscore(HighestScore);
	}

	return HighestScore;
}

void ScoreManager::Init()
{
	HighestScore = SaveManager::Get().GetSaveData().highestScore;
}

void ScoreManager::ResetScore()
{
	totalScore = 0;
}