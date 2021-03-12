#include "stdafx.h"
#include "TiledRenderer.h"

#include "TiledParser.h"
#include "TiledLayer.h"

#include "RenderCommand.h"
#include "RenderQueue.h"

TiledRenderer::TiledRenderer(const TiledParser* aParser) :
	myParser(aParser)
{}

void TiledRenderer::Render(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	for (const auto& layer : myParser->myResult->GetLayers())
	{
		for (const auto& batchInfo : layer.GetRenderBatches())
		{
			aRenderQueue->Queue(RenderCommand(batchInfo.myBatch));
		}
	}
}
