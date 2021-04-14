#include "stdafx.h"
#include "RenderQueue.h"

#include "RenderCommand.h"

RenderQueue::RenderQueue()
{
	myCommands.reserve(1024);
}

RenderQueue::~RenderQueue() = default;

void RenderQueue::Queue(const RenderCommand& aCommand)
{
	myCommands.push_back(aCommand);
}

void RenderQueue::Clear()
{
	myCommands.clear();
}
