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
	CommonUtilities::Input* myInput;
	InputInterface* myInputInterface;
};
