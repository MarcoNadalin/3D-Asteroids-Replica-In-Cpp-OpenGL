#include "Player.h"


Player::Player(InputManager* inputManager, SceneGraph* sceneGraph) : GameObject{}
{
    this->inputManager = inputManager;
    this->sceneGraph = sceneGraph;
}

Player::Player(InputManager* inputManager, SceneGraph* sceneGraph, float x, float y, float z) : GameObject{ x, y, z }
{
    this->SetScale(0.5f);
    this->inputManager = inputManager;
    this->sceneGraph = sceneGraph;

    this->playerRocket = std::make_unique<std::vector<Vertex*>>();

    this->collider = std::make_unique<CircleCollider>(*this->transform.get(), 65);
    this->near_wall_collider = std::make_unique<CircleCollider>(*this->transform.get(), 130);

    /* non-rocket model*/
    this->AddVertex(-40, -40, -1);
    this->AddVertex(0, -20, -1);
    this->AddVertex(0, 0, -1);
    this->AddVertex(0, -20, -1);
    this->AddVertex(40, -40, -1);
    this->AddVertex(0, 50, -1);

    /* rocket model */
    this->AddVertex(*this->playerRocket, -40, -40, -1);
    this->AddVertex(*this->playerRocket, 0, -40, -1);
    this->AddVertex(*this->playerRocket, 0, -20, -1);
    this->AddVertex(*this->playerRocket, 0, -40, -1);
    this->AddVertex(*this->playerRocket, 40, -40, -1);
    this->AddVertex(*this->playerRocket, 0, 50, -1);
}
    


void Player::Update(float dt)
{
    this->Check_Collision();
    //this->MovePlayer(dt);
    this->RotatePlayer(dt);

    /* Update player score */
    this->score = sceneGraph->total_num_destroyed_asteroids - (turrets_spawned * turret_cost);
    
    /* update weapon switch timer, so holding 'r' doesnt rapidly switch weapons */
    this->time_since_weapon_switch += dt;
    /* Switch Weapon */
    if (this->inputManager->IsKeyPressed('r') && time_since_weapon_switch >= weapon_switch_time) {
        this->currentWeaponType == Normal ? currentWeaponType = SeekingRocket : currentWeaponType = Normal;
        time_since_weapon_switch = 0;
    }

    /* Keep rotation value within 0 - 360 degrees */
    if (this->transform->euler_angles->z < 0) {
        this->transform->euler_angles->z += 360;
    }
    else if (this->transform->euler_angles->z > 360) {
        this->transform->euler_angles->z -= 360;
    }

    /* Update time since last shot*/
    this->timeSinceLastShot += dt;

    /* Shoot if spacebar is pressed */
    if (this->inputManager->IsKeyPressed(' ')) {
        this->Shoot(dt);
    }   

    this->time_since_turret_deploy += dt;
    /* Spawn turret if 'x' is pressed and a turret currently isnt in game */
    if (this->inputManager->IsKeyPressed('x') && this->sceneGraph->GetNumberOfObjects("Turret") < 2 && this->score >= turret_cost && time_since_turret_deploy >= turret_deploy_time) {
        this->SpawnTurret();
        this->time_since_turret_deploy = 0.0f;
    }


    
}

void Player::Render() {
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    if (currentWeaponType == Normal) {
        glVertex3f(-40, -40, -1);
        glVertex3f(0, -20, -1);
        glVertex3f(0, 0, -1);
        glVertex3f(0, -20, -1);
        glVertex3f(40, -40, -1);
        glVertex3f(0, 50, -1);
    }
    else if (currentWeaponType == SeekingRocket) {
        glVertex3f(-40, -40, -1);
        glVertex3f(0, -40, -1);
        glVertex3f(0, -20, -1);
        glVertex3f(0, -40, -1);
        glVertex3f(40, -40, -1);
        glVertex3f(0, 50, -1);
    }    
    
    glEnd();
}


