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
		pitch += yoffset / 2.0f;

		if (pitch > 89.9f) {
			pitch = 89.9f;
		}
		else if (pitch < -89.9f) {
			pitch = -89.9f;
		}

		lx = cos(DegToRad(yaw));
		lz = sin(DegToRad(yaw));
		ly = sin(DegToRad(-pitch));

		//std::cout << "mouseX: " << inputManager->mouseX << "xoffset: " << xoffset << ", yoffset : " << yoffset << ", pitch : " << pitch << ", yaw: " << yaw << std::endl;
		//std::cout << "ly: " << ly << ", lx: " << lx << ", lz" << lz << std::endl;
		
	}
}

void Camera::MoveCamera(float dt)
{
	float looky = ly;
	this->transform->pivot_position->x += dt * lx * 0.1f;
	this->transform->pivot_position->z += dt * lz * 0.1f;
	this->transform->pivot_position->y += dt * ly * 0.1f;
}


