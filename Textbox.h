#ifndef texTBOX_H
#define texTBOX_H
#include <SFML\Graphics.hpp>
#include <iostream>
class textbox : public sf::RectangleShape
{
private:
	std::string theInfo;
	sf::Font theFont;
	sf::Text thetext;
	sf::Texture boxtexture;
	bool typeMode;
	bool isPressed;
public:
	textbox();
	~textbox();
	std::string getString()const;
	bool getTypeMode()const;
	void settextSize(const int size);
	void draw(sf::RenderWindow & window);
	void update(sf::RenderWindow & window, sf::Event & theEvent, sf::View & view, sf::RectangleShape mouse);
};
#endif
