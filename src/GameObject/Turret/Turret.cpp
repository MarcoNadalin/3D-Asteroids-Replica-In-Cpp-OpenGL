#include "Turret.h"

Turret::Turret(SceneGraph* sceneGraph, const Vector3f& spawn_position)
{
	this->sceneGraph = sceneGraph;
	this->transform->pivot_position->x = spawn_position.x;
	this->transform->pivot_position->y = spawn_position.y;
	this->transform->pivot_position->z = 0;

	this->SetScale(0.5f);

	this->tag = "Turret";

	this->collider = std::make_unique<CircleCollider>(*this->transform, 40);

	/* Create Turret Vertecies */
	this->AddVertex(-40, 0, 0);
	this->AddVertex(-40, -40, 0);
	this->AddVertex(40, -40, 0);
	this->AddVertex(40, 0, 0);
	this->AddVertex(10, 0, 0);
	this->AddVertex(10, 30, 0);
	this->AddVertex(-10, 30, 0);
	this->AddVertex(-10, 0, 0);

	std::cout << "turret spawned" << std::endl;
}

void Turret::Update(float dt)
{
	/* update time since last shot */
	this->time_since_last_shot += dt;
	/* Get nearest asteroid */
	GameObject* nearest_asteroid = NearestGameObject();
	if (nearest_asteroid != nullptr) {
		float direction = this->transform->pivot_position->RotationToFaceTowards(*nearest_asteroid->transform->pivot_position);
		this->transform->euler_angles->z = direction;
	}

	/* Shoot automatically if an asteroid is in range */
	if (nearest_asteroid != nullptr) {
		Shoot();
	}

	/* Check for collision and destroy turret if it collids with an asteroid */
	this->CheckCollision();
}

void Turret::Render()
{
	glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
	this->CreateVerticies();
	glEnd();
}

void Turret::Shoot()
{
	/* Checks if enough time has passed before the player can shoot */
	if (time_since_last_shot >= fire_rate) {
		this->time_since_last_shot = 0;
		//Create bullet
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(this->sceneGraph, this->transform->pivot_position.get(), this->transform->euler_angles->z);
		//Add bullet to scene graph
		this->sceneGraph->AddGameObject(bullet);
	}
}

void Turret::CheckCollision()
{
	std::list<std::shared_ptr<GameObject>>::iterator it;
	std::list<std::shared_ptr<GameObject>>* gameObjects = this->sceneGraph->GetGameObjects();
	for (it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		GameObject* current_game_object = (*it).get();
		if (current_game_object != nullptr) {
			if (this->AsteroidCollision(current_game_object)) {
				return;
			}
		}
	}
}

bool Turret::AsteroidCollision(GameObject* gameObject)
{
	bool collided = false;
	if (gameObject->GetTag() == "Asteroid") {
		if (this->collider->CollidingWithCircle(gameObject->GetCollider())) {
			std::shared_ptr<ParticleGroup> particle = std::make_shared<ParticleGroup>(this->sceneGraph, transform->pivot_position.get(), 0.7f, 6, 5, 100, 150, 2.55f, 2.55f, 2.55f);
			this->sceneGraph->AddGameObject(particle);
			this->sceneGraph->RemoveGameObject(this);
			collided = true;
		}
	}
	return collided;
}

GameObject* Turret::NearestGameObject()
{
	float smallest_distance = -1;
	GameObject* current_nearest_gameobject = nullptr;
	std::list<std::shared_ptr<GameObject>>::iterator it;
	std::list<std::shared_ptr<GameObject>>* gameObjects = this->sceneGraph->GetGameObjects();
	for (it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		GameObject* current_game_object = (*it).get();
		if (current_game_object != nullptr && current_game_object->GetTag() == "Asteroid") {
			float current_distance = current_game_object->transform->pivot_position->Distance(*this->transform->pivot_position);
			if (current_distance < smallest_distance || smallest_distance < 0) {
				smallest_distance = current_distance;
				current_nearest_gameobject = current_game_object;
			}
		}
	}

	return current_nearest_gameobject;
}
