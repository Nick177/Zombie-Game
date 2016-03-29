#pragma once
#ifndef STATUS_BAR
#define STATUS_BAR

#include "SFML\Graphics.hpp"

class StatusBar {
protected:
	float WIDTH;
	float HEIGHT;
public:
	sf::RectangleShape barRect;
	sf::RectangleShape barOutline;
	sf::Color barColor;
	StatusBar();

	void setWidth(int width) { this->WIDTH = width; }
	void setHeight(int height) { this->HEIGHT = height; }

};
#endif