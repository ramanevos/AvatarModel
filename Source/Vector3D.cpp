#include "Vector3D.h"

Vector3D::Vector3D()
{
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

float Vector3D::GetX(void) const
{
	return _x;
}

void Vector3D::SetX(float x)
{
	_x = x;
}

float Vector3D::GetY(void) const
{
	return _y;
}

void Vector3D::SetY(float y)
{
	_y = y;
}

float Vector3D::GetZ(void) const
{
	return _z;
}

void Vector3D::SetZ(float z)
{
	_z = z;
}

float Vector3D::DotProduct(Vector3D vect1,Vector3D vect2)
{
	float _DotProduct = vect1.GetX() * vect2.GetX() + vect1.GetY() * vect2.GetY() + vect1.GetZ() * vect2.GetZ();

	return _DotProduct;
}

Vector3D Vector3D::CrossProduct(Vector3D vect1, Vector3D vect2)
{
	float cross_x = vect1.GetY() * vect2.GetZ() - vect1.GetZ() * vect2.GetY();
	float cross_y = vect1.GetZ() * vect2.GetX() - vect1.GetX() * vect2.GetZ();
	float cross_z = vect1.GetX() * vect2.GetY() - vect1.GetY() * vect2.GetX();
	Vector3D _CrossProduct(cross_x, cross_y, cross_z);

	return _CrossProduct;
}
