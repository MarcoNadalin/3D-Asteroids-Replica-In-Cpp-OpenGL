#include "Asteroid.h"

Asteroid::Asteroid(SceneGraph* sceneGraph, Vector3f* spawnPosition, float radius, float rotation)
{
	this->sceneGraph = sceneGraph;
	this->direction_rotation = std::make_unique<Vector3f>();
	this->direction_rotation->z = rotation;

	if (this->direction_rotation->z < 0) {
		this->direction_rotation->z += 360;
	}

	this->collider = std::make_unique<CircleCollider>(*this->transform.get(), radius);

	//Set spawn position of the bullet
	this->transform->pivot_position->x = spawnPosition->x;
	this->transform->pivot_position->y = spawnPosition->y;

	this->radius = radius;
	this->tag = "Asteroid";

	/* Randomize asteroid speed and rotation speed */
	this->asteroid_speed = rand() % MIN_ASTEROID_SPEED + MAX_ASTEROID_SPEED;
	this->rotation_speed = rand() % 50 + 100;

	/* Set rotation*/
	rand() % 2 == 0 ? clockwise_rotation = 1 : clockwise_rotation = -1;

	/* initialise vector containing random values for asteroid generation */
	random_values = std::make_unique<std::vector<int>>();
	GenerateRandomAsteroidValues();

	/* Set up asteroid hitpoints based off radius */
	if (this->radius < 60) {
		this->max_hitpoints = 2;
		this->current_hit_points = 2;
	}
	else if (this->radius >= 60) {
		this->max_hitpoints = 3;
		this->current_hit_points = 3;
	}
}

Asteroid::Asteroid()
{

}

void Asteroid::Update(float dt)
{
	/* rotate asteroid at constant speed */
	//this->transform->euler_angles->z += rotation_speed * clockwise_rotation * dt;
	/* update direction rotation so the value isnt negative */
	if (this->direction_rotation->z < 0) {
		direction_rotation->z += 360;
	}
	/* if asteroid has 0 hitpoints, destroy it */
	if (current_hit_points <= 0) {
		this->destroyed = true;
		/* update asteroid count before destroying */
		int count = sceneGraph->GetAsteroidCount() - 1;
		sceneGraph->SetAsteroidCount(count);
		sceneGraph->SetDestroyedAsteroidCount(sceneGraph->GetDestroyedAsteroidCount() + 1);
		sceneGraph->total_num_destroyed_asteroids += 1;
		this->DestroyAsteroid();
		/* if the asteroid should be destroyed, end the update function early to prevent nullptr error */
		return;
	}

	/* check if asteroid went on screen, so it can be destroyed once it leaves the arena */
	if ((this->transform->pivot_position->x + radius + 5 < glutGet(GLUT_SCREEN_WIDTH) && this->transform->pivot_position->x - radius - 5 > 0) &&
		(this->transform->pivot_position->y + radius + 5 < glutGet(GLUT_SCREEN_HEIGHT)  && this->transform->pivot_position->y - radius - 5 > 0) && !went_in_viewpoint) {
		this->went_in_viewpoint = true;
		std::cout << "ASTEROID ENTERED ARENA" << std::endl;
	}

	/* collision check for asteroid */
	this->Collision();

	/* Move asteroid in same direction at constant speed, unless hitting a wall */
	std::unique_ptr<Vector3f> velocity = std::make_unique<Vector3f>();
	velocity->y += asteroid_speed * dt;
	velocity->RotateZ(direction_rotation->z);

	this->Move(*velocity);


	/* If asteroid is off screen, destroy the asteroid */
	if ((this->transform->pivot_position->x > glutGet(GLUT_SCREEN_WIDTH) + radius || this->transform->pivot_position->x < 0 - radius ||
		this->transform->pivot_position->y > glutGet(GLUT_SCREEN_HEIGHT) + radius || this->transform->pivot_position->y < 0 - radius) && went_in_viewpoint) {

		/* update asteroid count before destroying */
		int count = sceneGraph->GetAsteroidCount() - 1;
		sceneGraph->SetAsteroidCount(count);
		std::cout << "ASTEROID DESTROYED" << std::endl;
		this->DestroyAsteroid();
	}

}