void Player::MovePlayer(float dt)
{
    /* Initialise the velocity vector as 0,0,0 */
    Vector3f velocity = Vector3f();

    /* Moves player in direction its facing. */
    if (this->inputManager->IsKeyPressed('w')) {
        /* Add velocity to the y */
        current_velocity += acceleration_rate;
        current_velocity = Clamp(current_velocity, 0.0f, playerSpeed);
        velocity.y += current_velocity * dt;
        /* Set direction of velocity vector to the direction the player is facing */
        velocity.RotateZ(this->transform->euler_angles->z);
        this->Move(velocity);
    }
    else if (this->inputManager->IsKeyPressed('s')) {
        current_velocity -= acceleration_rate;
        current_velocity = Clamp(current_velocity, -playerSpeed, 0);
        velocity.y += current_velocity * dt;
        /* Set direction of velocity vector to the direction the player is facing */
        velocity.RotateZ(this->transform->euler_angles->z);
        this->Move(velocity);
    }
    /* If the a key isnt being pressed, start decellerating */
    else {
        if (current_velocity < 0) {
            current_velocity += decelleration_rate;
            current_velocity = Clamp(current_velocity, -playerSpeed, 0.0f);
            velocity.y += current_velocity * dt;
            /* Set direction of velocity vector to the direction the player is facing */
            velocity.RotateZ(this->transform->euler_angles->z);
            this->Move(velocity);
        }
        else {
            current_velocity -= decelleration_rate;
            current_velocity = Clamp(current_velocity, 0.0f, playerSpeed);
            velocity.y += current_velocity * dt;
            /* Set direction of velocity vector to the direction the player is facing */
            velocity.RotateZ(this->transform->euler_angles->z);
            this->Move(velocity);
        }
        
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
            std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(this->sceneGraph, this->transform->pivot_position.get(), this->transform->euler_angles->z);
            //Add bullet to scene graph
            this->sceneGraph->AddGameObject(bullet);
        }
        else {
            std::shared_ptr<Rocket> rocket = std::make_shared<Rocket>(this->sceneGraph, this->transform->pivot_position.get(), this->transform->euler_angles->z);
            //Add bullet to scene graph
            this->sceneGraph->AddGameObject(rocket);
        }       
    }
}

void Player::SpawnTurret()
{
    this->turrets_spawned++;
    std::shared_ptr<Turret> turret = std::make_shared<Turret>(this->sceneGraph, *this->transform->pivot_position);
    this->sceneGraph->AddGameObject(turret);
}

void Player::Check_Collision() {
    std::list<std::shared_ptr<GameObject>>::iterator it;
    std::list<std::shared_ptr<GameObject>>* gameObjects = this->sceneGraph->GetGameObjects();
    for (it = gameObjects->begin(); it != gameObjects->end(); ++it) {
        GameObject* current_game_object = (*it).get();
        if (current_game_object != nullptr) {
            this->Check_Wall_Collision(current_game_object);
            this->AsteroidCollision(current_game_object);
        }        
    }
}

void Player::Check_Wall_Collision(GameObject* gameObject) {
    if (gameObject->GetTag() == "LEFT_WALL") {

        if ((transform->pivot_position->x - near_wall_collider->radius) < gameObject->transform->pivot_position->x) {
            gameObject->ChangeColour(1, 0, 0);
            if ((transform->pivot_position->x - collider->radius) < gameObject->transform->pivot_position->x) {
                this->reset_game = true;
            }
        }
        else {
            gameObject->ChangeColour(255, 255, 255);
        }
    }

    if (gameObject->GetTag() == "RIGHT_WALL") {
        if ((transform->pivot_position->x + near_wall_collider->radius) > gameObject->transform->pivot_position->x) {
            gameObject->ChangeColour(1, 0, 0);
            if ((transform->pivot_position->x + collider->radius) > gameObject->transform->pivot_position->x) {
                this->reset_game = true;
            }
        }
        else {
            gameObject->ChangeColour(255, 255, 255);
        }
    }

    if (gameObject->GetTag() == "TOP_WALL") {
        if ((transform->pivot_position->y + near_wall_collider->radius) > gameObject->transform->pivot_position->y) {
            gameObject->ChangeColour(1, 0, 0);
            if ((transform->pivot_position->y + collider->radius) > gameObject->transform->pivot_position->y) {
                this->reset_game = true;
            }
        }
        else {
            gameObject->ChangeColour(255, 255, 255);
        }
    }

    if (gameObject->GetTag() == "BOTTOM_WALL") {
        if ((transform->pivot_position->y - near_wall_collider->radius) < gameObject->transform->pivot_position->y) {
            gameObject->ChangeColour(1, 0, 0);
            if ((transform->pivot_position->y - collider->radius) < gameObject->transform->pivot_position->y) {
                this->reset_game = true;
            }
        }
        else {
            gameObject->ChangeColour(255, 255, 255);
        }
    }
}

void Player::AsteroidCollision(GameObject* gameObject) {
    if (gameObject->GetTag() == "Asteroid") {
        if (this->collider->CollidingWithCircle(gameObject->GetCollider())) {
            this->reset_game = true;
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

