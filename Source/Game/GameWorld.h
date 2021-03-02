#pragma once

namespace Tga2D
{
	class CSprite;
	class FBXModel;
	class CAudio;
}

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render();
private:
	Tga2D::CSprite* myTga2dLogoSprite;
};