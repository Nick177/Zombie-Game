#pragma once

#include "screens.h"
#include<iostream>
#include<cmath>

#include "Player.h"
#include "projectile.h"
#include "enemy.h"
#include "healthBar.h"
#include <random>
#include "textDisplay.h"

#ifndef GAME_SCREEN
#define GAME_SCREEN
class GameScreen : public Screen
{
private:
	
public:
	GameScreen(void);
	int Run(sf::RenderWindow &App);

};
#endif

GameScreen::GameScreen(void)
{

}

float calcSlope(sf::Vector2f pointA, sf::Vector2f pointB);
float calcAng(sf::Vector2f pointA, sf::Vector2f pointB);
Vector2f normalize(const Vector2f& source);

int GameScreen::Run(sf::RenderWindow &App)
{

	//To replace a word: CTRL + SHIFT + F


	using namespace sf;
	using namespace std;
	/*
	float calcSlope(sf::Vector2f pointA, sf::Vector2f pointB);
	float calcAng(sf::Vector2f pointA, sf::Vector2f pointB);
	Vector2f normalize(const Vector2f& source);

	sf::Vector2f zombieDirection;

	int main(int argc, char ** argv) {
	*/
		//sf::RenderWindow renderWindow(sf::VideoMode(1366, 768), "Demo Game");
		//renderWindow.setFramerateLimit(120);

		sf::Vector2f zombieDirection;
		sf::Color color(sf::Color::Red);
		sf::Event event;
		sf::IntRect rectSourceSprite(0, 0, 32, 32);
		sf::Texture texture, zombieTexture;
		sf::Clock clock, zombieClock, zombieClock2;
		sf::Time elapsed;

		float angle;

		float slope;
		//***********************************
		//Variable to be used for boundaries
		bool borderRight,
			borderLeft,
			borderTop,
			borderBottom;

		//***********************************
		//Background Setup:
		sf::Texture bTexture;

		if (!bTexture.loadFromFile("Images/background1.jpg"))
		{
			std::cout << "Error\n";
		}

		sf::Sprite background(bTexture);
		background.setTextureRect(sf::IntRect(0, 0, 1074, 762));

		sf::RectangleShape backgroundRect;
		backgroundRect.setPosition(background.getPosition());
		backgroundRect.setSize(sf::Vector2f(bTexture.getSize().x, bTexture.getSize().y));
		//***********************************

		//*******************************
		//View setup (camera for main character):
		sf::View v1;
		v1.setSize(sf::Vector2f(App.getSize().x, App.getSize().y));
		v1.setCenter(sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2));
		App.setView(v1);
		//*******************************

		//Projectile setup:
		int projCounter = 0;
		const int  PROJ_LIMIT = 100;

		std::vector<Projectile>::const_iterator iter;
		std::vector<Projectile> projectileArray;

		Projectile projectile1;

		//*********************************
		int counter = 0, counter2 = 0;
		//*********************************
		//Player setup:
		Player p1;

		if (!texture.loadFromFile("Images/testSprite.png"))
		{
			std::cout << "Error\n";
		}
		p1.sprite.setTexture(texture);
		p1.sprite.setTextureRect(rectSourceSprite);
		//p1.sprite.scale(sf::Vector2f(3, 3));
		App.setKeyRepeatEnabled(false);

		p1.sprite.setPosition(sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2));
		p1.rect.setPosition(sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2));
		p1.sprite.scale(sf::Vector2f(1, 1.5));
		//******************************

		//StatusBar bar;
		HealthBar hBar;
		//hBar.barRect.setSize(sf::Vector2f(64 * 3, 32));

		//*****************************
		//Enemy setup:
		if (!zombieTexture.loadFromFile("Images/zombie.png"))
		{
			std::cout << "Error\n";
		}
		//Enemy setup:
		std::vector<Enemy>::const_iterator iter4;
		std::vector<Enemy> enemyArray;

		Enemy enemy1;

		enemy1.sprite.setTexture(zombieTexture);
		enemy1.sprite.setTextureRect(IntRect(0, 0, 64, 64));
		enemyArray.push_back(enemy1);

		int enemiesJustDefeated = 0;
		//*****************************
		Font font;
		if (!font.loadFromFile("consola.ttf"))
			return EXIT_FAILURE;

		//Text vector Array
		vector<TextDisplay>::const_iterator textIter;
		vector<TextDisplay> textDisplayArray;

		//Text display object
		TextDisplay text1;
		//text1.text.setPosition(300, 300);
		text1.text.setFont(font);
		//textDisplayArray.push_back(text1);


		//**************************************************
		//Main Game Loop:

		while (App.isOpen()) {
			//****************************************
			//Event Loop
			while (App.pollEvent(event)) {

				if (event.type == sf::Event::EventType::Closed)
					App.close();

			} // end event loop
			  //****************************************
			  //Clears screenp
			App.clear();
			//Draws Background
			App.draw(background);
			//***********************************
			//This sets up the boundaries:
			borderTop = (p1.rect.getPosition().y < backgroundRect.getPosition().y + 5);
			borderBottom = (p1.rect.getPosition().y > backgroundRect.getSize().y - 5 - 32);
			borderLeft = (p1.rect.getPosition().x < backgroundRect.getPosition().x + 5);
			borderRight = (p1.rect.getPosition().x > backgroundRect.getSize().x - 5);

			if (borderBottom || borderTop || borderLeft || borderRight)
			{
				switch (p1.getDirection())
				{
				case 1: p1.setCanMoveUp(false);
					if (!borderTop)
						p1.setCanMoveUp(true);
					break;
				case 2: p1.setCanMoveDown(false);
					if (!borderBottom)
						p1.setCanMoveDown(true);
					break;
				case 3: p1.setCanMoveRight(false);
					if (!borderRight)
						p1.setCanMoveRight(true);
					break;
				case 4: p1.setCanMoveLeft(false);
					if (!borderLeft)
						p1.setCanMoveLeft(true);
					break;
				default:
					std::cout << "Error" << std::endl;
				}
			}
			else
			{
				p1.setCanMoveUp(true);
				p1.setCanMoveDown(true);
				p1.setCanMoveLeft(true);
				p1.setCanMoveRight(true);
			}
			//******************************************************
			//Enemy collides with player
			if (zombieClock2.getElapsedTime().asSeconds() >= 0.5)
			{
				zombieClock2.restart();
				counter = 0;
				for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
				{
					if (p1.rect.getGlobalBounds().intersects(enemyArray[counter].rect.getGlobalBounds()))
					{
						p1.healthReduction(enemyArray[counter].getAttackDamage());
					}
					counter++;
				}
			}
			//**********************************************
			//elapsed is to keep track of time to manage objects within game such as projectiles
			//elapsed = clock.getElapsedTime();
			//Keyboard event to shoot projectiles
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (clock.getElapsedTime().asSeconds() > 0.2))
			{
				projectile1.rect.setPosition(p1.rect.getPosition().x + p1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2, p1.rect.getPosition().y + p1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
				projectile1.setDirection(p1.getDirection());
				projectileArray.push_back(projectile1);
				clock.restart();
			}

			//*************************************************************
			// Creating a new enemy every 2 seconds
			if (zombieClock.getElapsedTime().asMilliseconds() >= 5000 /*&& (enemyArray.size() < 10)*/)
			{
				enemy1.rect.setPosition(enemy1.randomPositionX(App.getSize().x),
					enemy1.randomPositionY(App.getSize().y));

				enemyArray.emplace_back(enemy1);
				zombieClock.restart();
			}

			//****************************************************************
			// Draw enemies to screen and chases player if within range of the enemy
			counter = 0;
			for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
			{
				enemyArray[counter].update();

				if (enemyArray[counter].getCircle().getGlobalBounds().intersects(p1.rect.getGlobalBounds()))
				{
					enemyArray[counter].setPlayerInRange(true);

					zombieDirection = normalize(p1.sprite.getPosition() - enemyArray[counter].sprite.getPosition());

					enemyArray[counter].rect.move(enemyArray[counter].getMovementSpeed() * zombieDirection);

					angle = calcAng(enemyArray[counter].rect.getPosition(), p1.rect.getPosition());

					if (p1.rect.getPosition().x < enemyArray[counter].rect.getPosition().x
						&& p1.rect.getPosition().y < enemyArray[counter].rect.getPosition().y)
						angle = 180 - angle;
					else if (p1.rect.getPosition().x < enemyArray[counter].rect.getPosition().x
						&& p1.rect.getPosition().y > enemyArray[counter].rect.getPosition().y)
						angle = (180 + 90) - angle;
					else if (p1.rect.getPosition().x > enemyArray[counter].rect.getPosition().x
						&& p1.rect.getPosition().y > enemyArray[counter].rect.getPosition().y)
						angle = 360 - angle;
					else
						angle += 0;

					enemyArray[counter].changeDirection(angle);

					/*
					slope = calcSlope(enemyArray[counter].rect.getPosition(), p1.rect.getPosition());

					if (p1.rect.getPosition().x < enemyArray[counter].rect.getPosition().x)
					{
					if ((slope >= 0.0 && slope < (3.0 / 4.0)) || (slope <= 0 && slope > (-3.0 / 4.0)))
					enemyArray[counter].setDirection(3);
					else if (slope >= (3.0 / 4.0) && slope <= 1.25)
					enemyArray[counter].setDirection(5);
					else if (slope > 1.25)
					enemyArray[counter].setDirection(2);
					else if (slope < (-3.0 / 4.0))
					enemyArray[counter].setDirection(1);
					}

					else if (p1.rect.getPosition().x > enemyArray[counter].rect.getPosition().x)
					{
					if ((slope >= 0.0 && slope < (3.0 / 4.0)) || (slope <= 0 && slope >(-3.0 / 4.0)))
					enemyArray[counter].setDirection(4);
					else if (slope <= (-3.0 / 4.0) && slope >= -1.25)
					enemyArray[counter].setDirection(6);
					else if (slope > 1.25)
					enemyArray[counter].setDirection(1);
					else if (slope < -1.25)
					enemyArray[counter].setDirection(2);
					}
					*/

					enemyArray[counter].updateMovement();

					//cout << angle << endl;

				}
				else
				{
					enemyArray[counter].setPlayerInRange(false);
					enemyArray[counter].updateMovement();

				}

				//Draws the circle around the enemy
				//renderWindow.draw(enemyArray[counter].getCircle());

				App.draw(enemyArray[counter].sprite);

				counter++;
			}
			//****************************************************************
			//This for loop draws the projectiles along with setting those that hit enemies be destroyed and enemies as well
			counter = 0;
			enemiesJustDefeated = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				projectileArray[counter].update();
				App.draw(projectileArray[counter].rect);

				if (projectileArray[counter].getDistance() >= 600)
					projectileArray[counter].canDestroy(true);


				counter2 = 0;
				for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
				{
					if (projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray[counter2].rect.getGlobalBounds()))
					{
						//Text Display damage taken by the enemy
						text1.text.setString(to_string(projectileArray[counter].getAttackDamage()));
						text1.text.setPosition(enemyArray[counter2].rect.getPosition().x, enemyArray[counter2].rect.getPosition().y);
						textDisplayArray.push_back(text1);

						projectileArray[counter].canDestroy(true);
						enemyArray[counter2].setHP(projectileArray[counter].getAttackDamage());// -= projectileArray[counter].attackDamage;
						if (enemyArray[counter2].getHP() <= 0.0)
						{
							enemyArray[counter2].isDead();// = false;
						}
						//enemyArray[counter2].isDead();
						enemiesJustDefeated++;
					}

					counter2++;
				}
				counter++;
			}
			//*****************************************************************************
			//This following for loop draws the enemies still alive


			counter = 0;
			for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
			{

				if (!enemyArray[counter].isAlive())
				{
					//cout << "Target neutralized!" << endl;
					enemyArray.erase(iter4);
					break;
				}

				counter++;

			}

			//******************************************************************************
			//The following for loop destroys any projectiles that need to be destroyed
			counter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				if (projectileArray[counter].isDestroyed())
				{
					projectileArray.erase(iter);
					projCounter--;
					//std::cout << "Delete!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11" << std::endl;
					break;
				}
				counter++;
			}


			// Delete Text Display


			counter = 0;
			for (textIter = textDisplayArray.begin(); textIter != textDisplayArray.end(); textIter++)
			{
				if (textDisplayArray[counter].getDestroy())
				{
					textDisplayArray.erase(textIter);
					break;
				}
				counter++;
			}
			//******************************************************************************
			//These lines of code update the player position (basically allows player to move)
			p1.updateMovement();
			//p1.updateDirection(sf::Mouse::getPosition(renderWindow).x, sf::Mouse::getPosition(renderWindow).y);
			p1.update();

			//**********************************
			//This sets the view to our view object and centers are view object relative to our sprite
			//In short, the camera follows our character
			App.setView(v1);
			v1.setCenter(p1.rect.getPosition());
			App.draw(p1.sprite);
			//***********************************
			hBar.update(p1.getHealth());
			hBar.barRect.setPosition((p1.rect.getPosition().x - App.getSize().x / 2) + 10, (p1.rect.getPosition().y - App.getSize().y / 2) + 10);
			hBar.barOutline.setPosition(hBar.barRect.getPosition());
			App.draw(hBar.barRect);
			App.draw(hBar.barOutline);

			counter = 0;
			for (textIter = textDisplayArray.begin(); textIter != textDisplayArray.end(); textIter++)
			{
				textDisplayArray[counter].update();
				App.draw(textDisplayArray[counter].text);
				counter++;
			}

			App.display();

		}

		return -1;

	/*
	float calcSlope(sf::Vector2f pointA, sf::Vector2f pointB)
	{
		float slope;

		slope = ((pointB.y - pointA.y) / (pointB.x - pointA.x));

		return -1 * (slope);
	}
	Vector2f normalize(const Vector2f& source)
	{
		float length = sqrt((source.x * source.x) + (source.y * source.y));
		if (length != 0)
			return Vector2f(source.x / length, source.y / length);
		else
			return source;
	}

	float calcAng(sf::Vector2f pointA, sf::Vector2f pointB)
	{
		float angle;
		float x, y, z;

		x = abs(pointA.x - pointB.x);
		y = abs(pointA.y - pointB.y);

		angle = atanf(y / x) * 180 / 3.14;

		cout << angle << endl;

		return angle;

	} */
}

float calcSlope(sf::Vector2f pointA, sf::Vector2f pointB)
{
	float slope;

	slope = ((pointB.y - pointA.y) / (pointB.x - pointA.x));

	return -1 * (slope);
}
Vector2f normalize(const Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return Vector2f(source.x / length, source.y / length);
	else
		return source;
}

float calcAng(sf::Vector2f pointA, sf::Vector2f pointB)
{
	float angle;
	float x, y, z;

	x = abs(pointA.x - pointB.x);
	y = abs(pointA.y - pointB.y);

	angle = atanf(y / x) * 180 / 3.14;

	cout << angle << endl;

	return angle;

}


