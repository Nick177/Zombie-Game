#include "textDisplay.h"

TextDisplay::TextDisplay()
{
	movementSpeed = 0.02;
	counter = 0;
	lifeTime = 1600;

	destroy = false;
	text.setColor(sf::Color::Red);
	text.setCharacterSize(50);
	text.setString(myString);
}

void TextDisplay::update()
{

	text.move(0, -movementSpeed);


	counter++;
	if (counter >= lifeTime)
	{
		destroy = true;
		counter = 0;
	}
}