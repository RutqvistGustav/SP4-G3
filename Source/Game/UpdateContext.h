#pragma once

#include "InputInterface.h"

namespace CommonUtilities
{
	class Input;
}

class InputInterface;
class Player;

struct UpdateContext
{
	Player* myPlayer;
	CommonUtilities::Input* myInput;
	InputInterface* myInputInterface;
};
