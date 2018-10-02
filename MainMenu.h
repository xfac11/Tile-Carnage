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
	void addText(std::string text);
	void changeText(Direction dir);
	void changeText();
	void movementForFire(sf::RenderWindow & window,float deltaTime);
	void drawText(sf::RenderWindow & window,float deltaTime);
	void setPosition(sf::Vector2f pos,float space);
	int getCurrentText()const;
	Selected getCurrentSelected()const;
private:
	sf::Font font;
	sf::Text* text;
	int nrOfTexts;
	int cap;
	int currentText;
	Selected state;
	bool upButton;
	bool downButton;

	Animate* fireBall;

	sf::Sprite box;
	sf::Texture textForBox;
};
#endif // !MAINMENU_H
