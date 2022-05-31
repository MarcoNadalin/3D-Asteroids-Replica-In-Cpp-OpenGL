#ifndef TURRET_H
#define TURRET_H

#include <memory>
#include "../GameObject.h"
#include "../Components/CircleCollider.h"
#include "../../SceneGraph/SceneGraph.h"
#include "../../Math/Vector3f.h"
#include "../Bullet/Bullet.h"
#include "../../Particle/ParticleGroup.h"

/**
* Class for deployable turret game object.
*/
class Turret : public GameObject
{
private:
	SceneGraph* sceneGraph;
	std::unique_ptr<CircleCollider> collider;

	float detection_radius = 100.0f;
	float fire_rate = 2.5f;
	float time_since_last_shot = 0.0f;

public:

	Turret(SceneGraph* sceneGraph, const Vector3f& spawn_position);

	void Update(float dt);
	void Render();

	void Shoot();

	void CheckCollision();
	bool AsteroidCollision(GameObject* gameObject);

	GameObject* NearestGameObject();

};

#endif