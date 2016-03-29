#include "projectile.h"

Projectile::Projectile()
{
	rect.setSize(sf::Vector2f(10, 10));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Green);

	movementSpeed = 0.5;
	projLifeTime = 2.0;
	direction = 0;
	destroy = false;
	distance = 0;
	damage = 5;
}

void Projectile::update()
{

	if (direction == 1) // UP
		rect.move(0, -movementSpeed);
	if (direction == 2) // down
		rect.move(0, movementSpeed);
	if (direction == 3) // right
		rect.move(movementSpeed, 0);
	if (direction == 4) // left
		rect.move(-movementSpeed, 0);

	distance += movementSpeed;
}