void Asteroid::Render() {
	glLineWidth(2.0f);

	glBegin(GL_LINE_LOOP);
	this->CreateCartesianCircle(this->radius, num_verticies);
	glEnd();
}

void Asteroid::CreateCartesianCircle(float rad, int vertexes)
{
	float x, y;

	vertexes /= 2;

	for (int i = 0; i < vertexes; i++)
	{
		x = ((i / (float)vertexes - 0.5) * 2.0) * rad;
		y = sqrt(rad * rad - x * x) - (random_values->at(i));
		glColor3f(1.76f, 0.38f, 2.55f);
		glVertex2f(x, y);
	}

	for (int i = vertexes; i > 0; i--)
	{
		x = (i / (float)vertexes - 0.5) * 2.0 * rad;
		y = -sqrt(rad * rad - x * x) - (random_values->at(i));
		glColor3f(1.76f, 0.38f, 2.55f);
		glVertex2f(x, y);
	}
}

bool Asteroid::CollisionWithWalls(GameObject* wall)
{
	if (wall->GetTag() == "LEFT_WALL") {		
		if (transform->pivot_position->x - radius <= wall->transform->pivot_position->x) {
			this->direction_rotation->ReflectLeft(*direction_rotation);
			this->transform->pivot_position->x += 5;
			return true;
		}			
	}	

	if (wall->GetTag() == "RIGHT_WALL") {
		if (transform->pivot_position->x + radius >= wall->transform->pivot_position->x) {
			this->direction_rotation->ReflectRight(*direction_rotation);
			this->transform->pivot_position->x -= 5;
			return true;
		}
	}

	if (wall->GetTag() == "TOP_WALL") {
		if (transform->pivot_position->y + radius >= wall->transform->pivot_position->y) {
			this->direction_rotation->ReflectUp(*direction_rotation);
			this->transform->pivot_position->y -= 5;
			return true;
		}
	}

	if (wall->GetTag() == "BOTTOM_WALL") {
		if (transform->pivot_position->y - radius <= wall->transform->pivot_position->y) {
			this->direction_rotation->ReflectDown(*direction_rotation);
			this->transform->pivot_position->y += 5;
			return true;
		}
	}
	return false;
}

void Asteroid::GenerateRandomAsteroidValues()
{
	for (int i = 0; i < num_verticies; i++) {
		random_values->push_back(rand() % 20);
	}
}

void Asteroid::Collision() {
	std::list<std::shared_ptr<GameObject>>::iterator it;
	std::list<std::shared_ptr<GameObject>>* gameObjects = this->sceneGraph->GetGameObjects();
	for (it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		GameObject* current_game_object = (*it).get();

		if (current_game_object != nullptr && current_game_object->GetTag() == "Bullet") {
			CollisionWithBullet(current_game_object);
		}

		else if (current_game_object != nullptr && went_in_viewpoint == true) {
			if (CollisionWithWalls(current_game_object)) {
				/* Change rotation direction when asteroid hits wall */
				clockwise_rotation *= -1;
			}
		}
	}
}

void Asteroid::DestroyAsteroid()
{
	std::shared_ptr<ParticleGroup> particle = std::make_shared<ParticleGroup>(this->sceneGraph, transform->pivot_position.get(), 0.7f, 12, this->radius - 10, 100, 150, 1.76f, 0.38f, 2.55f);
	this->sceneGraph->AddGameObject(particle);
	this->sceneGraph->RemoveGameObject(this);
}

void Asteroid::CollisionWithBullet(GameObject* bullet)
{
	CircleCollider* bullet_collider = bullet->GetCollider();
	/* if asteroid is colliding with the bullet */
	if (this->collider->CollidingWithPoint(*bullet->transform->pivot_position)) {
		/* Despawn the bullet */
		this->sceneGraph->RemoveGameObject(bullet);
		this->current_hit_points--;
	}
}
