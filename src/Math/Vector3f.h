#ifndef VECTOR3F_H
#define VECTOR3F_H

#include "Math.h"
#include <iostream>

/**
* Holds x,y, and z values, as well as other vector-related calculations.
*/
class Vector3f
{
private:
	const double pi = 3.14159265358979323846;
public:

	/* Positional coordinates */
	float x = 0;
	float y = 0;
	float z = 0;

	Vector3f();
	/* Constructor */
	Vector3f(float x, float y, float z);
	/* Destructor */
	~Vector3f();

	/**
	* Returns the CrossProduct between two vectors
	* 
	* @param other The other vector to calculate the cross-product between
	* @return The new vector that is the cross-product between two vectors
	*/
	Vector3f Cross(const Vector3f& other) const;

	/**
	* Returns dot product between two vectors
	* 
	* @param  The other vector to calculate the dot-product with
	* @return The value of the dot-product
	*/
	float Dot(const Vector3f& other) const;

	/**
	* Calculates the magnitude of this vector
	* 
	* @return The magnitude of this vector
	*/
	float Magnitude() const;
	
	/**
	* Normalizes the the current vector
	* 
	* @return A normalized vector
	*/
	Vector3f Normalize() const;

	/**
	* Adds a vector to this current vector
	* 
	* @param vector The vector to add 
	* @return reference to new vector whos values are the sum of two vectors
	*/
	Vector3f& Add(const Vector3f& vector);

	Vector3f& Multiply(float other);

	Vector3f& Multiply(const Vector3f& vector);

	/**
	* Rotates a vector by some degrees on the Z-axis in an anti-clockwise fashion 
	* 
	* @param degrees The number of degrees to rotate the vector by on the z-axis
	* @return reference to the vector that has been rotated
	*/
	Vector3f& RotateZ(float degrees);

	/**
	* Rotates a vector around an origin on the z-axis
	* 
	* @param origin The point to rotate this vector around
	* @param degrees The number of degrees to rotate the vector by on the z-axis
	* @return reference to the new vector that has been rotated around an origin
	*/
	Vector3f& RotateZAroundOrigin(const Vector3f& origin, float degrees);

	/**
	* Calculate the rotation in degrees required to rotate this vector to point towards another vector
	* 
	* @param other the vector to face towards
	* @return the degrees required to rotate the current vector
	*/
	float RotationToFaceTowards(const Vector3f& other);

	/**
	* Calculates the distance between this and another vector
	* 
	* @param other the vector to calculate the distance from
	* @return the distance between this and another vector
	*/
	float Distance(const Vector3f& other) const;

	void ReflectLeft(Vector3f& rotation) const;

	void ReflectRight(Vector3f& rotation) const;

	void ReflectUp(Vector3f& rotation) const;

	void ReflectDown(Vector3f& rotation) const;

	void ReflectLeft(Vector3f& rotation, Vector3f& other) const;

	void ReflectRight(Vector3f& rotation, Vector3f& other) const;

	void ReflectUp(Vector3f& rotation, Vector3f& other) const;

	void ReflectDown(Vector3f& rotation, Vector3f& other) const;
};

#endif



