#pragma once
#include "Vertex.h"
#include "Matrix.h"
#include <cmath>
class Camera
{
public:
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	Vertex getPosition(); 
	Matrix GetCamera();


private:
	float _xRotation = 0;
	float _yRotation = 0;
	float _zRotation = 0;
	Vertex _position = { 0,0,-50 };



	Matrix xRotation = { 1, 0, 0 ,0,
						0, cos(_xRotation), sin(_xRotation) ,0,
						0, -sin(_xRotation),cos(_xRotation) ,0,
						0, 0, 0, 1 };
	Matrix yRotation = { cos(_yRotation), 0, -sin(_yRotation) ,0,
						0, 1, 0 ,0,
						sin(_yRotation), 0, cos(_xRotation) ,0,
						0, 0, 0, 1 };
	Matrix zRotation = { cos(_zRotation), sin(_zRotation), 0 ,0,
						-sin(_zRotation), cos(_zRotation), 0 ,0,
						0, 0, 1 ,0,
						0, 0, 0, 1 };
	Matrix Position = { 1, 0, 0 ,-float(_position.GetX()),
						0, 1, 0 ,-float(_position.GetY()),
						0, 0 ,1 ,-float(_position.GetZ()),
						0, 0, 0, 1 };
	Matrix camera = xRotation * yRotation * zRotation * Position;


};


