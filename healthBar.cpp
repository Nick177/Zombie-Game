#include "healthBar.h"

HealthBar::HealthBar() : StatusBar()
{
	previousHealth = 100.0;
	counter = 1;
	tempWidth = WIDTH;
}

void HealthBar::update(float playerHealth)
{
	if (playerHealth <= 0)
	{
		barRect.setSize(sf::Vector2f(0, HEIGHT));
	}
	if (counter == 1)
		previousHealth = playerHealth;
	counter++;
	if (counter >= 100)
		counter = 2;

	if (previousHealth == playerHealth)
	{
		return;
	}
	if (playerHealth > 0)
	{
		tempWidth = WIDTH * playerHealth / 100;
		barRect.setSize(sf::Vector2f(tempWidth, HEIGHT));
	}
	if (playerHealth >= 30 && playerHealth <= 70)
	{
		barColor.g = 247;
		barColor.r = 229;
		barColor.b = 32;
		barRect.setFillColor(barColor);
	}
	if (playerHealth >= 0 && playerHealth < 30)
	{
		barColor.g = 0;
		barColor.r = 252;
		barColor.b = 0;
		barRect.setFillColor(barColor);
	}

	previousHealth = playerHealth;
}