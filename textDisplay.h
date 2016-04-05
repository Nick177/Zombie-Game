#pragma once
#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "Entity.h"

using namespace std;

class TextDisplay : public Entity
{
	private:
		float movementSpeed;
		int counter;
		int lifeTime;
		bool destroy;
		string myString = "TESTING";


	public:
		TextDisplay();
		void update();
		bool getDestroy()const { return this->destroy; }


};
#endif