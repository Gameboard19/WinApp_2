#pragma once

#include "Graphics.h"
#include "COLLISION_DATA.h"
#include "AxisData.h"
#include <d2d1.h>
#include <string>
#include <cmath>

#define PI 3.14159
#define TORADIANS(x) (x * (PI / 180.0))
#define TODEGREES(x) (x * (180.0 / PI))
//Axis enums were here, they have now been put in there own header file

//TODO: rework collision. have it return a COLLISION_DATA class that can be used in other methods.

class Entity
{
private:
	//position info
	//TODO:Entities will have their own Graphics object.
protected:
	D2D1_ELLIPSE entityShape_;
	D2D1::Matrix3x2F matrix_;
	float veloX_, veloY_;												//Reworking how I handle movement. these store the entity's velicity on each axis
	float veloMax_;														//the greatest absolute value the entity's velocity can reach;
	float accelerationSpeed_, friction_;								//speeds of accelerating and un-accelerating;
	AXISDIRECTION axisXMovement_, axisYMovement_;								//enum for communicating which way the entity is trying to accelerate.
	float rotation_;			//NOTE: for the sake of compatability this is measured in degrees
	float r_;
	float g_;
	float b_;
	float alpha_;
	float radius_;
	bool axisXIsMoving_, axisYIsMoving_;								//bools for determining is the respective x axis is being moved on.
public:
	Entity(); //no constructors will generate a generic entity at (0, 0)
	Entity(float x, float y);
	float getRotation();												//returns this Entity's Rotation (in radians)
	float getX();														//returns this Entity's X Coord
	float getY();														//returns this Entity's Y Coord
	D2D1_MATRIX_3X2_F getRMatrix();										//returns a rotation matrix.
	float getRadius();													//returns this Entity's radius
	void setX(float newX);												//tp this Entity to specified X Coord
	void setY(float newY);												//tp this Entity to specified Y Coord
	void setR(float newR);												//turns this Entity to be facing the specified angle (in radians)
	void tpTo(float newX, float newY);									//tp this Entity to specified (X, Y) Coords
	void tpTo(float newX, float newY, float newR);						//tp this Entity to specified (X, Y) Coords and rotate it to face the specified angle 
	void Accelerate(AXIS axis);										//increments this Entity's specified velocity
	void Decelerate(AXIS axis);
	float GetAccelSpeed() { return accelerationSpeed_; };
	float GetFriction() { return friction_; };
	void SetFriction(float friction);
	void SetAccelSpeed(float accelSpeed);
	void AttemptMovement();										//this is a virtual as NPC's will use a subclass of Entity
	bool IsXMoving() { return axisXIsMoving_; };
	bool IsYMoving() { return axisXIsMoving_; };
	AXISDIRECTION GetXMovement() { return axisXMovement_; };
	AXISDIRECTION GetYMovement() { return axisYMovement_; };
	float GetXVelo() { return abs(veloX_); };
	float GetYVelo() { return abs(veloY_); };
	void lookAt(float targetX, float targetY);							//does trigonometry to have the target face the specified (X, Y) Coords
	void Render(Graphics* graphics);
	float FindDistance(float x, float y);								//returns the distance between this entity and specified angle.
	COLLISION_DATA CheckEntityCollision(Entity* entity);								//checks if this entity is colliding with a defined entity.
	bool TouchingSquare(float leftX, float topY, float rightX, float bottomY);	//checks if this entity is colliding with a defined rectangle.
	bool TouchingCircle(float x, float y, float radius);				//checks if this entity is colliding with a defined circle
	bool TouchingPoint(float x, float y);								//checks if this entity is colliding with a defined point
	void DoCollisionLogic(COLLISION_DATA data);
};
//just so I don't have to do a bunch of correcting
#define posX_ entityShape_.point.x
#define posY_ entityShape_.point.y

