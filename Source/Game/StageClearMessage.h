#pragma once

#include "GenericGameMessageSubscriber.h"

struct StageClearMessageData
{};

using StageClearMessage = GenericGameMessageSubscriber<StageClearMessageData>;
