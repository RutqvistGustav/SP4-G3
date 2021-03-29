#pragma once
#include "Vector2.hpp"
#include <any>

#ifdef _DEBUG
namespace Tga2D
{
	class CSprite;
}
#include "SpriteWrapper.h"
#endif // _DEBUG

class SpriteWrapper;
//class GameObject;
class TiledCollision;
class TiledTile;
class RenderQueue;
class RenderContext;
class CollisionListener;

class Collider
{
	friend class CollisionManager;
public:
	Collider();
	Collider(CollisionListener* aGameObject, CU::Vector2<float> aPos, float aRadius = 100.f);
	Collider(CollisionListener* aGameObject, float aX, float aY, float aRadius = 100.f);
	virtual ~Collider();
	void Init(CollisionListener* aGameObject, CU::Vector2<float> aPos, float aRadius = 100.f);
	
	void SetPos(const CU::Vector2<float> aPos);
	bool GetCollision(const Collider* aCollider);
	const TiledTile* GetCollision(const TiledCollision* aTiledCollision, CU::Vector2<float> anOffsetDirection);
	//const std::shared_ptr<GameObject> GetGameObject()const;
	std::any GetGameObject()const;


	void SetBoxSize(const CU::Vector2<float> aSize);
	CU::Vector2<float> GetBoxSize();
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
		FirstFrame,//anv�nds ej
		MiddleFrames,
		LastFrame,//anv�nds ej
		Count
	};
	const eCollisionStage GetCollisionStage()const;
	//const bool GetIsCube()const;

private:
	void AdvanceCollisionStage();
	eCollisionStage myCollisionStage = eCollisionStage::NotColliding;
	CU::Vector2<float> myCheckOffset = CU::Vector2<float>(0.0f, 0.0f);

	CommonUtilities::Vector2<float> myPos;
	CU::Vector2<float> myDimentions;
	CollisionListener* myExtraInfo = nullptr;


};

//TODO:Sync colliders with correct positon
//TODO:man kan fr�ga collision manager om collisions

