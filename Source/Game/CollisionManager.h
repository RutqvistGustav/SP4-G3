#pragma once
#include <map>
#include <memory>

#include "Collider.h"

namespace Tga2D
{
	class CColor;
}

class CollisionManager
{
public:
	static std::shared_ptr<CollisionManager> GetInstance()
	{
		static std::shared_ptr<CollisionManager> ourCollisionManager(new CollisionManager);
		return ourCollisionManager;
	}
	CollisionManager(CollisionManager const&) = delete;
	void operator=(CollisionManager const&) = delete;
	~CollisionManager();

	void Update();

	void AddCollider(std::shared_ptr<Collider> aCollider);

#ifdef _DEBUG
	void InitDebug();
	void RenderDebug();
#endif // _DEBUG


private:
	CollisionManager();
	std::vector<std::shared_ptr<Collider>> myColliders;
	std::map<int, int> myCollisionIndexes;

};

