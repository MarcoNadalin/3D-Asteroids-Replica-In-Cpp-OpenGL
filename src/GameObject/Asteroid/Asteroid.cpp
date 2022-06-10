#include "Asteroid.h"

Asteroid::Asteroid(SceneGraph* sceneGraph, Vector3f* spawnPosition, Vector3f* travel_position, float radius, float rotation)
{
	this->sceneGraph = sceneGraph;

	//Set velocity vector
	std::cout << "x: " << travel_position->x << ", y: " << travel_position->y << ", z: " << travel_position->z << std::endl;
	this->velocity_vector = std::make_unique<Vector3f>(travel_position->x, travel_position->y, travel_position->z);

	//Set spawn position of the asteroid
	this->transform->pivot_position->x = spawnPosition->x;
	this->transform->pivot_position->y = spawnPosition->y;
	this->transform->pivot_position->z = spawnPosition->z;

	/* set rotation */
	this->transform->euler_angles->x = travel_position->x;

	this->radius = radius;
	this->tag = "Asteroid";

	this->radius = radius;

}

Asteroid::Asteroid()
{

}

void Asteroid::Update(float dt)
{
	/* Move Asteroid towards player */
	Vector3f vel = Vector3f(velocity_vector->x, velocity_vector->y, velocity_vector->z);
	vel.Multiply(dt * asteroid_speed);
	this->Move(vel);
	
	/* check if in arena */
	if (!went_in_viewpoint && InsideArena()) {
		went_in_viewpoint = true;
		std::cout << "ASTEROID ENTERED ARENA" << std::endl;
	}

	/* Check Collision */
	Collision();

	/* check if asteroid has left arena */
	if (LeftArena() && went_in_viewpoint) {
		/* update asteroid count before destroying */
		int count = sceneGraph->GetAsteroidCount() - 1;
		sceneGraph->SetAsteroidCount(count);
		std::cout << "ASTEROID LEFT ARENA AND IS DESTROYED" << std::endl;
		this->DestroyAsteroid();
		return;
	}


	if (this->current_hit_points <= 0) {
		/* update asteroid count before destroying */
		int count = sceneGraph->GetAsteroidCount() - 1;
		sceneGraph->SetAsteroidCount(count);
		sceneGraph->SetDestroyedAsteroidCount(sceneGraph->GetDestroyedAsteroidCount() + 1);
		sceneGraph->total_num_destroyed_asteroids += 1;
		this->DestroyAsteroid();
		return;
	}

}

void Asteroid::Render() {
	glutSolidSphere(radius, 12, 12);
	glFlush();
}

void Asteroid::Collision() {
	std::list<std::shared_ptr<GameObject>>::iterator it;
	std::list<std::shared_ptr<GameObject>>* gameObjects = this->sceneGraph->GetGameObjects();
	for (it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		GameObject* current_game_object = (*it).get();

		if (current_game_object != nullptr && current_game_object->GetTag() == "Bullet") {
			CollisionWithBullet(current_game_object);
		}
	}
}

bool Asteroid::InsideArena()
{
	bool inside = false;
	/* check if asteroid went on screen, so it can be destroyed once it leaves the arena */
	if ((this->transform->pivot_position->x + radius < 100 && this->transform->pivot_position->x - radius > -100) &&
		(this->transform->pivot_position->y + radius < 100 && this->transform->pivot_position->y - radius > -100) && 
		(this->transform->pivot_position->z + radius < 100 && this->transform->pivot_position->z - radius > -100)) {
		inside = true;
	}

	return inside;
}

bool Asteroid::LeftArena()
{
	bool left = false;
	/* check if asteroid went on screen, so it can be destroyed once it leaves the arena */
	if ((this->transform->pivot_position->x > 100 + radius || this->transform->pivot_position->x < -100 - radius) ||
		(this->transform->pivot_position->y > 100 + radius || this->transform->pivot_position->y < -100 - radius) ||
		(this->transform->pivot_position->z > 100 + radius || this->transform->pivot_position->z < -100 - radius)) {
		left = true;
	}

	return left;
}

void Asteroid::CollisionWithBullet(GameObject* bullet)
{
	/* if asteroid is colliding with the bullet */
	float distance = bullet->transform->pivot_position->Distance(*this->transform->pivot_position);
	if (distance < this->radius) {
		/* Despawn the bullet */
		this->sceneGraph->RemoveGameObject(bullet);
		this->current_hit_points--;
	}
}

void Asteroid::DestroyAsteroid()
{
	//std::shared_ptr<ParticleGroup> particle = std::make_shared<ParticleGroup>(this->sceneGraph, transform->pivot_position.get(), 0.7f, 12, this->radius - 10, 100, 150, 1.76f, 0.38f, 2.55f);
	//this->sceneGraph->AddGameObject(particle);
	this->sceneGraph->RemoveGameObject(this);
}
