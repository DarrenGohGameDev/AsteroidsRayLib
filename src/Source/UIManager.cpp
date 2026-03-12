#include "UIManager.h"
#include "raylib.h"
#include "ScoreManager.h"
#include "raygui.h"
#include "SoundManager.h"

UIManager::UIManager()
{
	sfxSliderValue = SoundManager::Get().GetSfxVolume();
	bgmSliderValue = SoundManager::Get().GetBgmVolume();
}

void UIManager::DrawCurrentGameStateUI()
{
	switch (GameManager::Get().GetCurrentGameState())
	{
	case MENU:
		DrawGameMenuUI();
		break;
	case PLAYING:
		DrawInGameUI();
		break;
	case PAUSED:
		DrawGamePauseUI();
		break;
	case GAMEOVER:
		DrawGameOverUI();
		break;
	default:
		break;
	}
}

void UIManager::SetPlayer(Player* player)
{
	playerStat = player;
}

void UIManager::DrawGameMenuUI()
{
	DrawCenteredText("Asteroid", 80, WHITE,{0.0f,-100.0f});
	DrawTutorialText();

	shootMeBtn.DrawEntity();
}

void UIManager::DrawInGameUI()
{
	DrawText(TextFormat("Player HP:%d", playerStat->GetEntityHp()), 40, 40, 32, WHITE);
	DrawText(TextFormat("Player Score:%d", ScoreManager::Get().GetTotalScore()), 300, 40, 32, WHITE);
}

void UIManager::DrawGamePauseUI()
{
	DrawCenteredText("PAUSE", 80, WHITE, { 0.0f,-80.0f });
	DrawCenteredText("PRESS P TO UNPAUSE", 40, WHITE, { 0.0f,-20.0f });
	DrawSettingUI();
	DrawTutorialText();
}

void UIManager::DrawGameOverUI()
{
	DrawCenteredText("GAME OVER",80,WHITE, { 0.0f,-100.0f });
	DrawCenteredText("PRESS R TO RETRY",32,WHITE, { 0.0f,0.0f });
	DrawCenteredText(TextFormat("TOTAL SCORE:%d", ScoreManager::Get().GetTotalScore()),40,WHITE,{0.0f,100.0f});
	DrawCenteredText(TextFormat("HIGHEST SCORE:%d", ScoreManager::Get().GetHighestScore()),40,WHITE, { 0.0f,150.0f });
}

void UIManager::DrawTutorialText()
{
	DrawText("W A S D to Move ", 40, 400, 32, WHITE);
	DrawText("Mouse to Aim ", 40, 450, 32, WHITE);
	DrawText("Left Click to Shoot ", 40, 500, 32, WHITE);
	DrawText("P to PAUSE & SETTINGS", 40, 550, 32, WHITE);
}

void UIManager::DrawSettingUI()
{
	float sliderWidth = 300.0f;
	float sliderHeight = 20.0f;
	float sliderXpos = GameManager::Get().screenCenter.x - sliderWidth / 2;
	float sliderYpose = GameManager::Get().screenCenter.y - sliderHeight / 2;
	
	prevSfxVolume = sfxSliderValue;

	DrawSliderWithPaddingAndCustomText(sliderWidth, sliderHeight, sliderXpos, sliderYpose + 20, &sfxSliderValue, 0.0f, 1.0f, "Sfx Volume", 15,{10.0f, 2.0f}, { 10.0f, 2.0f }, WHITE, WHITE);
	DrawSliderWithPaddingAndCustomText(sliderWidth, sliderHeight, sliderXpos, sliderYpose + 50, &bgmSliderValue, 0.0f, 1.0f, "Bgm Volume", 15,{10.0f, 2.0f}, { 10.0f, 2.0f }, WHITE, WHITE);

	SoundManager::Get().SetSfxVolume(sfxSliderValue);
	SoundManager::Get().SetBgmVolume(bgmSliderValue);

	if (sfxSliderValue != prevSfxVolume && GetTime() > lastTestSfxPlayed + 0.5f)
	{
		SoundManager::Get().PlayRandomSfx();
		lastTestSfxPlayed = GetTime();
	}
}

void UIManager::DrawSliderWithPaddingAndCustomText(float sliderWidth, float sliderHeight, float sliderXpos, float sliderYpose, float* value, float sliderMinValue, float sliderMaxValue, const char* labelText, int fontSize, Vector2 labelTextPadding, Vector2 displayTextPadding, Color labelTextColor, Color displayTextColor)
{
	GuiSlider(
		Rectangle{ sliderXpos, sliderYpose, sliderWidth, sliderHeight },
		"",
		"",
		value,
		sliderMinValue,
		sliderMaxValue
	);

	float labelTextWidth = MeasureText(labelText, fontSize) + labelTextPadding.x;

	DrawText(labelText, sliderXpos - labelTextWidth, sliderYpose + labelTextPadding.y, fontSize, labelTextColor);

	DrawText(TextFormat("%.2f", *value), sliderXpos + sliderWidth + displayTextPadding.x, sliderYpose + displayTextPadding.y, fontSize, displayTextColor);
}

void UIManager::DrawCenteredText(const char* text ,int fontSize , Color color ,Vector2 padding)
{
	int textWidth = MeasureText(text, fontSize);

	float x = GameManager::Get().screenCenter.x - textWidth / 2;
	float y = GameManager::Get().screenCenter.y - fontSize / 2;

	DrawText(text, x+ padding.x, y + padding.y, fontSize, color);
}
