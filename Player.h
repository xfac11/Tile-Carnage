#pragma once
#include<SFML/Graphics.hpp>
class Player: 
	public sf::RectangleShape
{
public:
	Player();
	~Player();
	void update(sf::RenderWindow & window, float dt);
	void updateMovement(float dt);
	void onCollision(sf::RectangleShape * obj, int x, int y);
private:
	float speed;
	float moveX;
	float moveY;
	sf::Vector2f prevPos;
};

