#pragma once
#include "Vector3.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "AABB3D.hpp"
#include "TemplateUtilities.h"

namespace CommonUtilities
{
	// If the ray is parallel to the plane, anOutIntersectionPoint remains unchanged.
	// If the ray is in the plane, true is returned, if not, false is returned.
	// If the ray isn't parallel to the plane, the intersection point is stored in
	// aOutIntersectionPoint and true return.
	template<typename T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& aOutIntersectionPoint)
	{
		T denominator = aRay.GetDirection().Dot(aPlane.GetNormal());

		if (denominator == 0)
		{
			return aPlane.IsInside(aRay.GetOrigin()) == false;
		}

		//Vector3<T> pn = aPlane.GetPoint() - aRay.GetOrigin();
		//T t = pn.Dot(aPlane.GetNormal()) / denominator;

		T d = aPlane.GetNormal().Dot(aPlane.GetPoint());
		T pn = aRay.GetOrigin().Dot(aPlane.GetNormal());

		T t = (d - pn) / denominator;

		if (t >= 0)
		{
			Vector3<T> intersection = aRay.GetOrigin() + (t * aRay.GetDirection());
			aOutIntersectionPoint = intersection;

			return true;
		}

		return false;
	}

	// If the ray intersects the AABB, true is returned, if not, false is returned.
	// A ray in one of the AABB's side is counted as intersection it.
	template<typename T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay)
	{
		float txMin = (aAABB.GetMin().x - aRay.GetOrigin().x) / aRay.GetDirection().x;
		float txMax = (aAABB.GetMax().x - aRay.GetOrigin().x) / aRay.GetDirection().x;

		if (txMin > txMax) Swap(txMin, txMax);

		float tyMin = (aAABB.GetMin().y - aRay.GetOrigin().y) / aRay.GetDirection().y;
		float tyMax = (aAABB.GetMax().y - aRay.GetOrigin().y) / aRay.GetDirection().y;

		if (tyMin > tyMax) Swap(tyMin, tyMax);

		if ((txMin > tyMax) || (tyMin > txMax)) return false;

		if (tyMin > txMin) txMin = tyMin;
		if (tyMax < txMax) txMax = tyMax;

		float tzMin = (aAABB.GetMin().z - aRay.GetOrigin().z) / aRay.GetDirection().z;
		float tzMax = (aAABB.GetMax().z - aRay.GetOrigin().z) / aRay.GetDirection().z;

		if (tzMin > tzMax) Swap(tzMin, tzMax);

		if ((txMin > tzMax) || (tzMin > txMax)) return false;

		if (tzMin > txMin) txMin = tzMax;
		if (tzMax < txMax) txMax = tzMax;

		return true;
	}


	// If the ray intersects the sphere, true is returned, if not, false is returned.
	// A ray intersecting the surface of the sphere is considered as intersecting it.
	template<typename T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay)
	{
		Vector3<T> e = aSphere.GetCenter() - aRay.GetOrigin();
		T a = e.Dot(aRay.GetDirection());

		T basePow2 = powf(e.Length(), 2) - powf(a, 2);
		T radiusPow2 = powf(aSphere.GetRadius(), 2);

		if ((radiusPow2 - basePow2) < 0)
		{
			return false;
		}

		T f = sqrt(radiusPow2 - basePow2);
		T t = a - f;

		if (t >= 0)
		{
			return true;
		}

		Vector3<T> point = aRay.GetOrigin() + (aRay.GetDirection() * t);
		if (aSphere.IsInside(point) == true)
		{
			return true;
		}

		return false;
	}

	template<typename T>
	bool IntersectionAABB_AABB(const AABB3D<T>& aBox1, const AABB3D<T>& aBox2)
	{
		if (aBox1.GetMin().x >= aBox2.GetMax().x) return false;
		if (aBox1.GetMax().x <= aBox2.GetMin().x) return false;
		if (aBox1.GetMin().y >= aBox2.GetMax().y) return false;
		if (aBox1.GetMax().y <= aBox2.GetMin().y) return false;
		if (aBox1.GetMin().z >= aBox2.GetMax().z) return false;
		if (aBox1.GetMax().z <= aBox2.GetMin().z) return false;

		return true;
	}
}

namespace CU = CommonUtilities;