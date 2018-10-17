#include "Player.h"



Player::Player()
{
	this->eye.setSize(sf::Vector2f(5, 5));
	this->eye.setFillColor(sf::Color::White);
	setFillColor(sf::Color::Blue);
	setSize(sf::Vector2f(64.0f-2.f, 64.0f-2.f));
	setOrigin(sf::Vector2f(getSize().x/2.f, getSize().y/2.f));
	setPosition(100.0f, 100.0f);
	this->speed = 200.0f;//With high speed the collision will be breaked
	this->moveX = 0.f;
	this->moveY = 0.f;
	//eyePos = sf::Vector2f(getPosition().x, getPosition().y);
}


Player::~Player()
{
}

sf::RectangleShape Player::getEye()
{
	return this->eye;
}

void Player::update(sf::RenderWindow & window, float dt)
{
	prevPos = getPosition();
	//window.draw(this->eye);
	//this->eye.setPosition(eyePos);
	//window.draw(*this);
	move(this->moveX, this->moveY);
	
}

int Player::updateMovement(float dt)
{
	moveX = 0.f;
	moveY = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveY = -this->speed*dt;
		rotation = 0;
		//eyePos = sf::Vector2f(getPosition().x, getPosition().y-32.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveY = this->speed*dt;
		rotation = 180;
		//eyePos = sf::Vector2f(getPosition().x, getPosition().y+32.f-this->eye.getSize().y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveX = -this->speed*dt;
		rotation = 180 + 90;
		//eyePos = sf::Vector2f(getPosition().x-32.f, getPosition().y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveX = this->speed*dt;
		
		rotation = 90;
		//eyePos = sf::Vector2f(getPosition().x + 32.f-this->eye.getSize().x, getPosition().y);
	}
	return rotation;

}

void Player::onCollision(sf::RectangleShape * obj, int x, int y)
{
	//Collision is Broken when high speed
	setPosition(prevPos);
	
}

void Player::draw(sf::RenderWindow & window)
{
	window.draw(*this);
}
