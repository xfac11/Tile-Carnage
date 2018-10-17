#ifndef MAINMENU_H
#define MAINMENU_H
#include<SFML/Graphics.hpp>
#include<iostream>
#include"Animate.h"
enum Selected
{
	StartTest,
	EditWorld,
	Options,
	Exit
};
enum Direction
{
	UP,
	DOWN
};
class MainMenu
{
public:
	MainMenu(std::string fileName);
	MainMenu();
	virtual~MainMenu();
	void addtext(std::string text);
	void changetext(Direction dir);
	void changetext();
	void movementForFire(sf::RenderWindow & window,float deltaTime);
	void drawtext(sf::RenderWindow & window,float deltaTime);
	void setPosition(sf::Vector2f pos,float space);
	int getCurrenttext()const;
	Selected getCurrentSelected()const;
private:
	sf::Font font;
	sf::Text* text;
	int nrOftexts;
	int cap;
	int currenttext;
	Selected state;
	bool upButton;
	bool downButton;

	Animate* fireBall;

	sf::Sprite box;
	sf::Texture textForBox;
};
#endif // !MAINMENU_H
