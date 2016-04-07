#include "screens.h"
#include "GameScreen.h"
#include "MenuScreen.h"
#include <vector>

int main(int argc, char** argv)
{
	std::vector<Screen*> Screens;

	int currentScreen = 0;

	sf::RenderWindow App(sf::VideoMode(1366, 768), "Demo Game");

	MenuScreen mainMenu;
	GameScreen gameWindow;

	Screens.push_back(&mainMenu);
	Screens.push_back(&gameWindow);

	while (currentScreen >= 0)
	{
		currentScreen = Screens[currentScreen]->Run(App);
	}


	
	return EXIT_SUCCESS;
}