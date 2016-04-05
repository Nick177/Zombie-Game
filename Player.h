#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
private:
	bool isMoving;
	float health;
	bool isAlive;
	float movementSpeed;
	int counterWalking;
	int direction;
	bool ableToMoveUp;
	bool ableToMoveDown;
	bool ableToMoveLeft;
	bool ableToMoveRight;
	bool upKeyPressed;
	bool downKeyPressed;
	bool leftKeyPressed;
	bool rightKeyPressed;


public:

	Player();
	void update();
	
	void updateMovement();
	/*int mX, int mY);
	void updateDirection(int mX, int mY);
	void setDirection(int direction);
	*/

	float getMovementSpeed() const { return movementSpeed; }
	int getDirection() const { return direction; }
	bool isAbleToMoveUp() { return ableToMoveUp; }
	bool isAbleToMoveDown() { return ableToMoveDown; }
	bool isAbleToMoveLeft() { return ableToMoveLeft; }
	bool isAbleToMoveRight() { return ableToMoveRight; }
	float getHealth() { return health; }
	bool isStillAlive() { return isAlive; }

	void setCanMoveUp(bool move) { ableToMoveUp = move; }
	void setCanMoveDown(bool move) { ableToMoveDown = move; }
	void setCanMoveLeft(bool move) { ableToMoveLeft = move; }
	void setCanMoveRight(bool move) { ableToMoveRight = move; }
	void setAliveTo(bool isAlive) { this->isAlive = isAlive; }

	void setMovementSpeed(float movementSpeed) { this->movementSpeed = movementSpeed; }
	void healthReduction(float damageTaken);

};

#endif
