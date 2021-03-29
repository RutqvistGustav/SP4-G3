#pragma once

class SpriteWrapper;

class ForegroundImage
{
public:
	ForegroundImage() = default;
	~ForegroundImage() = default;

	void Init();
	void Update(const float aDeltaTime);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

private:

};

