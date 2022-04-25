#include "Vertex.h"

// Constructors

Vertex::Vertex(void)
{
	_x = 0.0f;
	_y = 0.0f;
	_w = 1.0f;
	_z = 0.0f;
}

Vertex::Vertex(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

Vertex::Vertex(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1;
}

Vertex::Vertex(const Vertex& v)
{
	Copy(v);
}

/*
Vertex::Vertex(Vertex&& v)
{
	Copy(v);
}
*/

Vertex::~Vertex(void)
{
}

// Accessors and mutators

float Vertex::GetX(void) const
{
	return _x;
}

void Vertex::SetX(float x)
{
	_x = x;
}

float Vertex::GetY(void) const
{
	return _y;
}

void Vertex::SetY(float y)
{
	_y = y;
}

float Vertex::GetZ(void) const
{
	return _z;
}

void Vertex::SetZ(float z)
{
	_z = z;
}


float Vertex::GetW(void) const
{
	return _w;
}

void Vertex::SetW(float w)
{
	_w = w;
}

// Operator overloads


Vertex& Vertex::operator= (const Vertex& rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

/*
Vertex& Vertex::operator= (Vertex&& rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}
*/

Vector3D Vertex::VertexSub(Vertex vert)
{
	
	return Vector3D(_x - vert.GetX(), _y - vert.GetY(), _z - vert.GetZ());
}

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _w + rhs.GetW(), _z + rhs.GetZ());
}


// Private methods

void Vertex::Copy(const Vertex& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	_w = v.GetW();
}

Vertex Vertex::dehomogenizeVertices(float x, float y, float z, float w)
{

	_x = x / w;
	_y = y / w;
	_w = w / w;
	_z = z / w;

	return Vertex(_x, _y, _z,_w);
}



