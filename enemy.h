
#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include<iostream>

using namespace sf;
using namespace std;

class Enemy : public Entity
{
private:
	float movementSpeed;
	float attackDamage;
	int counterWalking;
	int direction; // 1 - up, 2 - down, 3 - left, 4 - right
	int counter;
	float hp;
	bool alive;
	int offset;
	CircleShape circle;
	bool isPlayerInRange;

public:
	Enemy();
	void update();
	void updateMovement();
	int rand();
	int randomPositionX(int x);
	int randomPositionY(int y);
	void isDead() { alive = false; }
	void setHP(float dmg) { this->hp = hp - dmg; }
	float getHP()const { return hp; }
	bool isAlive()const { return alive; }
	float getAttackDamage()const { return attackDamage; }
	int getDirection()const { return direction; }
	void setDirection(int direction) { this->direction = direction; }
	void setPlayerInRange(bool playerInRange) { this->isPlayerInRange = playerInRange; }
	CircleShape getCircle()const { return circle; }

};
#endif