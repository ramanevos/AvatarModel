#pragma once
#include <vector>
#include "Vector3D.h"

class Directional_lighting
{
public:
	Directional_lighting();
	Directional_lighting(int red, int green, int blue, Vector3D direction);
	void SetRed(int value);
	int GetRed() const;
	void SetGreen(int value);
	int GetGreen() const;
	void SetBlue(int value);
	int GetBlue() const;
	void SetVector(Vector3D value);
	Vector3D GetVector() const;
	Vector3D NormalizedDirection(Vector3D direction);


private:
	int _R;
	int _G;
	int _B;
	Vector3D _direction;
	Vector3D normalized;
   
	
};

