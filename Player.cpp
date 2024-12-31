#include "pch.h"
#include "Player.h"

Player::Player() {
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
	accelerationSpeed_ = 0.5;
	friction_ = 0.3;
	w_ = false;
	a_ = false;
	s_ = false;
	d_ = false;
	r_ = 0.0;
	g_ = 1.0;
	b_ = 0.0;
	alpha_ = 1.0;
	rotation_ = 0.0;
}
Player::Player(float x, float y) {
	radius_ = 30;
	entityShape_.radiusX = radius_;
	entityShape_.radiusY = radius_ - 5;
	entityShape_.point.x = x;
	entityShape_.point.y = y;
	axisXIsMoving_ = false;
	axisYIsMoving_ = false;
	axisXMovement_ = NONE;
	axisYMovement_ = NONE;
	veloX_ = 0;
	veloY_ = 0;
	veloMax_ = 5;
	accelerationSpeed_ = 0.5;
	friction_ = 0.3;
	w_ = false;
	a_ = false;
	s_ = false;
	d_ = false;
	r_ = 0.0;
	g_ = 1.0;
	b_ = 0.0;
	alpha_ = 1.0;
	rotation_ = 0.0;
}
void Player::MovementInput(bool keyDown, int key) {
	if (keyDown) {
		switch (key) {
		case 0x57:
			w_ = keyDown;
			if (!s_) {
				axisYMovement_ = NEGATIVE;
				axisYIsMoving_ = true;
			}
			else {
				axisYMovement_ = NONE;
				axisYIsMoving_ = false;

			}
			break;
		case 0x53:
			s_ = keyDown;
			if (!w_) {
				axisYMovement_ = POSITIVE;
				axisYIsMoving_ = true;
			}
			else {
				axisYMovement_ = NONE;
				axisYIsMoving_ = false;
			}
			break;
		case 0x41:
			a_ = keyDown;
			if (!d_) {
				axisXMovement_ = NEGATIVE;
				axisXIsMoving_ = true;
			}
			else {
				axisXMovement_ = NONE;
				axisXIsMoving_ = false;
			}
			break;
		case 0x44:
			d_ = keyDown;
			if (!a_) {
				axisXMovement_ = POSITIVE;
				axisXIsMoving_ = true;
			}
			else {
				axisXMovement_ = NONE;
				axisXIsMoving_ = false;
			}
			break;
		}
	}
	else if (!keyDown) {
		/* BUG REPORT - Wrong input
		DESCRIPTION - Sometimes, when you mash buttons in the right way, the program gets confused what button you are holding,
		so you could be holding [D] and the program thinks you are holding [A]. this is consistent enough to be frequent,
		but inconsistent enough to make it difficult to identify what is actually happening.

		STATUS - FIXED
		*/
		//I believe the wrong input bug originates in this section of code, but I can't be sure.
		//So the purpose of this section is mored or less to smooth out the movement so the entity doesn't stall while changing directions
		//spoiler alert - it wasn't in here. it was actually in Entity::Accelerate()
		switch (key) {
		case 0x57:
			w_ = keyDown;
			if (s_) {
				axisYMovement_ = POSITIVE;
				axisYIsMoving_ = true;
			}
			else {
				axisYMovement_ = NONE;
				axisYIsMoving_ = false;

			}
			break;
		case 0x53:
			s_ = keyDown;
			if (w_) {
				axisYMovement_ = NEGATIVE;
				axisYIsMoving_ = true;
			}
			else {
				axisYMovement_ = NONE;
				axisYIsMoving_ = false;
			}
			break;
		case 0x41:
			a_ = keyDown;
			if (d_) {
				axisXMovement_ = POSITIVE;
				axisXIsMoving_ = true;
			}
			else {
				axisXMovement_ = NONE;
				axisXIsMoving_ = false;
			}
			break;
		case 0x44:
			d_ = keyDown;
			if (a_) {
				axisXMovement_ = NEGATIVE;
				axisXIsMoving_ = true;
			}
			else {
				axisXMovement_ = NONE;
				axisXIsMoving_ = false;
			}
			break;
		}
	}
	return;
}