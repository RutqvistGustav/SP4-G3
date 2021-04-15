#pragma once
#include <vector>
#include <string>
#include <memory>
#include <map>

namespace Tga2D
{
	class CAudio;
}

class AudioManager
{
public:

	AudioManager();
	~AudioManager();

	void SetMasterVolume(float aVolume);
	float GetMasterVolume() const;

	void SetSfxVolume(float aVolume);
	float GetSfxVolume() const;

	void SetMusicVolume(float aVolume);
	float GetMusicVolume() const;

	void PlayMusic(const std::string& anAudioPath);
	void PlaySfx(const std::string& anAudioPath);

	void StopMusic(const std::string& anAudioPath);
	void StopSfx(const std::string& anAudioPath);

	bool IsPlaying(const std::string& anAudioPath);

	void StopAll();

private:

	float GetAbsoluteMasterVolume() const;

private:
	static constexpr float ourMaxMasterAbsoluteVolume = 0.2f;

	float myMasterVolume{};
	float myMusicVolume{};
	float mySfxVolume{};

	std::map<std::string, std::unique_ptr<Tga2D::CAudio>> myMusic;
	std::map<std::string, std::unique_ptr<Tga2D::CAudio>> mySounds;

};
