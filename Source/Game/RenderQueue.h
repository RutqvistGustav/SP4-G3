#pragma once

class RenderCommand;

class RenderQueue
{
public:

	RenderQueue();
	~RenderQueue();

	void Queue(const RenderCommand& aCommand);
	void Queue(RenderCommand&& aCommand);
	void Clear();

private:

	friend class RenderManager;

	std::vector<RenderCommand> myCommands;

};
