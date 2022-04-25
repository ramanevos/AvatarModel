#include "Rasteriser.h"

Rasteriser app;

bool Rasteriser::Initialise()
{
	if (!MD2Loader::LoadModel("marvin.md2", _model,
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}
	AmbientLight ambient;
	Directional_lighting directional;
	PointLight pointlight;
	_ambient_lighting.push_back(ambient);
	_directional_lighting.push_back(directional);
	_point_lighting.push_back(pointlight);
	return true;

	
}

void Rasteriser::Update(const Bitmap& bitmap)
{
		
	//translation
	if (frameCount <90) 
	{
		
		_x += 0.0f;
		_y += 0.3f;
		_z += 0.0f;
		Matrix traslate{ 1, 0, 0, _x ,
						  0, 1, 0, _y,
						  0, 0, 1, _z,
						  0, 0, 0, 1 };
		transform = traslate;
		frameCount++;
	}

	else if (frameCount >=90 && frameCount <180)
	{
	
		_x += 0.0f;
		_y -= 0.3f;
		_z += 0.0f;
		Matrix traslate{ 1, 0, 0, _x ,
						  0, 1, 0, _y,
						  0, 0, 1, _z,
						  0, 0, 0, 1 };
		transform = traslate;
		frameCount++;
	}

	//scalation
	else if (frameCount >= 180 && frameCount < 270)
	{
		
		
			_x -= 0.01f;
			_y -= 0.01f;
			_z += 0.0f;
		
		Matrix scale{ _x, 0, 0, 0 ,
					  0, _y, 0, 0,
					  0, 0, _z, 0,
					  0, 0, 0, 1 };

		transform = scale;
		frameCount++;
	
	}

	else if (frameCount >= 270 && frameCount < 360)
	{
	
		_x += 0.01f;
		_y += 0.01f;
		_z += 0.0f;
		Matrix scale{ _x, 0, 0, 0 ,
					  0, _y, 0, 0,
					  0, 0, _z, 0,
					  0, 0, 0, 1 };

		transform = scale;
		frameCount++;
		
	}

	//rotation around x axis
	else if (frameCount >= 360 && frameCount < 540)
	

	{
		_x += 2.0f;
		float radians = (float)(_x * 3.14 / 180);

		Matrix rotate = { 1, 0 ,0, 0,
						  0 ,cos(radians) , -sin(radians), 0,
						  0 ,sin(radians), cos(radians) , 0,
						  0 , 0, 0 , 1 };
		transform = rotate;
		frameCount++;
	}

	//rotation around z axis
	else if (frameCount >= 540 && frameCount < 720)
	{
		_x += 2.0f;
		float radians = (float)(_x * 3.14 / 180);

		Matrix rotate = { cos(radians), -sin(radians),0, 0,
						  sin(radians), cos(radians), 0, 0,
						 0 , 0, 1 , 0,
						 0 , 0, 0 , 1 };
		transform = rotate;
		frameCount++;
	}

	//rotation around y axis
	else
	
	{
		_x += 2.0f;
		float radians = (float)(_x * 3.14 / 180);

		Matrix rotate = { cos(radians), 0, sin(radians), 0,
							0, 1, 0, 0,
						  -sin(radians), 0, cos(radians) , 0,
						  0, 0, 0, 1 };
		transform = rotate;
		frameCount++;
	}

	
	//generate perspective matrix
	GeneratePerspectiveMatrix(1, (float)bitmap.GetWidth() / bitmap.GetHeight());
	//generate view matrix
	GenerateViewMatrix(1, bitmap.GetWidth(), bitmap.GetHeight());
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	perspective={
						   d / aspectRatio,0,0,0,
						   0,d,0,0,
						   0,0,d,0,
						   0,0,1,0
	};
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	view = { (float)width / 2, 0, 0 ,(float)width / 2,
			  0, (float)-height / 2, 0 ,(float)height / 2,
			  0, 0 ,d / 2 ,d / 2,
			  0, 0, 0, 1 };
}


void Rasteriser::DrawWireFrame(const Bitmap& bitmap)
{

	polygons = _model.GetPolygons();
	TransVertices = _model.GetTransformedVertices();

	for (int i = 0; i < _model.GetPolygonCount(); i++)
	{
		s_points[0] = TransVertices[polygons[i].GetIndex(0)];
		s_points[1] = TransVertices[polygons[i].GetIndex(1)];
		s_points[2] = TransVertices[polygons[i].GetIndex(2)];

		if (polygons[i].GetCulling() == false)
			LineDraw(s_points, bitmap.GetDC());
	}
}



void Rasteriser::DrawSolidFlat(const Bitmap& bitmap)
{
	polygons = _model.GetPolygons();
	TransVertices = _model.GetTransformedVertices();


	for(int i=0;i< _model.GetPolygonCount(); i++)
	{ 
		points[0].x = (int)TransVertices[polygons[i].GetIndex(0)].GetX();
		points[0].y = (int)TransVertices[polygons[i].GetIndex(0)].GetY();
		points[1].x = (int)TransVertices[polygons[i].GetIndex(1)].GetX();
		points[1].y = (int)TransVertices[polygons[i].GetIndex(1)].GetY();
		points[2].x = (int)TransVertices[polygons[i].GetIndex(2)].GetX();
		points[2].y = (int)TransVertices[polygons[i].GetIndex(2)].GetY();

		if (polygons[i].GetCulling() == false) 
		{
			COLORREF colour = polygons[i].GetColour();
			FlatDraw(points, bitmap.GetDC(), 3, colour);
		}
			
    }
	
}


void Rasteriser::FlatDraw(POINT points[], HDC hdc,int vertices,COLORREF colour)
{
	if(frameCount >= 1080 && frameCount < 1260)
	{
		HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 255,255));
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
		HGDIOBJ olpen = SelectObject(hdc, pen);
		HGDIOBJ olbrush = SelectObject(hdc, brush);
		Polygon(hdc, points, vertices);
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		DeleteObject(pen);
		DeleteObject(brush);
	}
	else
	{
		HPEN pen = CreatePen(BS_SOLID, 2, colour);
		HBRUSH brush = CreateSolidBrush(colour);
		HGDIOBJ olpen = SelectObject(hdc, pen);
		HGDIOBJ olbrush = SelectObject(hdc, brush);
		Polygon(hdc, points, vertices);
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		DeleteObject(pen);
		DeleteObject(brush);
	}
}


