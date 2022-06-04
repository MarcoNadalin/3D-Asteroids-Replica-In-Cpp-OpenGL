#ifndef GAME_H
#define GAME_H

#include <memory>
#include <iostream>
#include <cstdlib>

#include "./Input/InputManager.h"
#include "./GameObject/Player/Player.h"
#include "./SceneGraph/SceneGraph.h"
#include "GameObject/ArenaBoundry.h"
#include "GameObject/Asteroid/Asteroid.h"
#include "Particle/ParticleGroup.h"
#include "UI/GUI.h"
#include "GameObject/Components/Camera.h"
#include "Graphics/Cubemap.h"
#include "Assets/AssetLoader.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

enum GameState { Paused, Playing, GameOver };

/**
* Main class of the game. Initialises and holds all classes required for the game.
*/
class Game
{
private:
	std::unique_ptr<GUI> gui;

	std::unique_ptr<SceneGraph> sceneGraph;
	
	InputManager* inputManager;

	std::unique_ptr<Cubemap> skybox;

	std::unique_ptr<Camera> camera;

	GameState state = Playing;
	float elapsed_round_time = 0;
	float time_start_round = 0;
	

	int current_wave = 1;

	float deltaMove = 0;

	/**
	* Initialises all the class-variables and other setup
	*/
	void Init();


public:

	Game(InputManager* inputManager);

	/**
	* Calls update on scene graph and calls UpdateRound
	*/
	void Update(float dt);

	/**
	* Calls render on scene graph, and handles all UI rending
	*/
	void Render();

	/**
	* Restarts the game back to the starting state
	*/
	void ResetGame();

	/**
	* Handles all round calculations, to determine what the current round should be, and how many 
	* asteroids need to be spawned in the current round
	*/
	void UpdateRound(float dt);

	/**
	*  Spawns one asteroid at a random point outside the arena, facing the player
	*/
	void SpawnAsteroid();	

	void setSkyBox(Cubemap* skybox);

	void createLighting();

	void UpdateCamera(float dt);
};

#endif
