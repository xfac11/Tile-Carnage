#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
#include <string>
#include <fstream>
#include <iostream> // temp
class TileMap
{
private:
	std::string name;

	int nrOfTiles;
	int cap;
	Tile* *theTiles; //different types of tiles later
	void extendArray();
public:
	TileMap(std::string loadMap); //construct
	TileMap();
	~TileMap();
	TileMap(const TileMap & other); // copy
	void freeMemory();
	void addTile(int x, int y, int id, TileType type = Normal);
	void removeTile(Tile *theTile);
	void searchRemove(int x, int y);
	Tile* getTile(int x, int y)const;
	Tile* getAt(int nr);
	void changeSizeOfAllTiles(float x, float y);
	int getNrOfTiles()const;
	void saveToFile(std::string fileName);
	bool loadSheet(std::string loadMap);
	void reset();
	void setName(std::string name);
	std::string getName()const;

	void update(sf::RenderWindow & window);
};
#endif TILEMAP_H
