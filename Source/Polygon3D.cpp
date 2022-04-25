#include "Polygon3D.h"
#include <windef.h>
#include <wingdi.h>

Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	_culling = false;
	_z_average = 0;
	_colour = RGB(255, 255, 255);

}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_culling = false;
	_z_average = 0;
	_colour = RGB(255, 255, 255);

}

void Polygon3D::SetCulling(bool value)
{
	_culling = value;
}

bool Polygon3D::GetCulling() const
{
	return _culling;
}

void Polygon3D::SetZaverage(float zAverage)
{
	_z_average = zAverage;
}

float Polygon3D::GetZaverage() const
{
	return _z_average;
}

void Polygon3D::SetNormal(Vector3D normalized)
{
	_normalized = normalized;
}

Vector3D Polygon3D::GetNormal()
{
	return _normalized;
}

Polygon3D::~Polygon3D()
{
}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	Copy(p);
}

int Polygon3D::GetIndex(int a) const
{
	return _indices[a];
}

Polygon3D& Polygon3D::operator=(const Polygon3D& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}

void Polygon3D::SetColor(COLORREF colour)
{
	_colour=colour;
}

COLORREF Polygon3D::GetColour() const
{
	return _colour;;
}

void Polygon3D::Copy(const Polygon3D& other)
{
	_indices[0] = other.GetIndex(0);
	_indices[1] = other.GetIndex(1);
	_indices[2] = other.GetIndex(2);
	_culling = other.GetCulling();
	_z_average = other.GetZaverage();
	_colour = other.GetColour();
}