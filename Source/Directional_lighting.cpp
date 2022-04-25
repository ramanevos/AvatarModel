#include "Directional_lighting.h"

Directional_lighting::Directional_lighting()
{
	_R = 0;
	_G = 255;
	_B = 255;
	_direction = { 1, 0, 1};
}

Directional_lighting::Directional_lighting(int red, int green, int blue, Vector3D direction)
{
	_R = red;
	_G = green;
	_B = blue;
	_direction = direction;
}

void Directional_lighting::SetRed(int redvalue)
{
	_R = redvalue;
}

int Directional_lighting::GetRed() const
{
	return _R;
}

void Directional_lighting::SetGreen(int value)
{
	_G = value;
}

int Directional_lighting::GetGreen() const
{
	return _G;
}

void Directional_lighting::SetBlue(int value)
{
	_B = value;
}

int Directional_lighting::GetBlue() const
{
	return _B;
}

void Directional_lighting::SetVector(Vector3D value)
{
	_direction = value;
}

Vector3D Directional_lighting::GetVector() const
{
	return _direction;
}

Vector3D Directional_lighting::NormalizedDirection(Vector3D direction)
{
	float lenght = sqrtf(powf(direction.GetX(), 2) + powf(direction.GetY(), 2) + powf(direction.GetZ(), 2));
	Vector3D normalizedirection(float(direction.GetX() / lenght), float(direction.GetY() / lenght), float(direction.GetZ() / lenght));

	return normalizedirection;
}


