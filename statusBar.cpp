#include "statusBar.h"

StatusBar::StatusBar()
{
	WIDTH = 64 * 4;
	HEIGHT = 28;
	barRect.setSize(sf::Vector2f(WIDTH, HEIGHT));
	barOutline.setSize(barRect.getSize());
	barOutline.setFillColor(sf::Color::Transparent);
	barOutline.setOutlineThickness(2);
	barOutline.setOutlineColor(sf::Color::Black);
	barColor.g = 175;
	barColor.r = 22;
	barColor.b = 11;
	barRect.setFillColor(barColor);
	barRect.setPosition(20, 20);
	barOutline.setPosition(barRect.getPosition());
}