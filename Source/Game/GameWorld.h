#pragma once
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

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta, CommonUtilities::Input* anInput); 
	void Render();
private:
	Tga2D::CSprite* myTga2dLogoSprite;

	std::unique_ptr<Player> myPlayer;
};