#include "Camera.h"

Camera::Camera(InputManager* inputManager)
{
	this->inputManager = inputManager;
	this->yaw = 0;
	this->pitch = 0;
}

void Camera::Update(float dt)
{
	time_elapsed += dt;

	if (time_elapsed >= activate_time) {
		float xoffset = inputManager->mouseX * dt * inputManager->mouse_sensitivity;
		float yoffset = inputManager->mouseY * dt * inputManager->mouse_sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		lx = sin(DegToRad(yaw));
		lz = -cos(DegToRad(yaw));
		ly = sin(DegToRad(pitch));

		//std::cout << "coffset: " << xoffset << ", yoffset : " << yoffset << ", pitch : " << pitch << ", yaw: " << yaw << std::endl;
	}	
}


