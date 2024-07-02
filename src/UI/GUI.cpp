#include "GUI.h"

GUI::GUI()
{

}

void GUI::WriteText(std::string text, int x_pos, int y_pos)
{
	glColor3f(255, 255, 255);
	glRasterPos2f(x_pos, y_pos);
	WriteString(text, GLUT_BITMAP_TIMES_ROMAN_24);
}

void GUI::WriteCharacter(char c, void* font, int x_pos, int y_pos)
{
	
	//glutBitmapCharacter
}

void GUI::WriteString(std::string text, void* font)
{
	for (int i = 0; i < text.length(); i++) {
		
		glutBitmapCharacter(font, text.at(i));
	}
}
