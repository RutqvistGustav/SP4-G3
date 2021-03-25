#pragma once

#include "GenericGameMessageSubscriber.h"

class Interactable;

struct InteractableMessageData
{
	Interactable* myInteractable;
};

using InteractableMessage = GenericGameMessageSubscriber<InteractableMessageData>;
