#pragma once
#include "Polygon3D.h"
#include "Vertex.h"
#include <vector>
#include "Matrix.h"
#include "Vector3D.h"
#include "Directional_lighting.h"
#include "AmbientLight.h"
#include "PointLight.h"

using namespace std;

class Model
{
public:
	Model();

	// Accessors
	const vector<Polygon3D>& GetPolygons();
	const vector<Vertex>& GetVertices();
	const vector<Vertex>& GetTransformedVertices();

	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);

	void ApplyTransformToLocalVertices(const Matrix& transform);
	void ApplyTransformToTransformedVertices(const Matrix& transform);
	const vector<Vertex>& ApplyDehomoToTransVertices();
	void CalculateBackfaces(Vertex camPosition);
	void Sort(void);
	void CalculateLightingDirectional(vector<Directional_lighting> D_light);
	void CalculateLightingDirectionalNoAmbient(vector<Directional_lighting> D_light);
	void CalculateAmbientLight(vector<AmbientLight> A_light);
	void CalculateLightingPoint(vector<PointLight> P_light);
	

private:
	vector<Polygon3D> _polygons;
	vector<Vertex> _vertices;
	vector<Vertex> _transformedVertices;
	
	float kd_red = 0.5f;
	float kd_blue = 0.5f;
	float kd_green = 0.5f;
	float ka_red = 0.4f;
	float ka_blue = 0.4f;
	float ka_green = 0.4f;


	vector<float> kd;
	vector<float> ka;
	
	




};
