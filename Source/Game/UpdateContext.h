#pragma once

#include "InputInterface.h"

namespace CommonUtilities
{
	class Input;
}

class AudioManager;
class InputInterface;

struct UpdateContext
{
	AudioManager* myAudioManager;

	CommonUtilities::Input* myInput;
	InputInterface* myInputInterface;
};
