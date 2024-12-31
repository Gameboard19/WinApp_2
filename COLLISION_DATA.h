#pragma once

#include "AxisData.h"

struct COLLISION_DATA
{
	bool isColliding;
	float x;
	float y;
	float xVelocity;
	float yVelocity;
	AXISDIRECTION xAxis;
	AXISDIRECTION yAxis;
};

