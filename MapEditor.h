#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#include "TileMap.h"
#include"TileOptions.h"
#include"textbox.h"
#define BLOCKWIDTH 32.f //gör klass som håller alla define
#define BLOCKHEIGHT 32.f
class MapEditor
{
private:
	TileMap currentMap;
	bool isPressed;
	bool isMovable;
	//InputHandler theInputs;
	bool isRightClick;
	bool tileChange;

	sf::RectangleShape location;
	sf::Texture textureLocation;

	TileType currentTileType;
	int currentTileTypeNr;
	sf::Text currentTileTypetext;
	std::string currentTileTypeString;
	sf::Font tileTypeFont;

	sf::Texture textureTileMenu;
	sf::RectangleShape tileMenu;
	sf::Texture arrow[4];
	sf::RectangleShape theArrows[4];

	TileOptions theTileOptions;
	sf::Texture textureForAll;
	sf::RectangleShape theMouse;
	Tile* tempBlock;
	int prevId;

	float speedForMovingCamera;

	float windowX(float size);
	float windowY(float size);

	sf::RectangleShape saveRect;
	sf::Texture textureSaveRect;
	sf::RectangleShape loadRect;
	sf::Texture textureLoadRect;
	sf::RectangleShape hudForLoadNSaveNtext;
	sf::Texture textureHudLoadSave;
	textbox textBox;

	bool temp;
	sf::Vector2i getMouseID();
	bool mouseOnObject(sf::RectangleShape object);
	void updateHUD(sf::View &view, float deltaTime);

public:
	MapEditor();
	~MapEditor();
	bool getTypeMode()const;
	void draw(sf::RenderWindow & window, float deltaTime, sf::View & view,sf::Event &theEvent);
	
	
};
#endif