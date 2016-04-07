#pragma once
#include "SFML\Graphics.hpp"
//#include "MenuScreen.h"
//#include "GameScreen.h"
#include <iostream>
#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
public:
	Screen(void);
	virtual int Run(sf::RenderWindow &App) = 0;
};

#endif // !SCREEN

Screen::Screen(void)
{

}
