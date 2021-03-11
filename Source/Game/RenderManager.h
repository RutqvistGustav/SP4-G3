#pragma once

#include "Vector2.hpp"

#include <memory>

namespace Tga2D
{
	class CSprite;
}

class RenderCommand;
class RenderQueue;
class IRenderer;

class RenderManager
{
public:

	RenderManager();
	~RenderManager();

	void Render();

	void SwapBuffers();

	inline RenderQueue* GetUpdateQueue() { return myUpdateQueue.get(); }

	inline void SetPan(CU::Vector2<float> aPan) { myPan = aPan; }
	inline CU::Vector2<float> GetPan() const { return myPan; }

private:

	static bool CommandSort(const RenderCommand& aLhs, const RenderCommand& aRhs);

private:

	CU::Vector2<float> myPan;

	std::unique_ptr<RenderQueue> myUpdateQueue;
	std::unique_ptr<RenderQueue> myRenderQueue;

	std::unique_ptr<IRenderer> myRenderer;

};
