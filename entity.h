#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Entity
{
public:
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Text text;
	Entity();
};

#endif
