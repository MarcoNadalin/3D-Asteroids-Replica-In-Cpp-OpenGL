#ifndef ROCKET_H
#define ROCKET_H

# include <windows.h>
# include <GL/gl.h>
#include <cmath>

#include <memory>
#include <vector>
#include "../Components/Transform.h"
#include "../Components/CircleCollider.h"
#include "../../SceneGraph/SceneGraph.h"

#include <iostream>

class Rocket : public GameObject
{
private:
	SceneGraph* sceneGraph;
	Vector3f* direction;
	float bulletSpeed = 300;
	float bulletRotation = 0;

	float rotation_speed = 0.2f;

	
	float collider_radius = 0.5;

	bool IsOutOfBounds();
	GameObject* NearestGameObject();

public:
	Rocket(SceneGraph* sceneGraph, Vector3f* spawnPosition, float rotation);
	Rocket();
	void Update(float dt);
	void Render();

	std::unique_ptr<CircleCollider> collider;

	CircleCollider& GetCollider();

};

#endif


