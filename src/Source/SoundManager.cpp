#include "SoundManager.h"

void SoundManager::LoadSfxAssets()
{
	InitAudioDevice();
	playerShoot = LoadSound("Assets/Sound/CoinCollect.ogg");
	playerHit = LoadSound("Assets/Sound/CoinCollect.ogg");
	playerDeath = LoadSound("Assets/Sound/CoinCollect.ogg");
	playerMove = LoadSound("Assets/Sound/CoinCollect.ogg");
	AsteroidHit = LoadSound("Assets/Sound/CoinCollect.ogg");
	BGM = LoadMusicStream("Assets/Sound/BGM.ogg");

	allSfx.push_back(playerShoot);
	allSfx.push_back(playerHit);
	allSfx.push_back(playerDeath);
	allSfx.push_back(playerMove);
	allSfx.push_back(AsteroidHit);
}

void SoundManager::SetSfxVolume(float value)
{
	sfxVolume = value;

	for (size_t i = 0; i < allSfx.size(); i++)
	{
		SetSoundVolume(allSfx[i], sfxVolume);
	}
}

void SoundManager::SetBgmVolume(float value)
{
	bgmVolume = value;
	SetMusicVolume(BGM,bgmVolume);
}

void SoundManager::PlayRandomSfx()
{
	int index = GetRandomValue(0, allSfx.size() - 1);
	PlaySound(allSfx[index]);
}
