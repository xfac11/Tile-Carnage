#include "Textbox.h"

Textbox::Textbox()
{
	setSize(sf::Vector2f(500, 40));
	setFillColor(sf::Color::White);

	this->theInfo = "";
	this->theFont.loadFromFile("Font/PressStart2P.ttf");
	this->theText.setFont(theFont);
	this->theText.setCharacterSize(25);
	this->theText.setFillColor(sf::Color::Black);


	this->isPressed = false;
	this->typeMode = false;
}

Textbox::~Textbox()
{}

std::string Textbox::getString() const
{
	return theInfo;
}

bool Textbox::getTypeMode() const
{
	return this->typeMode;
}

void Textbox::setTextSize(const int size)
{
	this->theText.setCharacterSize(size);
}

void Textbox::draw(sf::RenderWindow & window)
{
	window.draw(*this);
	window.draw(theText);
}

void Textbox::update(sf::RenderWindow & window, sf::Event & theEvent, sf::View & view, sf::RectangleShape mouse)
{
	//this->setPosition(sf::Vector2f(100, 100)); //textbox fix view.getCenter();
	setPosition(view.getCenter().x-view.getSize().x/2+10.0f,(view.getCenter().y-view.getSize().y/2)+50.0f);
	this->theText.setPosition(getPosition());
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse.getGlobalBounds().intersects(getGlobalBounds()))
		this->typeMode = true;
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->typeMode = false;

	if (theEvent.type == sf::Event::TextEntered && isPressed == false && typeMode == true)
	{
		if (theEvent.text.unicode < 128 && theEvent.text.unicode>32 && theInfo.length() < 18)
		{
			this->theInfo += static_cast<char>(theEvent.text.unicode);
			theText.setString(theInfo);
		}
		else if (theEvent.text.unicode == 8 && theInfo != "")
		{
			this->theInfo.erase(theInfo.end() - 1);
			theText.setString(theInfo);
		}
		isPressed = true;
	}
	else if (theEvent.type == sf::Event::TextEntered && isPressed) {}
	else
	{
		isPressed = false;
	}

	
}
