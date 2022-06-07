#include "Camera.h"

Camera::Camera()
{
	this->yaw = 0;
	this->pitch = 0;
	this->transform = std::make_unique<Transform>(0,0,0);
}

Camera::Camera(InputManager* inputManager)
{
	this->inputManager = inputManager;
	this->yaw = 0;
	this->pitch = 0;
	this->transform = std::make_unique<Transform>(0, 0, 0);
}

Camera::Camera(InputManager* inputManager, float x, float y, float z)
{
	this->inputManager = inputManager;
	this->yaw = 0;
	this->pitch = 0;
	this->transform = std::make_unique<Transform>(x, y, z);
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

		//std::cout << "mouseX: " << inputManager->mouseX << "xoffset: " << xoffset << ", yoffset : " << yoffset << ", pitch : " << pitch << ", yaw: " << yaw << std::endl;
	}
}

void Camera::MoveCamera(float dt)
{
	this->transform->pivot_position->x += dt * lx * 0.1f;
	this->transform->pivot_position->z += dt * lz * 0.1f;
}


