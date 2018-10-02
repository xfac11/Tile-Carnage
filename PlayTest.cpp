#include "PlayTest.h"

PlayTest::PlayTest(sf::RenderWindow& window ,sf::View &view)
{
	this->theMouse.setSize(sf::Vector2f(5.f, 5.f));
	this->theMouse.setFillColor(sf::Color::White);
	this->theMouse.setOrigin(2.5f, 2.5f);
	map.loadSheet("karlos");
	map.changeSizeOfAllTiles(128.0f,128.0f);
	for (int i = 0; i < map.getNrOfTiles(); i++)
	{
		if (this->map.getAt(i)->getTileType() == Collidable)
		{
			collBlock.insert(this->map.getAt(i));
		}
	}
	//Skövvla in alla med typen Collidable i en tile array och kolla dessa med collision
	textBox.setScale(1.f/3.f, 1.f/3.f);
	this->textBox.setTextSize(10);
	//playTestView = view;
	//playTestView.zoom(0.9);
	//view.zoom(0.8);
	//window.setView(view);
}

PlayTest::PlayTest()
{

}

PlayTest::~PlayTest()
{
}

//sf::View & PlayTest::getView()
//{
//	this->playTestView;
//}

void PlayTest::update(sf::RenderWindow & window,sf::Event &theEvent, sf::View & view,float deltaTime)
{
	//view.setSize(sf::Vector2f(window.getSize().x/3, window.getSize().y/3))
	map.update(window);
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	this->theMouse.setPosition(worldPos);
	textBox.update(window, theEvent, view, theMouse);
	if (this->textBox.getTypeMode() == false)
		player.updateMovement(deltaTime);
	player.update(window, deltaTime);
	//The player collision is broken when the player is set on a high speed
	collisionCheck();

	view.setCenter(this->player.getPosition());
	window.draw(this->theMouse);
}

void PlayTest::collisionCheck()
{
	//What the player does when it collides need to be updated. It does stop and you can move afterwards
	//But it seems the world/player is shaking when you keep moving at the colBlock


	//This collision works with the map but if we add objects that can move the whole tree need to be updated
	//Which will take time. So we might do a second tree for the moveable objects and update that tree. 
	//Updating can be to remove all the things in it and insert it again.
	int x = int(this->player.getPosition().x) / 128;
	int y = int(this->player.getPosition().y) / 128;
	//int xMouse = int(this->theMouse.getPosition().x) / 128;
	//int yMouse = int(this->theMouse.getPosition().y) / 128;
	this->player.setFillColor(sf::Color::Blue);
	Tile* temp = nullptr;
	temp = collBlock.getAt(x - 1, y - 1);
	if (temp!=nullptr)
		if(temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		this->player.setFillColor(sf::Color::Magenta);
		this->player.onCollision(temp,-1,-1);
	}
	temp = collBlock.getAt(x - 1, y);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		this->player.onCollision(temp,-1,0);
		this->player.setFillColor(sf::Color::Magenta);
	}
	temp = collBlock.getAt(x - 1, y + 1);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		  this->player.onCollision(temp,-1,1);
		this->player.setFillColor(sf::Color::Magenta);
	}
	temp = collBlock.getAt(x, y - 1);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		  this->player.onCollision(temp,0,-1);
	}
	temp = collBlock.getAt(x, y);
	  if(temp!=nullptr)
	if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		this->player.onCollision(temp,0,0);
		this->player.setFillColor(sf::Color::Green);

	}
	  temp = collBlock.getAt(x, y + 1);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		  this->player.onCollision(temp,0,1);

	}
	temp = collBlock.getAt(x + 1, y - 1);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		  this->player.onCollision(temp,1,-1);

	}
	temp = collBlock.getAt(x + 1, y);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		  this->player.onCollision(temp,1,0);

		 
	}
	temp = collBlock.getAt(x + 1, y + 1);
	  if (temp != nullptr)
	if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		this->player.onCollision(temp,1,1);

	}
}
