#include "stdafx.h"
#include "RenderManager.h"

#include "Metrics.h"

#include "RenderCommand.h"
#include "RenderQueue.h"

#include "TgaRenderer.h"

#include <algorithm>

#include <tga2d/sprite/sprite.h>

RenderManager::RenderManager()
{
	myUpdateQueue = std::make_unique<RenderQueue>();
	myRenderQueue = std::make_unique<RenderQueue>();

	myRenderer = std::make_unique<TgaRenderer>(&Tga2D::CEngine::GetInstance()->GetDirect3D());
}

RenderManager::~RenderManager() = default;

void RenderManager::Render()
{
	std::vector<RenderCommand>& commands = myRenderQueue->myCommands;
	
	// TODO: NOTE: Might need to be replaced with a stable_sort at some point
	std::sort(commands.begin(), commands.end(), RenderManager::CommandSort);

	for (const RenderCommand& command : commands)
	{
		switch (command.myType)
		{
		case RenderObjectType::Sprite:
		{
			auto& data = command.mySpriteRenderData;

			const ExtraRenderInformation extraRenderInformation{ myPan * command.myPanStrengthFactor };

			myRenderer->Render(data, extraRenderInformation);
		}

			break;

		case RenderObjectType::SpriteBatch:
		{
			auto& data = command.mySpriteBatchRenderData;

			const ExtraRenderInformation extraRenderInformation{ myPan * command.myPanStrengthFactor };

			myRenderer->Render(data, extraRenderInformation);
		}

			break;

		case RenderObjectType::Text:
		{
			// TODO: Inefficient but might be good enough for this game with a small amount of text

			auto& data = command.myText;

			Tga2D::CText text{ data.myPathAndName.c_str(), data.myFontSize, data.myBorderSize };

			text.SetText(data.myText);
			text.SetRotation(data.myRotation);
			text.SetScale(data.myScale);
			text.SetColor(data.myColor);

			text.SetPosition({ data.myPosition.x / Metrics::GetReferenceSize().x, data.myPosition.y / Metrics::GetReferenceSize().y });

			text.Render();
		}

			break;

		default:
			assert(false && "Trying to render invalid command type!");
			break;
		}
	}
}

void RenderManager::SwapBuffers()
{
	myRenderQueue->Clear();

	std::swap(myUpdateQueue, myRenderQueue);
}

bool RenderManager::CommandSort(const RenderCommand& aLhs, const RenderCommand& aRhs)
{
	return aLhs.myLayer < aRhs.myLayer;
}
