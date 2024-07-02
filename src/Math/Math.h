#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <algorithm>
#include <iostream>

const double pi = 3.14159265358979323846;

/**
* Converts radians to degrees
* 
* @param degrees the number of degrees to convert to radians
* @return radians
*/
float DegToRad(float degrees);

/**
* Converts degrees to radians
* 
* @param radians the number of radians to convert to degrees
* @return degrees
*/
float RadToDeg(float radians);

/**
* Clamps a value between a max and a minimum
* 
* @param value the value to clamp
* @param min the minimum value
* @param max the maximum value
* @return the value clamped between the max and min
*/
float Clamp(float value, float min, float max);

float Abs(float value);

float GetXCoordinatesOnCircle(float rotation, float radius);
float GetYCoordinatesOnCircle(float rotation, float radius);

#endif