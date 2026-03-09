#include "ScoreManager.h"
#include "GameManager.h"
#include "raylib.h"
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
	}
	SaveHighScore();
	return HighestScore;
}

void ScoreManager::ResetScore()
{
	totalScore = 0;
}

void ScoreManager::Init()
{
	LoadHighScore();
}

void ScoreManager::LoadHighScore()
{
	std::ifstream saveFile("save.dat", std::ios::binary);

	if (saveFile.is_open())
	{
		saveFile.read((char*)&HighestScore, sizeof(HighestScore));
		saveFile.close();
	}
}

void ScoreManager::SaveHighScore()
{
	std::ofstream saveFile("save.dat", std::ios::binary);

	if (saveFile.is_open())
	{
		saveFile.write((char*)&HighestScore, sizeof(HighestScore));
		saveFile.close();
	}
}
