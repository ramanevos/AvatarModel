#pragma once
#include "Vector3D.h"
#include "Vertex.h"
class PointLight
{
public:
	PointLight();
	void SetRed(int value);
	int GetRed() const;
	void SetGreen(int value);
	int GetGreen() const;
	void SetBlue(int value);
	int GetBlue() const;
	void SetVector(Vector3D value);
	void SetPosition(Vertex value);
	Vertex GetPosition() ;
	Vector3D GetVector() const;
	Vector3D Normalize(Vector3D value);
	float GetAttenuationA();
	float GetAttenuationB();
	float GetAttenuationC();

	
private:
	int _R;
	int _G;
	int _B;
	Vertex position;
	Vector3D _direction;
	float AttenuationA;
	float AttenuationB;
	float AttenuationC;
};

