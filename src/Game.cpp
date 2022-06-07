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


	GLuint spaceship = assetloader::loadTextureEdgeClamp("../assets/models/xwing/xwing_diffuse.png");

	skybox = std::make_unique<Cubemap>(sky_front, sky_back, sky_top, sky_bottom, sky_left, sky_right);


	////////////////////////////////////////////////////////////
	////////////* CREATE AND POSITION GAME OBJECTS *///////////
	//////////////////////////////////////////////////////////
	this->player = std::make_shared<Player>(this->inputManager, this->sceneGraph.get(), "../assets/models/xwing/xwing.obj", 0, 0, 0);
	player->SetTexture(spaceship);
	player->SetScale(5);
	player->transform->euler_angles->y = 90; // rotating spaceship so it is oriented correctly in front of the camera
	player->transform->pivot_position->y = -2.8f; // moving it down slightly so the perspective is correct
	player->transform->pivot_position->z = -1.0f; // moving it forward so it doesnt clip through the camera
	this->active_camera = this->player->GetCamera();
	
	this->sceneGraph->AddGameObject(player);

	std::cout << "START!" << std::endl;
}

void Game::Update(float dt) {
	this->sceneGraph->Update(dt);
}

void Game::Render() {
	/* Render skybox before lighting scene */
	if (this->skybox) {
		this->skybox->RenderCubemap(0,0,0);
	}	
	/* Add lighting to scene */
	this->createLighting();
	/* Load identity matrix before performing translations / camera movements */
	glLoadIdentity();
	/* Render camera perspective */
	gluLookAt(active_camera->GetTransform()->pivot_position->x, 1.0f, active_camera->GetTransform()->pivot_position->z,
		active_camera->GetTransform()->pivot_position->x + active_camera->lx,
		active_camera->GetTransform()->pivot_position->y + active_camera->ly,
		active_camera->GetTransform()->pivot_position->z + active_camera->lz,
		0.0f, 1.0f, 0.0f);

	
	/* RENDER ALL OBJECTS WITHIN SCENE GRAPH */
	this->sceneGraph->Render();

	/* DRAW SIMPLE DEBUG CUBE. WILL DELETE */
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
	float light_position_1[] = { 0.5, 0.5, 0.5f, 1.0f };
	float light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	float mat_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float mat_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_1);
	glEnable(GL_LIGHT0);
}
