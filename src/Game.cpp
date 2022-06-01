#include "Game.h"

Game::Game(InputManager* inputManager) {

	this->gui = std::make_unique<GUI>();
	
	this->sceneGraph = std::make_unique<SceneGraph>();

	this->inputManager = inputManager;	

	this->camera = std::make_unique<Camera>(this->inputManager);

	this->Init();
}

void Game::Init()
{
	const int SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	const int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);

	
	std::cout << "START!" << std::endl;
}

void Game::Update(float dt) {
	if (this->inputManager->IsKeyPressed('w')) {
		camera->deltaMove = 0.5f;
	}
	else if (this->inputManager->IsKeyPressed('s')) {
		camera->deltaMove = -0.5f;
	}
	else {
		camera->deltaMove = 0;
	}
	this->camera->Update(dt);
	UpdateCamera(camera->deltaMove);
}

void Game::Render() {
	/* Render camera perspective */
	gluLookAt(camera->x, 1.0f, camera->z,
		camera->x + camera->lx, camera->y + camera->ly, camera->z + camera->lz,
		0.0f, 1.0f, 0.0f);

	// Draw ground

	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	/* Draw cube */
	glPushMatrix();
	glTranslatef(0, 0, -20.0f);
	glutSolidCube(10);
	glPopMatrix();
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

}

void Game::UpdateCamera(float dt)
{
	camera->x += dt * camera->lx * 0.1f;
	camera->z += dt * camera->lz * 0.1f;
}
