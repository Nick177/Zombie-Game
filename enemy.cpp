//
//  enemy.cpp
//  InstallingSFML
//
//  Created by Blank Blank on 2015-08-11.
//  Copyright (c) 2015 Blank Blank. All rights reserved.
//

#include "enemy.h"
#include <random>
#include <cstdlib>

using namespace sf;



Enemy::Enemy()
{
	movementSpeed = 0.05;
	attackDamage = 10;
	counterWalking = 0;
	direction = 0;
	counter = 0;
	hp = 5;
	alive = true;

	rect.setSize(sf::Vector2f(60, 64));
	rect.setPosition(200, 200);
	//sprite.setPosition(200, 200);
	rect.setFillColor(sf::Color::Blue);
	sprite.setTextureRect(IntRect(0, 0, 64, 64));


	circle.setRadius(100);
	circle.setFillColor(sf::Color::Red);

	offset = 35 - (circle.getRadius());
	circle.setPosition(rect.getPosition().x + offset, rect.getPosition().y + offset);



	srand(time(NULL));
}


void Enemy::update()
{
	sprite.setPosition(rect.getPosition());
	circle.setPosition(rect.getPosition().x + offset, rect.getPosition().y + offset);
}

void Enemy::updateMovement()
{

	if ((direction) == 1)
	{
		rect.move(0, -movementSpeed); // up
		sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 5, 64, 64));
		direction = 1;
	}
	else if ((direction) == 2)
	{
		rect.move(0, movementSpeed); //down
		sprite.setTextureRect(sf::IntRect(counterWalking * 64, 0, 64, 64));
		direction = 2;
	}
	else if ((direction) == 3) // left
	{
		rect.move(-movementSpeed, 0);
		sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 1, 64, 64));
		direction = 3;
	}
	else if ((direction) == 4) // right
	{
		rect.move(movementSpeed, 0);
		sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 2, 64, 64));
		direction = 4;
	}
	else if ((direction) == 5) // down left
	{
		rect.move(-movementSpeed, movementSpeed); // down left
		sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 3, 64, 64));
		direction = 5;
	}
	else if ((direction) == 6) // down right
	{
		rect.move(movementSpeed, movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 4, 64, 64));
		direction = 6;
	}
	else
	{
		// No movement
	}

	// Controls the speed of the animation (+ slower , - faster)
	if (counter % 100 == 0)
		counterWalking++;

	if (counterWalking == 3)
	{
		counterWalking = 0;
	}

	counter++;

	if (counter >= 2000)
	{
		direction = rand();
		counter = 0;
	}


}


int Enemy::rand()
{
	uniform_int_distribution<int> randomMovement(0, 10);
	random_device rand;


	return randomMovement(rand);
}
int Enemy::randomPositionX(int x)
{
	uniform_int_distribution<int> positionX(0, x);
	random_device randomNumber;

	return positionX(randomNumber);
}
int Enemy::randomPositionY(int y)
{
	uniform_int_distribution<int> positionY(0, y);
	random_device randomNumber;

	return positionY(randomNumber);
}
void chase()
{



}