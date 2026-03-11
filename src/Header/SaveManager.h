#pragma once
#include "GlobalManagerTemplate.h"

struct SaveData
{
    int highestScore;
    float sfxVolume;
    float bgmVolume;
};

class SaveManager : public GlobalManagerTemplate<SaveManager>
{
    public :

        void LoadSaveData();

        const SaveData& GetSaveData() { return saveData; }

        void SavePlayerHighscore(int score);

        void SavePlayerSfxVolumeSettings(float sfx);

        void SavePlayerBgmVolumeSettings(float bgm);

    private :

        SaveData saveData;

        void UpdateSaveData();
};

