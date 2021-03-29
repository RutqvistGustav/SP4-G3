#pragma once

class Collider;

class ContactKey
{
public:

	ContactKey(Collider* aColliderA, Collider* aColliderB)
	{
		if (aColliderA <= aColliderB)
		{
			myColliderA = aColliderA;
			myColliderB = aColliderB;
		}
		else
		{
			myColliderA = aColliderB;
			myColliderB = aColliderA;
		}
	}

	friend inline bool operator==(const ContactKey& aKeyA, const ContactKey& aKeyB)
	{
		return
			aKeyA.myColliderA == aKeyB.myColliderA &&
			aKeyA.myColliderB == aKeyB.myColliderB;
	}

	friend inline bool operator<(const ContactKey& aKeyA, const ContactKey& aKeyB)
	{
		if (aKeyA.myColliderA < aKeyB.myColliderA)
		{
			return true;
		}

		if (aKeyA.myColliderA == aKeyB.myColliderA && aKeyA.myColliderB < aKeyB.myColliderB)
		{
			return true;
		}

		return false;
	}

private:

	friend class CollisionManager;
	friend class ContactManager;

	Collider* myColliderA{};
	Collider* myColliderB{};

};
