#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <memory>
#include "../../Math/Vector3f.h"

/**
* A class which contains the rotation and pivot position for any game object
*/
class Transform
{
private:
	

public:
	std::shared_ptr<Vector3f> pivot_position;

	std::shared_ptr<Vector3f> euler_angles;

	Transform();

	Transform(float x, float y, float z);

};

#endif