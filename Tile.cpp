#include "Tile.h"

Tile::Tile(int xID, int yID, TileType theType, int imageId)
	:sf::RectangleShape()
{
	this->imageId = imageId;
	int imageCount = 4;//Image on row and column
	int x = imageId%imageCount;
	int y = imageId/imageCount;
	this->xID = xID;
	this->yID = yID;
	//this->textureName = thetexture;
	this->stringFortextType = ToString(theType);
	if (this->font.loadFromFile("Font/PressStart2P.ttf"))
	{
		std::cout << "funkar";
	}
	this->typetext.setFont(this->font);
	this->typetext.setString(this->stringFortextType[0]);
	this->typetext.setCharacterSize(10);
	//std::cout << stringFortextType << std::endl;
	this->thetexture.loadFromFile("textures/Ground_Sprites.png");
	uvRect.width = (int)(this->thetexture.getSize().x / imageCount);
	uvRect.height = (int)(this->thetexture.getSize().y / imageCount);
	uvRect.left = x * uvRect.width;
	uvRect.top = y * uvRect.height;
	setSize(sf::Vector2f((float)this->uvRect.width, (float)this->uvRect.height));
	setTextureRect(this->uvRect);
	setTexture(&this->thetexture);

	//settextureRect(posIntexture);
	//setSize(sf::Vector2f(32, 32));
	setOrigin(sf::Vector2f(getSize().x/2.f, getSize().y/2.f));
	setPosition(xID*getSize().x+getSize().x/2, yID*getSize().y + getSize().y / 2);
	this->typetext.setPosition(getPosition() + sf::Vector2f(7.0f, 0.0f));
	this->theType = theType;
}
//This constructor for TileOptions
Tile::Tile(int imageId)
	:sf::RectangleShape()
{
	this->imageId = imageId;
	int imageCount = 4;//Image on row and column
	int x = imageId % imageCount;
	int y = imageId / imageCount;
	this->xID = xID;
	this->yID = yID;
	//this->textureName = thetexture;
	this->stringFortextType = ToString(Normal);
	if (this->font.loadFromFile("Font/PressStart2P.ttf"))
	{
		std::cout << "funkar";
	}
	this->typetext.setFont(this->font);
	this->typetext.setString(this->stringFortextType[0]);
	this->typetext.setCharacterSize(10);
	//std::cout << stringFortextType << std::endl;
	this->thetexture.loadFromFile("textures/Ground_Sprites.png");
	uvRect.width = (int)(this->thetexture.getSize().x / imageCount);
	uvRect.height = (int)(this->thetexture.getSize().y / imageCount);
	uvRect.left = x * uvRect.width;
	uvRect.top = y * uvRect.height;
	setSize(sf::Vector2f((float)this->uvRect.width, (float)this->uvRect.height));
	setTextureRect(this->uvRect);
	setTexture(&this->thetexture);

	//settextureRect(posIntexture);
	//setSize(sf::Vector2f(32, 32));
	setOrigin(sf::Vector2f(16, 16));
	//setPosition(xyPos);
	this->typetext.setPosition(getPosition() + sf::Vector2f(7.0f, 0.0f));
	this->theType = theType;
}

void Tile::operator=(const Tile & obj)
{
	if (this != &obj)
	{
		this->imageId = obj.imageId;
		this->xID = xID;
		this->yID = yID;
		this->stringFortextType = ToString(Normal);
		if (this->font.loadFromFile("Font/PressStart2P.ttf"))
		{
			std::cout << "funkar";
		}
		this->typetext.setFont(this->font);
		this->typetext.setString(this->stringFortextType[0]);
		this->typetext.setCharacterSize(10);
		//std::cout << stringFortextType << std::endl;
		this->thetexture.loadFromFile("textures/Ground_Sprites.png");
		setSize(obj.getSize());
		this->uvRect = obj.uvRect;
		setTextureRect(this->uvRect);
		setTexture(&this->thetexture);

		//settextureRect(posIntexture);
		//setSize(sf::Vector2f(32, 32));
		setOrigin(sf::Vector2f(16, 16));
		setPosition(obj.getPosition());
		this->typetext.setPosition(getPosition() + sf::Vector2f(7.0f, 0.0f));
		this->theType = obj.theType;
	}
}

Tile::Tile()
	:sf::RectangleShape()
{
	//load some texture to show unloaded stuff
	//setSize(sf::Vector2f(32, 32));
	this->imageId = 4;
	setOrigin(sf::Vector2f(16, 16));
	this->theType = Normal;
}

Tile::~Tile()
{
}

int Tile::getXID() const
{
	return this->xID;
}

int Tile::getYID() const
{
	return this->yID;
}

void Tile::setTileType(TileType theType)
{
	this->theType = theType;
}

TileType Tile::getTileType() const
{
	return this->theType;
}

std::string Tile::gettextureName() const
{
	return this->textureName;
}

void Tile::draw(sf::RenderWindow & window)
{
	if (this != nullptr)
	{
		window.draw(*this);
		window.draw(this->typetext);
	}
	//std::cout << ":  " << this << std::endl;
	
}

int Tile::getImageId() const
{
	return this->imageId;
}

void Tile::updateTypetextPos()
{
	this->typetext.setPosition(getPosition()); //+ sf::Vector2f(7.0f, 0.0f));
}
