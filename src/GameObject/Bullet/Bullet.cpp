#include "Bullet.h"

Bullet::Bullet(SceneGraph* sceneGraph, Vector3f* spawnPosition, Vector3f* direction)
{
	this->tag = "Bullet";
	this->sceneGraph = sceneGraph;
	this->direction = std::make_unique<Vector3f>(direction->x, direction->y, direction->z);

	//Set spawn position of the bullet
	this->transform->pivot_position->x = spawnPosition->x;
	this->transform->pivot_position->y = spawnPosition->y;
	this->transform->pivot_position->z = spawnPosition->z;

	/* Move the bullet forward a little bit so it doesnt spawn right in the camera */
	this->transform->pivot_position->Add(this->direction->Multiply(2));

	//std::cout << "BULLET SPAWN: " << this->transform->pivot_position->x << ", " << this->transform->pivot_position->y << ", " << this->transform->pivot_position->z << std::endl;
	//std::cout << "BULLET DIRECTION:  x = " << direction->x << ", y = " << direction->y << ", z = " << direction->z << std::endl;
}

Bullet::Bullet()
{

}

void Bullet::Update(float dt)
{
	Vector3f velocity = Vector3f(direction->x, direction->y, direction->z);
	velocity.Multiply(dt * bulletSpeed);


	this->Move(velocity);

	//std::cout << "BULLET UPDATE: " << this->transform->pivot_position->x << ", " << this->transform->pivot_position->y << ", " << this->transform->pivot_position->z << std::endl;
	/* If bullet is off screen, destroy the bullet */
	if (is_bullet_out_of_bounds()) {
		std::cout << "DESTROY BULLET" << std::endl;
		this->sceneGraph->RemoveGameObject(this);
	}
}

void Bullet::Render() {
	glutSolidSphere(0.2f, 6, 6);
	glFlush();	
}

bool Bullet::is_bullet_out_of_bounds() {
	bool out_of_bounds = false;
	
	float x = this->transform->pivot_position->x;
	float y = this->transform->pivot_position->y;
	float z = this->transform->pivot_position->z;

	if (x < -100 || x > 100) {
		return true;
	}

	if (y < -100 || y > 100) {
		return true;
	}

	if (z < -100 || z > 100) {
		return true;
	}
	
	return out_of_bounds;
}
