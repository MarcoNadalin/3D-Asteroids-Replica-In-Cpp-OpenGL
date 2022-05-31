#ifndef ARENABOUNDRY_H
#define ARENABOUNDRY_H

# include <windows.h>
# include <GL/gl.h>
#include <cmath>

#include <memory>
#include <vector>
#include "./Components/Transform.h"
#include "./Player/Player.h"
#include "../SceneGraph/SceneGraph.h"

#include <iostream>

class ArenaBoundry : public GameObject
{
private:
	Player* player;
	bool touching_player = false;
	bool near_player = false;

	int height = 0, width = 0;

public:
	ArenaBoundry(Player* player, int height, int width, std::string tag, float x, float y, float z);

	void Update(float dt);
	void Render();

};

#endif


