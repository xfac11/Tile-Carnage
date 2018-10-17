#ifndef PLAYTEST_H
#define PLAYTEST_H
#include"textbox.h"
#include"TileMap.h"
#include"Player.h"
#include"Tree.h"
#include"LoadingScreen.h"
class PlayTest
{
public:
	PlayTest();
	PlayTest(sf::RenderWindow& window,sf
::View &view);
	~PlayTest();
	//sf::View& getView();
	void update(sf::RenderWindow & window, sf::Event &theEvent, sf::View & view, float deltaTime);
	void collisionCheck(sf::Vector2f windowSize);
	void enterDoor(std::string mapName,sf::Vector2f windowSize);
	void loadingScene(sf::RenderWindow & window,float deltaTime);
private:
	TileMap map;
	textbox textBox;
	Player player;

	sf::RectangleShape blackBox;

	//Scene loading
	LoadingScreen* loading;
	bool loadedMap;
	bool scene;
	//
	sf::View playTestView;
	sf::RectangleShape theMouse;
	Tree<Tile> collBlock;
	float tileSize;
	//Light
	sf::ConvexShape light;
	sf::RenderTexture tex;
	std::vector<sf::Vector2f> lights;
	//Texture
};
#endif // !PLAYTEST_H
