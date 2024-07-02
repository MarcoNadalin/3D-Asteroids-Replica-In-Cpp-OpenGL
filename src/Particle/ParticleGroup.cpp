#include "ParticleGroup.h"

ParticleGroup::ParticleGroup(SceneGraph* sceneGraph, Vector3f* spawn_position, float life_time, const int& num_particles, const float& radius, const int& min_speed, const int& max_speed, const float& r, const float& g, const float& b) {
	this->particle_objects = std::make_unique<std::list<std::shared_ptr<GameObject>>>();

	this->sceneGraph = sceneGraph;

	this->num_particles = num_particles;
	this->radius = radius;
	this->max_speed = max_speed;
	this->min_speed = min_speed;
	this->life_time = life_time;

	this->r = r;
	this->g = g;
	this->b = b;

	this->transform->pivot_position->x = spawn_position->x;
	this->transform->pivot_position->y = spawn_position->y;

	this->CreateParticles();
}

void ParticleGroup::Update(float dt)
{
	/* update all particles */
	std::list<std::shared_ptr<GameObject>>::iterator it;
	for (it = particle_objects->begin(); it != particle_objects->end(); ++it) {
		if ((*it).get() != nullptr) {

			(*it)->Update(dt);
		}
	}

	/* Destroy this particle object if it has been alive for too long */
	this->time_elapsed += dt;
	if (this->time_elapsed >= life_time) {
		sceneGraph->RemoveGameObject(this);
	}
}

void ParticleGroup::Render()
{
	/* render all particles */
	
	std::list<std::shared_ptr<GameObject>>::iterator it;
	for (it = particle_objects->begin(); it != particle_objects->end(); ++it) {
		if ((*it).get() != nullptr) {			
			(*it)->RenderGameObject();
		}
	}
}

void ParticleGroup::CreateParticles()
{
	float rotation_step_amount = 360 / num_particles;
	float current_rotation = 0;
	for (int i = 0; i < num_particles; i++) {
		/* Calculate spawn position of particle*/
		Vector3f spawn = Vector3f(this->transform->pivot_position->x, this->transform->pivot_position->y, 0);
		spawn.y += this->radius;
		spawn.RotateZAroundOrigin(*this->transform->pivot_position, current_rotation);
		/* Calculate speed of particle */
		int speed = (std::rand() % max_speed) + min_speed;
		/* Add particle to particle array */
		std::shared_ptr<Particle> particle = std::make_shared<Particle>(speed, spawn.x, spawn.y, 0);
		particle->AddVertex(0.0f, 0.0f, 0.0f, r, g, b);
		
		particle->transform->euler_angles->z = current_rotation;
		this->particle_objects->push_back(particle);

		current_rotation += rotation_step_amount;
	}
}
