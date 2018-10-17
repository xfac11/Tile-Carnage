#include "textbox.h"

textbox::textbox()
{
	setSize(sf::Vector2f(500, 40));
	setFillColor(sf::Color::White);
	this->boxtexture.loadFromFile("textures/textBoxtexture.png");
	setTexture(&this->boxtexture);
	this->theInfo = "";
	this->theFont.loadFromFile("Font/PressStart2P.ttf");
	this->thetext.setFont(theFont);
	this->thetext.setCharacterSize(25);
	this->thetext.setFillColor(sf::Color::Black);


	this->isPressed = false;
	this->typeMode = false;
}

textbox::~textbox()
{}

std::string textbox::getString() const
{
	return theInfo;
}

bool textbox::getTypeMode() const
{
	return this->typeMode;
}

void textbox::settextSize(const int size)
{
	this->thetext.setCharacterSize(size);
}

void textbox::draw(sf::RenderWindow & window)
{
	window.draw(*this);
	window.draw(thetext);
}

void textbox::update(sf::RenderWindow & window, sf::Event & theEvent, sf::View & view, sf::RectangleShape mouse)
{
	//this->setPosition(sf::Vector2f(100, 100)); //textbox fix view.getCenter();
	setPosition(view.getCenter().x-view.getSize().x/2+10.0f,(view.getCenter().y-view.getSize().y/2)+50.0f);
	this->thetext.setPosition(getPosition()+sf::Vector2f(1.f,10.f));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse.getGlobalBounds().intersects(getGlobalBounds()))
		this->typeMode = true;
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->typeMode = false;

	if (theEvent.type == sf::Event::TextEntered && isPressed == false && typeMode == true)
	{
		if (theEvent.text.unicode < 128 && theEvent.text.unicode>32 && theInfo.length() < 18)
		{
			this->theInfo += static_cast<char>(theEvent.text.unicode);
			thetext.setString(theInfo);
		}
		else if (theEvent.text.unicode == 8 && theInfo != "")
		{
			this->theInfo.erase(theInfo.end() - 1);
			thetext.setString(theInfo);
		}
		isPressed = true;
	}
	else if (theEvent.type == sf::Event::TextEntered && isPressed) {}
	else
	{
		isPressed = false;
	}

	
}
