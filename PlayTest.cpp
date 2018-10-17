#include "PlayTest.h"

PlayTest::PlayTest(sf::RenderWindow& window ,sf::View &view)
{
	//Editworld bug: when we put in too many tiles shit happens. The texture wont load.
	//Light
	
	//tex.create(window.getSize().x+1000, window.getSize().y+1000);
	
	//tex.setSmooth(true);
	//Scene loading
	loading = new LoadingScreen(sf::Vector2f(window.getSize()));
	this->loadedMap = false;
	this->scene = false;
	this->blackBox.setOrigin(this->player.getPosition());
	this->blackBox.setPosition(this->player.getPosition());
	this->blackBox.setSize(sf::Vector2f(window.getSize()));
	this->blackBox.setFillColor(sf::Color::Black);
	//
	this->theMouse.setSize(sf::Vector2f(5.f, 5.f));
	this->theMouse.setFillColor(sf::Color::White);
	this->theMouse.setOrigin(2.5f, 2.5f);
	map.loadSheet("karlos");
	tileSize = 64.0f;
	map.changeSizeOfAllTiles(tileSize,tileSize);
	for (int i = 0; i < map.getNrOfTiles(); i++)
	{
		if (this->map.getAt(i)->getTileType() == Collidable|| this->map.getAt(i)->getTileType()== Gate)
		{
			collBlock.insert(this->map.getAt(i));
		}
	}
	light.setPointCount(4);
	light.setPoint(0, sf::Vector2f(this->player.getPosition())-sf::Vector2f(32,32));
	light.setPoint(1, sf::Vector2f(this->player.getPosition()) - sf::Vector2f(-32, 32));
	light.setPoint(2, (sf::Vector2f(this->player.getPosition()) - sf::Vector2f(-32, 32))+sf::Vector2f(64,-128));
	light.setPoint(3, (sf::Vector2f(this->player.getPosition()) - sf::Vector2f(-32, 32)) + sf::Vector2f(-128, -128));
	light.setOrigin(light.getPoint(0));
	light.setFillColor(sf::Color(255,255,255,50));
	//Skövvla in alla med typen Collidable i en tile array och kolla dessa med collision
	textBox.setScale(1.f/3.f, 1.f/3.f);
	this->textBox.settextSize(10);
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
	delete this->loading;
}

//sf::View & PlayTest::getView()
//{
//	this->playTestView;
//}

void PlayTest::update(sf::RenderWindow & window, sf::Event &theEvent, sf::View & view, float deltaTime)
{
	int rotation = 0;
	//view.setSize(sf::Vector2f(window.getSize().x/3, window.getSize().y/3))
	//Light
	//tex.clear(sf::Color::Black);
	//this->tex.draw(light, sf::BlendAdd);
	//tex.setView(view);
	//tex.display();
	//
	map.update(window);
	//window.draw(this->blackBox);
	//window.draw(sf::Sprite(tex.getTexture()), sf::BlendMultiply);
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	this->theMouse.setPosition(worldPos);
	textBox.update(window, theEvent, view, theMouse);
	player.draw(window);
	if (this->textBox.getTypeMode() == false && this->loading->isLoadScene() == false)
	{
		rotation = player.updateMovement(deltaTime);
		player.update(window, deltaTime);
	}
	//Loading
	if (this->scene == true)
	{
		this->loadingScene(window,deltaTime);
	}
	if (!this->loading->isLoadDone() && !this->loading->isLoadScene())
	{
		this->scene = false;
	}
	//Light
	float x = 0;
	float y = 0;
	if (rotation == 0)
	{
		x = -32.f;
		y = -32.f;
	}
	else if (rotation == 90)
	{
		x = 32.f;
		y = -32.f;
	}
	else if (rotation == 180)
	{
		x = 32.f;
		y = 32.f;
	}
	else if (rotation == 180 + 90)
	{
		x = -32.f;
		y = 32.f;
	}
	this->light.setPosition(this->player.getPosition() + sf::Vector2f(x, y));
	this->light.setRotation(rotation);
	//
	//The player collision is broken when the player is set on a high speed
	collisionCheck(sf::Vector2f(window.getSize()));

	view.setCenter(this->player.getPosition());
	
	window.draw(this->theMouse);
	if (this->scene == true)
	{
		this->loading->draw(window);
	}
}

