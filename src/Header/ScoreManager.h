#pragma once
#include "GlobalManagerTemplate.h"

class ScoreManager : public GlobalManagerTemplate<ScoreManager>
{
public:

	ScoreManager();

	void UpdateScore(int amount);

	const int& GetTotalScore() { return totalScore; }

	const int& GetHighestScore();

private:

	int totalScore = 0;

	int HighestScore = 0;

	void ResetScore();
};

