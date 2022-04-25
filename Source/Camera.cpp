#include "Camera.h"


Camera::Camera()
{
	_xRotation = 0;
	_yRotation = 0;
	_zRotation = 0;
	_position = { 0,0,-50 };
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRotation = zRotation;
	_position = position;

}

Vertex Camera::getPosition() 
{
	return _position;
}

Matrix Camera::GetCamera()
{
	return camera;
}

