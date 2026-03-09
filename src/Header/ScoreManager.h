#pragma once
#include "GlobalManagerTemplate.h"

class ScoreManager : public GlobalManagerTemplate<ScoreManager>
{
public:

	ScoreManager();

	void UpdateScore(int amount);

	int GetTotalScore() { return totalScore; }

	int GetHighestScore();

private:

	int totalScore = 0;

	int HighestScore = 0;

	void ResetScore();

	void Init();

	void LoadHighScore();

	void SaveHighScore();
};

