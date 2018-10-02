#include "MapEditor.h"

float MapEditor::windowX(float size)
{
	float windowX = 1920.f / size;
	return sf::VideoMode::getDesktopMode().width / windowX;
}

float MapEditor::windowY(float size)
{
	float windowY = 1080.f / size;
	return sf::VideoMode::getDesktopMode().height / windowY;
}

sf::Vector2i MapEditor::getMouseID()
{
	float xF(this->theMouse.getPosition().x / 32);
	float yF(this->theMouse.getPosition().y / 32);
	//Fixar negativa positioner (-0,5 är ju 0 och inte 1)
	if (yF < 0)
	{
		yF -= 1;
	}
	if (xF < 0)
	{
		xF -= 1;
	}
	int x = int(xF);
	int y = int(yF);

	sf::Vector2i result(x, y);

	return result;
}

bool MapEditor::mouseOnObject(sf::RectangleShape object)
{
	bool result = false;
	if ((this->theMouse.getPosition().x > object.getPosition().x - object.getOrigin().x &&
		this->theMouse.getPosition().x < object.getPosition().x + object.getSize().x - object.getOrigin().x) &&
		(this->theMouse.getPosition().y < object.getPosition().y + object.getSize().y-object.getOrigin().y&&
			this->theMouse.getPosition().y>object.getPosition().y-object.getOrigin().y))
		
	{
		result = true;
	}
	return result;
}


