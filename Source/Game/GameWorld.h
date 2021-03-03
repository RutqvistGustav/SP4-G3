#pragma once
#include "CollisionManager.h"
#include <memory>

namespace Tga2D
{
	class CSprite;
	class FBXModel;
	class CAudio;
}

namespace CommonUtilities
{
	class Input;
}

class Player;
class RenderQueue;
class SpriteWrapper;

class CGameWorld
{
public:

	CGameWorld(); 
	~CGameWorld();

	void Init();

	void Update(float aTimeDelta, CommonUtilities::Input* anInput); 
	void Render(RenderQueue* aRenderQueue);

private:
	//Tga2D::CSprite* myTga2dLogoSprite;
	CollisionManager myCollisionManager;

	std::shared_ptr<SpriteWrapper> myTga2dLogoSprite;

	std::unique_ptr<Player> myPlayer;
};
