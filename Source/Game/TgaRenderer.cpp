#include "stdafx.h"
#include "TgaRenderer.h"

#include "ShaderNormalInstanced.h"

#include <tga2d/math/matrix44.h>
#include <tga2d/d3d/direct_3d.h>
#include <tga2d/shaders/shader_common.h>

#include <d3d11.h>

#define SAFE_RELEASE(aPointer) if(aPointer){ aPointer->Release();}

TgaRenderer::TgaRenderer(Tga2D::CDirectEngine* aDirectEngine) :
	myDirectEngine(aDirectEngine)
{
	if (!Setup())
	{
		ERROR_PRINT("%s", "Unable to setup TgaRenderer!");
	}
}

TgaRenderer::~TgaRenderer()
{
	SAFE_RELEASE(myVertexBuffer);
	SAFE_RELEASE(myInstanceBuffer);
}

void TgaRenderer::Render(const SpriteRenderData& aSprite, const ExtraRenderInformation& someExtraInformation)
{
	myShader->Render(aSprite, someExtraInformation, myInstanceBuffer, myVertexBuffer);
	myDirectEngine->SetObjectRenderCount(myDirectEngine->GetObjectRenderCount() + 1);
}

void TgaRenderer::Render(const SpriteBatchRenderData& aSpriteBatch, const ExtraRenderInformation& someExtraInformation)
{
	myShader->Render(aSpriteBatch, someExtraInformation, myInstanceBuffer, myVertexBuffer);
	myDirectEngine->SetObjectRenderCount(myDirectEngine->GetObjectRenderCount() + 1);
}

bool TgaRenderer::SetupInstanceBuffers()
{
	D3D11_BUFFER_DESC instanceBufferDescription = { 0 };

	instanceBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDescription.ByteWidth = sizeof(Tga2D::ObjectBufferInstanceType) * ShaderNormalInstanced::ourMaxInstanceCount;
	instanceBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDescription.MiscFlags = 0;
	instanceBufferDescription.StructureByteStride = 0;

	HRESULT result;
	result = myDirectEngine->GetDevice()->CreateBuffer(&instanceBufferDescription, nullptr, &myInstanceBuffer);
	if (FAILED(result))
	{
		ERROR_PRINT("%s", "Object Buffer error");
		
		return false;
	}

	return true;
}

bool TgaRenderer::SetupVertexBuffer()
{
	D3D11_BUFFER_DESC vertexBufferDescription = { 0 };
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };

	constexpr float size = 1.0f;
	constexpr float depth = 0.0f;
	
	SVertexInstanced vertices[6];
	vertices[0].X = -0;
	vertices[0].Y = -size;
	vertices[0].Z = depth;
	vertices[0].texX = 0.0f;
	vertices[0].texY = 1.0f;
	vertices[0].myVertexIndex = 0;

	vertices[1].X = -0;
	vertices[1].Y = -0;
	vertices[1].Z = depth;
	vertices[1].texX = 0.0f;
	vertices[1].texY = 0.0f;
	vertices[1].myVertexIndex = 1;

	vertices[2].X = size;
	vertices[2].Y = -size;
	vertices[2].Z = depth;
	vertices[2].texX = 1.0f;
	vertices[2].texY = 1.0f;
	vertices[2].myVertexIndex = 2;

	vertices[3].X = size;
	vertices[3].Y = -0;
	vertices[3].Z = depth;
	vertices[3].texX = 1.0f;
	vertices[3].texY = 0.0f;
	vertices[3].myVertexIndex = 3;

	vertices[4].X = size;
	vertices[4].Y = -size;
	vertices[4].Z = depth;
	vertices[4].texX = 1.0f;
	vertices[4].texY = 1.0f;
	vertices[4].myVertexIndex = 4;

	vertices[5].X = -0;
	vertices[5].Y = -0;
	vertices[5].Z = depth;
	vertices[5].texX = 0.0f;
	vertices[5].texY = 0.0f;
	vertices[5].myVertexIndex = 5;

	vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDescription.ByteWidth = sizeof(SVertexInstanced) * 6;
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDescription.MiscFlags = 0;
	vertexBufferDescription.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	HRESULT hr = myDirectEngine->GetDevice()->CreateBuffer(&vertexBufferDescription, &vertexData, &myVertexBuffer);
	if (FAILED(hr))
	{
		ERROR_PRINT("%s", "Buffer error");
		return false;
	}

	return true;
}

bool TgaRenderer::Setup()
{
	if (!SetupInstanceBuffers())
	{
		return false;
	}

	if (!SetupVertexBuffer())
	{
		return false;
	}

	myShader = std::make_unique<ShaderNormalInstanced>(Tga2D::CEngine::GetInstance());
	if (!myShader->Init())
	{
		return false;
	}

	return true;
}
