#include "stdafx.h"
#include "ShaderNormalInstanced.h"

#include "IRenderer.h"

#include "Metrics.h"

#include "SpriteRenderData.h"
#include "SpriteBatchRenderData.h"

#include <tga2d/d3d/direct_3d.h>

using Vector2f = CommonUtilities::Vector2<float>;

static inline VECTOR2F GetAsEngineVector(const CU::Vector2<float>& aPosition)
{
	return VECTOR2F(aPosition.x, aPosition.y);
}

static inline VECTOR2F NormalizePosition(const Vector2f aPosition)
{
	const Vector2f referenceSize = Metrics::GetReferenceSize();

	return { aPosition.x / referenceSize.x, aPosition.y / referenceSize.y };
}

static inline VECTOR2F NormalizeSize(const Vector2f aSize)
{
	const Vector2f referenceSize = Metrics::GetReferenceSize();

	// NOTE: / y on both is correct
	return { aSize.x / referenceSize.y, aSize.y / referenceSize.y };
}

ShaderNormalInstanced::ShaderNormalInstanced(Tga2D::CEngine* aEngine) :
	Tga2D::CShader(aEngine)
{
	myLayout = nullptr;
}

bool ShaderNormalInstanced::Init()
{
	return CreateShaders("shaders/instanced_sprite_shader_vs.fx", "shaders/sprite_shader_ps.fx");
}

void ShaderNormalInstanced::Render(const SpriteRenderData& someRenderData, const ExtraRenderInformation& someExtraInformation, ID3D11Buffer* anInstanceBuffer, ID3D11Buffer * aVertexBuffer)
{
	SetupForRender();

	const std::vector<SpriteRenderData> renderData{ someRenderData };

	const int renderCount = BindForRender(renderData, someRenderData.myTexture, someExtraInformation, anInstanceBuffer, aVertexBuffer);

	if (renderCount > 0)
	{
		myDirect3dEngine->GetContext()->DrawInstanced(6, renderCount, 0, 0);
	}
}

void ShaderNormalInstanced::Render(const SpriteBatchRenderData& someRenderData, const ExtraRenderInformation& someExtraInformation, ID3D11Buffer* anInstanceBuffer, ID3D11Buffer* aVertexBuffer)
{
	SetupForRender();

	const int renderCount = BindForRender(someRenderData.mySprites, someRenderData.myTexture, someExtraInformation, anInstanceBuffer, aVertexBuffer);

	if (renderCount > 0)
	{
		myDirect3dEngine->GetContext()->DrawInstanced(6, renderCount, 0, 0);
	}
}

bool ShaderNormalInstanced::CreateInputLayout(ID3D10Blob* aVS)
{
	D3D11_INPUT_ELEMENT_DESC polygonLayout[9];

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_UINT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "TEXCOORD";
	polygonLayout[2].SemanticIndex = 1;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	polygonLayout[3].SemanticName = "TEXCOORD";
	polygonLayout[3].SemanticIndex = 2;
	polygonLayout[3].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[3].InputSlot = 1;
	polygonLayout[3].AlignedByteOffset = 0;
	polygonLayout[3].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[3].InstanceDataStepRate = 1;

	polygonLayout[4].SemanticName = "TEXCOORD";
	polygonLayout[4].SemanticIndex = 3;
	polygonLayout[4].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[4].InputSlot = 1;
	polygonLayout[4].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[4].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[4].InstanceDataStepRate = 1;

	polygonLayout[5].SemanticName = "TEXCOORD";
	polygonLayout[5].SemanticIndex = 4;
	polygonLayout[5].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[5].InputSlot = 1;
	polygonLayout[5].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[5].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[5].InstanceDataStepRate = 1;

	polygonLayout[6].SemanticName = "TEXCOORD";
	polygonLayout[6].SemanticIndex = 5;
	polygonLayout[6].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[6].InputSlot = 1;
	polygonLayout[6].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[6].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[6].InstanceDataStepRate = 1;

	polygonLayout[7].SemanticName = "TEXCOORD";
	polygonLayout[7].SemanticIndex = 6;
	polygonLayout[7].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[7].InputSlot = 1;
	polygonLayout[7].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[7].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[7].InstanceDataStepRate = 1;

	polygonLayout[8].SemanticName = "TEXCOORD";
	polygonLayout[8].SemanticIndex = 7;
	polygonLayout[8].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[8].InputSlot = 1;
	polygonLayout[8].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[8].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[8].InstanceDataStepRate = 1;

	unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	HRESULT result = myDirect3dEngine->GetDevice()->CreateInputLayout(polygonLayout, numElements, aVS->GetBufferPointer(), aVS->GetBufferSize(), &myLayout);
	if (FAILED(result))
	{
		ERROR_PRINT("%s", "Layout error");

		return false;
	}

	return true;
}

