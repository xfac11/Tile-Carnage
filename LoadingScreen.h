#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include<SFML/Graphics.hpp>
class LoadingScreen
{
public:
	LoadingScreen();
	LoadingScreen(sf::Vector2f winSize);
	~LoadingScreen();
	void open(float speed,sf::Vector2f playerPos);
	void close(float speed,float deltaTime,sf::Vector2f windowPos);
	void draw(sf::RenderWindow & window);
	void setisLoad(bool isLoad);
	bool isLoadDone()const;
	bool isLoadScene()const;
private:
	sf::RectangleShape left;
	sf::RectangleShape right;
	bool isLoadingDone;
	bool isLoadingScene;
	float xLeft;
	float xRight;
	sf::Vector2f windowSize;

};
#endif // !LOADINGSCREEN_H

