#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <cctype>

class InputManager
{
private:
	/* length set to 255 since there are 127 ascii keys in c */
	bool keys[127] = { false };

public:

	InputManager();
	void HandleInput();
	void OnKeyDown(unsigned char key);
	void OnKeyUp(unsigned char key);

	bool IsKeyPressed(unsigned char key);
};

#endif