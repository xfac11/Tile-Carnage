#include "TileMap.h"

void TileMap::extendArray()
{
	this->cap += 20;
	Tile* *temp= new Tile*[this->cap];

	for (int i = 0; i < nrOfTiles;i++)
	{
		temp[i] = this->theTiles[i];
	}
	std::cout << "wow";

	delete[] this->theTiles;
	this->theTiles = temp;
}

void TileMap::freeMemory()
{
	for (int i = 0; i < this->nrOfTiles; i++)
	{
		delete theTiles[i];
	}
	delete[]theTiles;
}

TileMap::TileMap(std::string loadMap) //
{
	this->name = loadMap;

	std::ifstream input;
	input.open("mapFiles/"+loadMap + ".txt");
	input >> this->name;
	//std::cout << this->name;
	/*
	File:
	Tent  //name  
	20  //nrOf
	32  //cap 
	3 3 3 3 3 ? ? ?  //layout  //nr istype of tile, but tile load its name as texture6
	3 1 2 1 3 ? ? ? // Tile(xID: int, yId: int, Texture: Texture , type: TileType)
	3 1 1 1 3 ? ? ?
	3 3 4 3 3 ? ? ?
	
	*/
	input.close();
}

TileMap::TileMap()
{
	this->name="Default";
	this->nrOfTiles = 0;
	this->loadSheet("lol");

}

TileMap::~TileMap()
{
	this->freeMemory();
}

TileMap::TileMap(const TileMap & other)
{
	this->nrOfTiles = other.nrOfTiles;
	this->cap = other.cap;
	for (int i = 0;i < nrOfTiles;i++)
	{
		this->theTiles[i] = other.theTiles[i];
	}
	this->theTiles = other.theTiles;
}

void TileMap::addTile(int x, int y, int id, TileType type) //
{
	if (this->nrOfTiles == this->cap)
		extendArray();
	this->theTiles[this->nrOfTiles] = new Tile(x, y,type,id);
	this->nrOfTiles++;
}

void TileMap::removeTile(Tile * theTile)
{

	delete theTile;
	theTile = this->theTiles[this->nrOfTiles - 1];
	this->theTiles[this->nrOfTiles - 1] = nullptr;
	this->nrOfTiles--;
}

void TileMap::searchRemove(int x, int y)
{
	int pos = -1;
	for (int i = 0; i < this->nrOfTiles&&pos==-1; i++)
	{
		if (this->theTiles[i]->getXID() == x && this->theTiles[i]->getYID() == y)
		{
			pos = i;
		}
	}
	delete this->theTiles[pos];
	this->theTiles[pos] = this->theTiles[this->nrOfTiles - 1];
	this->theTiles[this->nrOfTiles - 1] = nullptr;
	this->nrOfTiles--;
}

Tile * TileMap::getTile(int x, int y) const
{
	Tile* temp = nullptr;
	int pos = -1;
	for (int i = 0;i < this->nrOfTiles&&pos==-1;i++)
	{
		if (this->theTiles[i]->getXID() == x && this->theTiles[i]->getYID() == y)
		{
			temp = theTiles[i];
			pos = i;
		}
	}
	return temp;
}

Tile * TileMap::getAt(int nr)
{
	Tile* temp = nullptr;
	temp = theTiles[nr];
	return temp;
}

void TileMap::changeSizeOfAllTiles(float x, float y)
{
	for (int i = 0; i < this->nrOfTiles; i++)
	{
		this->theTiles[i]->setPosition(this->theTiles[i]->getXID()*x, this->theTiles[i]->getYID()*y);
		this->theTiles[i]->setSize(sf::Vector2f(x, y));
		this->theTiles[i]->setOrigin(sf::Vector2f(x / 2.f, y / 2.f));
		this->theTiles[i]->updateTypeTextPos();
	}
}

int TileMap::getNrOfTiles() const
{
	return this->nrOfTiles;
}

void TileMap::saveToFile(std::string fileName) //fix this mannen
{
	std::ofstream outPut;
	int typeInt = 0;
	outPut.open("mapFiles/" + fileName + ".txt");
	outPut << this->name<<std::endl;
	outPut << this->nrOfTiles << std::endl;
	outPut << this->cap << std::endl;
	for (int i = 0; i < this->nrOfTiles; i++)
	{
		int typeNr(theTiles[i]->getTileType());
		std::string temp;
		temp += std::to_string(theTiles[i]->getXID()) + " " +
			std::to_string(theTiles[i]->getYID()) + " " +
			std::to_string(typeNr) + " " + 
			std::to_string(theTiles[i]->getImageId());

		outPut << temp << std::endl;
	}
	outPut.close();
}


bool TileMap::loadSheet(std::string loadMap) //use this, decide better name
{
	std::ifstream input;
	int xValue = -1;
	int yValue = -1;
	int typeInt = 0;
	TileType tileType = Normal;
	int textureId = 0;
	input.open("mapFiles/" + loadMap + ".txt");
	if(input.is_open()==true)
	{
		if (theTiles != nullptr)
		{
			this->freeMemory();
		}
		std::cout << "den är öppen";
		input >> this->name;
		//std::cout <<"name: "<< this->name<<std::endl;
		input >> this->nrOfTiles;
		//std::cout << "nrOf: " << this->nrOfTiles<<std::endl;
		input >> this->cap;
		//std::cout << "cap: " << this->cap<<std::endl;
		
		this->theTiles = new Tile*[cap];
		for (int i = 0; i < cap; i++)
		{
			theTiles[i] = nullptr;
		}
		for (int i = 0; i < this->nrOfTiles; i++)
		{
			input >> xValue;
			input >> yValue;
			//input >> theTexture;
			input >> typeInt;
			tileType = TileType(typeInt);
			//input >> xTexturePos;
			//input >> yTexturePos;
			input >> textureId;
			//std::cout << "Tile(" << xValue << ", " << yValue << ", " << theTexture << ", " << tileType << ");" << std::endl;

			theTiles[i] = new Tile(xValue, yValue, tileType, textureId); //sf::IntRect(xTexturePos * 32, yTexturePos * 32, 32, 32));
			//theTiles[i]->setPosition(xValue*theTiles[i]->getSize().x + theTiles[i]->getSize().x /2, yValue*theTiles[i]->getSize().y + theTiles[i]->getSize().y / 2);
		}
		input.close();
		return true;
	}
	else
	{
		std::cout << "den är stängd";
		return false;
	}



}

void TileMap::reset()//as´k if reset
{
	this->freeMemory();
	this->nrOfTiles = 0;
	this->cap = 10;
	this->theTiles = new Tile*[cap];
	for (int i = 0; i < cap; i++)
	{
		theTiles[i] = nullptr;
	}
}

void TileMap::setName(std::string name)
{
	this->name = name;
}

std::string TileMap::getName() const
{
	return this->name;
}

void TileMap::update(sf::RenderWindow & window)
{
	//std::cout << ": " << nrOfTiles << std::endl;
	for (int i = 0;i < this->nrOfTiles;i++)
	{
		if(theTiles[i]!=nullptr)
			theTiles[i]->draw(window);
	}

}
