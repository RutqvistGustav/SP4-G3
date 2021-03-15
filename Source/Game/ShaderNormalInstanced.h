#pragma once

#include <tga2d/shaders/shader.h>
#include <tga2d/shaders/shader_common.h>

#include <array>

struct ExtraRenderInformation;
struct SpriteRenderData;
struct SpriteBatchRenderData;

class ShaderNormalInstanced : public Tga2D::CShader
{
public:

	static constexpr int ourMaxInstanceCount = 2048;

	ShaderNormalInstanced(Tga2D::CEngine* aEngine);

	virtual bool Init() override;

	void Render(const SpriteRenderData& someRenderData, const ExtraRenderInformation& someExtraInformation, ID3D11Buffer* anInstanceBuffer, ID3D11Buffer* aVertexBuffer);
	void Render(const SpriteBatchRenderData& someRenderData, const ExtraRenderInformation& someExtraInformation, ID3D11Buffer* anInstanceBuffer, ID3D11Buffer* aVertexBuffer);

protected:

	virtual bool CreateInputLayout(ID3D10Blob* aVS) override;

private:

	void SetupForRender();
	int BindForRender(const std::vector<SpriteRenderData>& someRenderData, Tga2D::CTexture* aTexture, const ExtraRenderInformation& someExtraInformation, ID3D11Buffer* anInstanceBuffer, ID3D11Buffer* aVertexBuffer);

private:

	std::array<Tga2D::ObjectBufferInstanceType, ourMaxInstanceCount> myRenderBuffer{};

};

