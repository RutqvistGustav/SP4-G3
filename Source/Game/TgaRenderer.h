#pragma once

#include "IRenderer.h"

#include <tga2d/render/render_common.h>

namespace Tga2D
{
	class CDirectEngine;
}

struct ID3D11Buffer;
class ShaderNormalInstanced;

class TgaRenderer : public IRenderer
{
public:

	TgaRenderer(Tga2D::CDirectEngine* aDirectEngine);
	virtual ~TgaRenderer() override;

	virtual void Render(const SpriteRenderData& aSprite, const ExtraRenderInformation& someExtraInformation) override;
	virtual void Render(const SpriteBatchRenderData& aSpriteBatch, const ExtraRenderInformation& someExtraInformation) override;

private:

	bool SetupInstanceBuffers();
	bool SetupVertexBuffer();
	bool Setup();

private:

	Tga2D::CDirectEngine* myDirectEngine{};

	ID3D11Buffer* myVertexBuffer{};
	ID3D11Buffer* myInstanceBuffer{};

	std::unique_ptr<ShaderNormalInstanced> myShader;

};
