#pragma once

#include "InputInterface.h"

namespace CommonUtilities
{
	class Input;
}

class AudioManager;
class InputInterface;
class Player;

struct UpdateContext
{
	AudioManager* myAudioManager;

	Player* myPlayer;
	CommonUtilities::Input* myInput;
	InputInterface* myInputInterface;
};
