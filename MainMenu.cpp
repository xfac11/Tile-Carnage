#include"MainMenu.h"

MainMenu::MainMenu(std::string fileName)
{
	this->upButton = false;
	this->downButton = false;
	this->currentText = 0;
	this->state = StartTest;//=currentText
	this->font.loadFromFile(fileName);
	this->text = new sf::Text[5];
	this->nrOfTexts = 4;
	this->cap = 5;
	for (int i = 0; i < this->cap; i++)
	{
		this->text[i] = sf::Text();
		this->text[i].setFont(this->font);
	}
	this->text[0].setString("Start Test");
	this->text[1].setString("Edit world");
	this->text[2].setString("Options");
	this->text[3].setString("Exit");
}

MainMenu::MainMenu()
{
	fireBall = new Animate("fireBall", 6, 0.08f);
	//this->box.setFillColor(sf::Color(137,124,124));
	this->upButton = false;
	this->downButton = false;
	this->currentText = 0;
	this->textForBox.loadFromFile("Textures/MainMenuScreen_Shit.png");
	this->box.setTexture(this->textForBox);
	//this->box.setColor(sf::Color(100,100,100));
	this->state = StartTest;//=currentText
	this->font.loadFromFile("Font/PressStart2P.ttf");
	this->text = new sf::Text[5];
	this->nrOfTexts = 4;
	this->cap = 5;
	for (int i = 0; i < this->cap; i++)
	{
		this->text[i] = sf::Text();
		this->text[i].setFont(this->font);
	}
	this->text[0].setString("Start Test");
	this->text[1].setString("Edit World");
	this->text[2].setString("Options");
	this->text[3].setString("Exit");
}

MainMenu::~MainMenu()
{
	delete this->fireBall;
	delete[] this->text;
}

void MainMenu::addText(std::string text)
{
	if (this->nrOfTexts == this->cap)
	{
		this->cap += 5;
		sf::Text* tempText = new sf::Text[this->cap];
		for (int i = 0; i < this->nrOfTexts; i++)
		{
			tempText[i] = this->text[i];
		}
		delete[] this->text;
		this->text = tempText;
	}
	this->text[this->nrOfTexts] = sf::Text(text,this->font);
	this->nrOfTexts++;
}

void MainMenu::changeText(Direction dir)
{
	this->text[this->currentText].setFillColor(sf::Color::White);
	if (dir == DOWN)
	{
		if (currentText == this->nrOfTexts)
		{
			this->currentText = 0;
			this->state = Selected(0);
		}
		else
		{
			this->currentText++;
			this->state = Selected(this->currentText);
		}
	}
	else if (dir == UP)
	{
		if (currentText == 0)
		{
			
			this->currentText = this->nrOfTexts;
			this->state = Selected(this->currentText);
		}
		else
		{
			this->currentText--;
			this->state = Selected(this->currentText);
		}
	}
	this->text[this->currentText].setFillColor(sf::Color::Red);
}

void MainMenu::changeText()
{
	this->text[this->currentText].setFillColor(sf::Color::White);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&this->downButton==false)
	{
		this->downButton = true;
		if (currentText == this->nrOfTexts-1)
		{
			
			this->currentText = 0;
			this->state = Selected(this->currentText);
		}
		else
		{
			this->currentText++;
			this->state = Selected(this->currentText);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{

	}
	else
	{
		this->downButton = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&this->upButton==false)
	{
		this->upButton = true;
		if (currentText == 0)
		{
			this->currentText = this->nrOfTexts-1;
			this->state = Selected(this->currentText);
		}
		else
		{
			this->currentText--;
			this->state = Selected(this->currentText);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{

	}
	else
	{
		this->upButton = false;
	}
	this->text[this->currentText].setFillColor(sf::Color::Red);
	//std::cout << "menu:" << this->currentText << std::endl;
}

void MainMenu::movementForFire(sf::RenderWindow & window, float deltaTime)
{
	int dir = rand() % 1920 + -1;

	this->fireBall->move(0, 200 * deltaTime);
	if (this->fireBall->getPosition().x > window.getSize().x - 000 || this->fireBall->getPosition().x<000 ||
		this->fireBall->getPosition().y >window.getSize().y - 000 || this->fireBall->getPosition().y < 000)
	{
		this->fireBall->setPosition(dir, 010);
	}
}

void MainMenu::drawText(sf::RenderWindow & window,float deltaTime)
{
	//this->fireBall->movement(window);
	window.draw(box);
	this->fireBall->update(window, deltaTime);
	for (int i = 0; i < this->nrOfTexts; i++)
	{
		window.draw(this->text[i]);
	}
	this->movementForFire(window,deltaTime);
}

void MainMenu::setPosition(sf::Vector2f pos,float space)
{
	float y = pos.y;
	int maxChars = 0;
	for (int i = 0; i < this->nrOfTexts; i++)
	{
		sf::FloatRect textRect = text[i].getLocalBounds();
		text[i].setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		if (this->text[maxChars].getString().getSize() < this->text[i].getString().getSize())
		{
			maxChars = i;
		}
		this->text[i].setPosition(pos.x, y);
		this->text[i].setCharacterSize(40);
		y += this->text[i].getCharacterSize() + space;
	}
	//this->box.setSize(sf::Vector2f(31*this->text[maxChars].getString().getSize(), 10.0f+this->nrOfTexts*this->text[0].getCharacterSize() + (this->nrOfTexts - 1)*space));
	//this->box.setSize(sf::Vector2f(1920.0f, 1080.0f));
	this->box.setOrigin(sf::Vector2f(1920.0f/ 2, 1080.0f / 2));
	this->box.setPosition(pos.x , pos.y );

}

int MainMenu::getCurrentText() const
{
	return this->currentText;
}

Selected MainMenu::getCurrentSelected() const
{
	return this->state;
}
