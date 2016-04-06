#include "Player.h"
Player::Player()
{
	isMoving = false;
	health = 100.0;
	isAlive = true;
	movementSpeed = 0.5;
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
	upKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	downKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	leftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	rightKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);


	if (upKeyPressed && rightKeyPressed && !downKeyPressed && !leftKeyPressed)
	{
		isMoving = true;
		rect.move(movementSpeed, -movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 6, 32, 32));
		direction = 3;
		ableToMoveDown = true;
	}
	else if (upKeyPressed && leftKeyPressed && !rightKeyPressed && !downKeyPressed)
	{
		isMoving = true;
		rect.move(-movementSpeed, -movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 6, 32, 32));
		direction = 4;
		ableToMoveDown = true;
	}
	else if (downKeyPressed && rightKeyPressed && !upKeyPressed && !leftKeyPressed)
	{
		isMoving = true;
		rect.move(movementSpeed, movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 5, 32, 32));
		direction = 6;
		ableToMoveDown = true;
	}
	else if (downKeyPressed && leftKeyPressed && !upKeyPressed && !rightKeyPressed)
	{
		isMoving = true;
		rect.move(-movementSpeed, movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 4, 32, 32));
		direction = 5;
		ableToMoveDown = true;
	}

	else if (upKeyPressed && ableToMoveUp && !leftKeyPressed && !downKeyPressed && !rightKeyPressed)//sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ableToMoveUp)
	{
		isMoving = true;
		rect.move(0, -(movementSpeed));
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 3, 32, 32));
		direction = 1;
		ableToMoveDown = true;
	}
	else if (downKeyPressed && ableToMoveDown && !upKeyPressed && !leftKeyPressed && !rightKeyPressed)//sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ableToMoveDown)
	{
		isMoving = true;
		rect.move(0, movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 0, 32, 32));
		direction = 2;
		ableToMoveUp = true;
	}
	else if (rightKeyPressed && ableToMoveRight && !leftKeyPressed && !upKeyPressed && !downKeyPressed)//(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ableToMoveRight)
	{
		isMoving = true;
		rect.move(movementSpeed, 0);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 2, 32, 32));
		direction = 3;
		ableToMoveLeft = true;
	}
	else if (leftKeyPressed && ableToMoveLeft && !rightKeyPressed && !upKeyPressed && !downKeyPressed)//sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ableToMoveLeft)
	{
		isMoving = true;
		rect.move(-(movementSpeed), 0);
		sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 1, 32, 32));
		direction = 4;
		ableToMoveRight = true;
	}
	else
	{
		isMoving = false;
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
/*
void Player::setDirection(int direction)
{
	this->direction = direction;

	if (isMoving)
	{
		switch (direction)
		{
		case 1:	sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 3, 32, 32));
			break;
		case 2: sprite.setTextureRect(sf::IntRect(counterWalking * 32, 0, 32, 32));
			break;
		case 3: sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 1, 32, 32));
			break;
		case 4: sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 2, 32, 32));
			break;
		case 5: sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 4, 32, 32));
			break;
		case 6: sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 5, 32, 32));
			break;
		case 7: sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 6, 32, 32));
			break;
		case 8: sprite.setTextureRect(sf::IntRect(counterWalking * 32, 32 * 6, 32, 32));
			break;
		default: std::cout << "Error" << std::endl;
			break;
		}
	}
	else
	{
		switch (direction)
		{
		case 1:	sprite.setTextureRect(sf::IntRect(0 * 32, 32 * 3, 32, 32));
			break;
		case 2: sprite.setTextureRect(sf::IntRect(0 * 32, 0, 32, 32));
			break;
		case 3: sprite.setTextureRect(sf::IntRect(0 * 32, 32 * 1, 32, 32));
			break;
		case 4: sprite.setTextureRect(sf::IntRect(0 * 32, 32 * 2, 32, 32));
			break;
		case 5: sprite.setTextureRect(sf::IntRect(0 * 32, 32 * 4, 32, 32));
			break;
		case 6: sprite.setTextureRect(sf::IntRect(0 * 32, 32 * 5, 32, 32));
			break;
		case 7: sprite.setTextureRect(sf::IntRect(0 * 32, 32 * 6, 32, 32));
			break;
		case 8: sprite.setTextureRect(sf::IntRect(0 * 32, 32 * 6, 32, 32));
			break;
		default: std::cout << "Error" << std::endl;
			break;
		}
	}
	counterWalking++;

	if (counterWalking == 3)
		counterWalking = 0;
}

void Player::updateDirection(int mX, int mY)
{
	
	float slope = ((rect.getPosition().y - mY) / (rect.getPosition().x - mX));
	slope = -1 * slope;

	if (mX < rect.getPosition().x)
	{
		if ((slope >= 0.0 && slope < (3.0 / 4.0)) || (slope <= 0 && slope > (-3.0 / 4.0)))
		{	
			setDirection(3);
		}
		else if (slope >= (3.0 / 4.0) && slope <= 1.25)
		{
			setDirection(5);
		}
		else if (slope > 1.25)
		{
			setDirection(2);
		}
		else if (slope < (-3.0 / 4.0))
		{
			setDirection(1);
		}
	}

	else if (mX > rect.getPosition().x)
	{
		if ((slope >= 0.0 && slope < (3.0 / 4.0)) || (slope <= 0 && slope >(-3.0 / 4.0)))
		{
			setDirection(4);	
		}
		else if (slope <= (-3.0 / 4.0) && slope >= -1.25)
		{
			setDirection(6);
		}
		else if (slope > 1.25)
		{
			setDirection(1);
		}
		else if (slope < -1.25)
		{
			setDirection(2);
		}
	}
}
*/