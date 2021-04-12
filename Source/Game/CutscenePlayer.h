#pragma once

#include <memory>

namespace Tga2D
{
	class CVideo;
}

class RenderQueue;
class SpriteWrapper;

class CutscenePlayer
{
public:

	CutscenePlayer();
	~CutscenePlayer();

	bool Init(const std::string& aVideoPath);

	void Update(const float aDeltaTime);
	void Render(RenderQueue* const aRenderQueue);

	bool IsPlaying();
	void Stop();

private:
	std::unique_ptr<Tga2D::CVideo> myVideo;
	std::shared_ptr<SpriteWrapper> myFrameSprite;

};
