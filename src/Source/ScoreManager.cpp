#include "ScoreManager.h"
#include "GameManager.h"
#include "raylib.h"

ScoreManager::ScoreManager()
{
	GameManager::Get().GetDispatcher().sink<GameRestartRequest>().connect<&ScoreManager::ResetScore>(this);
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
	}

	return HighestScore;
}

void ScoreManager::ResetScore()
{
	totalScore = 0;
}
