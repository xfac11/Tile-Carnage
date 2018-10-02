#ifndef TILE_H
#define TILE_H
#include<iostream>
#include "TileType.h"
#include "Destination.h"
#include <SFML/Graphics.hpp>
class Tile : public sf::RectangleShape
{
private:
	sf::Texture theTexture;
	std::string textureName;
	std::string stringForTextType;
	sf::Text typeText;
	TileType theType;
	int xID, yID;
	Destination theDest;
	sf::Font font;	
	sf::IntRect uvRect;
	int imageId;
	//TileHitbox thehitbox
	//New with sprite 
	//sf::Vector2i textureRectPos;
public:
	Tile(int xID, int yID, TileType theType, int imageId);//Tilemap
	//This constructor for tileOptions
	Tile(int imageId);
	void operator=(const Tile & obj);
	//Tile(); //konstuktor för spritesheet
	//Tile(int xID, int yID, sf::Texture & theTexture, TileType theType, Destination theDest);
	Tile();
	virtual~Tile();
	int getXID()const;
	int getYID()const;
	void setTileType(TileType theType);
	TileType getTileType()const;
	std::string getTextureName()const;
	void draw(sf::RenderWindow & window);
	int getImageId()const;
	void updateTypeTextPos();
	// draw itself
	//New with sprite
	//sf::Vector2i getTextureRectPos()const;
};
#endif // !TILE_H
