#include "Animate.h"

Animate::Animate(std::string file, int imageCount, float switchTime) //make a handler to add multiple animations
{
	this->theTx.loadFromFile("textures/" + file + ".png");
	this->setPosition(sf::Vector2f(600, -200)); //remove (can decide this outside class)
	this->setSize(sf::Vector2f(128, 128)); //remove (can decide this outside class)
	this->imageCount = imageCount;
	this->currentImage = 0;
	this->totalTime = 0.f;
	this->switchTime = switchTime;

	this->uvRect.width = this->theTx.getSize().x / imageCount;
	this->uvRect.height = this->theTx.getSize().y;
}
Animate::~Animate()
{}
void Animate::update(sf::RenderWindow & window, float deltaTime)
{
	this->totalTime += deltaTime;
	if (this->totalTime >= this->switchTime)
	{
		this->totalTime -= this->switchTime;
		this->currentImage++;
		if (this->currentImage >= this->imageCount)
		{
			this->currentImage = 0;
		}
	}
	this->uvRect.left = this->currentImage * this->uvRect.width;
	this->uvRect.top = 0;
	this->setTextureRect(this->uvRect);
	this->setTexture(&this->theTx);
	window.draw(*this);
}