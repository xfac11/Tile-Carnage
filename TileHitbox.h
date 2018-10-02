#ifndef TILEHITBOX_H
#define TILEHITBOX_H
#include <SFML/Graphics.hpp>
class TileHitbox:public sf::RectangleShape
{
private:
	sf::Vector2f size; //si<e of hitbox
	sf::Vector2f pos; //position of hitbox
public:
	//TileHitbox(sf::Vector2f size, );
	//~TileHitbox();
};
#endif