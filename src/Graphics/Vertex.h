#ifndef VERTEX_H
#define VERTEX_H

#include "../Math/Vector3f.h"

class Vertex
{
private:
	
public:
	float x, y, z;

	std::shared_ptr<Vector3f> position;
	std::shared_ptr<Vector3f> color;
	std::shared_ptr<Vector3f> texcoord;
	std::shared_ptr<Vector3f> normal;

	Vertex(float x, float y, float z);
	Vertex();

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
};

#endif