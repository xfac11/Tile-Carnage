#include "LoadingScreen.h"

LoadingScreen::LoadingScreen()
{
	this->isLoadingDone = false;
}

LoadingScreen::LoadingScreen(sf::Vector2f winSize)
{
	this->isLoadingDone = false;
	this->isLoadingScene = false;
	this->windowSize = winSize;
	this->xLeft = 0;
	this->xRight = 0;
	this->left.setPosition(winSize);
	this->right.setPosition(winSize);
	this->left.setFillColor(sf::Color::Magenta);
	this->right.setFillColor(sf::Color(0,255,0,50));
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::open(float speed,sf::Vector2f playerPos)
{
	
}

void LoadingScreen::close(float speed,float deltaTime, sf::Vector2f windowPos)
{
	if (!this->isLoadingScene)
	{
		this->isLoadingScene = true;
		this->left.setPosition(windowPos);
		this->right.setPosition(windowPos.x+windowSize.x-10.f,windowPos.y);
	}
	if (this->isLoadingDone != true)
	{
		//this->left.setPosition(playerPos.x - windowSize.x / 2, playerPos.y - windowSize.y / 2);
		if (xLeft <= (windowSize.x / 2)+20)
			xLeft += speed*deltaTime;
		else
		{
			this->isLoadingDone = true;
		}
		this->left.setSize(sf::Vector2f(xLeft, windowSize.y));
		//this->right.setPosition(playerPos.x + windowSize.x / 2, playerPos.y - windowSize.y / 2);
		if (xRight >= (-windowSize.x / 2) -20)
			xRight -= speed*deltaTime;

		this->right.setSize(sf::Vector2f(xRight, windowSize.y));
	}
	else
	{
		//this->left.setPosition(playerPos.x - windowSize.x / 2, playerPos.y - windowSize.y / 2);
		if (xLeft >= 0.f)
			xLeft -= speed*deltaTime;
		else
		{
			this->isLoadingScene = false;
			this->isLoadingDone = false;
		}
		this->left.setPosition(windowPos);
		this->left.setSize(sf::Vector2f(xLeft, windowSize.y));
		//this->right.setPosition(playerPos.x + windowSize.x / 2, playerPos.y - windowSize.y / 2);
		if (xRight <= 0.0f)
			xRight += speed*deltaTime;
		this->right.setPosition(windowPos.x + windowSize.x-10.f, windowPos.y);
		this->right.setSize(sf::Vector2f(xRight, windowSize.y));
	}
}

void LoadingScreen::draw(sf::RenderWindow & window)
{
	window.draw(this->left);
	window.draw(this->right);
}

void LoadingScreen::setisLoad(bool isLoad)
{
	this->isLoadingScene = isLoad;
}

bool LoadingScreen::isLoadDone() const
{
	return this->isLoadingDone;
}


bool LoadingScreen::isLoadScene() const
{
	return this->isLoadingScene;
}

