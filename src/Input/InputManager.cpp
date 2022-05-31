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
