#ifndef PARTICLECREATOR_H
#define PARTICLECREATOR_H

#include <memory>

#include "Particle.h"
#include "../SceneGraph/SceneGraph.h"
#include "../Math/Vector3f.h"

class Particle : public GameObject
{
private:
	float speed = 5.0f;
	float current_speed = 5.0f;
	float min_speed = 0.5f;
	int decelleration_rate = 15.0f;
public:
	Particle(const float& speed, const float& x, const float& y, const float& z);
	void Update(float dt);
	void Render();
};

#endif