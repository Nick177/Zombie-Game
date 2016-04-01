#include "Player.h"
Player::Player()
{
	health = 100.0;
	isAlive = true;
	movementSpeed = 0.07;
	counterWalking = 0;
	direction = 0;

	ableToMoveUp = true;
	ableToMoveDown = true;
	ableToMoveLeft = true;
	ableToMoveRight = true;

	upKeyPressed = false;
	downKeyPressed = false;
	leftKeyPressed = false;
	rightKeyPressed = false;


	rect.setSize(sf::Vector2f(32, 32)); // Want this box to be same size as sprite because it will be the sprite's collision detection
	rect.setPosition(sf::Vector2f(0, 0));
	rect.setFillColor(sf::Color::Blue);

	sprite.setPosition(sf::Vector2f(0, 0));
}
void Player::update()
{
	sprite.setPosition(rect.getPosition());
}
void Player::updateMovement()//int mX, int mY)
{
	//int directionMouse;
	//figure out direction player is facing according to mouse coords
	//directionMouse = 

	//***************************************************************

	upKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	downKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	leftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	rightKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);


	if (upKeyPressed && rightKeyPressed && !downKeyPressed && !leftKeyPressed)
	{
		rect.move(movementSpeed, -movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 3, 32, 32));
		direction = 3;
		ableToMoveDown = true;
	}
	if (upKeyPressed && leftKeyPressed && !rightKeyPressed && !downKeyPressed)
	{
		rect.move(-movementSpeed, -movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 3, 32, 32));
		direction = 4;
		ableToMoveDown = true;
	}
	if (downKeyPressed && rightKeyPressed && !upKeyPressed && !leftKeyPressed)
	{
		rect.move(movementSpeed, movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 3, 32, 32));
		direction = 3;
		ableToMoveDown = true;
	}
	if (downKeyPressed && leftKeyPressed && !upKeyPressed && !rightKeyPressed)
	{
		rect.move(-movementSpeed, movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 3, 32, 32));
		direction = 4;
		ableToMoveDown = true;
	}

	if (upKeyPressed && ableToMoveUp && !leftKeyPressed && !downKeyPressed && !rightKeyPressed)//sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ableToMoveUp)
	{
		rect.move(0, -(movementSpeed));
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 3, 32, 32));
		direction = 1;
		ableToMoveDown = true;
	}
	if (downKeyPressed && ableToMoveDown && !upKeyPressed && !leftKeyPressed && !rightKeyPressed)//sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ableToMoveDown)
	{
		rect.move(0, movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 0, 32, 32));
		direction = 2;
		ableToMoveUp = true;
	}
	if (rightKeyPressed && ableToMoveRight && !leftKeyPressed && !upKeyPressed && !downKeyPressed)//(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ableToMoveRight)
	{
		rect.move(movementSpeed, 0);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 2, 32, 32));
		direction = 3;
		ableToMoveLeft = true;
	}
	if (leftKeyPressed && ableToMoveLeft && !rightKeyPressed && !upKeyPressed && !downKeyPressed)//sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ableToMoveLeft)
	{
		rect.move(-(movementSpeed), 0);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 1, 32, 32));
		direction = 4;
		ableToMoveRight = true;
	}

	counterWalking++;

	if (counterWalking == 3)
		counterWalking = 0;
}

void Player::healthReduction(float damageTaken)
{
	if (health - damageTaken >= 0)
	{
		health -= damageTaken;
	}
	else
	{
		isAlive = false;
	}
}