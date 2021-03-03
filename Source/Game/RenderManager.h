#pragma once

#include <memory>

namespace Tga2D
{
	class CSprite;
}

class RenderCommand;
class RenderQueue;

class RenderManager
{
public:

	RenderManager();
	~RenderManager();

	void Render();

	void OnPostFrameThreadSync();

	inline RenderQueue* GetUpdateQueue() { return myUpdateQueue.get(); }

private:

	static bool CommandSort(const RenderCommand& aLhs, const RenderCommand& aRhs);

private:

	std::unique_ptr<RenderQueue> myUpdateQueue;
	std::unique_ptr<RenderQueue> myRenderQueue;

	std::unique_ptr<Tga2D::CSprite> myRenderSprite;

};
