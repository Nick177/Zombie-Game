#pragma once
#ifndef HEALTH_BAR
#define HEALTH_BAR

#include "statusBar.h"
#include<iostream>

class HealthBar :public StatusBar
{
private:
	float previousHealth;
	int counter;
	float tempWidth;
public:
	HealthBar();

	float getCurrentHealth() const { return previousHealth; }

	void setHealth(float health) { previousHealth = health; }
	void update(float playerHealth);
};

#endif // !HEALTH_BAR
