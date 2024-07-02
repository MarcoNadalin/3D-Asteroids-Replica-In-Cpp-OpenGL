#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <list>
#include <memory>


#include "../GameObject/GameObject.h"

/**
* Holds all game objects in the game, and iterates through them to update and render them each frame.
*/
class SceneGraph
{
private:

	std::unique_ptr<std::list<std::shared_ptr<GameObject>>> gameObjects;

	/* Asteroid stats */
	int asteroid_count = 0;
	int max_asteroids_in_arena = 1;
	int destroyed_asteroid_count = 0;
	
	
public:
	int total_num_destroyed_asteroids = 0;
	SceneGraph();

	/**
	* Adds a GameObject to the list containing GameObjects
	* 
	* @param go A shared pointer holding the game object to be added to the list of GameObjects
	*/
	void AddGameObject(std::shared_ptr<GameObject> go);

	/**
	* Removes a game object from the gameObjects list
	* 
	* @param go The gameobject to be removed from the list
	*/
	void RemoveGameObject(GameObject* go);

	/**
	* Calls the update method on all objects within the gameObjects list
	* 
	* @param dt DeltaTime
	*/
	void Update(float dt);

	/**
	* Calls the render method on all GameObjects within the gameObjects list
	*/
	void Render();

	/**
	* Set the current number of Asteroids being held in the scene
	* 
	* @param count The number to change the asteroid count variable to
	*/
	void SetAsteroidCount(int count);

	/**
	* Returns the number of asteroids in the scene
	*/
	int GetAsteroidCount();

	/**
	* Returns the number of asteroids that have been destroyed by the player
	*/
	int GetDestroyedAsteroidCount();

	/**
	* Sets the number of asterids that have been destroyed by the player
	* 
	* @param num The number of asteroids destroyed by the player
	*/
	void SetDestroyedAsteroidCount(int num);

	/**
	* Returns the list that all GameObjects are held within the scene
	*/
	std::list<std::shared_ptr<GameObject>>* GetGameObjects();

	bool DoesGameObjectExist(std::string tag);

	int GetNumberOfObjects(std::string tag);

};

#endif