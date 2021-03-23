#pragma once
#include "Vector2.hpp"

#ifdef _DEBUG
namespace Tga2D
{
	class CSprite;
}
#include "SpriteWrapper.h"
#endif // _DEBUG

class SpriteWrapper;
class GameObject;
class TiledCollision;
class TiledTile;
class RenderQueue;
class RenderContext;

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

	void RenderDebug(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);
	void setRenderColor(Tga2D::CColor aColor);
	std::shared_ptr<SpriteWrapper> myDebugSprite;
	bool myDoRender = true;
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

//TODO:Sync colliders with correct positon
//TODO:man kan fråga collision manager om collisions