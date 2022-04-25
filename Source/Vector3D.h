#pragma once
class Vector3D
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	float GetX(void) const;
	void SetX(float x);
	float GetY(void) const;
	void SetY(float y);
	float GetZ(void) const;
	void SetZ(float z);
	static float DotProduct(Vector3D vect1,Vector3D vect2);
	static Vector3D CrossProduct(Vector3D vect1, Vector3D vect2);


private:
	float _x;
	float _y;
	float _z;
	
};

