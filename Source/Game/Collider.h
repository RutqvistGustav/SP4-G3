#pragma once
#include "Vector2.hpp"

#ifdef _DEBUG
namespace Tga2D
{
	class CSprite;
}
#endif // _DEBUG

class GameObject;
class TiledCollision;
class TiledTile;

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
	const TiledTile* GetCollision(const TiledCollision* aTiledCollision, CU::Vector2<float> anOffsetDirection);
	//const std::shared_ptr<GameObject> GetGameObject()const;
	GameObject* GetGameObject()const;


	void SetRadius(const float aRadius);//will be moved to a CircleCollider
	const float GetRadius()const;//will be moved to a CircleCollider
	const CU::Vector2<float> GetPosition()const;
	const float GetWidth()const;
	const float GetHight()const;

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
	//const bool GetIsCube()const;

private:
	void AdvanceCollisionStage();
	eCollisionStage myCollisionStage = eCollisionStage::NotColliding;
	//TileType myCollisionType = TileType::Solid;


	//bool myIsCube = true;//temp var
	CommonUtilities::Vector2<float> myPos;
	//float myRadius;
	CU::Vector2<float> myDimentions;
	//std::shared_ptr<GameObject> myGameObject;
	GameObject* myGameObject = nullptr;


};

