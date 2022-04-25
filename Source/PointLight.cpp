#include "PointLight.h"
#include <math.h>

PointLight::PointLight()
{
	_R = 255;
	_G = 255;
	_B = 255;
	position = {0,0,-50};
	AttenuationA = 0.0f;
	AttenuationB = 1.0f;
	AttenuationC = 0.0f;
}




void PointLight::SetRed(int redvalue)
{
	_R = redvalue;
}

int PointLight::GetRed() const
{
	return _R;
}

void PointLight::SetGreen(int value)
{
	_G = value;
}

int PointLight::GetGreen() const
{
	return _G;
}

void PointLight::SetBlue(int value)
{
	_B = value;
}

int PointLight::GetBlue() const
{
	return _B;
}

void PointLight::SetVector(Vector3D value)
{
	_direction = value;
}

void PointLight::SetPosition(Vertex value)
{
	position = value;
}

Vertex PointLight::GetPosition() 
{
	return position;
}

Vector3D PointLight::GetVector() const
{
	return _direction;
}

Vector3D PointLight::Normalize(Vector3D value)
{
	float lenght = sqrtf(powf(value.GetX(), 2) + powf(value.GetY(), 2) + powf(value.GetZ(), 2));
	Vector3D normalize(float(value.GetX() / lenght), float(value.GetY() / lenght), float(value.GetZ() / lenght));

	return normalize;
}

float PointLight::GetAttenuationA()
{
	return AttenuationA;
}

float PointLight::GetAttenuationB()
{
	return AttenuationB;
}

float PointLight::GetAttenuationC()
{
	return AttenuationC;
}
