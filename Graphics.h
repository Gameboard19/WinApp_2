#pragma once

#include <Windows.h>
#include <d2d1.h>

#define GRAPHICSBRUSH_DEFAULT 1.0f, 1.0f, 1.0f, 1.0

class Graphics
{
private:
	//the I indicates that these are interfaces.
	ID2D1Factory* factory_;							// this is a factory, it is... the factory
	ID2D1HwndRenderTarget* renderTarget_;			// this is a render target. it is the thing we want to draw on.
	ID2D1SolidColorBrush* brush_;					// this is a brush, but is commented out for now until i figure out a better system for it.
	ID2D1StrokeStyle* style_;
	//ID2D1Mesh* mesh_;								// this is a mesh. purpose pending.
public:
	//default constructor & destructors
	Graphics();
	~Graphics();
	//initialize graphics
	bool Init(const HWND hWnd);
	//drawing functions
	void BeginDraw() { renderTarget_->BeginDraw(); };
	void EndDraw() { renderTarget_->EndDraw(); };
	//drawing wrappers
	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius);
	void DrawEllipse(D2D1_ELLIPSE* ellipse);
	void FillEllipse(D2D1_ELLIPSE* ellipse);
	void DrawSquare(float x, float y, float sideLength);
	void DrawRect(D2D1_RECT_F* rect);
	//void DrawRect(float x, float y, float baseLength, float sideLength);
	//void DrawRect(D2D1_POINT_2F point1, D2D1_POINT_2F point2);
	void FillRect(D2D1_RECT_F* rect);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawLine(D2D1_POINT_2F point1, D2D1_POINT_2F point2);
	void SetBrush(float r, float g, float b, float a);
	void SetTransform(D2D1_MATRIX_3X2_F transform);
};

