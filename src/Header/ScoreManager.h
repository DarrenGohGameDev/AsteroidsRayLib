#pragma once
#include "GlobalManagerTemplate.h"

class ScoreManager : public GlobalManagerTemplate<ScoreManager>
{
public:

	void ChangeScore(int amount);

private:
	int totalScore = 0;
};

