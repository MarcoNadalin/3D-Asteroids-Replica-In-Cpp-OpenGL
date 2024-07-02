#ifndef ASTEROID_H
#define ASTEROID_H

#include <cmath>

#include <memory>
#include <vector>
#include "../Components/Transform.h"
#include "../GameObject.h"
#include "../../SceneGraph/SceneGraph.h"
#include "../../Math/Math.h"
#include "../Bullet/Bullet.h"
#include "../../Particle/ParticleGroup.h"


/**
* Class for an asteroid game object
*/
class Asteroid : public GameObject
{
private:
	SceneGraph* sceneGraph;
	std::unique_ptr<Vector3f> direction_rotation;
	std::unique_ptr<Vector3f> velocity_vector;
	float radius;

	int asteroid_speed = 15.0f;
	int rotation_speed = 50;
	int current_hit_points = 2;

	bool destroyed = false;
	bool went_in_viewpoint = false;
	
	/**
	* Removes this asteroid object from the scene graph
	*/
	void DestroyAsteroid();

public:
	Asteroid(SceneGraph* sceneGraph, Vector3f* spawnPosition, Vector3f* travel_position, float radius, float rotation);
	Asteroid();
	void Update(float dt);
	void Render();
	void Collision();
	bool InsideArena();
	bool LeftArena();
	void CollisionWithBullet(GameObject* bullet);
};

#endif


