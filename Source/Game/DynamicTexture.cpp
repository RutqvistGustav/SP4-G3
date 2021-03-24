#include "stdafx.h"
#include "DynamicTexture.h"

#include <tga2d/engine.h>
#include <tga2d/math/matrix44.h>
#include <tga2d/d3d/direct_3d.h>
#include <tga2d/texture/texture.h>
#include <d3d11.h>

DynamicTexture::DynamicTexture(int aWidth, int aHeight) :
	myWidth(aWidth),
	myHeight(aHeight)
{
	myAlignedWidth = static_cast<int>(std::powf(2.0f, std::ceilf(std::log2f(myWidth))));
	myAlignedHeight = static_cast<int>(std::powf(2.0f, std::ceilf(std::log2f(myHeight))));

	myPixelBuffer = std::make_unique<Pixel[]>(myWidth * myHeight);

	Build();
}

DynamicTexture::~DynamicTexture()
{
	if (myEngineTexture != nullptr)
	{
		// NOTE: Set to failed so CTexture::dtor does not try to do anything, we will take care of it
		myEngineTexture->myIsFailedTexture = true;
	}

	if (myTextureResourceView != nullptr)
	{
		myTextureResourceView->Release();
		myTextureResourceView = nullptr;
	}

	if (myTexture != nullptr)
	{
		myTexture->Release();
		myTexture = nullptr;
	}
}

void DynamicTexture::SetPixel(int aPosX, int aPosY, const Tga2D::CColor& aColor)
{
	assert(aPosX >= 0 && aPosX < myWidth);
	assert(aPosY >= 0 && aPosY < myHeight);

	Pixel& pixel = myPixelBuffer[aPosX + aPosY * myWidth];

	pixel.myR = static_cast<std::uint8_t>(255.0f * aColor.myR);
	pixel.myG = static_cast<std::uint8_t>(255.0f * aColor.myG);
	pixel.myB = static_cast<std::uint8_t>(255.0f * aColor.myB);
	pixel.myA = static_cast<std::uint8_t>(255.0f * aColor.myA);
}

Tga2D::CColor DynamicTexture::GetPixel(int aPosX, int aPosY) const
{
	assert(aPosX >= 0 && aPosX < myWidth);
	assert(aPosY >= 0 && aPosY < myHeight);

	const Pixel& pixel = myPixelBuffer[aPosX + aPosY * myWidth];

	return Tga2D::CColor(pixel.myR / 255.0f, pixel.myG / 255.0f, pixel.myB / 255.0f, pixel.myA / 255.0f);
}

void DynamicTexture::CommitChanges()
{
	UpdateTexture();
}

CU::Vector2<float> DynamicTexture::GetNormalizedPixelSize() const
{
	return CU::Vector2<float>(1.0f / myAlignedWidth, 1.0f / myAlignedHeight);
}

void DynamicTexture::Build()
{
	ID3D11Device* device = Tga2D::CEngine::GetInstance()->GetDirect3D().GetDevice();

	std::memset(myPixelBuffer.get(), 0xFF, sizeof(Pixel) * myWidth * myHeight);

	D3D11_TEXTURE2D_DESC textureDescription;
	ZeroMemory(&textureDescription, sizeof(D3D11_TEXTURE2D_DESC));

	textureDescription.Width = myAlignedWidth;
	textureDescription.Height = myAlignedHeight;
	textureDescription.MipLevels = 1;
	textureDescription.ArraySize = 1;

	textureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDescription.SampleDesc.Count = 1;
	textureDescription.SampleDesc.Quality = 0;
	textureDescription.Usage = D3D11_USAGE_DYNAMIC;
	textureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	textureDescription.MiscFlags = 0;

	device->CreateTexture2D(&textureDescription, nullptr, &myTexture);
	device->CreateShaderResourceView(myTexture, nullptr, &myTextureResourceView);

	// TODO: Need to zero out pointer fields in CTexture
	myEngineTexture = std::make_unique<Tga2D::CTexture>();
	myEngineTexture->myResource = myTextureResourceView;
	myEngineTexture->myImageSize = VECTOR2UI(myAlignedWidth, myAlignedHeight);
#ifdef _DEBUG
	myEngineTexture->myPath = "INTERNAL__DynamicTextureInstance";
#endif // _DEBUG
}

void DynamicTexture::UpdateTexture()
{
	ID3D11DeviceContext* context = Tga2D::CEngine::GetInstance()->GetDirect3D().GetContext();

	D3D11_MAPPED_SUBRESOURCE mappedTexture;
	HRESULT result = context->Map(myTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedTexture);
	if (FAILED(result))
	{
		ERROR_PRINT("Failed to update dynamic texture!");

		return;
	}

	Pixel* pixels = reinterpret_cast<Pixel*>(mappedTexture.pData);

	for (int y = 0; y < myHeight; ++y)
	{
		for (int x = 0; x < myWidth; ++x)
		{
			pixels[x + y * myAlignedWidth] = myPixelBuffer[x + y * myWidth];
		}
	}

	context->Unmap(myTexture, 0);
}