void ShaderNormalInstanced::SetupForRender()
{
	assert(myVertexShader != nullptr);
	assert(myPixelShader != nullptr);
	assert(myIsReadyToRender);

	// TODO: Depend on rendered object if we need  to
	myDirect3dEngine->SetSamplerState(ESamplerFilter::ESamplerFilter_Bilinear, ESamplerAddressMode::ESamplerAddressMode_Clamp);
	myDirect3dEngine->SetBlendState(EBlendState::EBlendState_Alphablend);

	myDirect3dEngine->GetContext()->VSSetShader(myVertexShader, NULL, 0);
	myDirect3dEngine->GetContext()->PSSetShader(myPixelShader, NULL, 0);
	myDirect3dEngine->GetContext()->IASetInputLayout(myLayout);
	myDirect3dEngine->GetContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_MAPPED_SUBRESOURCE mappedResourceCommon;
	Tga2D::CommonBufferType* commonBuffer;
	
	HRESULT result = myDirect3dEngine->GetContext()->Map(myCommonBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResourceCommon);
	if (FAILED(result))
	{
		ERROR_PRINT("Could not map common buffer!");

		return;
	}

	commonBuffer = reinterpret_cast<Tga2D::CommonBufferType*>(mappedResourceCommon.pData);
	commonBuffer->myResolution = Tga2D::Vector4f(static_cast<float>(myEngine->GetRenderSize().x), static_cast<float>(myEngine->GetRenderSize().y), 0, 0);
	commonBuffer->myTimings.x = myEngine->GetTotalTime();
	commonBuffer->myTimings.y = myEngine->GetDeltaTime();
	commonBuffer->myRandomValues.x = static_cast<float>(myRandomSeed);
	commonBuffer->myRandomValues.y = (static_cast<float>(((rand() % 2000) - 1000)) / 1000.0f);

	myDirect3dEngine->GetContext()->Unmap(myCommonBuffer, 0);

	myDirect3dEngine->GetContext()->VSSetConstantBuffers(Tga2D::EConstantBufferSlot_Common, 1, &myCommonBuffer);
	myDirect3dEngine->GetContext()->PSSetConstantBuffers(Tga2D::EConstantBufferSlot_Common, 1, &myCommonBuffer);

}

int ShaderNormalInstanced::BindForRender(const std::vector<SpriteRenderData>& someRenderData, Tga2D::CTexture* aTexture, const ExtraRenderInformation& someExtraInformation, ID3D11Buffer* anInstanceBuffer, ID3D11Buffer* aVertexBuffer)
{
	assert(anInstanceBuffer != nullptr);
	assert(aVertexBuffer != nullptr);
	assert(someRenderData.size() > 0);
	assert(someRenderData.size() <= ourMaxInstanceCount);

	myDirect3dEngine->GetContext()->PSSetShaderResources(1, 1, &aTexture->myResource);

	int currentIndex = 0;
	for (const auto& renderData : someRenderData)
	{
		auto& buffer = myRenderBuffer[currentIndex];

		const VECTOR2F position = NormalizePosition(renderData.myPosition + someExtraInformation.myOffset);
		const VECTOR2F pivot = GetAsEngineVector(renderData.myPivot);
		const VECTOR2F size = NormalizeSize(renderData.mySize);

		buffer.myPosition = position;

		buffer.myPosition.x = (buffer.myPosition.x * 2.0f) - 1.0f;
		buffer.myPosition.y = -(buffer.myPosition.y * 2.0f) + 1.0f;

		buffer.myPivot.x = pivot.x;
		buffer.myPivot.y = pivot.y;
		buffer.myRotationAndSize.x = renderData.myRotation;

		buffer.myRotationAndSize.y = size.x * 2.0f;
		buffer.myRotationAndSize.z = size.y * 2.0f;

		buffer.myRotationAndSize.w = 0;

		buffer.myUVRect.x = renderData.myTextureRect.myStartX;
		buffer.myUVRect.y = renderData.myTextureRect.myStartY;
		buffer.myUVRect.z = renderData.myTextureRect.myEndX;
		buffer.myUVRect.w = renderData.myTextureRect.myEndY;

		buffer.myUV.x = 0.0f;
		buffer.myUV.y = 0.0f;
		buffer.myUV.z = 1.0f;
		buffer.myUV.w = 1.0f;

		buffer.myColor.x = renderData.myColor.myR;
		buffer.myColor.y = renderData.myColor.myG;
		buffer.myColor.z = renderData.myColor.myB;
		buffer.myColor.w = renderData.myColor.myA;

		++currentIndex;
	}

	D3D11_MAPPED_SUBRESOURCE mappedObjectResource;
	HRESULT result = myDirect3dEngine->GetContext()->Map(anInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedObjectResource);
	if (FAILED(result))
	{
		ERROR_PRINT("Could not map instance buffer!");
		
		return -1;
	}

	memcpy((Tga2D::ObjectBufferInstanceType*)mappedObjectResource.pData, myRenderBuffer.data(), sizeof(Tga2D::ObjectBufferInstanceType) * currentIndex);
	myDirect3dEngine->GetContext()->Unmap(anInstanceBuffer, 0);

	static constexpr unsigned int strides[2] = { sizeof(SVertexInstanced), sizeof(Tga2D::ObjectBufferInstanceType) };
	static constexpr unsigned int offsets[2] = { 0, 0 };
	ID3D11Buffer* bufferPointers[2] = { aVertexBuffer, anInstanceBuffer };

	myDirect3dEngine->GetContext()->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	return currentIndex;
}
