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
	
	
	/* ADD GAME OBJEJCTS TO SCENE GRAPH */
	this->sceneGraph->AddGameObject(this->player);
	
	std::cout << "START!" << std::endl;
}

void Game::Update(float dt) {
	/* check if the scene needs to be reset */
	if (player->reset_game) {
		this->elapsed_round_time = glutGet(GLUT_ELAPSED_TIME);
		this->time_start_round = glutGet(GLUT_ELAPSED_TIME);
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
	/* UI that is displayed if the game is in a playing state, or gameover state */
	std::string wave_text = "WAVE: " + std::to_string(current_wave);
	this->gui->WriteText(wave_text, glutGet(GLUT_SCREEN_WIDTH) / 2 - 170, glutGet(GLUT_SCREEN_HEIGHT) - 50);

	std::string score_text = "SCORE: " + std::to_string(player->GetScore());
	this->gui->WriteText(score_text, glutGet(GLUT_SCREEN_WIDTH) / 2 - 20, glutGet(GLUT_SCREEN_HEIGHT) - 50);

	/* Rending game objects and time if the game is in a playing state */
	if (this->state == Playing) {
		std::string time_text = "TIME: " + std::to_string((glutGet(GLUT_ELAPSED_TIME) - time_start_round) / 1000);
		this->gui->WriteText(time_text, glutGet(GLUT_SCREEN_WIDTH) / 2 + 120, glutGet(GLUT_SCREEN_HEIGHT) - 50);

		this->sceneGraph->Render();
	}
	/* Rending game over text if the game state is in a GameOver state */
	else if (this->state == GameOver) {
		std::string gameover_text = "Game Over, man. Press \'r\' to restart the game.";
		this->gui->WriteText(gameover_text, glutGet(GLUT_SCREEN_WIDTH) / 2 - 300, glutGet(GLUT_SCREEN_HEIGHT) /2);
	}
	else if (this->state == Paused) {
		std::string paused_text = "Press spacebar to start the game.";
		this->gui->WriteText(paused_text, glutGet(GLUT_SCREEN_WIDTH) / 2 - 300, glutGet(GLUT_SCREEN_HEIGHT) / 2);
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

void Game::UpdateRound(float dt)
{

}

void Game::SpawnAsteroid()
{
	/* Set random size for asteroid radius */
	int radius = rand() % 65 + 55;
	/* set spawn point as centre of screen */
	std::unique_ptr<Vector3f> origin = std::make_unique<Vector3f>((float) glutGet(GLUT_SCREEN_WIDTH) /2, (float) glutGet(GLUT_SCREEN_HEIGHT) / 2, 0);
	/* point to random  direction out from the centre, which points to a random point on the asteroid spawn circle*/
	float angle = (float) (rand() % 360);
	/* Set an asteroid spawn point the random point that the random angle is pointing to*/
	std::unique_ptr<Vector3f> spawn = std::make_unique<Vector3f>(glutGet(GLUT_SCREEN_WIDTH) / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2, 0);
	//spawn->y += asteroid_spawn_circle_radius;
	spawn->RotateZAroundOrigin(*origin, angle);

	/* make asteroid's z-rotation face current position of the player so it's forward direction is facing the payer */
	float rotation = spawn->RotationToFaceTowards(*player->transform->pivot_position);
	/* Create the asteroid, where its spawn position is a random point along spawn circle, and its z-rotation is towards the player */
	std::shared_ptr<Asteroid> asteroid = std::make_shared<Asteroid>(sceneGraph.get(), spawn.get(), radius, rotation);

	/* update number of asteroids before adding object */
	int count = this->sceneGraph->GetAsteroidCount() + 1;
	this->sceneGraph->SetAsteroidCount(count);
	/* add object to scene graph */
	this->sceneGraph->AddGameObject(asteroid);
	std::cout << "ASTEROID SPAWNED" << std::endl;
}
