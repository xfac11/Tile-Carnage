#include "Player.h"



Player::Player()
{
	setFillColor(sf::Color::Blue);
	setSize(sf::Vector2f(64.0f, 64.0f));
	setOrigin(sf::Vector2f(32.f, 32.f));
	setPosition(100.0f, 100.0f);
	this->speed = 200.0f;//With high speed the collision will be breaked
	this->moveX = 0.f;
	this->moveY = 0.f;
}


Player::~Player()
{
}

void Player::update(sf::RenderWindow & window, float dt)
{
	prevPos = getPosition();
	window.draw(*this);
	move(this->moveX, this->moveY);
}

void Player::updateMovement(float dt)
{
	moveX = 0.f;
	moveY = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveY = -this->speed*dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveY = this->speed*dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveX = -this->speed*dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveX = this->speed*dt;
	}

}

void Player::onCollision(sf::RectangleShape * obj, int x, int y)
{
	//Collision is Broken when high speed
	setPosition(prevPos);
	
}
