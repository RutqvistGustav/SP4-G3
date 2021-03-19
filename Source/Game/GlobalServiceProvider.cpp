#include "stdafx.h"
#include "GlobalServiceProvider.h"

GlobalServiceProvider::GlobalServiceProvider(
	AudioManager* anAudioManager,
	JsonManager* aJsonManager,
	WeaponFactory* aWeaponFactory,

	GameMessenger* aGameMessenger) :
	myAudioManager(anAudioManager),
	myJsonManager(aJsonManager),
	myWeaponFactory(aWeaponFactory),

	myGameMessenger(aGameMessenger)
{}
