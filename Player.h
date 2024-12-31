#pragma once
#include "Entity.h"
class Player : public Entity
{
private:
	bool w_, a_, s_, d_;
public:
	Player();
	Player(float x, float y);
	void MovementInput(bool keyDown, int key);
	void Shoot();
};