void Rasteriser::LineDraw(Vertex points[], HDC hDc)
{
	HPEN pen = CreatePen(BS_SOLID, 1, RGB(255, 255, 255));
	HGDIOBJ oldPen = SelectObject(hDc, pen);
	MoveToEx(hDc, (int)points[0].GetX(), (int)points[0].GetY(), NULL);
	LineTo(hDc, (int)points[1].GetX(), (int)points[1].GetY());
	LineTo(hDc, (int)points[2].GetX(), (int)points[2].GetY());
	LineTo(hDc, (int)points[0].GetX(), (int)points[0].GetY());
	SelectObject(hDc, pen);
	DeleteObject(pen);
}

void Rasteriser::StringDraw(const Bitmap& bitmap, LPCTSTR text)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(30,0,0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(20, 0, 0));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}



void Rasteriser::Render(const Bitmap& bitmap)
{
	bitmap.Clear(RGB(0, 0, 0));
	
/*
	_model.ApplyTransformToLocalVertices(transform);
	_model.CalculateBackfaces(camera.getPosition());
	_model.CalculateAmbientLight(_ambient_lighting);
	_model.CalculateLightingDirectional(_directional_lighting);
	_model.CalculateLightingPoint(_point_lighting);
	_model.ApplyTransformToTransformedVertices(camera.GetCamera());
	_model.Sort();
	_model.ApplyTransformToTransformedVertices(perspective);
	_model.ApplyDehomoToTransVertices();
	_model.ApplyTransformToTransformedVertices(view);
	DrawSolidFlat(bitmap);
*/
 
	//wireframe
	if (frameCount <900)
	{
		if (frameCount < 180)
			StringDraw(bitmap, L"Wireframe - Translating");
		else if(frameCount >= 180 && frameCount < 360)
			StringDraw(bitmap, L"Wireframe - Scaling");
		else if (frameCount >= 360 && frameCount < 540)
			StringDraw(bitmap, L"Wireframe - X axis Rotation");
		else if (frameCount >= 540 && frameCount < 720)
			StringDraw(bitmap, L"Wireframe - Z axis Rotation");
		else if (frameCount >= 720 && frameCount < 900)
			StringDraw(bitmap, L"Wireframe - Y axis Rotation");


		_model.ApplyTransformToLocalVertices(transform);
		_model.ApplyTransformToTransformedVertices(camera.GetCamera());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(perspective);
		_model.ApplyDehomoToTransVertices();
		_model.ApplyTransformToTransformedVertices(view);
		DrawWireFrame(bitmap);
		//StringDraw(bitmap,L"s");
	}

	//backface culling and sorting
	else if (frameCount>=900 && frameCount<1080)
	{ 
		StringDraw(bitmap, L"Wireframe - Backface Culling and Depth Sorting");
		_model.ApplyTransformToLocalVertices(transform);
		_model.CalculateBackfaces(camera.getPosition());
		_model.ApplyTransformToTransformedVertices(camera.GetCamera());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(perspective);
		_model.ApplyDehomoToTransVertices();
		_model.ApplyTransformToTransformedVertices(view);
		DrawWireFrame(bitmap);
		
	}

	//solid GDI shading
	else if(frameCount>=1080 && frameCount < 1260)
	{
		StringDraw(bitmap, L"Solid GDI Shading");
		_model.ApplyTransformToLocalVertices(transform);
		_model.CalculateBackfaces(camera.getPosition());
		_model.ApplyTransformToTransformedVertices(camera.GetCamera());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(perspective);
		_model.ApplyDehomoToTransVertices();
		_model.ApplyTransformToTransformedVertices(view);
		DrawSolidFlat(bitmap);
	}

	//Directional lightning with ambient light
	else if (frameCount >= 1260 && frameCount < 1440)
	{
		StringDraw(bitmap, L"Solid GDI Shading - Directional light with Ambient light");
		_model.ApplyTransformToLocalVertices(transform);
		_model.CalculateBackfaces(camera.getPosition());
		_model.CalculateAmbientLight(_ambient_lighting);
		_model.CalculateLightingDirectional(_directional_lighting);
		_model.ApplyTransformToTransformedVertices(camera.GetCamera());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(perspective);
		_model.ApplyDehomoToTransVertices();
		_model.ApplyTransformToTransformedVertices(view);
		DrawSolidFlat(bitmap);
	}

	//Ambient light off
	else if (frameCount >= 1440 && frameCount <1620)
	{
		StringDraw(bitmap, L"Solid GDI Shading - Directional light Without Ambient light");
		_model.ApplyTransformToLocalVertices(transform);
		_model.CalculateBackfaces(camera.getPosition());
		_model.CalculateLightingDirectionalNoAmbient(_directional_lighting);
		_model.ApplyTransformToTransformedVertices(camera.GetCamera());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(perspective);
		_model.ApplyDehomoToTransVertices();
		_model.ApplyTransformToTransformedVertices(view);
		DrawSolidFlat(bitmap);

	}

	//Ambient light on
	else if (frameCount >= 1620 && frameCount < 1800)
	{
		StringDraw(bitmap, L"Solid GDI Shading - Directional light with Ambient light");
		_model.ApplyTransformToLocalVertices(transform);
		_model.CalculateBackfaces(camera.getPosition());
		_model.CalculateAmbientLight(_ambient_lighting);
		_model.CalculateLightingDirectional(_directional_lighting);
		_model.ApplyTransformToTransformedVertices(camera.GetCamera());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(perspective);
		_model.ApplyDehomoToTransVertices();
		_model.ApplyTransformToTransformedVertices(view);
		DrawSolidFlat(bitmap);
	}

	//point lighting
	else if (frameCount >= 1800)
	{
		StringDraw(bitmap, L"Solid GDI Shading - Directional light, Ambient light and Point light");
		_model.ApplyTransformToLocalVertices(transform);
		_model.CalculateBackfaces(camera.getPosition());
		_model.CalculateAmbientLight(_ambient_lighting);
		_model.CalculateLightingDirectional(_directional_lighting);
		_model.CalculateLightingPoint(_point_lighting);
		_model.ApplyTransformToTransformedVertices(camera.GetCamera());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(perspective);
		_model.ApplyDehomoToTransVertices();
		_model.ApplyTransformToTransformedVertices(view);
		DrawSolidFlat(bitmap);
	}
	

}