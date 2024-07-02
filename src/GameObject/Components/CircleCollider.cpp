#include "CircleCollider.h"

CircleCollider::CircleCollider(const Transform& parent_transform, float radius) : transform(parent_transform)
{
	this->radius = radius;

}

void CircleCollider::CreateCartesianCircle(float rad, int vertexes)
{
	float x, y;

	vertexes /= 2;

	for (int i = 0; i < vertexes; i++)
	{
		x = ((i / (float)vertexes - 0.5) * 2.0) * rad;
		y = sqrt(rad * rad - x * x);
		glVertex2f(x, y);
	}

	for (int i = vertexes; i > 0; i--)
	{
		x = (i / (float)vertexes - 0.5) * 2.0 * rad;
		y = -sqrt(rad * rad - x * x);
		glVertex2f(x, y);
	}
}

void CircleCollider::RenderCircle()
{
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(transform.pivot_position->x, transform.pivot_position->y, 0);
	glRotatef(transform.euler_angles->z, 0, 0, 1);
	glScalef(1, 1, 1);

	glLineWidth(2.0);

	glBegin(GL_LINE_LOOP);
		CreateCartesianCircle(radius, 64);
	glEnd();

	glPopMatrix();
}

bool CircleCollider::CollidingWithCircle(CircleCollider* c2)
{
	float dx = (this->transform.pivot_position->x + this->radius) - (c2->transform.pivot_position->x + c2->radius);
	float dy = (this->transform.pivot_position->y + this->radius) - (c2->transform.pivot_position->y + c2->radius);

	float distance = sqrt((dx * dx) + (dy * dy));
	float radius_added = this->radius + c2->radius;
	
	if (distance <= radius_added) {
		return true;
	}
	else {
		return false;		
	}
}

bool CircleCollider::CollidingWithPoint(Vector3f& position)
{
	float x_point = position.x;
	float y_point = position.y;
	float x_circle = this->transform.pivot_position->x;
	float y_circle = this->transform.pivot_position->y;
	return ((x_point - x_circle) * (x_point - x_circle) + (y_point - y_circle) * (y_point - y_circle)) <= radius * radius;
}
