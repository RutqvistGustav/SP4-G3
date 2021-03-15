#pragma once

#include <string>
#include <memory>

namespace Tga2D
{
	class AudioOut;
}

class AudioManager
{
public:

	AudioManager();
	~AudioManager();

	void SetMasterVolume(float aVolume);
	float GetMasterVolume() const;

	void Play(const std::string& anAudioPath, float aVolume = 1.0f, bool aShouldLoop = false);
	void Stop(const std::string& anAudioPath);

	bool IsPlaying(const std::string& anAudioPath);

	void StopAll(bool anOnlyRepeating = false);

private:

	std::unique_ptr<Tga2D::AudioOut> myAudioOut;

};
