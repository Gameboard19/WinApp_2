#include "pch.h"
#include "Npc.h"
Npc::Npc(float x, float y, Entity* target, bool hostile) {
	radius_ = 30;
	entityShape_.radiusX = radius_;
	entityShape_.radiusY = radius_ - 5;
	posX_ = x, posY_ = y;
	target_ = target;
	axisXIsMoving_ = false;
	axisYIsMoving_ = false;
	axisXMovement_ = NONE;
	axisYMovement_ = NONE;
	veloX_ = 0;
	veloY_ = 0;
	veloMax_ = 7;
	accelerationSpeed_ = 0.3;
	friction_ = 0.3;
	r_ = 1.0;
	g_ = 0.0;
	b_ = 0.0;
	alpha_ = 1.0;
	rotation_ = 0.0;
	isHostile_ = hostile;
}
void Npc::lookAtTarget() {
	lookAt(target_->getX(), target_->getY());
}
void Npc::SetDirection() {
	if (isHostile_) {
		if (target_->getX() > getX()) axisXMovement_ = POSITIVE;
		if (target_->getX() < getX()) axisXMovement_ = NEGATIVE;
		if (target_->getX() == getX()) axisXMovement_ = NONE;
		if (target_->getY() > getY()) axisYMovement_ = POSITIVE;
		if (target_->getY() < getY()) axisYMovement_ = NEGATIVE;
		if (target_->getY() == getY()) axisYMovement_ = NONE;
	}
}
void Npc::Movement() {
	lookAtTarget();
	SetDirection();
	AttemptMovement();
}