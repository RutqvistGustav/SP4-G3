#pragma once
#include <memory>
#include "Collider.h"

namespace Tga2D
{
	class CColor;
}

class CollisionManager
{
public:
	CollisionManager(); //Singleton-ish?
	~CollisionManager();

	void Update();

	void AddCollider(Collider* aCollider);

#ifdef _DEBUG
	void RenderDebug();
#endif // _DEBUG


private:
	std::vector<std::shared_ptr<Collider>> myColliders;
};

