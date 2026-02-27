#include "ScoreManager.h"
#include "raylib.h"

void ScoreManager::UpdateScore(int amount)
{
	totalScore += amount;
}

void ScoreManager::DrawScore()
{
	DrawText(TextFormat("Player Score:%d", totalScore), 300, 40, 32, WHITE);
}