void PlayTest::collisionCheck(sf::Vector2f windowSize)
{
	//What the player does when it collides need to be updated. It does stop and you can move afterwards
	//But it seems the world/player is shaking when you keep moving at the colBlock
	//This collision works with the map but if we add objects that can move the whole tree need to be updated
	//Which will take time. So we might do a second tree for the moveable objects and update that tree. 
	//Updating can be to remove all the things in it and insert it again.
	int x = int(this->player.getPosition().x) / int(tileSize);
	int y = int(this->player.getPosition().y) / int(tileSize);
	//int xMouse = int(this->theMouse.getPosition().x) / 128;
	//int yMouse = int(this->theMouse.getPosition().y) / 128;
	this->player.setFillColor(sf::Color::Blue);
	Tile* temp = nullptr;
	temp = collBlock.getAt(x - 1, y - 1);
	if (temp!=nullptr)
		if(temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
			if (temp->getTileType() == Gate)
				enterDoor("cp",windowSize);
		this->player.setFillColor(sf::Color::Magenta);
		this->player.onCollision(temp,-1,-1);
	}
	temp = collBlock.getAt(x - 1, y);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		  if (temp->getTileType() == Gate)
			  enterDoor("cp",windowSize);
		 this->player.onCollision(temp,-1,0);
		this->player.setFillColor(sf::Color::Magenta);
	}
	temp = collBlock.getAt(x - 1, y + 1);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		  if (temp->getTileType() == Gate)
			  enterDoor("cp",windowSize);
		  this->player.onCollision(temp,-1,1);
		this->player.setFillColor(sf::Color::Magenta);
	}
	temp = collBlock.getAt(x, y - 1);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		  if (temp->getTileType() == Gate)
			  enterDoor("cp",windowSize);
		  this->player.onCollision(temp,0,-1);
	}
	temp = collBlock.getAt(x, y);
	  if(temp!=nullptr)
	if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		if (temp->getTileType() == Gate)
			enterDoor("cp",windowSize);
		this->player.onCollision(temp,0,0);
		this->player.setFillColor(sf::Color::Green);

	}
	  temp = collBlock.getAt(x, y + 1);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		  if (temp->getTileType() == Gate)
			  enterDoor("cp",windowSize);
		  this->player.onCollision(temp,0,1);

	}
	temp = collBlock.getAt(x + 1, y - 1);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		  if (temp->getTileType() == Gate)
			  enterDoor("cp",windowSize);
		  this->player.onCollision(temp,1,-1);

	}
	temp = collBlock.getAt(x + 1, y);
	if(temp!=nullptr)
	  if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		  if (temp->getTileType() == Gate)
			  enterDoor("cp",windowSize);
		  this->player.onCollision(temp,1,0);

		 
	}
	temp = collBlock.getAt(x + 1, y + 1);
	  if (temp != nullptr)
	if (temp->getGlobalBounds().intersects(this->player.getGlobalBounds()))
	{
		if (temp->getTileType() == Gate)
			enterDoor("cp",windowSize);
		this->player.onCollision(temp,1,1);

	}
}

void PlayTest::enterDoor(std::string mapName,sf::Vector2f windowSize)
{
	this->scene = true;
}

void PlayTest::loadingScene(sf::RenderWindow & window,float deltaTime)
{
	this->loading->close(1000.f,deltaTime, window.mapPixelToCoords(window.getPosition()));
	if (this->loading->isLoadDone() && this->loadedMap == false)
	{
		this->map.loadSheet("cp");
		map.changeSizeOfAllTiles(tileSize, tileSize);
		for (int i = 0; i < map.getNrOfTiles(); i++)
		{
			if (this->map.getAt(i)->getTileType() == Collidable || this->map.getAt(i)->getTileType() == Gate)
			{
				collBlock.insert(this->map.getAt(i));
			}
		}
		this->loadedMap = true;
	}
}
