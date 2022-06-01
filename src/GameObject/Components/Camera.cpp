#include "Camera.h"

Camera::Camera(InputManager* inputManager)
{
	this->inputManager = inputManager;
	this->yaw = 0;
}

void Camera::Update(float dt)
{
	
	float xoffset = inputManager->mouseX * dt;
	float yoffset = inputManager->mouseY * dt;

	yaw += xoffset;
	pitch += yoffset;

	lx = sin(DegToRad(yaw));
	lz = -cos(DegToRad(yaw));
	ly = sin(DegToRad(pitch));

	std::cout << "Ly : " << ly << "yOffset: " << yoffset << std::endl;
}


