#include "stdafx.h"
#include "EntityPhysicsController.h"

#include "CollisionManager.h"
#include "Scene.h"

using Vec2f = CU::Vector2<float>;
static const Vec2f locVecDown = Vec2f(0.0f, 1.0f);
static const Vec2f locVecRight = Vec2f(1.0f, 0.0f);
static const Vec2f locVecOne = Vec2f(1.0f, 1.0f);

EntityPhysicsController::EntityPhysicsController() = default;

EntityPhysicsController::~EntityPhysicsController() = default;

void EntityPhysicsController::Init(Scene* aScene, const Vec2f& aSize)
{
	myScene = aScene;
	mySize = aSize;
	myCollisionBuffer.reserve(16);
	BuildCollisionEdges();
}

void EntityPhysicsController::Update(float aDeltaTime)
{
	// Gravity
	myVelocity += myGravity * aDeltaTime;

	const Vec2f frameDisplacement = myFrameImpulses + myVelocity * aDeltaTime;

	if (!Move(EntityPhysicsController::Axis::Y, frameDisplacement.y))
		myVelocity.y = 0.0f;

	if (!Move(EntityPhysicsController::Axis::X, frameDisplacement.x))
		myVelocity.x = 0.0f;

	myFrameImpulses = Vec2f();
}

void EntityPhysicsController::SetGravity(const Vec2f& someGravity)
{
	myGravity = someGravity;
}

Vec2f EntityPhysicsController::GetGravity() const
{
	return myGravity;
}

void EntityPhysicsController::SetPosition(const Vec2f& aPosition)
{
	myPosition = aPosition;
}

const Vec2f& EntityPhysicsController::GetPosition() const
{
	return myPosition;
}

void EntityPhysicsController::ApplyFrameImpulse(const CU::Vector2<float>& anImpulse)
{
	myFrameImpulses += anImpulse;
}

void EntityPhysicsController::ApplyForce(const CU::Vector2<float>& aForce)
{
	myVelocity += aForce;
}

void EntityPhysicsController::SetVelocity(const Vec2f& aVelocity)
{
	myVelocity = aVelocity;
}

const Vec2f& EntityPhysicsController::GetVelocity() const
{
	return myVelocity;
}

AABB EntityPhysicsController::GetAABB() const
{
	return AABB::FromCenterAndSize(myPosition, mySize);
}

void EntityPhysicsController::BuildCollisionEdges()
{
	myCollisionEdges.clear();

	const AABB entityAABB = GetAABB();

	// NOTE: Currently using points, but if player starts to fall through / go through small / narrow custom colliders
	// we might need to change to a box or more points.
	// A box would probably be more efficient for our cases so if performance is bad this can be changed,
	// and a new BoxTest needs to be added to the CollisionManager.

	const int verticalPoints = static_cast<int>(entityAABB.GetSize().y / 32.0f) + 1;
	const int horizontalPoints = static_cast<int>(entityAABB.GetSize().x / 32.0f) + 1;

	myCollisionEdges[Edge::Bottom] = CreateCollisionEdge(entityAABB.GetCenter() + Vec2f(0.0f, entityAABB.GetSize().y * 0.5f), Vec2f(1.0f, 0.0f), horizontalPoints);
	myCollisionEdges[Edge::Top] = CreateCollisionEdge(entityAABB.GetCenter() - Vec2f(0.0f, entityAABB.GetSize().y * 0.5f), Vec2f(1.0f, 0.0f), horizontalPoints);

	myCollisionEdges[Edge::Right] = CreateCollisionEdge(entityAABB.GetCenter() + Vec2f(entityAABB.GetSize().x * 0.5f, 0.0f), Vec2f(0.0f, 1.0f), verticalPoints);
	myCollisionEdges[Edge::Left] = CreateCollisionEdge(entityAABB.GetCenter() - Vec2f(entityAABB.GetSize().x * 0.5f, 0.0f), Vec2f(0.0f, 1.0f), verticalPoints);
}

