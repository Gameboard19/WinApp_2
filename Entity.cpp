#include "pch.h"
#include "Entity.h"

Entity::Entity() {
	radius_ = 30;
	entityShape_.radiusX = radius_;
	entityShape_.radiusY = radius_ - 5;
	entityShape_.point.x = 0;
	entityShape_.point.y = 0;
	axisXIsMoving_ = false;
	axisYIsMoving_ = false;
	axisXMovement_ = NONE;
	axisYMovement_ = NONE;
	veloX_ = 0;
	veloY_ = 0;
	veloMax_ = 5;
	accelerationSpeed_ = 0.5f;
	friction_ = 0.3f;
	r_ = 0.0;
	g_ = 1.0;
	b_ = 0.0;
	alpha_ = 1.0;
	rotation_ = 0.0;
}
Entity::Entity(float x, float y) {
	radius_ = 30;
	entityShape_.radiusX = radius_;
	entityShape_.radiusY = radius_ - 5.0f;
	entityShape_.point.x = x;
	entityShape_.point.y = y;
	axisXIsMoving_ = false;
	axisYIsMoving_ = false;
	axisXMovement_ = NONE;
	axisYMovement_ = NONE;
	veloX_ = 0.0f;
	veloY_ = 0.0f;
	veloMax_ = 5.0f;
	accelerationSpeed_ = 0.5f;
	friction_ = 0.3f;
	r_ = 0.0f;
	g_ = 1.0f;
	b_ = 0.0f;
	alpha_ = 1.0f;
	rotation_ = 0.0f;
}
float Entity::getRotation() { return rotation_; }
float Entity::getX() { return posX_; }
float Entity::getY() { return posY_; }
float Entity::getRadius() { return radius_; }
D2D1_MATRIX_3X2_F Entity::getRMatrix() {
	return matrix_.Rotation(getRotation(), entityShape_.point);
}
void Entity::setX(float newX) {
	posX_ = newX;
	return;
}
void Entity::setY(float newY) {
	posY_ = newY;
	return;
}
void Entity::setR(float newR) {
	rotation_ = newR;
	return;
}
void Entity::tpTo(float newX, float newY) {
	posX_ = newX;
	posY_ = newY;
}
void Entity::tpTo(float newX, float newY, float newR) {
	posX_ = newX;
	posY_ = newY;
	rotation_ = newR;
}
void Entity::Accelerate(AXIS axis) {
	switch (axis) {
	case X:
		switch (axisXMovement_) {
		case POSITIVE:
			if (abs(veloX_) <= veloMax_) {
				veloX_ += accelerationSpeed_;
				if (abs(veloX_) > veloMax_) {
					veloX_ = veloMax_;
				}
			}
			break;
		case NEGATIVE:
			if (abs(veloX_) <= veloMax_) {
				veloX_ -= accelerationSpeed_;
				if (abs(veloX_) > veloMax_) {
					veloX_ = -veloMax_;
				}
			}
			break;
		}
		break;
	case Y:
		switch (axisYMovement_) {
		case POSITIVE:
			if (abs(veloY_) <= veloMax_) {
				veloY_ += accelerationSpeed_;
				if (abs(veloY_) > veloMax_) {
					veloY_ = veloMax_;
				}
			}
			break;
		case NEGATIVE:
			if (abs(veloY_) <= veloMax_) {
				veloY_ -= accelerationSpeed_;
				if (abs(veloY_) > veloMax_) {
					veloY_ = -veloMax_;
				}
			}
			break;
		}
		break;
	}
	return;
}
void Entity::Decelerate(AXIS axis) {
	switch (axis) {
	case X:
		if (axisXMovement_ == NONE) {
			if (veloX_ > 0.0) {
				veloX_ -= friction_;
			}
			else if (veloX_ < 0.0) {
				veloX_ += friction_;
			}
			if (abs(veloX_) <= 0.25) {
				veloX_ = 0.0;
			}
		}
		break;
	case Y:
		if (axisYMovement_ == NONE) {
			if (veloY_ > 0.0) {
				veloY_ -= friction_;
			}
			else if (veloY_ < 0.0) {
				veloY_ += friction_;
			}
			if (abs(veloY_) <= 0.25) {
				veloY_ = 0.0;
			}
		}
	}
}
void Entity::SetAccelSpeed(float accelSpeed) {
	accelerationSpeed_ = accelSpeed;
	return;
}
void Entity::SetFriction(float friction) {
	friction_ = friction;
	return;
}
void Entity::lookAt(float targetX, float targetY) {
	if (targetX < getX()) {
		rotation_ = 180.0f + TODEGREES(atan2(getY() - targetY, getX() - targetX));
	}
	else {
		rotation_ = 0.0f + TODEGREES(atan2(getY() - targetY, getX() - targetX));
	}
}
void Entity::AttemptMovement() {
	//x axis
	Accelerate(X);
	Decelerate(X);
	//y axis
	Accelerate(Y);
	Decelerate(Y);
	posX_ += veloX_;
	posY_ += veloY_;
}
void Entity::Render(Graphics* graphics) {
	graphics->SetBrush(r_, g_, b_, alpha_);
	graphics->SetTransform(getRMatrix());
	graphics->DrawEllipse(&entityShape_);
	graphics->FillEllipse(&entityShape_);
	return;
}
float Entity::FindDistance(float x, float y) {
	return sqrt(pow((x - posX_), 2) + pow((y - posY_), 2));
}
COLLISION_DATA Entity::CheckEntityCollision(Entity* entity) {
	COLLISION_DATA data;
	data.isColliding = TouchingCircle(entity->getX(), entity->getY(), entity->getRadius());
	data.x = entity->getX();
	data.y = entity->getY();
	data.xAxis = entity->GetXMovement();
	data.yAxis = entity->GetYMovement();
	data.xVelocity = entity->GetXVelo();
	data.yVelocity = entity->GetYVelo();
	return data;
}
bool Entity::TouchingSquare(float leftX, float topY, float rightX, float bottomY) {
	//checking the rect collision is going to be a bit more annoying, as it requires some logic
	//the program will check collision by finding it's distance to the closest point within the rect's boundaries.
	//for the purposes of this explanation, lets assume point 1 = (-50, -50) and point 2 = (25, 25)
	//if posX_ < -50 && posX_ < 25, then we assign closest x value to be -50.
	//if posX_ > -50 && posX_ > 25, then we assign closest x value to be 25.
	//if posX_ >= -50 && posX_ <= 25, then we assign closest x value to be posX_.
	//same process is done for the y value, and then we compare the distance to that point to radius_
	//NOTE: notice that the top right corner is considered (0,0)
	float nearestX, nearestY;
	if (posX_ < leftX && posX_ < rightX) {
		nearestX = leftX;
	}
	else if (posX_ > leftX && posX_ > rightX) {
		nearestX = rightX;
	}
	else {
		nearestX = posX_;
	}
	if (posY_ < topY && posY_ < bottomY) {
		nearestY = topY;
	}
	else if (posY_ > topY && posY_ > bottomY) {
		nearestY = bottomY;
	}
	else {
		nearestY = posY_;
	}
	return TouchingPoint(nearestX, nearestY);
}
bool Entity::TouchingCircle(float x, float y, float radius) {
	if (FindDistance(x, y) <= radius_ + radius) {
		return true;
	}
	else {
		return false;
	}
}
bool Entity::TouchingPoint(float x, float y) {
	if (FindDistance(x, y) <= radius_) {
		return true;
	}
	else {
		return false;
	}
}
void Entity::DoCollisionLogic(COLLISION_DATA data) {
	if (data.isColliding) {
		veloX_ = -veloX_;
		veloY_ = -veloY_;
		if (data.x < posX_) posX_ += 5;
		if (data.x > posX_) posX_ -= 5;
		if (data.y < posY_) posY_ += 5;
		if (data.y > posY_) posY_ -= 5;
	}
}