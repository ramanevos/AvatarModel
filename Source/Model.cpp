
#include "Model.h"
#include <algorithm>


using namespace std;
Model::Model()
{
	kd.push_back(kd_red);
	kd.push_back(kd_green);
	kd.push_back(kd_blue);
	ka.push_back(ka_red);
	ka.push_back(ka_green);
	ka.push_back(ka_blue);

}


const vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

const vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}

const vector<Vertex>& Model::GetTransformedVertices()
{
	return _transformedVertices;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

void Model::AddVertex(float x, float y, float z)
{
	Vertex a(x, y, z);
	_vertices.push_back(a);
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	Polygon3D a(i0, i1, i2);
	_polygons.push_back(a);
}

void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{
	_transformedVertices.clear();

	for (int i = 0; i < _vertices.size(); i++)
	{
		_transformedVertices.push_back(transform * _vertices[i]);
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (int i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i] = transform * _transformedVertices[i];
	}
}

const vector<Vertex>& Model::ApplyDehomoToTransVertices()
{
	for (int i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i] = _transformedVertices[i].dehomogenizeVertices(_transformedVertices[i].GetX(), _transformedVertices[i].GetY(), _transformedVertices[i].GetZ(), _transformedVertices[i].GetW());
	}
	return _transformedVertices;
}

void Model::CalculateBackfaces(Vertex camPosition)
{
	Vertex vertex[3];
	Vector3D dot_product;
	Vertex subtract;
	for (int i = 0; i < _polygons.size(); i++)
	{
		vertex[0] = GetTransformedVertices()[GetPolygons()[i].GetIndex(0)];
		vertex[1] = GetTransformedVertices()[GetPolygons()[i].GetIndex(1)];
		vertex[2] = GetTransformedVertices()[GetPolygons()[i].GetIndex(2)];

		Vector3D a = vertex[0].VertexSub(vertex[1]);
		Vector3D b = vertex[0].VertexSub(vertex[2]);
		Vector3D abCrossProduct = abCrossProduct.CrossProduct(b, a);

        //calculate lenght of the vector
		float lenght = sqrtf(powf(abCrossProduct.GetX(),2)+ powf(abCrossProduct.GetY(), 2) + powf(abCrossProduct.GetZ(), 2));
		
		//normalize the vector
		Vector3D normal(float(abCrossProduct.GetX() / lenght), float(abCrossProduct.GetY() / lenght), float(abCrossProduct.GetZ() / lenght));
		_polygons[i].SetNormal(normal);
		Vector3D eye_vector = vertex[0].VertexSub(camPosition);
		
		float DotProductResult = abCrossProduct.DotProduct(normal,eye_vector);
		if (DotProductResult < 0)
			_polygons[i].SetCulling(true);
		else
			_polygons[i].SetCulling(false);
	}
	
}

void Model::Sort(void)
{

	Vertex transVertices[3];
	float average_z = 0;
	for (int i = 0; i < _polygons.size(); i++)
	{
		transVertices[0] = GetTransformedVertices()[GetPolygons()[i].GetIndex(0)];
		transVertices[1] = GetTransformedVertices()[GetPolygons()[i].GetIndex(1)];
		transVertices[2] = GetTransformedVertices()[GetPolygons()[i].GetIndex(2)];
		average_z = (transVertices[0].GetZ() + transVertices[1].GetZ() + transVertices[2].GetZ()) / 3.0f;
		_polygons[i].SetZaverage(average_z);
	}

	sort(_polygons.begin(), _polygons.end(), [](const Polygon3D& lhs,const Polygon3D& rhs) { return lhs.GetZaverage()> rhs.GetZaverage(); });
	int senghh=0;
}





void Model::CalculateLightingDirectional(vector<Directional_lighting> D_light)
{
	int Totalr,Totalg,Totalb;
	int Tempr, Tempg, Tempb;

	for (int i = 0; i < _polygons.size(); i++)
	{
	
		COLORREF colour = _polygons[i].GetColour();
		Totalr = GetRValue(colour);
		Totalg = GetGValue(colour);
		Totalb = GetBValue(colour);
		for (int j = 0; j < D_light.size(); j++)
		{
			
			Tempr = D_light[j].GetRed();
			Tempg = D_light[j].GetGreen();
			Tempb = D_light[j].GetBlue();

			Tempr = (int) (Tempr* kd[0]);
			Tempg = (int) (Tempg* kd[1]);
			Tempb = (int) (Tempb* kd[2]);

			Vector3D normal;
			
			
			float dot_product = normal.DotProduct(D_light[j].NormalizedDirection(D_light[j].GetVector()), _polygons[i].GetNormal());
			Tempr = (int)(Tempr * dot_product);
			Tempg = (int)(Tempg * dot_product);
			Tempb = (int)(Tempb * dot_product);

			Totalr = Totalr + Tempr;
			Totalg = Totalg + Tempg;
			Totalb = Totalb + Tempb;
		}
		if (Totalr > 255)
			Totalr = 255;

		if (Totalr < 0)
			Totalr = 0;

		if (Totalg > 255)
			Totalg = 255;

		if (Totalg < 0)
			Totalg = 0;

		if (Totalb > 255)
			Totalb = 255;

		if (Totalb < 0)
			Totalb = 0;


		_polygons[i].SetColor(RGB(Totalr, Totalg, Totalb));
	}
}

