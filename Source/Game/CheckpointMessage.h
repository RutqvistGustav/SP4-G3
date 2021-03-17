#pragma once

#include "GenericGameMessageSubscriber.h"

class CheckpointContext;

struct CheckpointMessageData
{
	CheckpointContext* myCheckpointContext;
};

using CheckpointMessage = GenericGameMessageSubscriber<CheckpointMessageData>;
