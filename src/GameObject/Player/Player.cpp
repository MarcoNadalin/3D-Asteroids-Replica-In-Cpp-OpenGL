#include "Player.h"


Player::Player(InputManager* inputManager, SceneGraph* sceneGraph) : GameObject{}
{
    this->inputManager = inputManager;
    this->sceneGraph = sceneGraph;
    this->camera = std::make_shared<Camera>();
}

Player::Player(InputManager* inputManager, SceneGraph* sceneGraph, float x, float y, float z) : GameObject{ x, y, z }
{
    this->inputManager = inputManager;
    this->sceneGraph = sceneGraph;
    this->camera = std::make_shared<Camera>();
}

Player::Player(InputManager* inputManager, SceneGraph* sceneGraph, const char* obj_location, float x, float y, float z) : GameObject{obj_location, x, y, z }
{
    this->inputManager = inputManager;
    this->sceneGraph = sceneGraph;
    this->camera = std::make_shared<Camera>(this->inputManager, 0, 0, 0);
}
    


void Player::Update(float dt)
{
    if (this->inputManager->IsKeyPressed('w')) {
        camera->deltaMove = 1.5f;
    }
    else if (this->inputManager->IsKeyPressed('s')) {
        camera->deltaMove = -1.5f;
    }
    else {
        camera->deltaMove = 0;
    }
    camera->Update(dt);
    camera->MoveCamera(camera->deltaMove);
}

void Player::Render() {
    
    this->RenderVerticies(GL_TRIANGLES);
}


void Player::MovePlayer(float dt)
{
    /* Initialise the velocity vector as 0,0,0 */
    Vector3f velocity = Vector3f();

    /* Moves player in direction its facing. */
    if (this->inputManager->IsKeyPressed('w')) {
        /* Add velocity to the y */

    }
    else if (this->inputManager->IsKeyPressed('s')) {

    }
    /* If the a key isnt being pressed, start decellerating */
    else {
        
    }
}

void Player::Shoot(float dt)
{
    /* Checks if enough time has passed before the player can shoot */
    if (timeSinceLastShot >= fireRate) {
        std::cout << "SHOOT" << std::endl;
        this->timeSinceLastShot = 0;

        //Create bullet or rocket
        if (currentWeaponType == Normal) {
            //std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(this->sceneGraph, this->transform->pivot_position.get(), this->transform->euler_angles->z);
            //Add bullet to scene graph
            //this->sceneGraph->AddGameObject(bullet);
        }
        else {
            //std::shared_ptr<Rocket> rocket = std::make_shared<Rocket>(this->sceneGraph, this->transform->pivot_position.get(), this->transform->euler_angles->z);
            //Add bullet to scene graph
            //this->sceneGraph->AddGameObject(rocket);
        }       
    }
}

void Player::RotatePlayer(float dt) {
    if (this->inputManager->IsKeyPressed('a')) {
        this->transform->euler_angles->z += rotation_speed * dt;
    }
    else if (this->inputManager->IsKeyPressed('d')) {
        this->transform->euler_angles->z -= rotation_speed * dt;
    }
}


void Player::SetScore(int score)
{
    this->score = score;
}

int Player::GetScore()
{
    return this->score;
}

