#include "Game.h"

Game::Game(InputManager* inputManager) {

	this->gui = std::make_unique<GUI>();
	
	this->sceneGraph = std::make_unique<SceneGraph>();

	this->inputManager = inputManager;	

	this->Init();
}

void Game::Init()
{
	const int SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	const int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);

	////////////////////////////////////////////////////////////
	//////////////////* LOAD TEXTURES *////////////////////////
	//////////////////////////////////////////////////////////
	assetloader::setFlipVerticallyOnLoad(true); // flip image vertically when loading texture
	//----------------skybox--------------//	
	GLuint sky_front = assetloader::loadTextureEdgeClamp("../assets/textures/sky_2/front.png");
	GLuint sky_top = assetloader::loadTextureEdgeClamp("../assets/textures/sky_2/top.png");
	GLuint sky_left = assetloader::loadTextureEdgeClamp("../assets/textures/sky_2/left.png");
	GLuint sky_right = assetloader::loadTextureEdgeClamp("../assets/textures/sky_2/right.png");
	GLuint sky_bottom = assetloader::loadTextureEdgeClamp("../assets/textures/sky_2/bottom.png");
	GLuint sky_back = assetloader::loadTextureEdgeClamp("../assets/textures/sky_2/back.png");


	GLuint spaceship = assetloader::loadTextureEdgeClamp("../assets/models/spaceship/body_dif.png");

	skybox = std::make_unique<Cubemap>(sky_front, sky_back, sky_top, sky_bottom, sky_left, sky_right);


	////////////////////////////////////////////////////////////
	////////////* CREATE AND POSITION GAME OBJECTS *///////////
	//////////////////////////////////////////////////////////
	this->player = std::make_shared<Player>(this->inputManager, this->sceneGraph.get(), "../assets/models/spaceship/spaceship_2.obj", 0, 0, 0);
	player->SetTexture(spaceship);
	player->SetScale(1);
	player->transform->euler_angles->y = 90; // rotating spaceship so it is oriented correctly in front of the camera
	player->transform->pivot_position->y = -0.8f; // moving it down slightly so the perspective is correct
	player->transform->pivot_position->z = 1.0f; // moving it forward so it doesnt clip through the camera
	this->active_camera = this->player->GetCamera();
	
	this->sceneGraph->AddGameObject(player);

	std::cout << "START!" << std::endl;
}

void Game::Update(float dt) {
	/* check if the scene needs to be reset */
	if (player->reset_game) {
		this->elapsed_round_time = glutGet(GLUT_ELAPSED_TIME);
		this->state = GameOver;
	}

	if (this->state == Playing) {
		/* Do wave calculations and asteroid spawns */
		this->UpdateRound(dt);
		/* call the update function on all game objects within the scene graph */
		this->sceneGraph->Update(dt);
	}
	else if (this->state == GameOver) {
		/* Check if player presses restart button, then call ResetGame() */
		if (this->inputManager->IsKeyPressed('r')) {
			ResetGame();
		}
	}
	else if (this->state == Paused) {
		if (this->inputManager->IsKeyPressed(' ')) {
			this->time_start_round = glutGet(GLUT_ELAPSED_TIME);
			this->state = Playing;
		}
	}
}

void Game::Render() {
	/* Rending game objects and time if the game is in a playing state */
	if (this->state == Playing) {
		/* Render skybox before lighting scene */
		if (this->skybox) {
			this->skybox->RenderCubemap(0, 0, 0);
		}
		/* Add lighting to scene */
		this->createLighting();
		/* Load identity matrix before performing translations / camera movements */
		glLoadIdentity();
		/* Render camera perspective */
		gluLookAt(active_camera->GetTransform()->pivot_position->x, active_camera->GetTransform()->pivot_position->y, active_camera->GetTransform()->pivot_position->z,
			active_camera->GetTransform()->pivot_position->x + active_camera->lx,
			active_camera->GetTransform()->pivot_position->y + active_camera->ly,
			active_camera->GetTransform()->pivot_position->z + active_camera->lz,
			0.0f, 1.0f, 0.0f);


		/* RENDER ALL OBJECTS WITHIN SCENE GRAPH */
		this->sceneGraph->Render();
	}
	/* Rending game over text if the game state is in a GameOver state */
	else if (this->state == GameOver) {

	}
	else if (this->state == Paused) {

	}
}

void Game::ResetGame()
{
	this->sceneGraph = std::make_unique<SceneGraph>();
	std::cout << "GAME RESET" << std::endl;
	this->current_wave = 0;
	
	this->state = Playing;

	Init();
}

bool pressed_k = false;
void Game::UpdateRound(float dt)
{
	time_since_last_asteroid_spawn += dt;
	int asteroids_to_be_destroyed = current_wave - sceneGraph->GetDestroyedAsteroidCount();
	/* The number of asteroids spawned per wave corresponds to the current wave, and only a certain number of asteroids are active at once */
	if ((time_since_last_asteroid_spawn >= asteroid_spawn_rate) && (asteroids_to_be_destroyed > 0) && (sceneGraph->GetAsteroidCount() < current_wave)) {
		SpawnAsteroid();
		num_asteroids_spawned_in_round++;
		time_since_last_asteroid_spawn = 0;
	}
	/* Start new round if all asteroids were destroyed */
	if (sceneGraph->GetDestroyedAsteroidCount() == current_wave) {
		time_since_last_asteroid_spawn = 0;
		sceneGraph->SetDestroyedAsteroidCount(0);
		num_asteroids_spawned_in_round = 0;
		current_wave++;
		std::cout << "WAVE " << current_wave << std::endl;
	}	
}

void Game::SpawnAsteroid()
{
	/* CALCULATE SPAWN POINTS */
	float pos_x = rand() % 120;
	float pos_y = rand() % 120;
	float pos_z = rand() % 120;

	if (rand() > rand()) {
		pos_x *= -1;
	}
	if (rand() > rand()) {
		pos_y *= -1;
	}
	if (rand() > rand()) {
		pos_z *= -1;
	}


	Vector3f spawnPosition = Vector3f(pos_x, pos_y, pos_z);
	Vector3f playerPosition = Vector3f(active_camera->GetTransform()->pivot_position->x,
		active_camera->GetTransform()->pivot_position->y,
		active_camera->GetTransform()->pivot_position->z);

	Vector3f velocityVector = playerPosition.Subtract(spawnPosition);
	Vector3f normVelocityVector = velocityVector.Normalize();

	/* END CALCULATION FOR MOVE TOWARDS VECTOR */
	std::shared_ptr<Asteroid> asteroid = std::make_shared<Asteroid>(this->sceneGraph.get(), &spawnPosition, &normVelocityVector,15.0f, 10);
	this->sceneGraph->AddGameObject(asteroid);
	int count = this->sceneGraph->GetAsteroidCount() + 1;
	this->sceneGraph->SetAsteroidCount(count);
	std::cout << "ASTEROID SPAWNED" << std::endl;
}

void Game::createLighting()
{
	float light_position_1[] = { 0.4, 0.2, 0.4, 1 };
	float light_ambient[] = { 1.0f, 1.0f, 0.5f, 0.5f };
	float light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat color[4] = { 0.20, 0.20, 0.20, 1.00 };
	GLfloat spec[4] = { 0.30, 0.30, 0.30, 1.00 };
	GLfloat shiny = 8.0;

	float mat_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float mat_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
}
