#include "Cubemap.h"


Cubemap::Cubemap(GLuint front, GLuint back, GLuint top, GLuint bottom, GLuint left, GLuint right)
{
	this->cube_front = front;
	this->cube_back = back;
	this->cube_top = top;
	this->cube_bottom = bottom;
	this->cube_left = left;
	this->cube_right = right;
}

void Cubemap::RenderCubemap(float x, float y, float z)
{
	renderFront(x, y, z);
	renderBack(x, y, z);
	renderTop(x, y, z);
	renderBottom(x, y, z);
	renderLeft(x, y, z);
	renderRight(x, y, z);
}

void Cubemap::renderFront(float x, float y, float z)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cube_front);

	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-100, -100, -100);

	glTexCoord2f(1, 0);
	glVertex3f(100, -100, -100);

	glTexCoord2f(1, 1);
	glVertex3f(100, 100, -100);

	glTexCoord2f(0, 1);
	glVertex3f(-100, 100, -100);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Cubemap::renderBack(float x, float y, float z)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cube_back);

	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(100, -100, 100);

	glTexCoord2f(1, 0);
	glVertex3f(-100, -100, 100);

	glTexCoord2f(1, 1);
	glVertex3f(-100, 100, 100);

	glTexCoord2f(0, 1);
	glVertex3f(100, 100, 100);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Cubemap::renderTop(float x, float y, float z)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cube_top);

	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-100, 100, -100);

	glTexCoord2f(1, 0);
	glVertex3f(100, 100, -100);

	glTexCoord2f(1, 1);
	glVertex3f(100, 100, 100);

	glTexCoord2f(0, 1);
	glVertex3f(-100, 100, 100);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Cubemap::renderBottom(float x, float y, float z)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cube_bottom);

	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-100, -100, 100);

	glTexCoord2f(1, 0);
	glVertex3f(100, -100, 100);

	glTexCoord2f(1, 1);
	glVertex3f(100, -100, -100);

	glTexCoord2f(0, 1);
	glVertex3f(-100, -100, -100);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Cubemap::renderLeft(float x, float y, float z)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cube_left);

	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-100, -100, 100);

	glTexCoord2f(1, 0);
	glVertex3f(-100, -100, -100);

	glTexCoord2f(1, 1);
	glVertex3f(-100, 100, -100);

	glTexCoord2f(0, 1);
	glVertex3f(-100, 100, 100);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Cubemap::renderRight(float x, float y, float z)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cube_right);

	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(100, -100, -100);

	glTexCoord2f(1, 0);
	glVertex3f(100, -100, 100);

	glTexCoord2f(1, 1);
	glVertex3f(100, 100, 100);

	glTexCoord2f(0, 1);
	glVertex3f(100, 100, -100);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}