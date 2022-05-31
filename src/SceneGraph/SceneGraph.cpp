#include "SceneGraph.h"
#include <iostream>

SceneGraph::SceneGraph()
{
	this->gameObjects = std::make_unique<std::list<std::shared_ptr<GameObject>>>();
}

void SceneGraph::AddGameObject(std::shared_ptr<GameObject> go)
{
	/* If there is an empty slot, add it there, otherwise push_back */
	std::list<std::shared_ptr<GameObject>>::iterator it = gameObjects->begin();
	while (it != gameObjects->end()) {
		if ((*it).get() == nullptr) {
			(*it).swap(go);
			return;
		}
		++it;
	}
	gameObjects->push_back(go);
}


/* Instead of completely removing element from list, it simply sets the shared_ptr of the element as nullptr */
void SceneGraph::RemoveGameObject(GameObject* go)
{
	std::list<std::shared_ptr<GameObject>>::iterator it = gameObjects->begin();
	std::shared_ptr<GameObject> remove;
	while (it != gameObjects->end()) {
		if (go == (*it).get()) {
			(*it) = nullptr;
		}
		++it;
	}
}

void SceneGraph::Update(float dt)
{
	std::list<std::shared_ptr<GameObject>>::iterator it;
	for (it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		if ((*it).get() != nullptr) {
			(*it)->Update(dt);
		}		
	}
}

void SceneGraph::Render()
{
	std::list<std::shared_ptr<GameObject>>::iterator it;
	for (it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		if ((*it).get() != nullptr) {
			(*it)->RenderGameObject();
		}
	}
	
}

void SceneGraph::SetAsteroidCount(int count)
{
	if (!(count == asteroid_count)) {
		this->asteroid_count = count;
	}
}

int SceneGraph::GetAsteroidCount()
{
	return this->asteroid_count;
}

int SceneGraph::GetDestroyedAsteroidCount()
{
	return this->destroyed_asteroid_count;
}

void SceneGraph::SetDestroyedAsteroidCount(int num)
{
	this->destroyed_asteroid_count = num;
}

std::list<std::shared_ptr<GameObject>>* SceneGraph::GetGameObjects() {
	return this->gameObjects.get();
}

bool SceneGraph::DoesGameObjectExist(std::string tag)
{
	std::list<std::shared_ptr<GameObject>>::iterator it;
	for (it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		if ((*it).get() != nullptr && (*it).get()->GetTag() == tag) {
			return true;
		}
	}

	return false;
}

int SceneGraph::GetNumberOfObjects(std::string tag)
{
	int count = 0;
	std::list<std::shared_ptr<GameObject>>::iterator it;
	for (it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		if ((*it).get() != nullptr && (*it).get()->GetTag() == tag) {
			count++;
		}
	}

	return count;
}
