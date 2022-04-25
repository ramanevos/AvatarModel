#include "AmbientLight.h"

AmbientLight::AmbientLight()
{
	_R = 0;
	_G = 255;
	_B = 255;
}

AmbientLight::AmbientLight(int red, int green, int blue)
{
	_R = red;
	_G = green;
	_B = blue;
}

void AmbientLight::SetRed(int value)
{
	_R = value;
}

int AmbientLight::GetRed() const
{
	return _R;
}

void AmbientLight::SetGreen(int value)
{
	_G = value;
}

int AmbientLight::GetGreen() const
{
	return _G;
}

void AmbientLight::SetBlue(int value)
{
	_B = value;
}

int AmbientLight::GetBlue() const
{
	return _B;
}
