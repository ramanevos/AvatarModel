#pragma once
#include "windows.h"
#include "Vector3D.h"
class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);
	void SetCulling(bool value);
	bool GetCulling() const;
	void SetZaverage(float zAverage);
	float GetZaverage() const;
	void SetNormal(Vector3D normalized);
	Vector3D GetNormal();
	// Accessor to return index of specified vertex
	int GetIndex(int a) const;
	Polygon3D& operator= (const Polygon3D& rhs);
	void SetColor(COLORREF colour);
	COLORREF GetColour() const;
	

private:
	int _indices[3];
	void Copy(const Polygon3D& other);
	bool _culling;
	float _z_average;
	Vector3D _normalized;
	COLORREF _colour;
	

};

