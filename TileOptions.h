#ifndef TILEOPTIONS_H
#define TILEOPTIONS_H
#include<SFML/Graphics.hpp>
#include"Tile.h"
class TileOptions
{
public:
	TileOptions();
	~TileOptions();
	//void addTileTexture(sf::Texture *&texture);
	//Change to texture from color
	void addTileTexture(int textureRectPos);
	void changeShowingTiles();
	sf::RectangleShape & getRectFromTiles(const int pos);
	void drawCurrentTiles(sf::RenderWindow & window);
	void setPosition(float x, float y);
	Tile getTile(int pos);
	int getNrOfCurrentTiles()const;
private:
	int nrOfTiles;
	int cap;
	int from;
	int end;
	int currentShowing;
	float y;
	float x;
	Tile* showingtiles;
	Tile* allTiles;
	Tile* leftRight;
};
#endif // !TILEOPTIONS_H
