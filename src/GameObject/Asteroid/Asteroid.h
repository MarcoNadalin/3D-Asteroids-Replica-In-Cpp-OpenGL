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
	float radius;
	int num_verticies = 16;
	/* Randomize asteroid speed between 150 and 200 */
	const int MIN_ASTEROID_SPEED = 150;
	const int MAX_ASTEROID_SPEED = 210;
	int asteroid_speed = 350;
	int rotation_speed = 50;
	int clockwise_rotation = 1; // 1 = clockwise, -1 = anti-clockwise 
	/* save randomized values when generating asteroid in vector */
	std::unique_ptr<std::vector<int>> random_values;

	bool destroyed = false;

	std::unique_ptr<CircleCollider> collider;

	int max_hitpoints = 3;
	int current_hit_points = max_hitpoints;

	bool went_in_viewpoint = false;
	
	/**
	* Removes this asteroid object from the scene graph
	*/
	void DestroyAsteroid();

	/**
	* Checks if is colliding with a bullet
	* 
	* @param bullet the bullet game object to check if this asteroid is colliding with
	*/
	void CollisionWithBullet(GameObject* bullet);

	/**
	* Checks if is colliding with a wall
	* 
	* @param wall the wall game object
	* @return bool true if colliding with wall
	*/
	bool CollisionWithWalls(GameObject* wall);

	/**
	* Performs all collision checks
	*/
	void Collision();

public:
	Asteroid(SceneGraph* sceneGraph, Vector3f* spawnPosition, float radius, float rotation);
	Asteroid();
	void Update(float dt);
	void Render();

	void CreateCartesianCircle(float rad, int vertexes);
	void GenerateRandomAsteroidValues();
};

#endif


