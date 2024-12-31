#pragma once
#include "Entity.h"
class Npc : public Entity
{
private:
	Entity* target_;
	bool isHostile_;
public:
	//TODO: find out more sophisticated pathfinding than "move in direct line toward (x, y)"
	Npc(float x, float y, Entity* target, bool hostile);
	void lookAtTarget();
	void SetDirection();
	void Movement();
	Entity* GetTarget() { return target_; };
	void SetTarget(Entity* target);
};