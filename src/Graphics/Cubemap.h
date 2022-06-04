#ifndef CUBEMAP_H
#define CUBEMAP_H


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
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

/** 
*
* Cubemap class. Used to render the skybox.
* The cubemap takes in the x, y, and z coordinates of the camera.
* Then it translates each side of the cube depending on the x,y,z of the camera
* This is so the skybox is always the same distance away from the player, making it unreachable.
* 
*/
class Cubemap
{
private:
	GLuint cube_front;
	GLuint cube_back;
	GLuint cube_top;
	GLuint cube_bottom;
	GLuint cube_left;
	GLuint cube_right;

	void renderFront(float x, float y, float z);
	void renderBack(float x, float y, float z);
	void renderTop(float x, float y, float z);
	void renderBottom(float x, float y, float z);
	void renderLeft(float x, float y, float z);
	void renderRight(float x, float y, float z);

public:

	Cubemap(GLuint front, GLuint back, GLuint top, GLuint bottom, GLuint left, GLuint right);
	void RenderCubemap(float x, float y, float z);
	void RenderCubemap();

};

#endif