#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity
{
private:
	float movementSpeed;
	float projLifeTime;
	int direction;
	const static int projectileLimit = 20;
	bool destroy;
	double distance;
	int damage;
public:
	Projectile();
	void update();

	float getMovementSpeed() const { return movementSpeed; }
	float getProjLifeTime() const { return projLifeTime; }
	int getDirection() const { return direction; }
	bool isDestroyed() const { return destroy; }
	double getDistance() const { return distance; }
	int getAttackDamage() const { return damage; }

	void setMovementSpeed(float movementSpeed) { this->movementSpeed = movementSpeed; }
	void setProjLifeTime(float time) { projLifeTime = time; }
	void setDirection(int direction) { this->direction = direction; }
	void canDestroy(bool destroy) { this->destroy = destroy; }
};

#endif