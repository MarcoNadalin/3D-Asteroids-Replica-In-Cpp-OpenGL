#ifndef BULLET_H
#define BULLET_H

# include <windows.h>
# include <GL/gl.h>
#include <cmath>

#include <memory>
#include <vector>
#include "../Components/Transform.h"
#include "../Components/CircleCollider.h"
#include "../../SceneGraph/SceneGraph.h"

#include <iostream>

class Bullet : public GameObject
{
private:
	SceneGraph* sceneGraph;
	Vector3f* direction;
	float bulletSpeed = 600;
	float bulletRotation = 0;

	
	float collider_radius = 0.5;


	bool is_bullet_out_of_bounds();

public:
	Bullet(SceneGraph* sceneGraph, Vector3f* spawnPosition, float rotation);
	Bullet();
	void Update(float dt);
	void Render();

	std::unique_ptr<CircleCollider> collider;

	CircleCollider& GetCollider();

};

#endif


