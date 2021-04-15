#include "stdafx.h"
#include "AudioManager.h"

#include "MathHelper.h"

#include <tga2d/audio/audio.h>

#include <tga2d/audio/audio_out.h>

#include <algorithm>

#include <bass/bass.h>
#include <tga2d/audio/audio.h>

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#pragma comment(lib,"bass.lib")

AudioManager::AudioManager() 
{
    std::ifstream file("JSON/Sound-MusicPaths.json");
    nlohmann::json data = nlohmann::json::parse(file);

    for (std::string path : data.at("Music"))
    {
        myMusic[path] = std::make_unique<Tga2D::CAudio>();
        myMusic.at(path)->Init(path.c_str(), true);
    }
    for (std::string path : data.at("Sound"))
    {
        mySounds[path] = std::make_unique<Tga2D::CAudio>();
        mySounds.at(path)->Init(path.c_str(), false);
    }
}

AudioManager::~AudioManager()
{
    // NOTE: Free the Tga2D::AudioOut instance that is not freed by default by Tga2D...
    Tga2D::AudioOut*& audioOut = Tga2D::CAudio::GetAudioOut();
    if (audioOut != nullptr)
    {
        delete audioOut;
        audioOut = nullptr;
    }
}

void AudioManager::SetMasterVolume(float aVolume)
{
    myMasterVolume = MathHelper::Clamp(aVolume, 0.0f, 1.0f);

    SetSfxVolume(GetSfxVolume());
    SetMusicVolume(GetMusicVolume());
}

float AudioManager::GetMasterVolume() const
{
    return myMasterVolume;
}

void AudioManager::SetSfxVolume(float aVolume)
{
    mySfxVolume = std::clamp(aVolume, 0.0f, 1.0f);

    for (auto& song : mySounds)
    {
        song.second->SetVolume(GetAbsoluteMasterVolume() * mySfxVolume);
    }
}

float AudioManager::GetSfxVolume() const
{
    return mySfxVolume;
}

void AudioManager::SetMusicVolume(float aVolume)
{
    myMusicVolume = std::clamp(aVolume, 0.0f, 1.0f);

    for (auto& song : myMusic)
    {
        song.second->SetVolume(GetAbsoluteMasterVolume() * myMusicVolume);
    }
}

float AudioManager::GetMusicVolume() const
{
    return myMusicVolume;
}

void AudioManager::PlayMusic(const std::string& anAudioPath)
{
    myMusic.at(anAudioPath)->Play();
}

void AudioManager::PlaySfx(const std::string& anAudioPath)
{
    mySounds.at(anAudioPath)->Play();
}

void AudioManager::StopMusic(const std::string& anAudioPath)
{
    myMusic.find(anAudioPath)->second->Stop();
}

void AudioManager::StopSfx(const std::string& anAudioPath)
{
   mySounds.find(anAudioPath)->second->Stop();
}

bool AudioManager::IsPlaying(const std::string& /*anAudioPath*/)
{
    return false;
}

void AudioManager::StopAll()
{
    for (auto& song : myMusic)
    {
        song.second->Stop();
    }
}

float AudioManager::GetAbsoluteMasterVolume() const
{
    assert(ourMaxMasterAbsoluteVolume > 0.0f && ourMaxMasterAbsoluteVolume <= 1.0f);

    const float volumePercentage = MathHelper::Clamp(myMasterVolume, 0.0f, 1.0f);
    return MathHelper::Lerp(0.0f, ourMaxMasterAbsoluteVolume, volumePercentage);
}
