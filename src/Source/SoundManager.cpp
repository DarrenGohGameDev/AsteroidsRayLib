#include "SoundManager.h"
#include "SaveManager.h"

void SoundManager::LoadSfxAssets()
{
	InitAudioDevice();
	playerShoot = LoadSound("Assets/Sound/laserLarge_000.ogg");
	playerHit = LoadSound("Assets/Sound/explosionCrunch_000.ogg");
	playerDeath = LoadSound("Assets/Sound/explosionCrunch_001.ogg");
	AsteroidHit = LoadSound("Assets/Sound/rumble1.ogg");
	BGM = LoadMusicStream("Assets/Sound/BGM.ogg");

	allSfx.push_back(playerShoot);
	allSfx.push_back(playerHit);
	allSfx.push_back(playerDeath);
	allSfx.push_back(AsteroidHit);

	sfxVolume = SaveManager::Get().GetSaveData().sfxVolume;
	bgmVolume = SaveManager::Get().GetSaveData().bgmVolume;
	SetBgmVolume(bgmVolume);
	SetSfxVolume(sfxVolume);
}

void SoundManager::SetSfxVolume(float value)
{
	sfxVolume = value;

	for (size_t i = 0; i < allSfx.size(); i++)
	{
		SetSoundVolume(allSfx[i], sfxVolume);
	}
	SaveManager::Get().SavePlayerSfxVolumeSettings(sfxVolume);
}

void SoundManager::SetBgmVolume(float value)
{
	bgmVolume = value;
	SetMusicVolume(BGM,bgmVolume);
	SaveManager::Get().SavePlayerBgmVolumeSettings(bgmVolume);
}

void SoundManager::PlayRandomSfx()
{
	int index = GetRandomValue(0, allSfx.size() - 1);
	PlaySound(allSfx[index]);
}
