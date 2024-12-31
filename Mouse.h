#pragma once

#include <Windows.h>
#include <d2d1.h>
//this is set up more so as an "in case I need it" thing.
class Mouse
{
private:
	float x_;
	float y_;
public:
	Mouse();
	float getY() { return y_; };
	float getX() { return x_; };
	void setY(float y) { y_ = y; };
	void setX(float x) { x_ = x; };
};

