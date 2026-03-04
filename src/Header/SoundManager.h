#pragma once
#include "raylib.h"
#include "GlobalManagerTemplate.h"

class SoundManager : public GlobalManagerTemplate<SoundManager>
{
public :

	void LoadSfxAssets();

	Sound playerShoot;
	Sound playerHit;
	Sound playerDeath;
	Sound playerMove;
	
	Sound AsteroidHit;

	Music BGM;
};

