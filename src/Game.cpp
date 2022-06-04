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

	skybox = std::make_unique<Cubemap>(sky_front, sky_back, sky_top, sky_bottom, sky_left, sky_right);

	
	std::cout << "START!" << std::endl;
}

void Game::Update(float dt) {
	if (this->inputManager->IsKeyPressed('w')) {
		camera->deltaMove = 1.5f;
	}
	else if (this->inputManager->IsKeyPressed('s')) {
		camera->deltaMove = -1.5f;
	}
	else {
		camera->deltaMove = 0;
	}
	this->camera->Update(dt);
	UpdateCamera(camera->deltaMove);
}

void Game::Render() {
	/* Render skybox before lighting scene */
	if (this->skybox) {
		this->skybox->RenderCubemap(camera->x, camera->y, camera->z);
	}	
	/* Add lighting to scene */
	this->createLighting();
	/* Load identity matrix before performing translations / camera movements */
	glLoadIdentity();
	/* Render camera perspective */
	gluLookAt(camera->x, 1.0f, camera->z,
		camera->x + camera->lx, camera->y + camera->ly, camera->z + camera->lz,
		0.0f, 1.0f, 0.0f);

	// Draw ground

	//glColor3f(0.9f, 0.9f, 0.9f);
	//glBegin(GL_QUADS);
	//glVertex3f(-100.0f, 0.0f, -100.0f);
	//glVertex3f(-100.0f, 0.0f, 100.0f);
	//glVertex3f(100.0f, 0.0f, 100.0f);
	//glVertex3f(100.0f, 0.0f, -100.0f);
	//glEnd();

	/* Draw cube */
	glPushMatrix();
	glTranslatef(0, 0, -20.0f);
	glutSolidCube(10);
	glFlush();
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

void Game::createLighting()
{
	float light_position[] = { 1.0, 1,0, 1.0f, 0.0f };
	float light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	float mat_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float mat_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
}

void Game::UpdateCamera(float dt)
{
	camera->x += dt * camera->lx * 0.1f;
	camera->z += dt * camera->lz * 0.1f;
}
