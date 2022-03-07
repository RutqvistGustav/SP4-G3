#pragma once

#pragma once

#include "GenericGameMessageSubscriber.h"

struct IndexMessageData
{
	int myIndex;
};

using IndexMessage = GenericGameMessageSubscriber<IndexMessageData>;