#pragma once
#include "Vector2.hpp"

#ifdef _DEBUG
namespace Tga2D
{
	class CSprite;
}
#endif // _DEBUG

class GameObject;

class Collider
{
	friend class CollisionManager;
public:
	Collider();
	Collider(GameObject* aGameObject, CU::Vector2<float> aPos, float aRadius = 100.f);
	Collider(GameObject* aGameObject, float aX, float aY, float aRadius = 100.f);
	virtual ~Collider();
	void Init(GameObject* aGameObject, CU::Vector2<float> aPos, float aRadius = 100.f);

	void SetPos(const CU::Vector2<float> aPos);
	bool GetCollision(const Collider* aCollider);
	const std::shared_ptr<GameObject> GetGameObject()const;

	const bool isColliding()const;
	void SetRadius(const float aRadius);
	const float GetRadius()const;

#ifdef _DEBUG
	void InitDebug();

	void RenderDebug();
	void setRenderColor(Tga2D::CColor aColor);
	Tga2D::CSprite* myDebugSprite;
#endif // _DEBUG

	enum class eCollisionStage
	{
		NotColliding = 0,
		FirstFrame,//används ej
		MiddleFrames,
		LastFrame,//används ej
		Count
	};

	const eCollisionStage GetCollisionStage()const;

	void AdvanceCollisionStage();
private:
	
	eCollisionStage myCollisionStage = eCollisionStage::NotColliding;

	bool myIsNotColliding = true;
	bool myIsColliding = false;
	bool myIsCube = false;
	CommonUtilities::Vector2<float> myPos;
	float myRadius;
	std::shared_ptr<GameObject> myGameObject;


};

