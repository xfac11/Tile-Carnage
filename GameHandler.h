#ifndef GAMEHANDLER_H	
#define GAMEHANDLER_H
#include "MapEditor.h"
#include "MainMenu.h"
#include"PlayTest.h"
#define VIEW_HEIGHT 1080.0f
class GameHandler
{
private:
	sf::RenderWindow window;
	sf::Event theEvent;
	sf::Clock clock;
	float deltaTime;

	PlayTest* playTest;
	
	int loopTimes;

	sf::View view;
	MainMenu menu;
	MapEditor editor;
	sf::Vector2f originalViewCenter;
	int currentMenu;
	void resizeView(const sf::RenderWindow &window, sf::View &view);
public:
	GameHandler();
	~GameHandler();
	void updateMenu();
	void update();
};
#endif