void Model::CalculateLightingDirectionalNoAmbient(vector<Directional_lighting> D_light)
{
	int Totalr, Totalg, Totalb;
	int Tempr, Tempg, Tempb;

	for (int i = 0; i < _polygons.size(); i++)
	{

		Totalr = 0;
		Totalg = 0;
		Totalb = 0;
		for (int j = 0; j < D_light.size(); j++)
		{

			Tempr = D_light[j].GetRed();
			Tempg = D_light[j].GetGreen();
			Tempb = D_light[j].GetBlue();

			Tempr = (int)(Tempr * kd[0]);
			Tempg = (int)(Tempg * kd[1]);
			Tempb = (int)(Tempb * kd[2]);

			Vector3D normal;
			//float dot_product = normal.DotProduct(D_light[j].NormalizedDirection(D_light[j].GetVector()), _polygons[i].GetNormal());
			float dot_product = normal.DotProduct(D_light[j].NormalizedDirection(D_light[j].GetVector()), _polygons[i].GetNormal());
			Tempr = (int)(Tempr * dot_product);
			Tempg = (int)(Tempg * dot_product);
			Tempb = (int)(Tempb * dot_product);

			Totalr = Totalr + Tempr;
			Totalg = Totalg + Tempg;
			Totalb = Totalb + Tempb;
		}
		if (Totalr > 255)
			Totalr = 255;

		if (Totalr < 0)
			Totalr = 0;

		if (Totalg > 255)
			Totalg = 255;

		if (Totalg < 0)
			Totalg = 0;

		if (Totalb > 255)
			Totalb = 255;

		if (Totalb < 0)
			Totalb = 0;


		_polygons[i].SetColor(RGB(Totalr, Totalg, Totalb));
	}
}

void Model::CalculateAmbientLight(vector<AmbientLight> A_light)
{
	int Totalr, Totalg, Totalb;
	int Tempr, Tempg, Tempb;

	

	for (int i = 0; i < _polygons.size(); i++)
	{
		Totalr = 0;
		Totalg = 0;
		Totalb = 0;
		for (int j = 0; j < A_light.size(); j++)
		{
			Tempr = A_light[j].GetRed();
			Tempg = A_light[j].GetGreen();
			Tempb = A_light[j].GetBlue();

			Tempr = (int)(Tempr * ka[0]);
			Tempg = (int)(Tempg * ka[1]);
			Tempb = (int)(Tempb * ka[2]);

			Totalr = Totalr + Tempr;
			Totalg = Totalg + Tempg;
			Totalb = Totalb + Tempb;
		}
		if (Totalr > 255)
			Totalr = 255;

		if (Totalr < 0)
			Totalr = 0;

		if (Totalg > 255)
			Totalg = 255;

		if (Totalg < 0)
			Totalg = 0;

		if (Totalb > 255)
			Totalb = 255;

		if (Totalb < 0)
			Totalb = 0;


		_polygons[i].SetColor(RGB(Totalr, Totalg, Totalb));
	}
}

void Model::CalculateLightingPoint(vector<PointLight> P_light)
{
	int Totalr, Totalg, Totalb;
	int Tempr, Tempg, Tempb;
	

	for (int i = 0; i < _polygons.size(); i++)
	{

		COLORREF colour = _polygons[i].GetColour();
		Totalr = GetRValue(colour);
		Totalg = GetGValue(colour);
		Totalb = GetBValue(colour);
		for (int j = 0; j < P_light.size(); j++)
		{

			Tempr = P_light[j].GetRed();
			Tempg = P_light[j].GetGreen();
			Tempb = P_light[j].GetBlue();

			Tempr = (int)(Tempr * kd[0]);
			Tempg = (int)(Tempg * kd[1]);
			Tempb = (int)(Tempb * kd[2]);

			Vector3D normal;
			Vertex calculation = GetTransformedVertices()[GetPolygons()[i].GetIndex(0)];
			int CompensatingValue = 1;
			//Vector3D subtraction = P_light[j].GetPosition().VertexSub(GetTransformedVertices()[GetPolygons()[i].GetIndex(0)]);
			Vector3D subtraction = calculation.VertexSub(P_light[j].GetPosition());
			//float dot_product = normal.DotProduct(D_light[j].NormalizedDirection(D_light[j].GetVector()), _polygons[i].GetNormal());
			Vector3D LightSourceVector = P_light[j].Normalize(subtraction);
			float dot_product = normal.DotProduct(LightSourceVector, _polygons[i].GetNormal());
			float distance = sqrtf(powf(LightSourceVector.GetX(), 2) + powf(LightSourceVector.GetY(), 2) + powf(LightSourceVector.GetZ(), 2));
			Tempr = (int)(Tempr * dot_product);
			Tempg = (int)(Tempg * dot_product);
			Tempb = (int)(Tempb * dot_product);

			Tempr = (int)(Tempr * (1 / (P_light[j].GetAttenuationA() + P_light[j].GetAttenuationB() * distance + P_light[j].GetAttenuationC() * powf(distance, 2)))* CompensatingValue);
			Tempg = (int)(Tempg * (1 / (P_light[j].GetAttenuationA() + P_light[j].GetAttenuationB() * distance + P_light[j].GetAttenuationC() * powf(distance, 2))) * CompensatingValue);
			Tempb = (int)(Tempb * (1 / (P_light[j].GetAttenuationA() + P_light[j].GetAttenuationB() * distance + P_light[j].GetAttenuationC() * powf(distance, 2))) * CompensatingValue);

			Totalr = Totalr + Tempr;
			Totalg = Totalg + Tempg;
			Totalb = Totalb + Tempb;
		}
		if (Totalr > 255)
			Totalr = 255;

		if (Totalr < 0)
			Totalr = 0;

		if (Totalg > 255)
			Totalg = 255;

		if (Totalg < 0)
			Totalg = 0;

		if (Totalb > 255)
			Totalb = 255;

		if (Totalb < 0)
			Totalb = 0;


		_polygons[i].SetColor(RGB(Totalr, Totalg, Totalb));
	}
}





