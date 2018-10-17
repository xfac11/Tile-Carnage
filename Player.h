#pragma once
#include<SFML/Graphics.hpp>
class Player: 
	public sf::RectangleShape
{
public:
	Player();
	~Player();
	sf::RectangleShape getEye();
	void update(sf::RenderWindow & window, float dt);
	int updateMovement(float dt);
	void onCollision(sf::RectangleShape * obj, int x, int y);
	void draw(sf::RenderWindow & window);
private:
	float speed;
	float moveX;
	float moveY;
	sf::Vector2f prevPos;
	sf::RectangleShape eye;
	sf::Vector2f eyePos;
	int rotation;
};

