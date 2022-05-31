#include "ArenaBoundry.h"


ArenaBoundry::ArenaBoundry(Player* player, int height, int width, std::string tag, float x, float y, float z)
{
	this->tag = tag;
	this->player = player;
	this->height = height;
	this->width = width;

	this->transform->pivot_position->x = x;
	this->transform->pivot_position->y = y;

	this->AddVertex(-width, -height/2, -1);
	this->AddVertex(width, -height/2, -1);
	this->AddVertex(width, height/2, -1);
	this->AddVertex(-width, height/2, -1);
}

void ArenaBoundry::Update(float dt)
{
	
}

void ArenaBoundry::Render() {
	glBegin(GL_POLYGON);
		this->CreateVerticies();
	glEnd();
}
