#pragma once
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "MD2Loader.h"
#include "Camera.h"
#include "Directional_lighting.h"
#include "AmbientLight.h"
#include "PointLight.h"

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);
	void DrawWireFrame(const Bitmap& bitmap);
	void DrawSolidFlat(const Bitmap& bitmap);
	void FlatDraw(POINT points[], HDC hdc, int vertices, COLORREF colour);
	void LineDraw(Vertex points[], HDC hDc);
	void StringDraw(const Bitmap& bitmap, LPCTSTR text);
	

private:

	Vertex s_points[4];
	Matrix transform;
	Matrix traslateTrans;
	Matrix perspective;
	Matrix view;
	Camera camera;
	vector<Polygon3D>polygons;
	vector<Vertex> TransVertices;
	Model _model;
	POINT points[3] = {0};
	vector <Directional_lighting> _directional_lighting;
	vector <AmbientLight> _ambient_lighting;
	vector <PointLight> _point_lighting;

	int frameCount=0;
	float _x=1;
	float _y=1;
	float _z=1;

	float kd_red=1.0f;
	float kd_blue=1.0f;
	float kd_green=1.0f;
	float ka_red = 1.0f;
	float ka_blue = 1.0f;
	float ka_green = 1.0f;
	
	
};

