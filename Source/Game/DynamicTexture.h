#pragma once

#include "Vector2.hpp"

#include <tga2d/math/color.h>

#include <cstdint>

namespace Tga2D
{
	class CTexture;
}

struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;

class DynamicTexture
{
public:

	DynamicTexture(int aWidth, int aHeight);
	~DynamicTexture();

	void SetPixel(int aPosX, int aPosY, const Tga2D::CColor& aColor);
	Tga2D::CColor GetPixel(int aPosX, int aPosY) const;

	void CommitChanges();

	CU::Vector2<float> GetNormalizedPixelSize() const;

	inline int GetWidth() const { return myWidth; }
	inline int GetHeight() const { return myHeight; }

	inline Tga2D::CTexture* GetTexture() { return myEngineTexture.get(); }

private:

	void Build();
	void UpdateTexture();

private:

	union Pixel
	{
		struct
		{
			std::uint8_t myR;
			std::uint8_t myG;
			std::uint8_t myB;
			std::uint8_t myA;
		} myComponents;

		std::uint32_t myColor;
	};

	int myWidth;
	int myHeight;

	int myAlignedWidth;
	int myAlignedHeight;

	std::unique_ptr<Pixel[]> myPixelBuffer;

	std::unique_ptr<Tga2D::CTexture> myEngineTexture;

	ID3D11Texture2D* myTexture{};
	ID3D11ShaderResourceView* myTextureResourceView{};

};
