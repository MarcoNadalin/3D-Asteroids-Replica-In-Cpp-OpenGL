#include "Transform.h"

Transform::Transform()
{
	pivot_position = std::make_shared<Vector3f>();
	euler_angles = std::make_shared<Vector3f>();
}

Transform::Transform(float x, float y, float z)
{
	pivot_position = std::make_shared<Vector3f>(x, y, z);
	euler_angles = std::make_shared<Vector3f>();
}