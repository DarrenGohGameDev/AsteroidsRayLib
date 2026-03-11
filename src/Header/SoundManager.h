#pragma once
#include "raylib.h"
#include "GlobalManagerTemplate.h"
#include <vector>

class SoundManager : public GlobalManagerTemplate<SoundManager>
{
public :

	void LoadSfxAssets();

	float GetSfxVolume() { return sfxVolume; }
	float GetBgmVolume() { return bgmVolume; }

	void SetSfxVolume(float value);
	void SetBgmVolume(float value);

	void PlayRandomSfx();

	std::vector<Sound> allSfx;

	Sound playerShoot;
	Sound playerHit;
	Sound playerDeath;
	Sound playerMove;
	
	Sound AsteroidHit;

	Music BGM;

private :

	float sfxVolume = 1.0f;
	float bgmVolume = 1.0f;
};

