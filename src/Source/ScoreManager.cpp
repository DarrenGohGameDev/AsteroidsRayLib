#include "ScoreManager.h"
#include "GameManager.h"
#include "raylib.h"
#include "SaveManager.h"
#include <fstream>

ScoreManager::ScoreManager()
{
	GameManager::Get().GetDispatcher().sink<GameRestartRequest>().connect<&ScoreManager::ResetScore>(this);
	HighestScore = SaveManager::Get().GetSaveData().highestScore;
}

void ScoreManager::UpdateScore(int amount)
{
	totalScore += amount;
}

const int& ScoreManager::GetHighestScore()
{
	if (totalScore > HighestScore)
	{
		HighestScore = totalScore;
		SaveManager::Get().SavePlayerHighscore(HighestScore);
	}

	return HighestScore;
}

void ScoreManager::ResetScore()
{
	totalScore = 0;
}