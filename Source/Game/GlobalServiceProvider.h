#pragma once

class AudioManager;
class JsonManager;
class GameMessenger;
class WeaponFactory;

class GlobalServiceProvider
{
public:

	GlobalServiceProvider(
		AudioManager* anAudioManager,
		JsonManager* aJsonManager,
		WeaponFactory* aWeaponFactory,

		GameMessenger* aGameMessenger
	);

	inline AudioManager* GetAudioManager() const { return myAudioManager; }
	inline JsonManager* GetJsonManager() const { return myJsonManager; };
	inline WeaponFactory* GetWeaponFactory() const { return myWeaponFactory; }
	
	inline GameMessenger* GetGameMessenger() const { return myGameMessenger; }

private:

	AudioManager* myAudioManager;
	JsonManager* myJsonManager;
	WeaponFactory* myWeaponFactory;

	GameMessenger* myGameMessenger;

};
