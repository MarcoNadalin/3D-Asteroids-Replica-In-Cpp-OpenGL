#include "Player.h"


Player::Player(InputManager* inputManager, SceneGraph* sceneGraph) : GameObject{}
{
    this->inputManager = inputManager;
    this->sceneGraph = sceneGraph;
    this->camera = std::make_shared<Camera>();
    this->load_identity_before_render = true;
}

Player::Player(InputManager* inputManager, SceneGraph* sceneGraph, float x, float y, float z) : GameObject{ x, y, z }
{
    this->inputManager = inputManager;
    this->sceneGraph = sceneGraph;
    this->camera = std::make_shared<Camera>();
    this->load_identity_before_render = true;
}

Player::Player(InputManager* inputManager, SceneGraph* sceneGraph, const char* obj_location, float x, float y, float z) : GameObject{obj_location, x, y, z }
{
    this->inputManager = inputManager;
    this->sceneGraph = sceneGraph;
    this->camera = std::make_shared<Camera>(this->inputManager, 0, 0, 0);
    this->load_identity_before_render = true;
}
    


void Player::Update(float dt)
{
    this->timeSinceLastShot += dt;
    MovePlayer(dt);

    if (inputManager->IsKeyPressed(' ')) {
        Shoot(dt);
    }
    

    CollisionWithWalls();
}

void Player::Render() {
    
    this->RenderVerticies(GL_TRIANGLES);
}


void Player::MovePlayer(float dt)
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


    if (this->inputManager->IsKeyPressed('a')) {
        
    }
    else if (this->inputManager->IsKeyPressed('d')) {
        
    }

    camera->Update(dt);
    camera->MoveCamera(camera->deltaMove);
}

void Player::Shoot(float dt)
{
    /* Checks if enough time has passed before the player can shoot */
    if (timeSinceLastShot >= fireRate) {
        std::cout << "SHOOT" << std::endl;
        this->timeSinceLastShot = 0;

        //Create bullet or rocket
        if (currentWeaponType == Normal) {
            std::shared_ptr<Vector3f> bulletDirection = std::make_shared<Vector3f>(camera->lx, camera->ly, camera->lz);
            std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(this->sceneGraph, camera->GetTransform()->pivot_position.get(), bulletDirection.get());
            //Add bullet to scene graph
            this->sceneGraph->AddGameObject(bullet);
        }    
    }
}

void Player::CollisionWithWalls()
{
    /* The cameras transform properties are being used instead of the player gameobject
       because this player is essensially a "child" of the camera. So this players
       pivot position is always (0,0,0) relative to the cameras position.
    */

    /* check Z position */
    if (camera->GetTransform()->pivot_position->z < -93.0f) {
        camera->GetTransform()->pivot_position->z = -90.0f;
    }
    else if (camera->GetTransform()->pivot_position->z > 93.0f) {
        camera->GetTransform()->pivot_position->z = 90.0f;
    }

    /* check X position */
    if (camera->GetTransform()->pivot_position->x < -93.0f) {
        camera->GetTransform()->pivot_position->x = -90.0f;
    }
    else if (camera->GetTransform()->pivot_position->x > 93.0f) {
        camera->GetTransform()->pivot_position->x = 90.0f;
    }

    /* check Y position */
    if (camera->GetTransform()->pivot_position->y < -93.0f) {
        camera->GetTransform()->pivot_position->y = -90.0f;
    }
    else if (camera->GetTransform()->pivot_position->y > 93.0f) {
        camera->GetTransform()->pivot_position->y = 90.0f;
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

