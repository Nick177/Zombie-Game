
//To replace a word: CTRL + SHIFT + F

#include<iostream>
#include<cmath>

#include "Player.h"
#include "projectile.h"
#include "enemy.h"
//#include "statusBar.h"
#include "healthBar.h"

using namespace sf;

int main(int argc, char ** argv) {
	sf::RenderWindow renderWindow(sf::VideoMode(1366, 768), "Demo Game");
	//renderWindow.setFramerateLimit(120);

	sf::Color color(sf::Color::Red);
	sf::Event event;
	sf::IntRect rectSourceSprite(0, 0, 32, 32);
	sf::Texture texture, zombieTexture;
	sf::Clock clock, zombieClock, zombieClock2;
	sf::Time elapsed;


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
	v1.setSize(sf::Vector2f(renderWindow.getSize().x, renderWindow.getSize().y));
	v1.setCenter(sf::Vector2f(renderWindow.getSize().x / 2, renderWindow.getSize().y / 2));
	renderWindow.setView(v1);
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
	renderWindow.setKeyRepeatEnabled(false);

	p1.sprite.setPosition(sf::Vector2f(renderWindow.getSize().x / 2, renderWindow.getSize().y / 2));
	p1.rect.setPosition(sf::Vector2f(renderWindow.getSize().x / 2, renderWindow.getSize().y / 2));
	//******************************

	//StatusBar bar;
	HealthBar hBar;
	//hBar.barRect.setSize(sf::Vector2f(64 * 3, 32));

	//*****************************
	//Enemy setup:
	if (!zombieTexture.loadFromFile("Images/zombie2.png"))
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

	//**************************************************
	//Main Game Loop:

	while (renderWindow.isOpen()) {
		//****************************************
		//Event Loop
		while (renderWindow.pollEvent(event)) {

			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		} // end event loop
		  //****************************************
		  //Clears screenp
		renderWindow.clear();
		//Draws Background
		renderWindow.draw(background);
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
		if (zombieClock.getElapsedTime().asMilliseconds() == 2000 /*&& (enemyArray.size() < 10)*/)
		{
			enemy1.rect.setPosition(enemy1.randomPositionX(renderWindow.getSize().x),
				enemy1.randomPositionY(renderWindow.getSize().y));

			enemyArray.emplace_back(enemy1);
			zombieClock.restart();
		}

		//****************************************************************
		// Draw enemies to screen
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			enemyArray[counter].update();
			enemyArray[counter].updateMovement();
			//window.draw(enemyArray[counter].rect);
			renderWindow.draw(enemyArray[counter].getCircle());

			renderWindow.draw(enemyArray[counter].sprite);

			counter++;
		}
		//****************************************************************
		//This for loop draws the projectiles along with setting those that hit enemies be destroyed and enemies as well
		counter = 0;
		enemiesJustDefeated = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			projectileArray[counter].update();
			renderWindow.draw(projectileArray[counter].rect);

			if (projectileArray[counter].getDistance() >= 600)
				projectileArray[counter].canDestroy(true);


			counter2 = 0;
			for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray[counter2].rect.getGlobalBounds()))
				{
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
				//swapToLast(projectileArray, counter);
				projectileArray.erase(iter);
				projCounter--;
				//std::cout << "Delete!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11" << std::endl;
				break;
			}
			counter++;
		}

		//******************************************************************************
		//These lines of code update the player position (basically allows player to move)
		p1.updateMovement();
		p1.update();
		//**********************************
		//This sets the view to our view object and centers are view object relative to our sprite
		//In short, the camera follows our character
		renderWindow.setView(v1);
		v1.setCenter(p1.rect.getPosition());
		renderWindow.draw(p1.sprite);
		//***********************************
		hBar.update(p1.getHealth());
		hBar.barRect.setPosition((p1.rect.getPosition().x - renderWindow.getSize().x / 2) + 10, (p1.rect.getPosition().y - renderWindow.getSize().y / 2) + 10);
		hBar.barOutline.setPosition(hBar.barRect.getPosition());
		renderWindow.draw(hBar.barRect);
		renderWindow.draw(hBar.barOutline);

		renderWindow.display();

	}
}
