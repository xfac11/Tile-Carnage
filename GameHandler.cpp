#include "GameHandler.h"

void GameHandler::resizeView(const sf::RenderWindow & window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT*aspectRatio, VIEW_HEIGHT);
	
}

GameHandler::GameHandler()
{
	this->loopTimes = 0;
	this->currentMenu = -1;
	this->window.setFramerateLimit(60);
	this->window.create(sf::VideoMode::getDesktopMode(), "TileCarnage");
	this->window.setMouseCursorVisible(false);
	resizeView(this->window, this->view);
	menu.setPosition(this->view.getCenter(),30.0f);
	this->originalViewCenter = this->view.getCenter();
	//this->view.zoom(0.8f);
	this->playTest = new PlayTest(window, view);
	this->deltaTime = 0;
}

GameHandler::~GameHandler()
{
	delete playTest;
}

void GameHandler::updateMenu()
{
	deltaTime = clock.restart().asSeconds();
	this->loopTimes++;
	//std::cout << loopTimes << std::endl;
	if (deltaTime > 1.0f / 20.0f)
	{
		deltaTime = 1.0f / 20.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->currentMenu == -1)
	{
		this->currentMenu = this->menu.getCurrentText();
	}
	if (this->currentMenu == -1)
	{
		menu.drawText(window,deltaTime);
	}
	else if (this->currentMenu == StartTest)
	{

		//this->window.setView(this->playTest->getView());
		playTest->update(window, theEvent,view,deltaTime);
		//Put the startTest Update here or something
	}
	else if (this->currentMenu == EditWorld)
	{
		this->editor.draw(this->window, this->deltaTime, this->view, this->theEvent);
	}
	else if (this->currentMenu == Options)
	{
		//Put options thingy here
	}
	else if (this->currentMenu == Exit)
	{
		this->window.close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && this->currentMenu != -1&&this->editor.getTypeMode() == false)
	{
		this->currentMenu = -1;
		this->view.setCenter(this->originalViewCenter);
		this->view.setSize(sf::Vector2f(window.getSize()));
	}
}

void GameHandler::update()
{
	while (window.isOpen())
	{
		window.setView(view);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->window.close();
		while (this->window.pollEvent(this->theEvent))
		{
			if (theEvent.type == sf::Event::Closed)
				this->window.close();
		}
		this->window.clear(sf::Color(50,50,50));
		//this->window.draw();
		//Detta kollar vi eftersom när vi är i en state så ska inte menu ändras om man
		//trycker upp eller ner. Endast när currentMenu är -1. För då är vi i menu
		if (this->currentMenu == -1)
		{
			menu.changeText();
		}
		this->updateMenu();
		//open map here??

		this->window.display();
	}
}
