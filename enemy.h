
#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

using namespace sf;
using namespace std;

class Enemy : public Entity
{
private:
	float movementSpeed;
	int attackDamage;
	int counterWalking;
	int direction; // 1 - up, 2 - down, 3 - left, 4 - right
	int counter;
	int hp;
	bool alive;

public:
	Enemy();
	void update();
	void updateMovement();
	int rand();
	int randomPositionX(int x);
	int randomPositionY(int y);
	void isDead() { alive = false; }
	void setHP(int dmg) { this->hp = hp - dmg; }
	int getHP()const { return hp; }
	bool isAlive()const { return alive; }


};
#endif