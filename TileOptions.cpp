#include"TileOptions.h"

TileOptions::TileOptions()
{
	this->y = 600.0f;
	this->x = 20.0f;
	this->cap = 20;
	this->from = 0;
	this->nrOfShowing = 15;
	this->end = this->nrOfShowing;
	this->nrOfTiles = 0;
	this->currentShowing = 0;
	this->showingtiles = new Tile[this->nrOfShowing];
	this->leftRight = new Tile[2];
	this->allTiles = new Tile[this->cap];
}

TileOptions::~TileOptions()
{
	delete[] this->showingtiles;
	delete[] this->leftRight;
	delete[] this->allTiles;
}

void TileOptions::addTiletexture(int textureRectPos)//color to texture 
{
	if (this->nrOfTiles == this->cap) //extendurr
	{
		this->cap += this->nrOfShowing;
		Tile* temp = new Tile[this->cap];
		for (int i = 0; i < this->nrOfTiles; i++)
		{
			temp[i] = this->allTiles[i];
		}
		delete[] this->allTiles;
		this->allTiles = temp;
	}

	this->allTiles[this->nrOfTiles] = Tile(textureRectPos);
	//this->allTiles[this->nrOfTiles].settexture(&text);
	//this->allTiles[this->nrOfTiles].settextureRect(textureRectPos);
	//F�r att visa de f�rsta 
	if (this->nrOfTiles < this->nrOfShowing)
	{
		this->showingtiles[this->nrOfTiles] = this->allTiles[this->nrOfTiles];
	}
	if (this->nrOfTiles == this->nrOfShowing)
	{
		this->currentShowing = 1;
		this->from = this->nrOfShowing;
	}
	//

	//if (this->y >= 67.0f)
	//{
	//	this->x = 20.0f;
	//	this->y = 600.0f;
	//}
	this->nrOfTiles++;
}

void TileOptions::changeShowingTiles()
{
	if (this->end == this->nrOfTiles)
	{
		this->from = 0;
		this->end = this->nrOfShowing;
		this->currentShowing = 0;
	}
	if (this->nrOfTiles - (this->nrOfShowing * this->currentShowing) > this->nrOfShowing)
	{
		this->end = (1 + this->currentShowing) * this->nrOfShowing;
	}
	else
	{
		this->end = this->nrOfTiles;
	}

	int j = 0;
	for (int i = this->from; i < this->end; i++)
	{
		this->showingtiles[j] = this->allTiles[i];
		j += 1;
	}
	this->from = this->end;
	this->currentShowing += 1;

}

sf::RectangleShape & TileOptions::getRectFromTiles(const int pos)
{
	return this->showingtiles[pos];
}

void TileOptions::drawCurrentTiles(sf::RenderWindow & window)
{
	int numOfShow = 0;
	if (this->end %this->nrOfShowing == 0)
	{
		numOfShow = this->nrOfShowing;
	}
	else
	{
		numOfShow = this->end % this->nrOfShowing;
	}
	for (int i = 0; i < numOfShow; i++)
	{
		window.draw(this->showingtiles[i]);
	}
}

void TileOptions::setPosition(float x, float y)
{
	float startX = 30.f;
	float xPos = startX;
	float startY = 42.f;
	float yPos = startY;

	//this->theTileOptions.setPosition(this->tileMenu.getPosition().x,this->tileMenu.getPosition().y);
	for (int i = 0; i < this->nrOfShowing; i++)
	{

		this->showingtiles[i].setPosition(x + xPos, y + yPos);

		//this->theTileOptions.getTileFromAll(i).setPosition(x + this->tileMenu.getPosition().x, this->tileMenu.getPosition().y);
		if (xPos >= (startX + 32.f) * 4 && yPos >= 85.f)
		{
			xPos = startX;
			yPos = startY;
		}
		else if (xPos >= (startX + 32.f) * 4)
		{
			xPos = startX;
			yPos += startY;
		}
		else
		{
			xPos += startX + 32.0f;
		}

	}
}

Tile & TileOptions::getTile(int pos)
{
	return this->showingtiles[pos];
}

Tile & TileOptions::getTileFromAll(const int pos)
{
	return this->allTiles[pos];
}

int TileOptions::getNrOfAllTiles() const
{
	return this->nrOfTiles;
}

int TileOptions::getNrOfCurrentTiles() const
{
	int numOfShow = 0;
	if (this->end % this->nrOfShowing == 0)
	{
		numOfShow = this->nrOfShowing;
	}
	else
	{
		numOfShow = this->end % this->nrOfShowing;
	}
	return numOfShow;
}
