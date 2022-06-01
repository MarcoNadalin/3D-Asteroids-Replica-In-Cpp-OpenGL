#include "InputManager.h"

InputManager::InputManager() {
	
}

void InputManager::HandleInput()
{

}

void InputManager::OnKeyDown(unsigned char key)
{
	char lower_key = std::tolower(key);
	keys[lower_key] = true;
}
void InputManager::OnKeyUp(unsigned char key)
{
	char lower_key = std::tolower(key);
	keys[lower_key] = false;
}

bool InputManager::IsKeyPressed(unsigned char key)
{
	return keys[key];
}

void InputManager::MouseMotion(int x, int y)
{	
	float screen_width = glutGet(GLUT_SCREEN_WIDTH);
	float screen_height = glutGet(GLUT_SCREEN_HEIGHT);
	float middle_screen_height = screen_height / 2;
	float middle_screen_width = screen_width / 2;
	this->mouseX = x - middle_screen_width;
	this->mouseY = y - middle_screen_height;
}
