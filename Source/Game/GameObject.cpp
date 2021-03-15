#include "stdafx.h"
#include "GameObject.h"
#include "Collider.h"
#include "CollisionManager.h"


//GameObject::GameObject(Scene* aScene, float aX, float aY)
//	: GameObject(aScene)
//{
//	myCollider = nullptr;
//	myPosition.x = aX;
//	myPosition.y = aY;
//}

GameObject::~GameObject()
{
	myCollider.reset();
}

void GameObject::Init()
{

	/*myCollider = std::make_shared<Collider>();
	myCollider->Init(this, myPosition);


	CollisionManager::GetInstance()->AddCollider(myCollider);*/
}


#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"

GameObject::GameObject(Scene* aScene, const char* aSpritePath)
	: myScene(aScene)
{
	myCollider = std::make_shared<Collider>();
	myCollider->Init(this, myPosition);
	CollisionManager::GetInstance()->AddCollider(myCollider);

	mySprite = std::make_shared<SpriteWrapper>(SpriteWrapper(aSpritePath));
}

void GameObject::Update(const float /*aDeltaTime*/, UpdateContext& /*anUpdateContext*/)
{
	myCollider->SetPos(myPosition);

	myPositionLastFrame = myPosition;
}

void GameObject::Render(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	RenderCommand renderCommand = RenderCommand(mySprite);
	aRenderQueue->Queue(renderCommand);
}

const CU::Vector2<float>& GameObject::GetPosition() const
{
	return myPosition;
}

void GameObject::SetPosition(const CU::Vector2<float> aPosition)
{
	myPosition = aPosition;
	myCollider->SetPos(aPosition);
	mySprite->SetPosition(myPosition);
}

void GameObject::OnCollision(GameObject* aGameObject)
{

	switch (myCollider->GetCollisionStage())
	{
	case Collider::eCollisionStage::FirstFrame:
	case Collider::eCollisionStage::MiddleFrames:

#ifdef _DEBUG
		myCollider->setRenderColor(Tga2D::CColor(1.0f, 0.0f, 0.0f, 1.0f));
#endif // _DEBUG
		break;

	case Collider::eCollisionStage::NotColliding:
#ifdef _DEBUG
		myCollider->setRenderColor(Tga2D::CColor(1.0f, 1.0f, 1.0f, 1.0f));
#endif // _DEBUG
		break;
	default:
		break;
	}

}

const Collider* GameObject::GetCollider() const
{
	return myCollider.get();
}
