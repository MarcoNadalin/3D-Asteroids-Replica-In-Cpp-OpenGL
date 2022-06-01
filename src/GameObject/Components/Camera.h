#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include "../../Math/Vector3f.h"
#include "Transform.h"
#include "../../Input/InputManager.h"
#include <iostream>
#include "../../Math/Math.h"

#define M_PI 3.141592653589793238

/**
* A class which contains the rotation and pivot position for any game object
*/
class Camera
{
private:
	InputManager* inputManager;
	float yaw = 0.0f;
	float pitch = 0.0f;
		
public:

	// actual vector representing the camera's direction
	float lx = 0.0f, lz = -1.0f, ly = 1.0f;

	// XZ position of the camera
	float x = 0.0f, y = 1.0f, z = 5.0f;

	float deltaMove = 0;

	float activate_time = 3.0f;
	float time_elapsed = 0.0f;

	Camera(InputManager* inputManager);


	void Update(float dt);

	void MoveCamera(float dt);
};

#endif