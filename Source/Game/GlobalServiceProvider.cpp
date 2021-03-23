#include "stdafx.h"
#include "GlobalServiceProvider.h"

GlobalServiceProvider::GlobalServiceProvider(
	AudioManager* anAudioManager,
	JsonManager* aJsonManager,
	WeaponFactory* aWeaponFactory,
	InputInterface* aInputInterface,

	GameMessenger* aGameMessenger) :
	myAudioManager(anAudioManager),
	myJsonManager(aJsonManager),
	myWeaponFactory(aWeaponFactory),
	myInputInterface(aInputInterface),

	myGameMessenger(aGameMessenger)
{}
