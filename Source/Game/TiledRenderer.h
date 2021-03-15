#pragma once

class TiledParser;
class RenderQueue;
struct RenderContext;

class TiledRenderer
{
public:

	TiledRenderer(const TiledParser* aParser);

	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

private:

	const TiledParser* myParser;

};
