#pragma once
#include <Vector2.hpp>
class Camera
{
public:
	Camera(const CU::Vector2<float> aPosition);
	~Camera() {};

	//Update Camera center position.
	void Update(const CU::Vector2<float> aPosition);

	//Method to set Current Level bounds.
	void SetCameraBounds(const CU::Vector2<float> someCameraBounds);

	//Get the total movement of the Camera this frame.
	const CU::Vector2<float> GetCameraDeltaMovement();

private:
	CU::Vector2<float> myPosition;
	CU::Vector2<float> myCameraBounds;

	CU::Vector2<float> myDeltaMovement;


};

