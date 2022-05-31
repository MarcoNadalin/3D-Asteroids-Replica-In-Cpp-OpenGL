#include "Rocket.h"

Rocket::Rocket(SceneGraph* sceneGraph, Vector3f* spawnPosition, float rotation)
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
	this->AddVertex(-2, -10, -1, 0.68f, 0.11f, 2.12f);
	this->AddVertex(2, -10, -1, 0.68f, 0.11f, 2.12f);
	this->AddVertex(2, 10, -1, 0.68f, 0.11f, 2.12f);
	this->AddVertex(-2, 10, -1, 0.68f, 0.11f, 2.12f);
}

Rocket::Rocket()
{

}

void Rocket::Update(float dt)
{
	std::unique_ptr<Vector3f> velocity = std::make_unique<Vector3f>();
	/* Get nearest asteroid */
	GameObject* nearest_asteroid = NearestGameObject();
	if (nearest_asteroid != nullptr) {
		float direction = this->transform->pivot_position->RotationToFaceTowards(*nearest_asteroid->transform->pivot_position);
		this->transform->euler_angles->z = direction;
	}
	/* Move bullet in same direction at constant speed */	
	velocity->y += bulletSpeed * dt;
	velocity->RotateZ(this->transform->euler_angles->z);

	this->Move(*velocity);

	/* If bullet is off screen, destroy the bullet */
	if (IsOutOfBounds()) {
		std::cout << "DESTROY ROCKET" << std::endl;
		this->sceneGraph->RemoveGameObject(this);
	}
}

void Rocket::Render() {
	glBegin(GL_POLYGON);
		this->CreateVerticies();
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(-2, 11, -1);
		glVertex3f(2, 11, -1);
	glEnd();
}

bool Rocket::IsOutOfBounds() {
	bool out_of_bounds = false;
	if (this->transform->pivot_position->x > glutGet(GLUT_SCREEN_WIDTH) || this->transform->pivot_position->x < 0 ||
		this->transform->pivot_position->y > glutGet(GLUT_SCREEN_HEIGHT) || this->transform->pivot_position->y < 0) {
		out_of_bounds = true;
	}
	return out_of_bounds;
}

GameObject* Rocket::NearestGameObject()
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

CircleCollider& Rocket::GetCollider() {
	return *this->collider;
}
