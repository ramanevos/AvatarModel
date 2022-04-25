#pragma once
#include<vector>
#include"Vector3D.h"
using namespace std;

// Class representing a 2D vertex (i.e a point in two dimensional space)

class Vertex
{
public:
	Vertex(void);
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float w);
	Vertex(const Vertex& v);


	~Vertex(void);

	float GetX(void) const;
	void SetX(float x);
	float GetY(void) const;
	void SetY(float y);
	float GetZ(void) const;
	void SetZ(float z);
	float GetW(void) const;
	void SetW(float w);

	Vertex dehomogenizeVertices(float x, float y, float z, float w);
	Vertex& operator= (const Vertex& rhs);


	Vector3D VertexSub(Vertex vert);
	const Vertex operator+ (const Vertex& rhs) const;
private:
	float _x;
	float _y;
	float _z;
	float _w;
	void Copy(const Vertex& v);
};



