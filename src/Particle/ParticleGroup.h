#ifndef PARTICLEGROUP_H
#define PARTICLEGROUP_H

#include "../GameObject/GameObject.h"
#include "../SceneGraph/SceneGraph.h"
#include "Particle.h"
#include "../Math/Vector3f.h"
#include "../Math/Math.h"

class ParticleGroup : public GameObject
{
private:
	std::unique_ptr<std::list<std::shared_ptr<GameObject>>> particle_objects;
	SceneGraph* sceneGraph = nullptr;

	Vector3f* spawn_position;

	/* Particle Attributes */
	float radius = 50;
	int num_particles = 12;
	int min_speed = 5;
	int max_speed = 10;

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	

	float life_time = 5.0f;
	float time_elapsed = 0.0f;

	void CreateParticles();

public:
	ParticleGroup(SceneGraph* sceneGraph, Vector3f* spawn_position, float life_time, const int& num_particles, const float& radius, const int& min_speed, const int& max_speed, const float& r, const float& g, const float& b);
	void Update(float dt);
	void Render();
};

#endif