#pragma once
#include "Vector2.hpp"

#ifdef _DEBUG
namespace Tga2D
{
	class CSprite;
}
#endif // _DEBUG

class Collider
{
public:
	Collider();
	Collider(CU::Vector2<float> aPos, float aRadius = 0.1f);
	Collider(float aX, float aY, float aRadius = 0.1f);
	virtual ~Collider();

	void SetPos(const CU::Vector2<float> aPos);
	bool GetCollision(const Collider* aCollider)const;


#ifdef _DEBUG
	void InitDebug();

	void RenderDebug();
	void setRenderColor(Tga2D::CColor aColor);
	Tga2D::CSprite* myDebugSprite;
#endif // _DEBUG


private:
	CommonUtilities::Vector2<float> myPos;
	float myRadius;



};

