#ifndef GUI_H
#define GUI_H

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

#include<string>

class GUI
{
private:
	void WriteCharacter(char c, void* font, int x_pos, int y_pos);
	void WriteString(std::string text, void* font);

public:

	GUI();
	void WriteText(std::string text, int x_pos, int y_pos);
};

#endif