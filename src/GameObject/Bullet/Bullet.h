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
	std::unique_ptr<Vector3f> direction;
	float bulletSpeed = 65.0f;
	float bulletRotation = 0;

	bool is_bullet_out_of_bounds();

public:
	Bullet(SceneGraph* sceneGraph, Vector3f* spawnPosition, Vector3f* direrction);
	Bullet();
	void Update(float dt);
	void Render();
};

#endif


