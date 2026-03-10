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
}

void SoundManager::SetSfxVolume(float value)
{
	sfxVolume = value;
	SetSoundVolume(playerShoot, sfxVolume);
	SetSoundVolume(playerHit, sfxVolume);
	SetSoundVolume(playerDeath, sfxVolume);
	SetSoundVolume(playerMove, sfxVolume);
	SetSoundVolume(AsteroidHit, sfxVolume);
}

void SoundManager::SetBgmVolume(float value)
{
	bgmVolume = value;
	SetMusicVolume(BGM,bgmVolume);
}

void SoundManager::PlaySfx(Sound sfx)
{
	SetSoundVolume(sfx, sfxVolume);
	PlaySound(sfx);
}
