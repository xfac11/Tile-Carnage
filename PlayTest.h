#ifndef PLAYTEST_H
#define PLAYTEST_H
#include"Textbox.h"
#include"TileMap.h"
#include"Player.h"
#include"Tree.h"
class PlayTest
{
public:
	PlayTest();
	PlayTest(sf::RenderWindow& window,sf
::View &view);
	~PlayTest();
	//sf::View& getView();
	void update(sf::RenderWindow & window, sf::Event &theEvent, sf::View & view, float deltaTime);
	void collisionCheck();
private:
	TileMap map;
	Textbox textBox;
	Player player;
	sf::View playTestView;
	sf::RectangleShape theMouse;
	Tree<Tile> collBlock;
};
#endif // !PLAYTEST_H
