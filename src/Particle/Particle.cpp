#include "Particle.h"

Particle::Particle(const float& speed, const float& x, const float& y, const float& z) : GameObject(x, y, z) {
	this->speed = speed;
	this->current_speed = speed;
}

void Particle::Update(float dt)
{
	/* Update current speed */
	//this->current_speed = Clamp((speed - decelleration_rate), min_speed, speed);
	/* Create velocity vector in direction point is facing */
	Vector3f velocity = Vector3f();
	velocity.y += current_speed * dt;
	velocity.RotateZ(transform->euler_angles->z);

	/* Move particle according to velocity vector */
	this->Move(velocity);
}

void Particle::Render()
{
	glPointSize(4.0f);
	this->RenderVerticies(GL_POINTS);
}