std::vector<Vec2f> EntityPhysicsController::CreateCollisionEdge(const Vec2f& aMiddle, const Vec2f& aDirection, int aPointCount)
{
	int usedPointCount = aPointCount;
	if ((usedPointCount % 2) == 0)
	{
		++usedPointCount;
	}

	const AABB entityAABB = GetAABB();
	std::vector<Vec2f> result;

	constexpr float undershoot = 3.0f;

	const Vec2f size = Vec2f((entityAABB.GetSize().x - undershoot) * aDirection.x, (entityAABB.GetSize().y - undershoot) * aDirection.y);
	const Vec2f step = Vec2f(size.x / (usedPointCount - 1), size.y / (usedPointCount - 1));

	Vec2f startPosition = aMiddle - step * static_cast<float>(usedPointCount / 2);
	for (int i = 0; i < usedPointCount; ++i)
	{
		result.push_back(startPosition + step * static_cast<float>(i));
	}

	return result;
}

void EntityPhysicsController::AccumulateEdgeCollisions(Edge anEdge, const Vec2f& aFinalPosition)
{
	const auto& points = myCollisionEdges.at(anEdge);

	myCollisionBuffer.clear();
	for (const auto& point : points)
	{
		myScene->GetCollisionManager()->PointTestNoAlloc(aFinalPosition + point, CollisionLayer::MapSolid, myCollisionBuffer);
	}
}

void EntityPhysicsController::ResolveEdgeCollisions(Edge anEdge, const Vec2f& aFinalPosition, bool& aWasObstructed, float& aDisplacement)
{
	if (myCollisionBuffer.empty())
		return;

	const AABB& collisionAABB = myCollisionBuffer.front().myAABB;
	const AABB entityAABB = AABB::FromCenterAndSize(aFinalPosition, mySize);

	float displacementAdjust = 0.0f;

	// NOTE: Modify displacement so the player will end up right at the object it collided with
	switch (anEdge)
	{
	case Edge::Top:
		displacementAdjust = collisionAABB.GetMax().y - entityAABB.GetMin().y;
		break;
	case Edge::Bottom:
		displacementAdjust = collisionAABB.GetMin().y - entityAABB.GetMax().y + 1.0f;
		break;

	case Edge::Left:
		displacementAdjust = collisionAABB.GetMax().x - entityAABB.GetMin().x;
		break;

	case Edge::Right:
		displacementAdjust = collisionAABB.GetMin().x - entityAABB.GetMax().x;
		break;
	}

	aDisplacement += displacementAdjust;
	aWasObstructed = true;
}

bool EntityPhysicsController::Move(Axis anAxis, float aDistance)
{
	const Vec2f direction = anAxis == Axis::X ? locVecRight : locVecDown;
	float actualDistance = aDistance;
	bool wasObstructed = false;

	Edge testEdge;

	if (anAxis == Axis::Y)
	{
		testEdge = aDistance > 0.0f ? Edge::Bottom : Edge::Top;
	}
	else
	{
		testEdge = aDistance > 0.0f ? Edge::Right : Edge::Left;
	}

	const Vec2f predictedFinalPosition = myPosition + direction * actualDistance;

	AccumulateEdgeCollisions(testEdge, predictedFinalPosition);
	ResolveEdgeCollisions(testEdge, predictedFinalPosition, wasObstructed, actualDistance);

	if (anAxis == Axis::X)
	{
		const bool isAgainstWall = !myCollisionBuffer.empty();

		if (isAgainstWall)
			AddState(eState::eState_AgainstWall);
		else
			RemoveState(eState::eState_AgainstWall);
	}
	else if (anAxis == Axis::Y)
	{
		const bool isGrounded = (testEdge == Edge::Bottom) && !myCollisionBuffer.empty();
		// const bool hitCeiling = (testEdge == Edge::Top) && !myCollisionBuffer.empty();

		if (isGrounded)
			AddState(eState::eState_Grounded);
		else
			RemoveState(eState::eState_Grounded);
	}

	myPosition += direction * actualDistance;

	return !wasObstructed;
}
