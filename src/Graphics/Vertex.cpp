#include "Vertex.h"

Vertex::Vertex(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->position = std::make_shared<Vector3f>();
	this->color = std::make_shared<Vector3f>();
	this->texcoord = std::make_shared<Vector3f>();
	this->normal = std::make_shared<Vector3f>();
}

Vertex::Vertex()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;

	this->position = std::make_shared<Vector3f>();
	this->color = std::make_shared<Vector3f>();
	this->texcoord = std::make_shared<Vector3f>();
	this->normal = std::make_shared<Vector3f>();
}

