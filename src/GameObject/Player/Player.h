#ifndef PLAYER_H
#define PLAYER_H

# include <windows.h>
# include <GL/gl.h>
#include <memory>

#include "../GameObject.h"
#include "../../Input/InputManager.h"
#include "../../SceneGraph/SceneGraph.h"
#include "../Bullet/Bullet.h"
#include "../Components/CircleCollider.h"
#include "../Rocket/Rocket.h"
#include "../../Math/Math.h"
#include "../Turret/Turret.h"
#include "../../GameObject/Components/Camera.h"

enum WeaponType { Normal, SeekingRocket};

class Player : public GameObject
{
private:
	InputManager* inputManager;
	SceneGraph* sceneGraph;

	std::shared_ptr<Camera> camera;
	std::unique_ptr<CircleCollider> collider;
	std::unique_ptr<CircleCollider> near_wall_collider;

	/* Rocket Player Model */
	std::unique_ptr<std::vector<Vertex*>> playerRocket;

	/* Player Movement */
	float playerSpeed = 250.0f;
	float rotation_speed = 200.0f;
	float acceleration_rate = 15.0f;
	float decelleration_rate = 5.0f;
	float current_velocity = 0.0f;

	/* Shooting */
	WeaponType currentWeaponType = Normal;
	float time_since_weapon_switch = 0.f;
	float weapon_switch_time = 1.0f;

	float fireRate = 0.5f;
	float timeSinceLastShot = 0;
	int score = 0;

	void MovePlayer(float dt);
	void RotatePlayer(float dt);
	void Shoot(float dt);
	void Check_Collision();

public:
	bool reset_game = false;
	Player(InputManager* inputManager, SceneGraph* sceneGraph);
	Player(InputManager* inputManager, SceneGraph* sceneGraph, float x, float y, float z);
	Player(InputManager* inputManager, SceneGraph* sceneGraph, const char* obj_location, float x, float y, float z);
	void Update(float dt);
	void Render();

	void SetScore(int score);
	int GetScore();

	Camera* GetCamera() { return camera.get(); }

};

#endif


