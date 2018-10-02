#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML\Graphics.hpp>
#include <iostream>
class Textbox : public sf::RectangleShape
{
private:
	std::string theInfo;
	sf::Font theFont;
	sf::Text theText;

	bool typeMode;
	bool isPressed;
public:
	Textbox();
	~Textbox();
	std::string getString()const;
	bool getTypeMode()const;
	void setTextSize(const int size);
	void draw(sf::RenderWindow & window);
	void update(sf::RenderWindow & window, sf::Event & theEvent, sf::View & view, sf::RectangleShape mouse);
};
#endif
