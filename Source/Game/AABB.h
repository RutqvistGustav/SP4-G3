#pragma once

#include <Vector2.hpp>

class AABB
{
public:

	static AABB FromCenterAndSize(const CU::Vector2<float>& aCenter, const CU::Vector2<float>& aSize)
	{
		AABB aabb;

		aabb.myMin = aCenter - aSize * 0.5f;
		aabb.myMax = aabb.myMin + aSize;

		return aabb;
	}

	AABB() = default;
	AABB(const CU::Vector2<float>& aMin, const CU::Vector2<float>& aMax)
		: myMin(aMin),
		myMax(aMax)
	{}

	bool Intersects(const AABB& anOther)
	{
		return
			myMax.x >= anOther.myMin.x && myMin.x <= anOther.myMax.x
			&& myMax.y >= anOther.myMin.y && myMin.y <= anOther.myMax.y;
	}

	void Shift(const CU::Vector2<float>& aDisplacement)
	{
		myMin += aDisplacement;
		myMax += aDisplacement;
	}

	inline CU::Vector2<float> GetSize() const { return myMax - myMin; }
	inline CU::Vector2<float> GetCenter() const { return myMin + GetSize() * 0.5f; }

	inline const CU::Vector2<float>& GetMin() const { return myMin; }
	inline const CU::Vector2<float>& GetMax() const { return myMax; }

private:

	CU::Vector2<float> myMin;
	CU::Vector2<float> myMax;

};
