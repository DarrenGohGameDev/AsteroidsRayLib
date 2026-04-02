#pragma once
#include "GlobalManagerTemplate.h"
#include "GameManager.h"
#include "Player.h"
#include "ShootMeBtnEntity.h"

class UIManager : public GlobalManagerTemplate<UIManager>
{
public :

	UIManager();

	ShootMeBtnEntity shootMeBtn;

	void DrawCurrentGameStateUI();

	void SetPlayer(Player* player);

private:

	Player* playerStat = nullptr;

	float sfxSliderValue = 1.0f;

	float bgmSliderValue = 1.0f;

	float lastTestSfxPlayed = 0.0f;

	float prevSfxVolume = 0.0f;

	void DrawGameMenuUI();

	void DrawInGameUI();

	void DrawGamePauseUI();

	void DrawGameOverUI();

	void DrawTutorialText();

	void DrawSettingUI();

	void DrawSliderWithPaddingAndCustomText(float sliderWidth, float sliderHeight ,float sliderXpos ,float sliderYpose ,float * value ,float sliderMinValue ,float sliderMaxValue ,const char* labelText ,int fontSize ,Vector2 labelTextPadding ,Vector2 displayTextPadding ,Color labelTextColor ,Color displayTextColor);

	void DrawCenteredText(const char* text ,int fontSize ,Color color ,Vector2 padding = {0.0f,0.0f});
};

