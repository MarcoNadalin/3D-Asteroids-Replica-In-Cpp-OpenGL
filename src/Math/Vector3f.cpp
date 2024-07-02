#include "Vector3f.h"

Vector3f::Vector3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f::~Vector3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3f Vector3f::Cross(const Vector3f& other) const
{
	return Vector3f(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

Vector3f& Vector3f::Multiply(float other)
{
	x *= other;
	y *= other;
	z *= other;

	return *this;
}

Vector3f& Vector3f::Multiply(const Vector3f& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;

	return *this;
}

Vector3f& Vector3f::RotateZ(float degrees)
{
	float radians = DegToRad(degrees);
	float original_x = this->x;
	float original_y = this->y;
	this->x = (original_x * cos(radians)) - (original_y * sin(radians));
	this->y = (original_x * sin(radians)) + (original_y * cos(radians));

	return *this;
}

Vector3f& Vector3f::RotateZAroundOrigin(const Vector3f& origin, float degrees)
{
	float angle = DegToRad(degrees);
	float rotatedX = cos(angle) * (this->x - origin.x) - sin(angle) * (this->y - origin.y) + origin.x;
	float rotatedY = sin(angle) * (this->x - origin.x) + cos(angle) * (this->y - origin.y) + origin.y;
	this->x = rotatedX;
	this->y = rotatedY;
	return *this;
}

float Vector3f::RotationToFaceTowards(const Vector3f& other)
{

	float angle = 0;
	if (this->y > other.y) { //above 
		float hyp = Distance(other);
		float height = this->y - other.y;
		float radians = acos(height / hyp);
		angle = 180-RadToDeg(radians);
	}
	else if (this->y == other.y) { // on same level
		angle = 90;
	}
	else if (this->y < other.y) { // below
		float hyp = Distance(other);
		float height = other.y - this->y;
		float radians = acos(height / hyp);
		angle = RadToDeg(radians);
	}

	if (this->x < other.x) {
		return -angle;
	}
	else if (this->x == other.x) {
		
	}
	else if (this->x > other.x) {
		return angle;
	}

}

float Vector3f::Magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

Vector3f Vector3f::Normalize() const
{
	float length = Magnitude();
	return Vector3f(x / length, y / length, z / length);
}

Vector3f& Vector3f::Add(const Vector3f& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

Vector3f& Vector3f::Subtract(const Vector3f& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

float Vector3f::Distance(const Vector3f& other) const
{
	float a = x - other.x;
	float b = y - other.y;
	float c = z - other.z;
	return sqrt(a * a + b * b + c * c);
}

void Vector3f::ReflectLeft(Vector3f& rotation) const
{
	/* if coming from bottom */
	if (rotation.z < 90 && rotation.z > 0) {
		rotation.z = 360 % (int)rotation.z;
		float reflection = -rotation.z;
		rotation.z = reflection;
	}
	/* if coming from top */
	else if (rotation.z < 180 && rotation.z > 90) {
		float reflection = 180 + (180 - rotation.z);
		rotation.z = reflection;
	}
}

void Vector3f::ReflectRight(Vector3f& rotation) const
{
	/* if coming from bottom */
	if (rotation.z < 360 && rotation.z > 270) {
		float reflection = 0 - (360 - Abs(rotation.z));
		rotation.z = reflection;
	}
	/* if coming from top */
	else if (rotation.z < 270 && rotation.z > 180) {
		float reflection = 180 - (Abs(rotation.z) - 180);
		rotation.z = reflection;
	}
}

void Vector3f::ReflectUp(Vector3f& rotation) const
{
	/* if coming from left */
	if (rotation.z < 360 && rotation.z > 270) {
		float reflection = 180 + (360 - Abs(rotation.z));
		rotation.z = reflection;
	}
	/* if coming from right */
	else if (rotation.z > 0 && rotation.z < 90) {
		float reflection = 90 + Abs(rotation.z);
		rotation.z = reflection;
	}
}

void Vector3f::ReflectDown(Vector3f& rotation) const
{
	/* if coming from right */
	if (rotation.z > 90 && rotation.z < 180) {
		float reflection = Abs(rotation.z - 180);
		rotation.z = reflection;
	}
	/* if coming from left */
	else if (rotation.z > 180 && rotation.z < 270) {
		float reflection = -Abs(rotation.z - 180);
		rotation.z = reflection;
	}
}
