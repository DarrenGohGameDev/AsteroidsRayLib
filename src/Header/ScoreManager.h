#pragma once
#include "GlobalManagerTemplate.h"

class ScoreManager : public GlobalManagerTemplate<ScoreManager>
{
public:

	void UpdateScore(int amount);

	void DrawScore();

private:

	int totalScore = 0;
};