void MapEditor::updateHUD(sf::View &view, float deltaTime)
{
	float tileSpace=20.f;
	this->tileMenu.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y + view.getSize().y / 2 - this->tileMenu.getSize().y);
	this->theArrows[0].setPosition(view.getCenter().x, view.getCenter().y -view.getSize().y/2 +20);
	this->theArrows[1].setPosition(view.getCenter().x + view.getSize().x / 2 - 50, view.getCenter().y);
	this->theArrows[2].setPosition(view.getCenter().x, view.getCenter().y + view.getSize().y / 2 - 50);
	this->theArrows[3].setPosition(view.getCenter().x - view.getSize().x / 2 + 20, view.getCenter().y);

	this->hudForLoadNSaveNText.setPosition(this->textBox.getPosition().x-10.0f,this->textBox.getPosition().y-15.0f);
	this->loadRect.setPosition(this->textBox.getPosition().x +100,this->textBox.getPosition().y + this->loadRect.getSize().y+20.0f);
	this->saveRect.setPosition(this->loadRect.getPosition().x + this->saveRect.getSize().x + 50.0f, this->textBox.getPosition().y + this->saveRect.getSize().y + 20.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && this->tileChange == false&&this->textBox.getTypeMode()==false)
	{
		this->theTileOptions.changeShowingTiles();
		this->tileChange = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{

	}
	else
	{
		this->tileChange = false;
	}
	float x = 20.0f;
	float y = 42.f;
	//this->theTileOptions.setPosition(this->tileMenu.getPosition().x,this->tileMenu.getPosition().y);
	for (int i = 0; i < this->theTileOptions.getNrOfCurrentTiles(); i++)
	{
		//this->showingtiles[i].setPosition(this->x + x, this->y + y);
		this->theTileOptions.getRectFromTiles(i).setPosition(x + this->tileMenu.getPosition().x, y + this->tileMenu.getPosition().y);
		if (x >= 188.0f && y >= 85.f)
		{
			x = 20.0f;
			y = 42.f;
		}
		else if (x >= 188.0f)
		{
			x = 20.0f;
			y += 42.f;
		}
		else
		{
			x += 20.0f+ 32.0f;
		}
	  
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (mouseOnObject(saveRect))
		{
			if (textBox.getString() == "")
			{
				saveRect.setFillColor(sf::Color::Red);
			}
			else
			{
				currentMap.saveToFile(textBox.getString());//läsa från textfältet
				saveRect.setFillColor(sf::Color::Magenta);
			}
		}
		if (mouseOnObject(loadRect))
		{
			if (textBox.getString() == "")
			{
				loadRect.setFillColor(sf::Color::Red);
				currentMap.reset();
			}
			else
			{
				currentMap.reset();
				if (currentMap.loadSheet(textBox.getString()) == true)
				{
					loadRect.setFillColor(sf::Color::Green);
				}
				else
				{
					loadRect.setFillColor(sf::Color::Red);
				}
			}
		}
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) //make afunction
	{
		int pos = -1;
		for (int i = 0; i < theTileOptions.getNrOfCurrentTiles() && pos == -1; i++)
		{

			if (mouseOnObject(theTileOptions.getRectFromTiles(i)))//|| )
			{
				this->prevId = i;
				//för att ta upp och ner blocket
				//this->isMovable = true;
				//Skapar block i blocks för att sätta ut i världen
				delete tempBlock;
				this->tempBlock = new Tile(theTileOptions.getTile(i));
				//this->tempBlock->setFillColor(theTileOptions.getRectFromTiles(i).getFillColor());
				//this->tempBlock->setOrigin(BLOCKWIDTH / 2, BLOCKHEIGHT / 2);
				this->tempBlock->setPosition(this->theMouse.getPosition());
				this->currentTileTypeText.setPosition(this->tempBlock->getPosition() + sf::Vector2f(7.0f, 0.0f));
				pos = i;
				this->isMovable = true;
				if (this->isMovable == true) //can remove?
				{

				}
				
			}
			
			
		}
		if (mouseOnObject(*this->tempBlock) == true &&
			this->isMovable==true&&
			this->mouseOnObject(this->tileMenu)==false&&
			this->mouseOnObject(this->saveRect)==false&&
			this->mouseOnObject(this->loadRect)==false&&
			this->mouseOnObject(this->textBox)==false&&
			this->mouseOnObject(this->hudForLoadNSaveNText)==false)
			//&&this->mouseOnObject(this->typeBlock)//&& mouseOnObject(theTileOptions.getRectFromTiles(i)) == false)
		{

			int x = getMouseID().x;
			int y = getMouseID().y;
			if (currentMap.getTile(x, y) == nullptr)
			{
				//add
				currentMap.addTile(x, y, theTileOptions.getTile(this->prevId).getImageId(), this->currentTileType);
			}
			else if (currentMap.getTile(x, y) != nullptr)
			{
				//delete
				currentMap.searchRemove(x, y);
				//then add
				currentMap.addTile(x, y, this->theTileOptions.getTile(this->prevId).getImageId(), this->currentTileType);
			}
			//this->prevId = i;
			////för att ta upp och ner blocket
			//this->isMovable = true;
			////Skapar block i blocks för att sätta ut i världen
			//delete tempBlock;
			//this->tempBlock = new Tile(theTileOptions.getTile(i));
			////this->tempBlock->setFillColor(theTileOptions.getRectFromTiles(i).getFillColor());
			////this->tempBlock->setOrigin(BLOCKWIDTH / 2, BLOCKHEIGHT / 2);
			//this->tempBlock->setPosition(this->theMouse.getPosition());
			//this->currentTileTypeText.setPosition(this->tempBlock->getPosition() + sf::Vector2f(7.0f, 0.0f));
		}

		else
		{

		}
		this->isPressed = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{}
	else
	{
		this->isPressed = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->isRightClick == false&&this->isMovable)
	{
		if (this->currentTileTypeNr == 3)
		{
			this->currentTileTypeNr = -1;
		}
		this->currentTileTypeNr += 1;
		this->currentTileType =TileType(this->currentTileTypeNr);
		this->currentTileTypeString = ToString(this->currentTileType);
		this->currentTileTypeText.setString(this->currentTileTypeString[0]);
		this->isRightClick = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{

	}
	else
	{
		this->isRightClick = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
	{
		int x = getMouseID().x;
		int y = getMouseID().y;

		if (currentMap.getTile(x, y) != nullptr)
		{
			currentMap.searchRemove(x, y);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&this->textBox.getTypeMode()==false)
		view.move(0.f*deltaTime, -this->speedForMovingCamera*deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->textBox.getTypeMode() == false)
		view.move(0.f, this->speedForMovingCamera*deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->textBox.getTypeMode() == false)
		view.move(-this->speedForMovingCamera*deltaTime, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->textBox.getTypeMode() == false)
		view.move(deltaTime*this->speedForMovingCamera, .0f);
	
	
}

MapEditor::MapEditor()
{
	this->hudForLoadNSaveNText.setFillColor(sf::Color::Black);
	this->speedForMovingCamera = 500.0f;
	this->prevId = 0;
	this->temp = false;
	this->isPressed = false;
	this->isMovable = false;
	this->isRightClick = false;
	this->tileChange = false;
	//Changing tiletype
	this->currentTileTypeString = ToString(Normal);
	this->currentTileType = Normal;
	this->tileTypeFont.loadFromFile("Font/PressStart2P.ttf");
	this->currentTileTypeText.setFont(this->tileTypeFont);
	this->currentTileTypeText.setString(this->currentTileTypeString[0]);
	this->currentTileTypeText.setCharacterSize(20);
	//ui
	//tile menu
	this->tileMenu.setFillColor(sf::Color(192, 192, 192)); //silver
	this->tileMenu.setSize(sf::Vector2f(windowX(500), windowY(350)));

	//theArrows
	arrow[0].loadFromFile("textures/arrow-up.png");
	arrow[1].loadFromFile("textures/arrow-right.png");
	arrow[2].loadFromFile("textures/arrow-down.png");
	arrow[3].loadFromFile("textures/arrow-left.png");

	for (int i = 0;i < 4;i++)
		theArrows[i].setTexture(&arrow[i]);

	theArrows[0].setSize(sf::Vector2f(windowX(64), windowY(32)));
	theArrows[1].setSize(sf::Vector2f(windowX(32), windowY(64)));
	theArrows[2].setSize(sf::Vector2f(windowX(64), windowY(32)));
	theArrows[3].setSize(sf::Vector2f(windowX(32), windowY(64)));

	//menu tile choices
	
	//this->textureForAll.loadFromFile("Ground_Sprites.png");
	theTileOptions.addTileTexture(0);
	theTileOptions.addTileTexture(1);
	theTileOptions.addTileTexture(2);
	theTileOptions.addTileTexture(3);
	theTileOptions.addTileTexture(4);
	theTileOptions.addTileTexture(5);
	theTileOptions.addTileTexture(6);
	theTileOptions.addTileTexture(7);
	theTileOptions.addTileTexture(8);
	theTileOptions.addTileTexture(9);
	theTileOptions.addTileTexture(10);
	theTileOptions.addTileTexture(11);
	theTileOptions.addTileTexture(12);
	theTileOptions.addTileTexture(13);
	theTileOptions.addTileTexture(14);
	theTileOptions.addTileTexture(15);

	//theTileOptions.addTileTexture(this->textureForAll, sf::IntRect(32 * 0, 32 * 0, 32, 32));
	//theTileOptions.addTileTexture(this->textureForAll, sf::IntRect(32 * 0, 32 * 0, 32, 32));



	/*theTileOptions.addTileTexture(sf::Color::Blue);
	theTileOptions.addTileTexture(sf::Color::Blue);
	theTileOptions.addTileTexture(sf::Color::Blue);
	theTileOptions.addTileTexture(sf::Color::Blue);
	theTileOptions.addTileTexture(sf::Color::Green);
	theTileOptions.addTileTexture(sf::Color::Green);
	theTileOptions.addTileTexture(sf::Color::Green);
	theTileOptions.addTileTexture(sf::Color::Green);
	theTileOptions.addTileTexture(sf::Color::Green);
	theTileOptions.addTileTexture(sf::Color::Red);
	theTileOptions.addTileTexture(sf::Color::Red);
	theTileOptions.addTileTexture(sf::Color::Red);
	theTileOptions.addTileTexture(sf::Color::Red);
	theTileOptions.addTileTexture(sf::Color::Red);
	theTileOptions.addTileTexture(sf::Color::Yellow);*/
	//mouse 
	this->theMouse.setSize(sf::Vector2f(5.f, 5.f));
	this->theMouse.setFillColor(sf::Color::White);
	this->theMouse.setOrigin(2.5f, 2.5f);

	this->tempBlock = new Tile(); //sätter default på tempblock för att den inte ska vara null

	//Save & load
	this->saveRect.setSize(sf::Vector2f(100.0f, 50.0f));
	this->saveRect.setFillColor(sf::Color::Magenta);
	this->loadRect.setSize(sf::Vector2f(100.0f, 50.0f));
	this->loadRect.setFillColor(sf::Color::Green);
	this->hudForLoadNSaveNText.setSize(sf::Vector2f(this->textBox.getSize().x+20.0f, (this->saveRect.getSize().y*3)));// - this->textBox.getPosition().y));

}

MapEditor::~MapEditor()
{
	delete tempBlock;
}

bool MapEditor::getTypeMode() const
{
	return this->textBox.getTypeMode();
}

void MapEditor::draw(sf::RenderWindow & window, float deltaTime, sf::View &view,sf::Event &theEvent)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	this->theMouse.setPosition(worldPos);
	if (temp == false)
	{
		//currentMap.loadMap("test");
		temp = true;
	}

	if (isMovable == true)
	{
		tempBlock->setPosition(theMouse.getPosition());
		this->currentTileTypeText.setPosition(this->tempBlock->getPosition() + sf::Vector2f(7.0f, 0.0f));
	}

	//theInputs.update(window, theEvent);
	currentMap.update(window);
	
	
	this->textBox.update(window, theEvent, view, this->theMouse);
	updateHUD(view, deltaTime);
	window.draw(this->hudForLoadNSaveNText);
	this->textBox.draw(window);
	window.draw(tileMenu);
	
	for (int i = 0;i < 4;i++)
		window.draw(theArrows[i]);
	window.draw(this->saveRect);
	window.draw(this->loadRect);
	theTileOptions.drawCurrentTiles(window);
	//currentMap.update(window);
	window.draw(*tempBlock);
	if (this->isMovable)
	{
		window.draw(this->currentTileTypeText);
	}
	window.draw(theMouse);
}
