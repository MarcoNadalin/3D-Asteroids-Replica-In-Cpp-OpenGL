#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <stdlib.h>
#include <stdio.h>
#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

#include <iostream>
#include <cctype>

class InputManager
{
private:
	/* length set to 127 since there are 127 ascii keys in c */
	bool keys[127] = { false };		
	

public:

	float mouse_sensitivity = 0.15;
	float mouseX;
	float mouseY;


	bool left_mouse_pressed = false;
	bool right_mouse_pressed = false;

	InputManager();
	void HandleInput();
	void OnKeyDown(unsigned char key);
	void OnKeyUp(unsigned char key);

	bool IsKeyPressed(unsigned char key);

	void MouseMotion(int x, int y);
};

#endif