#pragma once

#include "screens.h"
#include<iostream>
using namespace std;
#ifndef MENU_SCREEN
#define MENU_SCREEN
class MenuScreen : public Screen
{
private:

public:
	MenuScreen(void);
	int Run(sf::RenderWindow &App);

};
#endif

MenuScreen::MenuScreen(void)
{

}

int MenuScreen::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	bool Running = true;
	short currentMenuItem = 0;
	const int fontSize = 20;
	sf::Font font;
	sf::Text menuTitle;
	sf::Text menuItem_1;
	sf::Text menuItem_2;
	sf::Text menuItem_3;

	if (!font.loadFromFile("consola.ttf"))
	{
		std::cout << "Font not loading correctly!!!!\n";
		return(-1);
	}

	menuTitle.setFont(font);
	menuTitle.setCharacterSize(fontSize);
	menuTitle.setString("Zombie Game");
	menuTitle.setPosition(App.getSize().x / 2, App.getSize().y / 8);
	menuTitle.setColor(sf::Color::Green);

	menuItem_1.setFont(font);
	menuItem_1.setCharacterSize(fontSize);
	menuItem_1.setString("Play");
	menuItem_1.setPosition(App.getSize().x / 2, App.getSize().y / 2);
	menuItem_1.setColor(sf::Color::Green);

	menuItem_2.setFont(font);
	menuItem_2.setCharacterSize(fontSize);
	menuItem_2.setString("Exit");
	menuItem_2.setPosition(App.getSize().x / 2, App.getSize().y * 6 / 8);
	menuItem_2.setColor(sf::Color::Green);


	while (Running)
	{
		while (App.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				return -1;
			}

			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Up:
					currentMenuItem = 0;
					break;
				case sf::Keyboard::Down:
					currentMenuItem = 1;
					break;
				case sf::Keyboard::Return:
					if (currentMenuItem == 0)
						return 1;
					else
						return -1;
					break;
				default:
					std::cout << "error\n";
					break;
				}
			}
		}

		if (currentMenuItem == 0)
		{
			menuItem_1.setColor(sf::Color::White);
			menuItem_2.setColor(sf::Color::Green);
		}
		else
		{
			menuItem_1.setColor(sf::Color::Green);
			menuItem_2.setColor(sf::Color::White);
		}

		App.clear();
		App.draw(menuTitle);
		App.draw(menuItem_1);
		App.draw(menuItem_2);
		App.display();
		
	}
	return -1;
}
