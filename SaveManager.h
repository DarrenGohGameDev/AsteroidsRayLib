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

        SaveManager();

        void UpdateSaveData();

        SaveData GetSaveData() { return saveData; }

    private :

        SaveData saveData;

        void LoadSaveData();
};

