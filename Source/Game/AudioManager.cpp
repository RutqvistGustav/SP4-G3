#include "stdafx.h"
#include "AudioManager.h"

#include <tga2d/audio/audio_out.h>

#include <algorithm>

#include <bass/bass.h>

#pragma comment(lib,"bass.lib")

AudioManager::AudioManager() :
    myAudioOut(std::make_unique<Tga2D::AudioOut>())
{}

AudioManager::~AudioManager() = default;

void AudioManager::SetMasterVolume(float aVolume)
{
    const DWORD volume = static_cast<DWORD>(std::clamp(aVolume, 0.0f, 1.0f) * 10000.0f);
    BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, volume);
}

float AudioManager::GetMasterVolume() const
{
    return static_cast<float>(BASS_GetConfig(BASS_CONFIG_GVOL_SAMPLE)) / 10000.0f;
}

void AudioManager::SetSfxVolume(float aVolume)
{
    // TODO: Implement
}

float AudioManager::GetSfxVolume() const
{
    // TODO: Implement
    return 0.0f;
}

void AudioManager::SetMusicVolume(float aVolume)
{
    // TODO: Implement
}

float AudioManager::GetMusicVolume() const
{
    // TODO: Implement
    return 0.0f;
}

void AudioManager::Play(const std::string& anAudioPath, float aVolume, bool aShouldLoop)
{
    Tga2D::AudioOut::Handle channel;

    myAudioOut->Play(anAudioPath, false, channel);
    myAudioOut->SetVolume(channel, aVolume);

    if (aShouldLoop)
    {
        BASS_ChannelFlags(channel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
    }
}

void AudioManager::Stop(const std::string& anAudioPath)
{
    myAudioOut->Stop(anAudioPath, true);
}

bool AudioManager::IsPlaying(const std::string& anAudioPath)
{
    return Tga2D::audio_helpers::IsNowPlaying(*myAudioOut, anAudioPath);
}

void AudioManager::StopAll(bool anOnlyRepeating)
{
    Tga2D::audio_helpers::StopAllNowPlaying(*myAudioOut, anOnlyRepeating);
}
