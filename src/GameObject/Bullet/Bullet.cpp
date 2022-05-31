#include "Bullet.h"

Bullet::Bullet(SceneGraph* sceneGraph, Vector3f* spawnPosition, float rotation)
{
	this->tag = "Bullet";
	this->sceneGraph = sceneGraph;
	this->direction = direction;

	//Set spawn position of the bullet
	this->transform->pivot_position->x = spawnPosition->x;
	this->transform->pivot_position->y = spawnPosition->y;

	//Set rotation of the bullet to match the direction of the player
	this->transform->euler_angles->z = rotation;

	//Initialize circle collider
	this->collider = std::make_unique<CircleCollider>(*this->transform.get(), 10);

	//Create the bullet mesh
	this->AddVertex(-2, -2, -1, 2.55f, 0.87f, 0.51f);
	this->AddVertex(2, -2, -1, 2.55f, 0.87f, 0.51f);
	this->AddVertex(2, 2, -1, 2.55f, 0.87f, 0.51f);
	this->AddVertex(-2, 2, -1, 2.55f, 0.87f, 0.51f);
}

Bullet::Bullet()
{

}

void Bullet::Update(float dt)
{
	/* Move bullet in same direction at constant speed */
	std::unique_ptr<Vector3f> velocity = std::make_unique<Vector3f>();
	velocity->y += bulletSpeed * dt;
	velocity->RotateZ(this->transform->euler_angles->z);

	this->Move(*velocity);

	/* If bullet is off screen, destroy the bullet */
	if (is_bullet_out_of_bounds()) {
		std::cout << "DESTROY BULLET" << std::endl;
		this->sceneGraph->RemoveGameObject(this);
	}
}

void Bullet::Render() {
	glBegin(GL_POLYGON);
		this->CreateVerticies();
	glEnd();

	//this->collider->RenderCircle();
}

bool Bullet::is_bullet_out_of_bounds() {
	bool out_of_bounds = false;
	if (this->transform->pivot_position->x > glutGet(GLUT_SCREEN_WIDTH) || this->transform->pivot_position->x < 0 ||
		this->transform->pivot_position->y > glutGet(GLUT_SCREEN_HEIGHT) || this->transform->pivot_position->y < 0) {
		out_of_bounds = true;
	}
	return out_of_bounds;
}

CircleCollider& Bullet::GetCollider() {
	return *this->collider;
}
