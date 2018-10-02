#pragma once
#include <SFML\Graphics.hpp>
#include <string>
class Animate : public sf::RectangleShape
{
private:
	sf::Texture theTx;
	sf::IntRect uvRect;

	int imageCount;
	int currentImage;
	float totalTime;
	float switchTime;
public:
	Animate(std::string file, int imageCount, float switchTime);
	~Animate();

	void update(sf::RenderWindow &window, float deltaTime);
};