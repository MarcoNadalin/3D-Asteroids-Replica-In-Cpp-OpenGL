#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

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

#include <memory>
#include <iostream>
#include "./Transform.h"
#include "../../Math/Vector3f.h"

class CircleCollider
{
private:
	

public:
	const Transform& transform;
	float radius = 0;

	CircleCollider(const Transform& transform, float radius);
	void CreateCartesianCircle(float radius, int vertexes);
	void RenderCircle();
	bool CollidingWithCircle(CircleCollider* c2);
	bool CollidingWithPoint(Vector3f& position);
};

#endif