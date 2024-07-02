#include "Math.h"

float DegToRad(float degrees) {
	return (degrees * (pi / 180));
}

float RadToDeg(float radians)
{
	return radians * (180 / pi);
}

float Clamp(float value, float min, float max)
{
	if (value <= max && value >= min) {
		return value;
	}
	else if (value > max) {
		return max;
	}
	else if (value < min) {
		return min;
	}
}

float Abs(float value)
{
	return std::abs(value);
}

float GetXCoordinatesOnCircle(float rotation, float radius)
{
	return (radius * cos(rotation));
}

float GetYCoordinatesOnCircle(float rotation, float radius)
{
	return (radius * sin(rotation));
}

