#include "SaveManager.h"
#include <fstream>

void SaveManager::UpdateSaveData()
{
	SaveData data;

	data.highestScore = saveData.highestScore;
	data.sfxVolume = saveData.sfxVolume;
	data.bgmVolume = saveData.bgmVolume;

	std::ofstream saveFile("save.dat", std::ios::binary);

	if (saveFile.is_open())
	{
		saveFile.write((char*)&data, sizeof(data));
		saveFile.close();
	}
}

void SaveManager::LoadSaveData()
{
	SaveData data;

	std::ifstream saveFile("save.dat", std::ios::binary);

	if (saveFile.is_open())
	{
		saveFile.read((char*)&data, sizeof(data));
		saveFile.close();

		saveData.highestScore = data.highestScore;
		saveData.sfxVolume = data.sfxVolume;
		saveData.bgmVolume = data.bgmVolume;
	}
}

void SaveManager::SavePlayerHighscore(int score)
{
	saveData.highestScore = score;
	UpdateSaveData();
}

void SaveManager::SavePlayerSfxVolumeSettings(float sfx)
{
	saveData.sfxVolume = sfx;
	UpdateSaveData();
}

void SaveManager::SavePlayerBgmVolumeSettings(float bgm)
{
	saveData.bgmVolume = bgm;
	UpdateSaveData();
}
