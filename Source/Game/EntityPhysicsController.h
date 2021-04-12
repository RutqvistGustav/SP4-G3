#pragma once

#include "CollisionItem.h"
#include "Vector2.hpp"
#include "AABB.h"

#include <unordered_map>

class Scene;

class EntityPhysicsController
{
public:

	enum eState
	{
		eState_None         = (0 << 0),
		eState_Grounded     = (1 << 0),

		eState_AgainstWall  = (1 << 1),
		eState_InsideWall	= (1 << 2)
	};

	EntityPhysicsController();
	~EntityPhysicsController();

	void Init(Scene* aScene, const CU::Vector2<float>& aSize);

	void Update(float aDeltaTime);

	void SetGravity(const CU::Vector2<float>& someGravity);
	CU::Vector2<float> GetGravity() const;

	void SetPosition(const CU::Vector2<float>& aPosition);
	const CU::Vector2<float>& GetPosition() const;

	void ApplyFrameImpulse(const CU::Vector2<float>& anImpulse);

	void ApplyForce(const CU::Vector2<float>& aForce);

	void SetVelocity(const CU::Vector2<float>& aVelocity);
	const CU::Vector2<float>& GetVelocity() const;

	AABB GetAABB() const;

	inline bool IsAgainstWall() const { return HasState(eState::eState_AgainstWall); }
	inline bool IsGrounded() const { return HasState(eState::eState_Grounded); }
	bool myGoThrough = false;

private:

	enum class Axis
	{
		X,
		Y,
	};

	enum class Edge
	{
		Top,
		Right,
		Bottom,
		Left,
	};

	void BuildCollisionEdges();
	std::vector<CU::Vector2<float>> CreateCollisionEdge(const CU::Vector2<float>& aMiddle, const CU::Vector2<float>& aDirection, int aPointCount);

	void AccumulateEdgeCollisions(Edge anEdge, const CU::Vector2<float>& aFinalPosition);
	void ResolveEdgeCollisions(Edge anEdge, const CU::Vector2<float>& aFinalPosition, bool& aWasObstructed, float& aDisplacement);

	bool Move(Axis anAxis, float aDistance);

	inline void AddState(eState aState) { myState = myState | aState; }
	inline void RemoveState(eState aState) { myState &= ~aState; }

	inline bool HasState(eState aState) const { return (GetState() & aState) != 0; }
	inline eState GetState() const { return static_cast<eState>(myState); }

private:

	CU::Vector2<float> myGravity;

	CU::Vector2<float> myPosition;
	CU::Vector2<float> myVelocity;
	CU::Vector2<float> mySize;

	CU::Vector2<float> myFrameImpulses;

	Scene* myScene{};

	std::underlying_type_t<eState> myState{ eState::eState_None };

	std::unordered_map<Edge, std::vector<CU::Vector2<float>>> myCollisionEdges;
	std::vector<CollisionItem> myCollisionBuffer;

};
