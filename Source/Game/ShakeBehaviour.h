#pragma once

#include <Vector2.hpp>

class ShakeBehaviour
{
public:
	
	void Update(float aDeltaTime);

	void Configure(float aSpeed, float aRange, float aDuration);
	void Stop();

	const CU::Vector2<float>& GetShakeVector() const;

private:

	void RandomizeTarget();

private:

	static constexpr float ourTargetThreshold = 2.0f;

	float myTime{ -1.0f };

	float mySpeed{};
	float myAmplitude{};
	float myDuration{};

	CU::Vector2<float> myShakeTarget;
	CU::Vector2<float> myShakeVector;

};
